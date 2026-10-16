#pragma once
#include "utilities.h"
#include "interval.h"
#include <dispatch/dispatch.h>
#include <vector>
#include <material.h>

class camera {
public:
    const int image_width = 1024;
    const int image_height = 1024;
    int samples_per_pixel = 10;
    int max_depth = 8;

    void render(const hittable& world) {
        initialize();

        std::vector<color> framebuffer(image_width * image_height);
        std::atomic<int> rows_done{0};

        struct job {
            camera* self;
            const hittable* world;
            color* fb;
            std::atomic<int>* done;
        };
        job jb{this, &world, framebuffer.data(), &rows_done};

        dispatch_apply_f(image_height, dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), &jb,
            [](void* ctx, size_t row) {
                auto* j = static_cast<job*>(ctx);
                j->self->render_row((int)row, *j->world, j->fb);

                int d = ++(*j->done);   // atomic increment, returns the new count
                if (d % 8 == 0 || d == j->self->image_height) {
                    fprintf(stderr, "\rRows done: %d / %d", d, j->self->image_height);
                }
            });

        fprintf(stderr, "\nDone.\n");

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (const auto& c : framebuffer) write_color(std::cout, c);
    }
private:
    vec3 center;         // Camera center
    float pixel_samples_scale;
    vec3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = 2.0;
        center = vec3(2,2,4);

        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x) * pixel_delta_u)
                          + ((j + offset.y) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_float() - 0.5, random_float() - 0.5, 0);
    }

    color ray_color(const ray& r, int depth, const hittable& world, bool count_emission = true) {
        if (depth <= 0) return color(0,0,0);

        hit_record rec;
        if (!world.hit(r, interval(0.001, infinity), rec))   // 0.001 instead of 0, to avoid self-hits
            return color(0,0,0);

        color result = count_emission ? rec.mat->emitted() : color(0,0,0);

        if (rec.mat->is_diffuse()) {
            const color Le(8,8,8);
            const float light_area = 1.0f;

            vec3 light_pt = vec3(random_float(1.5f, 2.5f), 3.99f, random_float(1.5f,2.5f));
            vec3 shadow_dir = light_pt - rec.p;
            ray shadowRay = ray(rec.p, shadow_dir);

            float len = shadow_dir.length();
            float len2 = shadow_dir.length_squared();
            vec3 unit_light_pt = light_pt/len;
            float cosS = dot(unit_light_pt, rec.normal);
            float cosL = unit_light_pt.y;
            float brdf = 1/pi;
            if (cosS > 0 && cosL > 0) {
                hit_record shr;
                if (!world.hit(shadowRay, interval(0.001f, 0.999f), shr)) {
                    result += (brdf * cosS * cosL * light_area / len2) * (rec.mat->diffuse_albedo() * Le);
                }
            }
        }

        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            bool next_count = !rec.mat->is_diffuse();
            result += attenuation * ray_color(scattered, depth - 1, world, next_count);
        }
        return result;
    }

    void render_row(int j, const hittable& world, color* fb) {
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            fb[j * image_width + i] = pixel_samples_scale * pixel_color;
        }
    }
};
#pragma once
#include "utilities.h"
#include "hittable.h"

class sphere : public hittable {
public:
    sphere() {};
    sphere(const vec3& c, float r, shared_ptr<material> m) : center(c), radius(std::fmax(0, r)), mat(m) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 C = center - r.origin();
        float a = dot(r.direction(), r.direction());   // |dir|^2, equals 1 if dir is normalized

        float A  = dot(C, r.direction()) / a;          // t at closest approach to the center
        float B2 = dot(C, C) - A * A * a;              // squared distance from center to the ray
        float R2 = radius * radius;
        if (B2 > R2) return false;

        float t_off = std::sqrt((R2 - B2) / a);        // half the chord, measured in t
        float t1 = A - t_off;                          // near intersection
        float t2 = A + t_off;                          // far intersection

        float t = t1;
        if (t <= ray_t.min || ray_t.max <= t) {
            t = t2;
            if (t <= ray_t.min || ray_t.max <= t) {
                return false;
            }
        }

        rec.t = t;
        rec.p = r.at(t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat.get();
        return true;
    }

private:
    vec3 center;
    float radius;
    shared_ptr<material> mat;
};
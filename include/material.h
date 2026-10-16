#ifndef TNCG15_RAYTRACER_MATERIAL_H
#define TNCG15_RAYTRACER_MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
    virtual color emitted() const { return {0,0,0}; }

    // true => ray_color adds a shadow-ray (direct light) term for this surface
    virtual bool  is_diffuse() const { return false; }
    virtual color diffuse_albedo() const { return {0,0,0}; }
};

class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
    bool is_diffuse() const override { return true; }
    color diffuse_albedo() const override { return albedo; }

private:
    color albedo;
};

class diffuse_light : public material {
public:
    diffuse_light(const color& e) : emit(e) {}
    color emitted() const override { return emit; }   // scatter() stays false
private:
    color emit;
};

class metal : public material {
public:
    metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif //TNCG15_RAYTRACER_MATERIAL_H
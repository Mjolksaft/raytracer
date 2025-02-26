#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitrecord.h"

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(
        const ray &r_in, const hit_rec &rec, vec3 &attenuation, ray &scattered) const
    {
        return false;
    }
};

class lambertian : public material
{
public:
    lambertian(const vec3 &albedo) : albedo(albedo) {}

    bool scatter(const ray &r_in, const hit_rec &hr, vec3 &attenuation, ray &scattered)
        const override
    {
        auto scatter_direction = hr.n + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = hr.n;

        scattered = ray(hr.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    vec3 albedo;
};

class metal : public material
{
public:
    metal(const vec3 &albedo) : albedo(albedo) {}

    bool scatter(const ray &r_in, const hit_rec &hr, vec3 &attenuation, ray &scattered)
        const override
    {
        vec3 reflected = reflect(r_in.direction(), hr.n);
        scattered = ray(hr.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    vec3 albedo;
};

#endif
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

        // get the point
        point3 p = hr.p;
        // calculate a new random vector
        vec3 rand_vec = hr.n + random_unit_vector();

        if (rand_vec.near_zero())
            rand_vec = hr.n;

        // send out a new ray
        scattered = ray(hr.p + hr.n * 1e-3, rand_vec); // move the point outside of the sphere
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
        scattered = ray(hr.p + hr.n * 1e-3, reflected);
        attenuation = albedo;
        return true;
    }

private:
    vec3 albedo;
};

#endif
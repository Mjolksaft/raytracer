#ifndef SPHERE_H
#define SPHERE_H

#include "utility.h"

class sphere
{
public:
    sphere(double radius, vec3 center, shared_ptr<material> mat) : rad(radius), cen(center), mat(mat) {}

    double radius() const { return rad; }
    vec3 center() const { return cen; }

    bool intersection(ray &r, hit_rec &hr) const
    {
        auto L = r.origin() - center();
        auto a = dot(r.direction(), r.direction());
        auto b = 2. * dot(r.direction(), L);
        auto c = dot(L, L) - radius() * radius();

        auto disc = b * b - 4 * a * c;
        if (disc < 0)
        {
            return false;
        }

        double t0 = (-b - sqrt(disc)) / (2. * a);
        if (t0 > 0.001 && t0 < hr.t)
        { // check which point is closer
            hr.t = t0;
            hr.p = r.at(t0);
            hr.n = unit_vector(hr.p - center());
            hr.mat = mat;
            return true;
        };

        double t1 = (-b + sqrt(disc)) / (2. * a);
        if (t1 > 0.001 && t1 < hr.t)
        {
            hr.t = t1;
            hr.p = r.at(t1);
            hr.n = unit_vector(hr.p - center());
            hr.mat = mat;
            return true;
        };

        return false;
    }

private:
    double rad;
    vec3 cen;
    shared_ptr<material> mat;
};

#endif
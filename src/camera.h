#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>

#include "sphere.h"
#include "utility.h"

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}


class camera
{
public:
    double aspect_ratio = 1.;
    int image_width = 400;
    double focal_length = 1.;
    double viewport_height = 2.;
    vec3 position = vec3(0, 0, 0);
    int samples = 10;
    int bounces = 10;

    void render(const std::vector<sphere> &spheres)
    {
        initialize();

        std::cout << "P3" << '\n'
                  << image_width << ' ' << image_height << '\n'
                  << "255" << '\n'; // format

        for (int y = 0; y < image_height; y++)
        {
            std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
            for (int x = 0; x < image_width; x++)
            {
                vec3 color(0, 0, 0);

                // for anti aliasing
                // generate a ray directed at a random point around [x,y]
                for (int i = 0; i < samples; i++)
                {
                    ray r = get_ray(x, y); // Ensure direction is normalized
                    color += ray_color(r, spheres, bounces);
                }
                color /= samples;

                // auto pixel0 = first_pixel + (pixeldelta_u * x) + ( pixeldelta_v * y);
                // ray r(pixel0, pixel0 - position);
                // color += ray_color(r, spheres, bounces);
                auto r = linear_to_gamma(color.x());
                auto g = linear_to_gamma(color.y());
                auto b = linear_to_gamma(color.z());
                
                int ri = int(clamp(r, 0, 1) * 255.999);
                int gi = int(clamp(g, 0, 1) * 255.999);
                int bi = int(clamp(b, 0, 1) * 255.999);
                std::cout << ri << ' ' << gi << ' ' << bi << '\n';
            }
        }
    }

private:
    int image_height;
    double viewport_width;
    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixeldelta_u;
    vec3 pixeldelta_v;
    vec3 top_left;
    vec3 first_pixel;

    void initialize()
    {
        image_height = int(image_width / aspect_ratio);

        viewport_width = viewport_height * (double(image_width) / image_height);

        viewport_u = vec3(viewport_width, 0, 0);
        viewport_v = vec3(0, -viewport_height, 0);

        pixeldelta_u = viewport_u / image_width;
        pixeldelta_v = viewport_v / image_height;

        top_left = position - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        first_pixel = top_left + (pixeldelta_u + pixeldelta_v) * 0.5;
    }

    ray get_ray(int x, int y)
    {

        point3 random_offset = point3(rand_double(-0.5, 0.5), rand_double(-0.5, 0.5), 0);
        point3 rand_point = first_pixel + (pixeldelta_u * (x + random_offset.x())) + (pixeldelta_v * (y + random_offset.y()));

        return ray(position, rand_point - position);
    }

    vec3 ray_color(ray &r, const std::vector<sphere> &spheres, int bounces)
    {
        hit_rec hr;
        bool hit_anything = false;
        for (const auto &s : spheres)
        {
            if (s.intersection(r, hr))
                hit_anything = true;
        }

        // for drawing normal map
        if (hit_anything)
        {
            // vec3 scaled = (hr.n + 1.) * 0.5;
            // return scaled;
            vec3 direction = hr.n + random_unit_vector();
            ray new_r = ray(hr.p, direction);
            return  ray_color(new_r, spheres, bounces) * 0.5;
        }

        vec3 unit = unit_vector(r.direction());
        unit = (unit + 1.) * 0.5;
        return vec3(1, 1, 1) * (1. - unit.y()) + vec3(0.5, 0.7, 1.) * unit.y();
    };
};

#endif
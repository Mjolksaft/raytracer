#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "hitrecord.h"


class camera
{
public:

    double aspect_ratio = 1.;    
    int image_width = 400;
    double focal_length = 1.;
    double viewport_height = 2.;
    vec3 position = vec3(0, 0, 0);
    int samples = 10;

    void render(const sphere& s)
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
                // generate a ray directed at a random point around [x,y]
                for (int i = 0; i < samples; i++)
                {
                    ray r = get_ray(x,y); // Ensure direction is normalized
                    color += ray_color(r, s);
                }

                color /= samples;

                int ri = int(clamp(color.x(), 0, 1) * 255.999);
                int gi = int(clamp(color.y(), 0, 1)  * 255.999);
                int bi = int(clamp(color.z(), 0, 1)  * 255.999);
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

    // Place viewport at +Z instead of -Z
    vec3 top_left;
    vec3 first_pixel;

    void initialize()
    {
        image_height = int(image_width / aspect_ratio); // rounds to int

        viewport_width = viewport_height * (double(image_width) / image_height);

        viewport_u = vec3(viewport_width, 0, 0);
        viewport_v = vec3(0, -viewport_height, 0);

        pixeldelta_u = viewport_u / image_width;
        pixeldelta_v = viewport_v / image_height;

        top_left = position - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        first_pixel = top_left + (pixeldelta_u + pixeldelta_v) * 0.5;

    }

    ray get_ray(int x, int y) {
        
        point3 random_offset = point3(rand_double(-0.5,0.5), rand_double(-0.5,0.5), 0);
        point3 rand_point = first_pixel + (pixeldelta_u * (x + random_offset.x())) + ( pixeldelta_v * (y + random_offset.y()));

        return ray(position, rand_point - position);
    }

    vec3 ray_color(ray &r, const sphere& s)
    {
        hit_rec hr;
        bool hit = s.intersection(r, hr);

        if (hit)
        {
            vec3 scaled = (hr.n + 1.) * 0.5;
            return scaled;
        }

        vec3 unit = unit_vector(r.direction());
        unit = (unit + 1.) * 0.5;
        return vec3(1, 1, 1) * (1. - unit.y()) + vec3(0.5, 0.7, 1.) * unit.y();
    };
};



#endif
#include <random>
#include <ranges>
#include <iostream> 
#include <vector> 


#include "src/rt.h"
#include "src/sphere.h"
#include "src/camera.h"
#include "src/hitrecord.h"
#include "src/material.h"

int main() {  

    auto material_ground = make_shared<lambertian>(vec3(0, 1, 0.0));
    auto metal_sphere = make_shared<metal>(vec3(0.8, 0.8, 0.8));
    auto sphere_material = make_shared<lambertian>(vec3(1, 0, 0.0));

    std::vector<sphere> spheres;
    spheres.emplace_back(sphere(1.5, vec3(-2,0.4,-3), metal_sphere));
    spheres.emplace_back(sphere(1.5, vec3(1,0.4,-3), sphere_material));
    spheres.emplace_back(sphere(100, vec3(0,-100,-16), material_ground));

    camera c;
    c.aspect_ratio = 16./9.;
    c.render(spheres);

}

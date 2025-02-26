#include <random>
#include <ranges>
#include <iostream> 
#include <vector> 

#include "src/vec3.h"
#include "src/ray.h"
#include "src/sphere.h"
#include "src/camera.h"


int main() {  
    std::vector<sphere> spheres;
    spheres.emplace_back(sphere(2, vec3(0.5,0,-3)));
    spheres.emplace_back(sphere(1, vec3(-0.5,0,-2)));

    camera c;
    c.aspect_ratio = 16./9.;  
    c.render(spheres);

}

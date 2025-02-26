#include <random>
#include <ranges>
#include <iostream> 
#include <vector> 


#include "src/rt.h"
#include "src/sphere.h"
#include "src/camera.h"
#include "src/hitrecord.h"

int main() {  

    std::vector<sphere> spheres;
    spheres.emplace_back(sphere(1.5, vec3(0,0.4,-3)));
    spheres.emplace_back(sphere(100, vec3(0,-100,-16)));

    camera c;
    c.aspect_ratio = 16./9.;  
    c.render(spheres);

}

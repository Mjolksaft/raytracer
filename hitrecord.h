#ifndef HITRECORD_H
#define HITRECORD_H

#include "vec3.h" 

struct hit_rec {
    point3 p;  // Point of intersection (using vec3 type)
    vec3 n;    // Normal vector (using vec3 type)
    double t;  // Intersection time (distance along the ray)
};

#endif
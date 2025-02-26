#ifndef HITRECORD_H
#define HITRECORD_H

#include "vec3.h" 

struct hit_rec {
    point3 p; 
    vec3 n;   
    double t = INFINITY; 
};

#endif
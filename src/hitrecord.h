#ifndef HITRECORD_H
#define HITRECORD_H

class material;

struct hit_rec {
    point3 p; 
    vec3 n;   
    double t = INFINITY; 
    shared_ptr<material> mat;
};

#endif 
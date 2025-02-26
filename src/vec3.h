#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include "utility.h"

class vec3 {
    public: 
        double e[3];
        vec3() : e{0,0,0} {}
        vec3(double x, double y, double z) : e{x,y,z} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        double length() const {
            return std::sqrt(length_squared());
        }
    
        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        vec3 operator+=(const vec3& u) {
            e[0] += u.e[0];
            e[1] += u.e[1];
            e[2] += u.e[2];
            return *this;
        }

        vec3 operator-=(const vec3& u) {
            e[0] -= u.e[0];
            e[1] -= u.e[1];
            e[2] -= u.e[2];
            return *this;
        }
        

        vec3 operator/=(double t) {
            e[0] /=  t;
            e[1] /=  t;
            e[2] /=  t;
            return *this;
        }

        vec3 operator*=(double t) {
            e[0] *=  t;
            e[1] *=  t;
            e[2] *=  t;
            return *this;
        }

        static vec3 random(double min, double max) {
            return vec3(rand_double(min, max), rand_double(min, max), rand_double(min, max));
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    out << v.x() << ' ' << v.y() << ' ' << v.z();
    return out;
}

inline vec3 operator+(const vec3& v, const vec3& u) {
    return vec3(v.x() + u.x(), v.y() + u.y(), v.z() + u.z());
}

inline vec3 operator+(const vec3& v, double t) {
    return vec3(v.x() + t, v.y() + t, v.z() + t);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
    return vec3(v.x() - u.x(), v.y() - u.y(), v.z() - u.z());
}

inline vec3 operator*(const vec3& v, const vec3& u) {
    return vec3(v.x() * u.x(), v.y() * u.y(), v.z() * u.z());
}

inline vec3 operator*(const vec3& v, double t) {
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator/(const vec3& v, double t) {
    return v * (1/t);
}

inline vec3 unit_vector(const vec3& v) {
    return v/v.length();
}

inline double dot(const vec3& v, const vec3& u)  {
    return v.x() * u.x() + v.y() * u.y() + v.z() * u.z(); 
}

inline vec3 random_unit(double min, double max) {
    vec3 rand_vec3 = vec3().random(-1,1);
    return unit_vector(rand_vec3);
}

inline vec3 random_valid(const vec3& v, const vec3& dir) {
    double same = dot(v, dir);
    if(same < 0) {
        return v * -1.;
    } else {
        return v;
    }
}

#endif
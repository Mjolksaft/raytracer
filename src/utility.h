#ifndef UTILITY_H
#define UTILITY_H

#include <random>
#include <ranges>

double rand_double(double min = -1., double max = 1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

double clamp(double t, double min, double max) {
    if(t < min) return min; 
    if(t > max) return max; 
    return t;
};

#endif 
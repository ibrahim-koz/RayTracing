//
// Created by ibrah on 04/07/2021.
//

#ifndef RAYTRACING_UTILS_H
#define RAYTRACING_UTILS_H

#include <random>

inline double random_double() {
    static std::random_device rd;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator{rd()};
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}


inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif //RAYTRACING_UTILS_H

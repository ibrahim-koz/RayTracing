//
// Created by ibrah on 29/06/2021.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "../Vector/Vector.h"
#include "../ImageLibrary/Image.h"

class Ray {
    point3 org;
    vec3 dir;
public:
    Ray() {}

    Ray(const point3 &origin, const vec3 &direction) : org{origin}, dir{direction} {}

    point3 origin() const {
        return org;
    }

    vec3 direction() const {
        return dir;
    }

    point3 at(double t) const {
        return org + t * dir;
    }
};


#endif //RAYTRACING_RAY_H
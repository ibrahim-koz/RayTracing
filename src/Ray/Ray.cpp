//
// Created by ibrah on 29/06/2021.
//

#include "Ray.h"

namespace helper_functions {
    double hit_sphere_point(const point3 &center, double radius, const Ray &r) {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-b - sqrt(discriminant)) / (2.0 * a);
        }
    };

    bool hit_sphere(const point3 &center, double radius, const Ray &r) {
        auto hitPoint = hit_sphere_point(center, radius, r);
        if (hitPoint == -1.0){
            return false;
        }
        return true;
    }
}


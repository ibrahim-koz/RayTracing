//
// Created by ibrah on 02/07/2021.
//

#include "ViewPort.h"

namespace helper_functions {
    double hit_sphere_point(const point3 &center, double radius, const Ray &r) {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-half_b - sqrt(discriminant)) / a;
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
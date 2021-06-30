//
// Created by ibrah on 29/06/2021.
//

#include "Ray.h"
namespace helper_function {
    bool hit_sphere(const point3 &center, double radius, const Ray &r) {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        return (discriminant > 0);
    }
}
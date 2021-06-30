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

namespace helper_functions {
    bool hit_sphere(const point3 &center, double radius, const Ray &r);

    double hit_sphere_point(const point3 &center, double radius, const Ray &r);
}

struct MyWrappeeMethod {
    const double aspect_ratio;
    const int img_width;
    const int img_height;

    MyWrappeeMethod(double aspect_ratio, int img_width) : aspect_ratio{aspect_ratio}, img_width{img_width},
                                                          img_height{static_cast<int>(img_width * aspect_ratio)} {

    }

    // this value is chosen arbitrarily
    // we're gonna set our viewport_width such that the pair of (viewport_height, viewport_width) comply with the
    // ratio of the picture to be drawn.
    const int viewport_height = 2;
    const int viewport_width = viewport_height * aspect_ratio;
    const double focal_length = 1.0;

    // the following two are created to make it easier to compute.
    vec3 viewport_height_vector = vec3(0, viewport_height, 0);
    vec3 viewport_width_vector = vec3(viewport_width, 0, 0);
    vec3 focal_point = vec3(0, 0, -focal_length);
    vec3 origin = vec3(0, 0, 0);
    // we'll draw our picture through the viewport, so we will project our rays to our viewport first.
    vec3 left_lower_corner = origin + (-(viewport_height_vector / 2) - (viewport_width_vector / 2) + focal_point);

    virtual color ray_color(const Ray &r) const {
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color{1.0, 1.0, 1.0} + t * color{0.5, 0.7, 1.0};
    }

    void operator()(int i, int j, ofstream &target) const {
        auto v = double(j) / (img_height - 1);
        auto u = double(i) / (img_width - 1);

        auto ray = Ray{origin,
                       left_lower_corner + u * viewport_width_vector + v * viewport_height_vector - origin};
        color pixel_color = ray_color(ray);
        write_color(target, pixel_color);
    }
};

struct HitSphereWrappee : public MyWrappeeMethod {
    HitSphereWrappee(double aspectRatio, int imgWidth) : MyWrappeeMethod(aspectRatio, imgWidth) {}

    virtual color ray_color(const Ray &r) const override {
        if (helper_functions::hit_sphere(point3{0, 0, -1}, 0.5, r)) {
            return color{1, 0, 0};
        }
        auto unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};


struct ShadedHitSphereWrappee : public MyWrappeeMethod {
    ShadedHitSphereWrappee(double aspectRatio, int imgWidth) : MyWrappeeMethod(aspectRatio,
                                                                               imgWidth) {}

    virtual color ray_color(const Ray &r) const override{
        auto t = helper_functions::hit_sphere_point(point3(0, 0, -1), 0.5, r);
        if (t > 0.0) {
            vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
            return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
        }
        vec3 unit_direction = unit_vector(r.direction());
        t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};

#endif //RAYTRACING_RAY_H
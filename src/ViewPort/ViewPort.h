//
// Created by ibrah on 02/07/2021.
//

#ifndef RAYTRACING_VIEWPORT_H
#define RAYTRACING_VIEWPORT_H

#include "../Ray/Ray.h"
#include "../Hittable/Hittable.h"
#include "bits/stdc++.h"

using namespace std;

namespace helper_functions {
    bool hit_sphere(const point3 &center, double radius, const Ray &r);

    double hit_sphere_point(const point3 &center, double radius, const Ray &r);
}

class ViewPort {
public:
    // this value is chosen arbitrarily
    // we're gonna set our viewport_width such that the pair of (viewport_height, viewport_width) comply with the
    // ratio of the picture to be drawn.
    double viewport_height;
    double viewport_width;
    double focal_length;
    // the following two are created to make it easier to compute.
    vec3 viewport_height_vector;
    vec3 viewport_width_vector;
    vec3 focal_point;
    vec3 origin;
    // we'll draw our picture through the viewport, so we will project our rays to our viewport first.
    vec3 left_lower_corner;

    ViewPort(double viewport_width, double viewport_height, vec3 origin, double focal_length) {
        this->viewport_width = viewport_width;
        this->viewport_height = viewport_height;
        this->focal_length = focal_length;
        this->viewport_height_vector = vec3(0, viewport_height, 0);
        this->viewport_width_vector = vec3(viewport_width, 0, 0);
        this->focal_point = vec3(0, 0, -focal_length);
        this->origin = origin;
        this->left_lower_corner = origin + (-(viewport_height_vector / 2) - (viewport_width_vector / 2) + focal_point);
    }
};

struct MyWrappeeMethod {
    int img_width;
    int img_height;
    ViewPort *viewPort;
    vector<Hittable *> hittables;
    unordered_map<int, HittableColorAssigner *> hittableColorAssigners;

    // actually we could assign each new hittable with a mechanism and store them in a map.
    MyWrappeeMethod(int img_width, int img_height, ViewPort *viewPort) {
        this->img_width = img_width;
        this->img_height = img_height;
        this->viewPort = viewPort;
    }

    void addHittableAndHittableColorAssigner(Hittable *hittable,
                                             HittableColorAssigner *hittableColorAssigner) {
        hittables.push_back(hittable);
        hittableColorAssigners.insert({hittable->id, hittableColorAssigner});
    }

    // TODO: ray_color and hit check will be separated.
    void operator()(int i, int j, ofstream &target) const {
        auto v = double(j) / (img_height - 1);
        auto u = double(i) / (img_width - 1);

        auto dir = viewPort->left_lower_corner + u * viewPort->viewport_width_vector +
                   v * viewPort->viewport_height_vector - viewPort->origin;
        auto ray = Ray{viewPort->origin,
                       dir};

        auto hitRecordOfTheClosestHittable = hit(ray, -100000);
        color pixel_color;
        if (hitRecordOfTheClosestHittable != nullptr) {
            auto hittableColorAssigner = hittableColorAssigners.find(hitRecordOfTheClosestHittable->id);
            //pixel_color = hittableColorAssigner->second->Color(*hitRecordOfTheClosestHittable);
            pixel_color = color{1, 0, 0};
        } else {
            //pixel_color = notHitColorAssign();
            pixel_color = color{0, 0, 1};
        }
        write_color(target, pixel_color);
    }

    HitRecord *hit(const Ray &ray, double t_min) const {
        auto t_max = DBL_MAX;
        HitRecord *hitRecordOfTheClosestHittable = nullptr;
        for (const auto &hittable : hittables) {
            auto hitRecord = hittable->hit(ray);
            //&& t_min < hitRecord->t && hitRecord->t < t_max
            if (hitRecord != nullptr) {
                t_max = hitRecord->t;
                hitRecordOfTheClosestHittable = hitRecord;
            }
        }
        return hitRecordOfTheClosestHittable;
    }

    color notHitColorAssign() const {
        return color{0, 0, 1.0};
    }

    // we'll create hittable_color;
};

#endif //RAYTRACING_VIEWPORT_H

//
// Created by ibrah on 02/07/2021.
//

#ifndef RAYTRACING_VIEWPORT_H
#define RAYTRACING_VIEWPORT_H

#include <utility>

#include "../Ray/Ray.h"
#include "../Hittable/Hittable.h"
#include "bits/stdc++.h"
#include "../Utils/Utils.h"

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

    ViewPort(double viewport_width, double viewport_height, const vec3 &origin, double focal_length) {
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
    shared_ptr<ViewPort> viewPort;
    vector<shared_ptr<Hittable>> hittables;
    unordered_map<int, shared_ptr<HittableColorAssigner>> hittableColorAssigners;

    // actually we could assign each new hittable with a mechanism and store them in a map.
    MyWrappeeMethod(int img_width, int img_height, shared_ptr<ViewPort> viewPort) {
        this->img_width = img_width;
        this->img_height = img_height;
        this->viewPort = std::move(viewPort);
    }

    void addHittableAndHittableColorAssigner(const shared_ptr<Hittable> &hittable,
                                             const shared_ptr<HittableColorAssigner> &hittableColorAssigner) {
        hittables.push_back(hittable);
        hittableColorAssigners.insert({hittable->id, hittableColorAssigner});
    }

    virtual void operator()(int i, int j, ofstream &target) const {
        auto v = double(j) / (img_height - 1);
        auto u = double(i) / (img_width - 1);

        auto dir = viewPort->left_lower_corner + u * viewPort->viewport_width_vector +
                   v * viewPort->viewport_height_vector - viewPort->origin;
        auto ray = Ray{viewPort->origin,
                       dir};

        auto hitRecordOfTheClosestHittable = hit(ray, 0.001);
        color pixel_color;
        if (hitRecordOfTheClosestHittable != nullptr) {
            auto hittableColorAssigner = hittableColorAssigners.find(hitRecordOfTheClosestHittable->id);
            pixel_color = hittableColorAssigner->second->Color(*hitRecordOfTheClosestHittable);
            //pixel_color = color{1, 0, 0};
        } else {
            pixel_color = notHitColorAssign();
            //pixel_color = color{0, 0, 1};
        }
        write_color(target, pixel_color);
    }

    shared_ptr<HitRecord> hit(const Ray &ray, double t_min) const {
        auto t_max = DBL_MAX;
        shared_ptr<HitRecord> hitRecordOfTheClosestHittable = nullptr;
        for (const auto &hittable : hittables) {
            auto hitRecord = hittable->hit(ray);
            if (hitRecord != nullptr && t_min < hitRecord->t && hitRecord->t < t_max) {
                t_max = hitRecord->t;
                hitRecordOfTheClosestHittable = hitRecord;
            }
        }
        return hitRecordOfTheClosestHittable;
    }

    virtual color notHitColorAssign() const {
        return color{0, 0, 1.0};
    }

    // we'll create hittable_color;
};


struct AntiAliasingWrappeeMethod : public MyWrappeeMethod {
    int samples_per_pixel;

    AntiAliasingWrappeeMethod(int imgWidth, int imgHeight, shared_ptr<ViewPort> viewPort,
                              int samplesPerPixel) : MyWrappeeMethod(imgWidth, imgHeight,
                                                                     std::move(viewPort)),
                                                     samples_per_pixel(samplesPerPixel) {}

    void operator()(int i, int j, ofstream &target) const override {
        color pixel_color{0, 0, 0};
        for (int s = 0;
             s < samples_per_pixel;
             ++s) {
            auto v = (double(j) + random_double()) / (img_height - 1);
            auto u = (double(i) + random_double()) / (img_width - 1);
            auto dir = viewPort->left_lower_corner + u * viewPort->viewport_width_vector +
                       v * viewPort->viewport_height_vector - viewPort->origin;
            auto ray = Ray{viewPort->origin,
                           dir};
            auto hitRecordOfTheClosestHittable = hit(ray, 0.001);
            if (hitRecordOfTheClosestHittable != nullptr) {
                auto hittableColorAssigner = hittableColorAssigners.find(hitRecordOfTheClosestHittable->id);
                pixel_color += hittableColorAssigner->second->Color(*hitRecordOfTheClosestHittable);
            } else {
                pixel_color += notHitColorAssign();
            }
        }
        write_color_anti_aliasing(target, pixel_color, samples_per_pixel);
    }

};

struct AntiAliasingAndDiffuserWrappeeMethod : public AntiAliasingWrappeeMethod {
    const int depth;

    AntiAliasingAndDiffuserWrappeeMethod(int imgWidth, int imgHeight,
                                         shared_ptr<ViewPort> viewPort, int samplesPerPixel, int depth)
            : AntiAliasingWrappeeMethod(imgWidth, imgHeight, std::move(viewPort), samplesPerPixel), depth{depth} {}

    void operator()(int i, int j, ofstream &target) const override {
        color pixel_color{0, 0, 0};
        for (int s = 0;
             s < samples_per_pixel;
             ++s) {
            auto v = (double(j) + random_double()) / (img_height - 1);
            auto u = (double(i) + random_double()) / (img_width - 1);
            auto dir = viewPort->left_lower_corner + u * viewPort->viewport_width_vector +
                       v * viewPort->viewport_height_vector - viewPort->origin;
            auto ray = Ray{viewPort->origin,
                           dir};

            double coefficient = 1;
            int counter = depth;
            while (--counter) {
                auto hitRecordOfTheClosestHittable = hit(ray, 0.001);
                if (hitRecordOfTheClosestHittable != nullptr) {
                    point3 target_point = hitRecordOfTheClosestHittable->p + hitRecordOfTheClosestHittable->normal +
                                          random_unit_vector();
                    ray = Ray{hitRecordOfTheClosestHittable->p, target_point - hitRecordOfTheClosestHittable->p};
                    coefficient *= 0.5;
                } else {
                    pixel_color = coefficient * notHitColorAssign(ray);
                    break;
                }
            }
        }
        write_color_anti_aliasing(target, pixel_color, samples_per_pixel);
    }

    static color notHitColorAssign(const Ray &ray) {
        vec3 unit_direction = unit_vector(ray.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};

#endif //RAYTRACING_VIEWPORT_H

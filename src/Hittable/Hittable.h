//
// Created by ibrah on 02/07/2021.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "../Ray/Ray.h"

class UIDGenerator {
private:
    UIDGenerator() {
        id = 0;
    }

public:
    static UIDGenerator &getInstance(){
        static UIDGenerator instance;
        return instance;
    }

    int getID() {
        id++;
        return id;
    };
public:
    int id;
};


struct HitRecord {
    int id;
    point3 p;
    vec3 normal;
    double t;
    bool front_face;


    inline void set_face_normal(const Ray &r, const vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    int id;

    Hittable(int id) {
        this->id = id;
    }

    virtual HitRecord* hit(const Ray &ray) const = 0;
};

class HittableColorAssigner {
public:
    color Color(const HitRecord &hitRecord) {
        return color{1.0, 0.0, 0.0};
    }
};

class SphereHittable : Hittable {
public:
    point3 center;
    double radius;
    SphereHittable(int id, const point3 &center, double radius) : Hittable(id),
                                                                  center(center), radius(radius) {}

    virtual HitRecord *hit(const Ray &ray) const override {
        vec3 oc = ray.origin() - center;
        auto a = ray.direction().length_squared();
        auto half_b = dot(oc, ray.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return nullptr;

        auto sqrtd = sqrt(discriminant);
        auto root = (-half_b - sqrtd) / a;

        HitRecord *hitRecord = new HitRecord{};
        hitRecord->id = id;
        hitRecord->t = root;
        hitRecord->p = ray.at(root);
        hitRecord->normal = (hitRecord->p - center) / radius;

        return hitRecord;
    }
};

#endif //RAYTRACING_HITTABLE_H

//
// Created by ibrah on 29/06/2021.
//

#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H
#include <bits/stdc++.h>
#include "catch.hpp"

using namespace std;

class vec3{
    vector<double> e;
public:
    vec3(): e{0, 0, 0} {}
    vec3(double a, double b, double c): e{a, b, c} {}

    vec3 operator-() const{
        return vec3(-x(), -y(), -z());
    }

    double x() const{
        return e.at(0);
    }

    double y() const{
        return e.at(1);
    }

    double z() const{
        return e.at(2);
    }

    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool operator==(const vec3& second_operand) const{
        for (int i = 0; i < 3; ++i){
            if (this->e.at(i) !=  second_operand.e.at(i))
                return false;
        }
        return true;
    }
};


// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
#endif //RAYTRACING_VECTOR_H

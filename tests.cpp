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

TEST_CASE("Testing vec3 library for basic operations upon them"){
    SECTION("Negate a vector") {
        vec3 my_vec = vec3{5, -1, 2};
        const vec3& expected_result = vec3{-5, 1, -2};
        CHECK(-my_vec == expected_result);
    }

    SECTION("Adding a rhs vector upon lhs vector"){
        vec3 lhs = vec3{1, 2, 3};
        vec3 rhs = vec3{2, 3 , 4};
        const vec3& expected_result = vec3{3, 5, 7};
        lhs += rhs;
        CHECK(lhs == expected_result);
    }

    SECTION("Multiply lhs with a scalar"){
        vec3 lhs = vec3{1, 2, 3};
        const vec3& expected_result = vec3{2, 4, 6};
        lhs *= 2;
        CHECK(lhs == expected_result);
    }

    SECTION("Divide lhs by a scalar"){
        vec3 lhs = vec3{2, 2, 3};
        lhs /= 2;
        CHECK((lhs.x() == 1 && lhs.y() == 1 && Approx(lhs.z()) == 1.5));
    }

    SECTION("Calculation of the lenght of a vector"){
        vec3 lhs = vec3{3, 4, 2};
        auto length = lhs.length();
        auto length_squared = lhs.length_squared();

        CHECK(Approx(length) == 5.38516480);
        CHECK(length_squared == 29);
    }
}

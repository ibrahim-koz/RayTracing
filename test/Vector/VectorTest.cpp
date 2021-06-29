#include "../../src/Vector/Vector.h"
#include <bits/stdc++.h>
#include "../../catch.hpp"

using namespace std;

TEST_CASE("Testing vec3 library for basic operations upon them") {
    SECTION("Negate a vector") {
        vec3 my_vec = vec3{5, -1, 2};
        const vec3 &expected_result = vec3{-5, 1, -2};
        CHECK(-my_vec == expected_result);
    }

    SECTION("Adding a rhs vector upon lhs vector") {
        vec3 lhs = vec3{1, 2, 3};
        vec3 rhs = vec3{2, 3, 4};
        const vec3 &expected_result = vec3{3, 5, 7};
        lhs += rhs;
        CHECK(lhs == expected_result);
    }

    SECTION("Multiply lhs with a scalar") {
        vec3 lhs = vec3{1, 2, 3};
        const vec3 &expected_result = vec3{2, 4, 6};
        lhs *= 2;
        CHECK(lhs == expected_result);
    }

    SECTION("Divide lhs by a scalar") {
        vec3 lhs = vec3{2, 2, 3};
        lhs /= 2;
        CHECK((lhs.x() == 1 && lhs.y() == 1 && Approx(lhs.z()) == 1.5));
    }

    SECTION("Calculation of the lenght of a vector") {
        vec3 lhs = vec3{3, 4, 2};
        auto length = lhs.length();
        auto length_squared = lhs.length_squared();

        CHECK(Approx(length) == 5.38516480);
        CHECK(length_squared == 29);
    }
}

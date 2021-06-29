#include <bits/stdc++.h>
#include "catch.hpp"
#include "src/Vector/Vector.h"
using namespace std;

TEST_CASE("Putting a camera from which the rays will be emitted"){
    SECTION("Seeing pixels colors are computed correctly"){
        const double aspect_ratio = 16/9;
        const int width = 400;
        const int height = width * aspect_ratio;

        // this value is chosen arbitrarily
        // we're gonna set our viewport_width such that the pair of (viewport_height, viewport_width) comply with the
        // ratio of the picture to be drawn.
        const int viewport_height = 2;
        const int viewport_width = viewport_height * aspect_ratio;
        const double focal_length = 1.0;

        // the following two are created to make it easier to compute.
        auto viewport_height_vector = vec3(0, viewport_height, 0);
        auto viewport_width_vector = vec3(viewport_width, 0, 0);
        auto focal_point = vec3(0, 0, -focal_length);

        // we'll draw our picture through the viewport, so we will project our rays to our viewport first.
        auto left_lower_corner = -(viewport_height_vector / 2) - (viewport_width_vector / 2) + focal_point;

        //for (int j = 0; j < width)
    }
}
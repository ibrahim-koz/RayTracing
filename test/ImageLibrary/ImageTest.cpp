//
// Created by ibrah on 29/06/2021.
//
#include "../../src/ImageLibrary/Image.h"
#include <bits/stdc++.h>
#include "../../catch.hpp"

TEST_CASE("Output an image") {
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());

    SECTION("Check if the output is created.", "[num]") {
        int signal = DrawSimplePpm("drawn_img_path.ppm");
        auto output = image_reader.read("drawn_img_path.ppm");
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }

    SECTION("Drawn image is the same as the given sample in the tutorial.") {
        PpmImage *expected_image = static_cast<PpmImage *>(image_reader.read("simple_ppm_image.ppm"));
        PpmImage *output = static_cast<PpmImage *>(image_reader.read("drawn_img_path.ppm"));
        REQUIRE(*output == *expected_image);
    }
}
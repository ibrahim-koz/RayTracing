//
// Created by ibrah on 29/06/2021.
//
#include "../../src/ImageLibrary/Image.h"
#include <bits/stdc++.h>
#include "../../catch.hpp"

inline void *MyWrappeeMethod(int i, int j, int img_height, int img_width, ofstream& target){
    auto r = double(i) / (img_height - 1);
    auto g = double(j) / (img_height - 1);
    auto b = 0.25;

    color pixel_color(r, g, b);

    write_color(target, pixel_color);
    return nullptr;
}

inline void *MyWrappeeMethod2(int i, int j, int img_height, int img_width, ofstream& target){
    auto r = double(i) / (img_height - 1);
    auto g = double(j) / (img_height - 1);
    auto b = 0.25;

    color pixel_color(r, g, b);

    write_color(target, pixel_color);
    return nullptr;
}

TEST_CASE("Output an image") {
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());

    SECTION("Check if the output is created.", "[num]") {
        int signal = DrawSimplePpm("drawn_img_path.ppm", 256,  256, MyWrappeeMethod);
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
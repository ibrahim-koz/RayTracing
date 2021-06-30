//
// Created by ibrah on 29/06/2021.
//
#include "../../src/ImageLibrary/Image.h"
#include <bits/stdc++.h>
#include "../../catch.hpp"

struct MyWrappeeMethod2{
    const int img_width;
    const int img_height;

    MyWrappeeMethod2(int img_width, int img_height): img_width{img_width}, img_height{img_height}{

    }

    void operator()(int i, int j, ofstream& target) const {
        auto r = double(i) / (img_height - 1);
        auto g = double(j) / (img_height - 1);
        auto b = 0.25;

        color pixel_color(r, g, b);

        write_color(target, pixel_color);
    }
};


TEST_CASE("Output an image") {
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());

    SECTION("Check if the output is created.", "[num]") {
        const int width = 256;
        const int height =  256;
        auto myWrappeeMethod = MyWrappeeMethod2{width, height};
        int signal = DrawSimplePpm("drawn_img_path.ppm", width, height, myWrappeeMethod);
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
#include <bits/stdc++.h>
#include "../../catch.hpp"
#include "Image.h"
using namespace std;


int DrawSimplePpm(const string &img_path) {
    const int img_height = 256;
    const int img_width = 256;

    ofstream target;
    target.open(img_path);

    target << "P3" << endl;
    target << img_height << " " << img_height << endl;
    target << 255 << endl;

    for (int i = img_height - 1; i >= 0; --i) {
        for (int j = 0; j < img_width; ++j) {
            auto r = double(j) / (img_height - 1);
            auto g = double(i) / (img_height - 1);
            auto b = 0.25;

            auto ir = static_cast<int>(255.999 * r);
            auto ig = static_cast<int>(255.999 * g);
            auto ib = static_cast<int>(255.999 * b);

            target << ir << " " << ig << " " << ib << endl;
        }
    }
    target.close();
    return 0;
}

// TODO: pixel test will be added.
bool operator==(const PpmImage &ppm_image1, const PpmImage &ppm_image2) {
    if (ppm_image1.format_type == ppm_image2.format_type
        && ppm_image1.height == ppm_image2.height
        && ppm_image1.width == ppm_image2.width
        && ppm_image1.rbg_values == ppm_image2.rbg_values)
        return true;
    return false;
}



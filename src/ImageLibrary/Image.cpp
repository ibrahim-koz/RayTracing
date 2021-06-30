#include <bits/stdc++.h>
#include "Image.h"
using namespace std;


void write_color(ofstream &out, const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto ir = static_cast<int>(255.999 * r);
    auto ig = static_cast<int>(255.999 * g);
    auto ib = static_cast<int>(255.999 * b);
    out << ir << " " << ig << " " << ib << endl;
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



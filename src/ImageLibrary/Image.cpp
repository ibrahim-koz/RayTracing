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


int DrawSimplePpm(const string &img_path, const int img_height, const int img_width,
                  void *(*WrappeeDrawingMethod)(int i, int j, int img_height , int img_width, ofstream& target)) {
    ofstream target;
    target.open(img_path);

    target << "P3" << endl;
    target << img_height << " " << img_height << endl;
    target << 255 << endl;

    for (int j = img_height - 1; j >= 0; --j) {
        for (int i = 0; i < img_width; ++i) {
            WrappeeDrawingMethod(i, j,  img_height, img_width, target);
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



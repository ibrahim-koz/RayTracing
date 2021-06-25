#include <bits/stdc++.h>
#include "catch.hpp"

using namespace std;

struct PpmImage{

};


PpmImage ReadPpmImage(string img_path){

}

void DrawSimplePpm(string img_path){
    const int img_height = 256;
    const int img_width = 256;

    ofstream target;
    target.open("simple_ppm_image.ppm");

    target << "P3" << endl;
    target << img_height << " " << img_height  << endl;
    target << 255 << endl;

    for (int i = img_height - 1; i >= 0 ; --i) {
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
}

bool operator==(PpmImage ppm_image1, PpmImage ppm_image2){
    //
}


TEST_CASE("Output an image"){
    //auto expected_image = ReadPpmImage("img_path");
    DrawSimplePpm("img_path");
    //auto output = ReadPpmImage("img_path");
    //REQUIRE(output == expected_image);
}
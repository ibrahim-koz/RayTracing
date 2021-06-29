//
// Created by ibrah on 29/06/2021.
//

#ifndef RAYTRACING_IMAGE_H
#define RAYTRACING_IMAGE_H

#include <bits/stdc++.h>
#include "../Vector/Vector.h"

using namespace std;

class Image {

};

class PpmImage : public Image {
public:
    string format_type;
    int height, width;
    int scale_factor;
    const int rgb_channel = 3;
    int i = 0, j = 0;

    vector<vector<vector<int>>> rbg_values;

    PpmImage(string formatType, int height, int width, int scaleFactor) : format_type(std::move(formatType)),
                                                                          height(height), width(width),
                                                                          scale_factor(scaleFactor),
                                                                          rbg_values(height, vector<vector<int>>(width,
                                                                                                                 vector<int>(
                                                                                                                         rgb_channel))) {
    }

    void AddPixel(int red, int green, int blue) {
        rbg_values.at(i).at(j).at(0) = red;
        rbg_values.at(i).at(j).at(1) = green;
        rbg_values.at(i).at(j).at(2) = blue;
        j++;
        if (j == width) {
            i++;
            j = 0;
        }
    }
};

class ReadImageStrategy {
public:
    virtual Image *read(string img_path) = 0;

    virtual ~ReadImageStrategy() = default;
};

class PpmImageStrategy : public ReadImageStrategy {
public:
    PpmImage *read(string img_path) override {
        stringstream ss;
        string line;
        ifstream myfile(img_path);
        if (myfile.is_open()) {
            string format_type;
            int height, width;
            int scale_factor;

            getline(myfile, line);
            ss << line;
            ss >> format_type;
            getline(myfile, line);
            ss.clear();
            ss << line;
            ss >> height >> width;
            ss.clear();
            getline(myfile, line);
            ss << line;
            ss >> scale_factor;
            ss.clear();
            auto ppmImage = new PpmImage(format_type, height, width, scale_factor);

            int red, green, blue;
            while (getline(myfile, line)) {
                ss << line;
                ss >> red >> green >> blue;
                ss.clear();
                ppmImage->AddPixel(red, green, blue);
            }
            myfile.close();
            return ppmImage;
        } else {
            cout << "Unable to open file";
            return nullptr;
        }
    }
};

class ReadImage {
public:
    ReadImageStrategy *readImageStrategy;

    void PickStrategy(ReadImageStrategy *strategy) {
        delete this->readImageStrategy;
        this->readImageStrategy = strategy;
    }

    Image *read(string img_path) const {
        return this->readImageStrategy->read(std::move(img_path));
    }
};

void write_color(ofstream &out, const color& pixel_color);
int DrawSimplePpm(const string &img_path, const int img_height, const int img_width,
                  void *(*WrappeeDrawingMethod)(int i, int j, int img_height , int img_width, ofstream& target));
bool operator==(const PpmImage &ppm_image1, const PpmImage &ppm_image2);

#endif //RAYTRACING_IMAGE_H

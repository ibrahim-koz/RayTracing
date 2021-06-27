#include <bits/stdc++.h>
#include "../../catch.hpp"

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

            int red, blue, green;
            while (getline(myfile, line)) {
                ss << line;
                ss >> red >> blue >> green;
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
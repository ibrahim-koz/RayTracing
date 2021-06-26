#include <bits/stdc++.h>
#include "catch.hpp"

using namespace std;

class Image{

};

class PpmImage: public Image{
public:
    string format_type;
    int height, width;
    int scale_factor;
    const int rgb_channel = 3;

    vector<vector<int>> rbg_values;
    PpmImage(string formatType, int height, int width, int scaleFactor) : format_type(std::move(formatType)),
                                                                                 height(height), width(width),
                                                                                 scale_factor(scaleFactor),
                                                                                 rbg_values(height * width, vector<int>(this->rgb_channel)){
    }

    void AddPixel(int red, int green, int blue){
        static int i = 0;
        rbg_values.at(i).at(0) = red;
        rbg_values.at(i).at(1) = green;
        rbg_values.at(i).at(2) = blue;
        i++;
    }


};

class ReadImageStrategy{
public:
    virtual Image* read(string img_path) = 0;
    virtual ~ReadImageStrategy() = default;
};

class PpmImageStrategy : public ReadImageStrategy{
public:
    PpmImage* read(string img_path) override{
        stringstream ss;
        string line;
        ifstream myfile(img_path);
        if (myfile.is_open()){
            string format_type;
            int height, width;
            int scale_factor;

            getline(myfile, line);
            ss << line;
            ss >> format_type;
            getline(myfile, line);
            ss << line;
            ss >> height >> width;
            getline(myfile, line);
            ss << line;
            ss >> scale_factor;
            auto ppmImage = new PpmImage(format_type, height, width, scale_factor);

            int red, blue, green;
            while (getline(myfile, line)){
                ss << line;
                ss >> red >> blue >> green;
                ppmImage->AddPixel(red, green, blue);
            }
            myfile.close();
            return ppmImage;
        }
        else{
            cout << "Unable to open file";
            return nullptr;
        }
    }
};

class ReadImage{
public:
    ReadImageStrategy* readImageStrategy;
    void PickStrategy(ReadImageStrategy *strategy){
        delete this->readImageStrategy;
        this->readImageStrategy = strategy;
    }

    [[nodiscard]] Image* read(string img_path) const{
        return this->readImageStrategy->read(std::move(img_path));
    }
};

void DrawSimplePpm(const string& img_path){
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

bool operator==(const PpmImage& ppm_image1, const PpmImage& ppm_image2){
    if (ppm_image1.format_type == ppm_image2.format_type
    &&  ppm_image1.height == ppm_image2.height
    &&  ppm_image1.width == ppm_image2.width
    &&  ppm_image1.rbg_values == ppm_image2.rbg_values)
        return true;
    return false;
}


TEST_CASE("Output an image"){
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());
    auto expected_image = image_reader.read("img_path");
    DrawSimplePpm("img_path");
    auto output = image_reader.read("drawn_img_path");
    REQUIRE(output == expected_image);
}
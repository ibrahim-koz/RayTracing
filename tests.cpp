#include <bits/stdc++.h>
#include "catch.hpp"
#include "src/Vector/Vector.h"
#include "src/Ray/Ray.h"
#include "src/ImageLibrary/Image.h"

using namespace std;

color ray_color(const Ray &r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color{1.0, 1.0, 1.0} + t * color{0.5, 0.7, 1.0};
}

struct MyWrappeeMethod{
    const double aspect_ratio;
    const int img_width;
    const int img_height;

    MyWrappeeMethod(double aspect_ratio, int img_width): aspect_ratio{aspect_ratio}, img_width{img_width},
    img_height{static_cast<int>(img_width * aspect_ratio)}{

    }

    // this value is chosen arbitrarily
    // we're gonna set our viewport_width such that the pair of (viewport_height, viewport_width) comply with the
    // ratio of the picture to be drawn.
    const int viewport_height = 2;
    const int viewport_width = viewport_height * aspect_ratio;
    const double focal_length = 1.0;

    // the following two are created to make it easier to compute.
    vec3 viewport_height_vector = vec3(0, viewport_height, 0);
    vec3 viewport_width_vector = vec3(viewport_width, 0, 0);
    vec3 focal_point = vec3(0, 0, -focal_length);
    vec3 origin = vec3(0, 0, 0);
    // we'll draw our picture through the viewport, so we will project our rays to our viewport first.
    vec3 left_lower_corner = origin + (-(viewport_height_vector / 2) - (viewport_width_vector / 2) + focal_point);

    void operator()(int i, int j, ofstream& target) const{
        auto v = double(j) / (img_height - 1);
        auto u = double(i) / (img_width - 1);

        auto ray = Ray{origin,
                       left_lower_corner + u * viewport_width_vector + v * viewport_height_vector - origin};
        color pixel_color = ray_color(ray);
        write_color(target, pixel_color);
    }
};

TEST_CASE("Putting a camera from which the rays will be emitted") {
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());

    SECTION("Seeing pixels colors are computed correctly") {
        string img_path = "new_gradient_sky.ppm";

        const double aspect_ratio = 16 / 9;
        const int img_width = 400;
        const int img_height = img_width * aspect_ratio;

        auto myWrappeeMethod = MyWrappeeMethod{aspect_ratio, img_width};
        int signal = DrawSimplePpm(img_path, img_height, img_height, myWrappeeMethod);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }
}
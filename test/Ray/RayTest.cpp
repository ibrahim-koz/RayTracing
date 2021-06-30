#include "../../catch.hpp"
#include "../../src/Vector/Vector.h"
#include "../../src/Ray/Ray.h"

using namespace std;


TEST_CASE("Putting a camera from which the rays will be emitted") {
    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());


    const double aspect_ratio = 16 / 9;
    const int img_width = 400;
    const int img_height = img_width * aspect_ratio;

    SECTION("Seeing pixels colors are computed correctly") {
        string img_path = "new_gradient_sky.ppm";

        auto myWrappeeMethod = MyWrappeeMethod{aspect_ratio, img_width};
        int signal = DrawSimplePpm(img_path, img_height, img_width, myWrappeeMethod);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }

    SECTION("Drawing a sphere"){
        string img_path = "sphere.ppm";

        auto hitSphereWrappee = HitSphereWrappee{aspect_ratio, img_width};
        int signal = DrawSimplePpm(img_path, img_height, img_width, hitSphereWrappee);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }


    SECTION("Drawing a shaded sphere"){
        string img_path = "shaded_sphere.ppm";

        auto shadedHitSphereWrappee = ShadedHitSphereWrappee{aspect_ratio, img_height};
        int signal = DrawSimplePpm(img_path, img_height, img_width, shadedHitSphereWrappee);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }
}
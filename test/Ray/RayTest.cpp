#include "../../catch.hpp"
#include "../../src/Vector/Vector.h"
#include "../../src/Ray/Ray.h"
#include "../../src/ViewPort/ViewPort.h"
#include "../../src/Hittable/Hittable.h"

using namespace std;


TEST_CASE("Putting a camera from which the rays will be emitted") {
    auto uiGenerator = UIDGenerator::getInstance();

    auto image_reader = ReadImage();
    image_reader.PickStrategy(new PpmImageStrategy());


    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = img_width * aspect_ratio;
    ViewPort* viewPort = new ViewPort{2.0 * aspect_ratio, 2.0, point3{0, 0, 0}, 1.0};

//    SECTION("Seeing pixels colors are computed correctly") {
//        string img_path = "new_gradient_sky.ppm";
//
//        auto myWrappeeMethod = MyWrappeeMethod{img_width, img_height, viewPort};
//        int signal = DrawSimplePpm(img_path, img_height, img_width, myWrappeeMethod);
//        auto output = image_reader.read(img_path);
//        REQUIRE(signal == 0);
//        REQUIRE(output != nullptr);
//    }
//
//    SECTION("Drawing a sphere") {
//        string img_path = "sphere.ppm";
//
//        auto myWrappeeMethod = MyWrappeeMethod{img_width, img_width, viewPort};
//        int signal = DrawSimplePpm(img_path, img_height, img_width, myWrappeeMethod);
//        auto output = image_reader.read(img_path);
//        REQUIRE(signal == 0);
//        REQUIRE(output != nullptr);
//    }


    SECTION("Drawing a shaded sphere") {
        string img_path = "shaded_sphere.ppm";
        auto myWrappeeMethod = MyWrappeeMethod{img_width, img_width, viewPort};
        Hittable *spherePtr = (Hittable *) new SphereHittable{uiGenerator.getID(), point3{0, 0, -1}, 0.5};
        auto hittableColorAssigner = new HittableColorAssigner{};
        myWrappeeMethod.addHittableAndHittableColorAssigner(spherePtr, hittableColorAssigner);
        int signal = DrawSimplePpm(img_path, img_height, img_width, myWrappeeMethod);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }
}
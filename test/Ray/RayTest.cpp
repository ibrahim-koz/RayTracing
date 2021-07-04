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


    const double aspect_ratio = 16 / 9;
    const int img_width = 400;
    const int img_height = img_width * aspect_ratio;
    ViewPort* viewPort = new ViewPort{2.0 * aspect_ratio, 2.0, point3{0, 0, 0}, 1.0};

    SECTION("Drawing a shaded sphere") {
        string img_path = "two_sphere.ppm";
        auto myWrappeeMethod = MyWrappeeMethod{img_width, img_height, viewPort};
        Hittable *spherePtr = (Hittable *) new SphereHittable{uiGenerator.getID(), point3{0, 0, -1}, 0.5};
        //Hittable *secondSpherePtr = (Hittable *) new SphereHittable{uiGenerator.getID(), point3{0,-100.5,-1}, 100};
        auto hittableColorAssigner = new HittableColorAssigner{};
        myWrappeeMethod.addHittableAndHittableColorAssigner(spherePtr, hittableColorAssigner);
        //myWrappeeMethod.addHittableAndHittableColorAssigner(secondSpherePtr, hittableColorAssigner);
        int signal = DrawSimplePpm(img_path, img_height, img_width, myWrappeeMethod);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }

    SECTION("Antialiasing is working correctly."){
        string img_path = "antialiasingsphere.ppm";
        auto antialiasingWrappeeMethod = AntiAliasingWrappeeMethod(img_width, img_height, viewPort, 100);

        Hittable *spherePtr = (Hittable *) new SphereHittable{uiGenerator.getID(), point3{0, 0, -1}, 0.5};
        //Hittable *secondSpherePtr = (Hittable *) new SphereHittable{uiGenerator.getID(), point3{0,-100.5,-1}, 100};
        auto hittableColorAssigner = new HittableColorAssigner{};
        antialiasingWrappeeMethod.addHittableAndHittableColorAssigner(spherePtr, hittableColorAssigner);
        //antialiasingWrappeeMethod.addHittableAndHittableColorAssigner(secondSpherePtr, hittableColorAssigner);
        int signal = DrawSimplePpm(img_path, img_height, img_width, antialiasingWrappeeMethod);
        auto output = image_reader.read(img_path);
        REQUIRE(signal == 0);
        REQUIRE(output != nullptr);
    }
}
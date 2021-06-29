cmake_minimum_required(VERSION 3.19)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp tests.cpp src/ImageLibrary/Image.cpp test/ImageLibrary/ImageTest.cpp src/ImageLibrary/Image.h src/Vector/Vector.h test/Vector/VectorTest.cpp src/Ray/Ray.cpp src/Ray/Ray.h)
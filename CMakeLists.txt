cmake_minimum_required(VERSION 4.1)
project(tncg15_raytracer)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(tncg15_raytracer
        include/camera.h
        include/ray.h
        include/triangle.h
        include/vec3.h
        src/camera.cpp
        src/main.cpp
        src/ray.cpp
        src/triangle.cpp)

cmake_minimum_required(VERSION 3.20)
project(tncg15_raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(tncg15_raytracer
        include/camera.h
        include/ray.h
        include/triangle.h
        include/vec3.h
        include/sphere.h
        include/hittable.h
        include/color.h
        src/main.cpp
        src/scene.cpp
        include/scene.h
        include/hittable_list.h
        include/utilities.h
        include/interval.h)
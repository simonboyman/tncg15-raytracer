#include <hittable_list.h>
#include <camera.h>
#include "scene.h"

int main() {

    // Scene

    hittable_list world;
    create_room(world);

    // Render

    camera cam;
    cam.samples_per_pixel = 1000;
    cam.max_depth = 3;
    cam.render(world);

}
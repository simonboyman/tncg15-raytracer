#include <hittable_list.h>
#include <camera.h>
#include "scene.h"

int main() {

    // Scene

    hittable_list world;
    create_room(world);

    // Render

    camera cam;
    cam.samples_per_pixel = 50;
    cam.max_depth = 20;
    cam.render(world);

}
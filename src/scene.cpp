#include <utilities.h>
#include <scene.h>
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "material.h"

void create_room(hittable_list& world) {
    std::vector<vec3> vertices = {
        vec3(0,0,0), // 0
        vec3(4,0,0), // 1
        vec3(4,4,0), // 2
        vec3(0,4,0), // 3
        vec3(0,0,4), // 4
        vec3(4,0,4), // 5
        vec3(4,4,4), // 6
        vec3(0,4,4)  // 7
    };

    // ---- Wall colors: edit these to taste ----
    const vec3 back_color    (0.30, 0.50, 0.85); // blue
    const vec3 front_color   (0.95, 0.85, 0.40); // yellow
    const vec3 floor_color   (0.60, 0.60, 0.60); // gray
    const vec3 ceiling_color (0.95, 0.95, 0.40); // yellow
    const vec3 left_color    (0.85, 0.25, 0.25); // red
    const vec3 right_color   (0.25, 0.75, 0.35); // green
    // ------------------------------------------


    // Splits a quad (a,b,c,d) into triangles (a,b,c) and (a,c,d)
    auto add_quad = [&](int a, int b, int c, int d, shared_ptr<material> mat) {
        world.add(make_shared<triangle>(vertices[a], vertices[b], vertices[c], mat));
        world.add(make_shared<triangle>(vertices[a], vertices[c], vertices[d], mat));
    };

    auto light = make_shared<diffuse_light>(color(8, 8, 8));
    world.add(make_shared<triangle>(vec3(1.5,3.99,1.5), vec3(1.5,3.99,2.5), vec3(2.5,3.99,2.5), light));
    world.add(make_shared<triangle>(vec3(1.5,3.99,1.5), vec3(2.5,3.99,2.5), vec3(2.5,3.99,1.5), light));

    add_quad(0, 1, 2, 3, make_shared<lambertian>(back_color));
    add_quad(4, 7, 6, 5, make_shared<lambertian>(front_color));
    add_quad(0, 4, 5, 1, make_shared<lambertian>(floor_color));
    add_quad(3, 2, 6, 7, make_shared<lambertian>(ceiling_color));
    add_quad(0, 3, 7, 4, make_shared<lambertian>(left_color));
    add_quad(1, 5, 6, 2, make_shared<lambertian>(right_color));

    // SPHERES

    world.add(make_shared<sphere>(vec3(1,1,1), 1, make_shared<lambertian>(color(1,0,0))));
    world.add(make_shared<sphere>(vec3(2.8,0.5,1.6), 0.4, make_shared<metal>(color(0.8, 0.8, 0.8))));
}
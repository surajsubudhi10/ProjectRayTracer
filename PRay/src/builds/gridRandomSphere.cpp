//
// Created by Suraj on 11-06-2018.
//

#include <World/World.h>
#include <Samplers/MultiJittered.h>
#include <Lights/AmbientOcculuder.h>
#include <Lights/PointLight.h>
#include <Camera/Orthographic.h>
#include <cmath>
#include <Objects/Grid.h>
#include <Materials/Matte.h>

void World::build()
{
    auto num_of_samples = 64;
    vp.set_hres(500);
    vp.set_vres(400);
    vp.set_pixel_size(1.0);
    vp.set_samples(num_of_samples);
    vp.set_gamma(1.0);
    vp.set_gamut_display(true);
    vp.set_max_depth(2);

    background_color = black;

    auto* occluder_ptr = new AmbientOcculuder(black, new MultiJittered(num_of_samples));
    occluder_ptr->scale_radiance(3.0);
    set_ambient_light(occluder_ptr);

    //// ================ Camera ===================== ////

    auto * pinhole_ptr = new Orthographic();
    pinhole_ptr->set_eye(100, 300, 00);
//    pinhole_ptr->set_eye(1400, 300, 00);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_zoom(0.5f);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);

    //// ====================== LIGHTS ======================= ////

    auto * point_light_ptr = new PointLight();
    point_light_ptr->set_location(240, 1240, 240);
    point_light_ptr->scale_radiance(2.0);
    add_light(point_light_ptr);

    auto * point_light_ptr2 = new PointLight();
    point_light_ptr2->set_location(0, 1840, 0);
    point_light_ptr2->scale_radiance(2.0);
    add_light(point_light_ptr2);

    //// ============================================= ////

    int numOfSphere = 100;
    float volume = 0.1f / numOfSphere;
    float radius = powf(static_cast<float>(0.75f * volume / PI), 1.0f / 3.0f);

    auto* grid_ptr = new Grid;
    set_rand_seed(15);

    for(auto i = 0; i < numOfSphere; i++){
        auto* matte_ptr = new Matte;
        matte_ptr->set_ka(0.25f);
        matte_ptr->set_kd(0.75f);
        matte_ptr->set_cd(rand_float(), rand_float(), rand_float());

        auto* sphere_ptr = new Sphere;
        sphere_ptr->set_radius(radius * 100.0f);
        sphere_ptr->set_center(100.0f * (rand_float()), 100.0f * (rand_float()), 100.0f * (rand_float()));
        sphere_ptr->set_material(matte_ptr);
        grid_ptr->add_object(sphere_ptr);
    }

    grid_ptr->setup_cells();
    add_object(grid_ptr);
}
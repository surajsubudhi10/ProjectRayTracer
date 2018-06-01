
#include <Materials/Reflective.h>
#include <Objects/Rectangle.h>
#include <Camera/Orthographic.h>
#include <Camera/ThinLens.h>
#include <Samplers/MultiJittered.h>
#include <Lights/AmbientOcculuder.h>
#include <Materials/GlossyReflector.h>
#include <Objects/OpenCylinder.h>
#include <Objects/Torus.h>
#include "World/World.h"
#include "Objects/Plane.h"
//#include "Camera/PinHole.h"

#include "Lights/Ambient.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/Phong.h"

#include "Objects/Box.h"
#include "Objects/Triangle.h"
#include "Objects/Disk.h"

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
    pinhole_ptr->set_eye(1400, 300, 00);
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


    auto* phong_ptr = new Phong();
    phong_ptr->set_ka(0.15);
    phong_ptr->set_ca(1.0, 0.0, 0.0);
    phong_ptr->set_kd(0.85);
    phong_ptr->set_cd(0.5, 0.5, 0.5);
    phong_ptr->set_ks(0.3);
    phong_ptr->set_exp_s(100);

    auto* matte_ptr1 = new Matte();
    matte_ptr1->set_ka(0.25);
    matte_ptr1->set_kd(0.65);
    matte_ptr1->set_cd(1, 0, 1);

    auto* sphere_ptr1 = new Sphere();
    sphere_ptr1->set_center(Point3D(0, 130.0, 0.0));
	sphere_ptr1->set_material(phong_ptr);
    sphere_ptr1->set_radius(140.0);
//    add_object(sphere_ptr1);

    auto* opencylinder_ptr1 = new OpenCylinder(100, 100, Point3D(100, 50, 0), matte_ptr1);
    add_object(opencylinder_ptr1);

    auto* box_ptr1 = new Box(Point3D(-70, -10, -70), Point3D(70, 130, 70));
    box_ptr1->set_material(matte_ptr1);
//    add_object(box_ptr1);


    //auto* torus_ptr1 = new Torus(Point3D(440, 130.0, -350.0), 30, 140);
    auto* torus_ptr1 = new Torus(Point3D(0, 50, 0), 30, 140);
    torus_ptr1->set_material(matte_ptr1);
    //add_object(torus_ptr1);

    auto* disk_ptr = new Disk(Point3D(-90, 30, -90), 70.0f, Normal(0, 1, 0));
    disk_ptr->set_material(matte_ptr1);
//    add_object(disk_ptr);

    auto* rectangle_ptr = new Rectangle(Point3D(-90, 30, 90), Vector3D(0, 0, 100), Vector3D(100, 0, 0));
    rectangle_ptr->set_material(matte_ptr1);
//    add_object(rectangle_ptr);

    auto* triangle_ptr = new Triangle(Point3D(0, 0, 90), Point3D(90, 0, 0), Point3D(-90, 0, 0));
    triangle_ptr->set_material(matte_ptr1);
//    add_object(triangle_ptr);


    auto* sphere_ptr3 = new Sphere();
    sphere_ptr3->set_center(Point3D(-230.0, 110.0, -230.0));
    sphere_ptr3->set_material(matte_ptr1);
    sphere_ptr3->set_radius(120.0);
    add_object(sphere_ptr3);

    //// ================ Ground Plane ===================== ////

    auto* matte_ptr01 = new Matte();
    matte_ptr01->set_ka(0.25);
    matte_ptr01->set_kd(0.65);
    matte_ptr01->set_cd(0.5, 0.5, 0.5);

    Plane* plane_ptr01 = new Plane(Point3D(0, -10, 0), Normal(0, 1, 0));
    plane_ptr01->set_material(matte_ptr01);
    add_object(plane_ptr01);

};

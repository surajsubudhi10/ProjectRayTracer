
#include <Materials/Reflective.h>
#include <Objects/Rectangle.h>
#include <Camera/Orthographic.h>
#include <Camera/ThinLens.h>
#include <Samplers/MultiJittered.h>
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

#define LIGHTBOX 1

#if LIGHTBOX == 0

void World::build() 
{
	vp.set_hres(1000);
	vp.set_vres(800);
	vp.set_pixel_size(1.0);
	vp.set_samples(1);
	vp.set_gamma(1.0);
	vp.set_gamut_display(true);
	vp.set_max_depth(2);

	background_color = black;

	auto * ambient_ptr = new Ambient();
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	auto * pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(30, 0, 0);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(200);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	auto * point_light_ptr = new PointLight();
	point_light_ptr->set_location(40, 40, 40);
	point_light_ptr->scale_radiance(3.0);
	add_light(point_light_ptr);

	auto * point_light_ptr2 = new PointLight();
	point_light_ptr2->set_location(40, 40, -40);
	point_light_ptr2->scale_radiance(2.0);
	add_light(point_light_ptr2);

	auto * phong_ptr = new Phong();
	phong_ptr->set_ka(0.15);
	phong_ptr->set_kd(0.85);
	phong_ptr->set_cd(1.0, 0.0, 0.0);
	phong_ptr->set_ks(0.3);
	phong_ptr->set_exp_s(100);

	auto * reflective_ptr = new Reflective();
    reflective_ptr->set_ka(0.15);
    reflective_ptr->set_kd(0.85);
    reflective_ptr->set_cd(1.0, 1.0, 0.0);
    reflective_ptr->set_ks(0.3);
    reflective_ptr->set_exp_s(100);
    reflective_ptr->set_kr(0.20f);
    reflective_ptr->set_cr(RGBColor(0.5, 0.5, 0.5));

	auto * sphere_ptr1 = new Sphere();
	sphere_ptr1->set_center(Point3D(0, 0.0, 0.0));
//	sphere_ptr1->set_material(phong_ptr);
	sphere_ptr1->set_material(reflective_ptr);
	sphere_ptr1->set_radius(10.0);
	add_object(sphere_ptr1);

	auto * matte_ptr1 = new Matte();
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 0, 1);

	auto* sphere_ptr2 = new Sphere();
	sphere_ptr2->set_center(Point3D(0.0, 0.0, 20.0));
	sphere_ptr2->set_material(matte_ptr1);
	sphere_ptr2->set_radius(10.0);
	add_object(sphere_ptr2);

    //// ================ Ground Plane ===================== ////

	auto * matte_ptr01 = new Matte();
	matte_ptr01->set_ka(0.25);
	matte_ptr01->set_kd(0.65);
	matte_ptr01->set_cd(0.5, 0.5, 0.5);

	Plane* plane_ptr01 = new Plane(Point3D(0, -10, 0), Normal(0, 1, 0));
	plane_ptr01->set_material(matte_ptr01);
	add_object(plane_ptr01);

    //// ================ Right Plane ===================== ////

    auto * matte_ptr02 = new Matte();
    matte_ptr02->set_ka(0.25);
    matte_ptr02->set_kd(0.65);
    matte_ptr02->set_cd(1, 0, 0);

    Plane* plane_ptr02 = new Plane(Point3D(0, 0, -60), Normal(0, 0, 1));
    plane_ptr02->set_material(matte_ptr02);
//    plane_ptr02->set_material(reflective_ptr);
    add_object(plane_ptr02);

    //// ================ Top Plane ===================== ////

    auto * matte_ptr03 = new Matte();
    matte_ptr03->set_ka(0.25);
    matte_ptr03->set_kd(0.65);
    matte_ptr03->set_cd(0.0, 0.0, 1.0);

    Plane* plane_ptr03 = new Plane(Point3D(0, 60, 0), Normal(0, -1, 0));
    plane_ptr03->set_material(matte_ptr03);
    add_object(plane_ptr03);

    //// ================ Left Plane ===================== ////

    auto * matte_ptr04 = new Matte();
    matte_ptr04->set_ka(0.25);
    matte_ptr04->set_kd(0.65);
    matte_ptr04->set_cd(0, 1, 0);

    Plane* plane_ptr4 = new Plane(Point3D(0, 0, 60), Normal(0, 0, -1));
    plane_ptr4->set_material(matte_ptr04);
    add_object(plane_ptr4);

    //// ================ Back Plane ===================== ////

    auto * matte_ptr05 = new Matte();
    matte_ptr05->set_ka(0.25);
    matte_ptr05->set_kd(0.65);
    matte_ptr05->set_cd(0, 1, 1);

    Plane* plane_ptr5 = new Plane(Point3D(-10, 0, 0), Normal(1, 0, 0));
    plane_ptr5->set_material(matte_ptr05);
    add_object(plane_ptr5);


}

#elif LIGHTBOX == 1

void World::build()
{
    vp.set_hres(1000);
    vp.set_vres(800);
    vp.set_pixel_size(1.0);
    vp.set_samples(5);
    vp.set_gamma(1.0);
    vp.set_gamut_display(true);
    vp.set_max_depth(2);

    background_color = black;

    auto * ambient_ptr = new Ambient();
    ambient_ptr->scale_radiance(2.0);
    set_ambient_light(ambient_ptr);

    //// ================ Camera ===================== ////

    auto * pinhole_ptr = new Orthographic;//ThinLens(40.0, 40.0, 1400.0, 20.0, new MultiJittered(5));
    pinhole_ptr->set_eye(1400, 300, 00);
    pinhole_ptr->set_lookat(0, 0, 0);
//    pinhole_ptr->set_view_distance(1200);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);

    //// ============================================= ////

    auto * point_light_ptr = new PointLight();
    point_light_ptr->set_location(240, 1240, 240);
    point_light_ptr->scale_radiance(2.0);
//    add_light(point_light_ptr);

    auto * point_light_ptr2 = new PointLight();
    point_light_ptr2->set_location(0, 1840, 0);
    point_light_ptr2->scale_radiance(2.0);
    add_light(point_light_ptr2);

    auto* phong_ptr = new Phong();
    phong_ptr->set_ka(0.15);
    phong_ptr->set_ca(1.0, 0.0, 0.0);
    phong_ptr->set_kd(0.85);
    phong_ptr->set_cd(0.5, 0.5, 0.5);
    phong_ptr->set_ks(0.3);
    phong_ptr->set_exp_s(100);

    auto* reflective_ptr = new Reflective();
    reflective_ptr->set_ka(0.15);
    reflective_ptr->set_kd(0.85);
    reflective_ptr->set_ca(0.5, 1.0, 1.0);
    reflective_ptr->set_cd(0.5, 0.5, 0.5);
    reflective_ptr->set_ks(0.3);
    reflective_ptr->set_exp_s(10);
    reflective_ptr->set_kr(0.20f);
    reflective_ptr->set_cr(white);

    auto* sphere_ptr1 = new Sphere();
    sphere_ptr1->set_center(Point3D(0, 130.0, 0.0));
//	sphere_ptr1->set_material(phong_ptr);
    sphere_ptr1->set_material(reflective_ptr);
    sphere_ptr1->set_radius(140.0);
    add_object(sphere_ptr1);

    auto* matte_ptr1 = new Matte();
    matte_ptr1->set_ka(0.25);
    matte_ptr1->set_kd(0.65);
    matte_ptr1->set_cd(1, 0, 1);

    auto* sphere_ptr2 = new Sphere();
    sphere_ptr2->set_center(Point3D(230.0, 110.0, 230.0));
    sphere_ptr2->set_material(phong_ptr);
    sphere_ptr2->set_radius(120.0);
    add_object(sphere_ptr2);


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

#endif
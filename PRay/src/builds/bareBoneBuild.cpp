
#include "World/World.h"
#include "Objects/Plane.h"
#include "Camera/PinHole.h"

#include "Lights/Ambient.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/Phong.h"

#include "Objects/Box.h"
#include "Objects/Triangle.h"
#include "Objects/Disk.h"

void World::build() 
{
	vp.set_hres(1000);
	vp.set_vres(800);
	vp.set_pixel_size(1.0);
	vp.set_samples(5);
	vp.set_gamma(1.0);
	vp.set_gamut_display(true);

	background_color = red;

	auto * ambient_ptr = new Ambient();
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	auto * pinhole_ptr = new Pinhole();
	pinhole_ptr->set_eye(50, 50, 0);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(400);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	auto * point_light_ptr = new PointLight();
	point_light_ptr->set_location(50, 50, 50);
	point_light_ptr->scale_radiance(3.0);
	add_light(point_light_ptr);

	auto * phong_ptr = new Phong();
	phong_ptr->set_ka(0.15);
	phong_ptr->set_kd(0.85);
	phong_ptr->set_cd(1.0, 1.0, 0.0);
	phong_ptr->set_ks(0.3);
	phong_ptr->set_exp_s(100);

	auto * sphere_ptr1 = new Sphere();
	sphere_ptr1->set_center(Point3D(0.0, 5.0, 0.0));
	sphere_ptr1->set_material(phong_ptr);
	sphere_ptr1->set_radius(10.0);
	add_object(sphere_ptr1);

	auto * matte_ptr1 = new Matte();
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 0, 1);

	auto* sphere_ptr2 = new Sphere();
	sphere_ptr2->set_center(Point3D(0.0, 5.0, 20.0));
	sphere_ptr2->set_material(matte_ptr1);
	sphere_ptr2->set_radius(10.0);
	add_object(sphere_ptr2);

	auto * matte_ptr2 = new Matte();
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(0, 1, 1);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);


//	auto * matte_ptr3 = new Matte;
//	matte_ptr3->set_ka(0.25);
//	matte_ptr3->set_kd(0.65);
//	matte_ptr3->set_cd(0, 0, 1);

//	Disk* newObj_ptr = new Disk(Point3D(0, 50, 100), 100.0, Normal(0, 0, 1));
//	newObj_ptr->set_material(matte_ptr3);
//	add_object(newObj_ptr);


}
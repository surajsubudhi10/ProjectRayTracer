
#include "../World/World.h"
#include "../Objects/Plane.h"
#include "../Camera/PinHole.h"

#include "../Lights/Ambient.h"
#include "../Lights/PointLight.h"

#include "../Materials/Matte.h"

void World::build() 
{
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = red;

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(300, 400, 500);
	pinhole_ptr->set_lookat(0, 0, -50);
	pinhole_ptr->set_view_distance(400);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* point_light_ptr = new PointLight;
	point_light_ptr->set_location(100, 50, 150);
	point_light_ptr->scale_radiance(3.0);
	add_light(point_light_ptr);


	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 1, 0);

	//Sphere* sphere_ptr1 = new Sphere();
	//sphere_ptr1->set_center(Point3D(0.0, 0.0, 0.0));
	////sphere_ptr1->set_color(0.5, 0.7, 0.1);
	//sphere_ptr1->set_radius(85.0);
	//add_object(sphere_ptr1);

	Sphere* sphere_ptr2 = new Sphere();
	sphere_ptr2->set_center(Point3D(0.0, 90.0, 0.0));
	//sphere_ptr2->set_color(1.0, 0.0, 1.0);
	sphere_ptr2->set_material(matte_ptr1);
	sphere_ptr2->set_radius(50.0);
	add_object(sphere_ptr2);

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(0, 1, 1);

	Plane* plane_ptr = new Plane(Point3D(0, 0, -85), Normal(0, 0, 1));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);

}
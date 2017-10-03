

#include "PointLight.h"
#include "../World/World.h"

PointLight::PointLight(void)
	: Light(),
	ls(1.0), color(1.0), location(0)
{}

PointLight::PointLight(const PointLight& pl)
	: Light(pl),
	ls(pl.ls), color(pl.color), location(pl.location)
{}

PointLight& PointLight::operator= (const PointLight& pl) 
{
	if (this == &pl)
		return (*this);

	Light::operator= (pl);

	ls = pl.ls;
	color = pl.color;
	location = pl.location;

	return (*this);
}

Light* PointLight::clone(void) const 
{
	return (new PointLight(*this));
}

Vector3D PointLight::get_direction(ShadeRec& sr) 
{
	Vector3D temp = location;
	Vector3D temp2 = location - sr.hit_point;
	Vector3D temp3 = temp2.hat();
	return ((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr) 
{
	return (ls * color);
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const 
{
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);

	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return (true);

	return (false);
}
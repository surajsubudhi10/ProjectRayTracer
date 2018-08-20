

#include "Lights/PointLight.h"
#include "World/World.h"

PointLight::PointLight()
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

Light* PointLight::clone() const
{
	return (new PointLight(*this));
}

Vector3D PointLight::get_direction(ShadeRec& sr) 
{
	return ((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr) 
{
	return (ls * color);
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const 
{
	auto t = (float) kHugeValue;
	auto num_objects = (int)sr.w.objects.size();
	auto d = static_cast<float>(location.distance(ray.o));

	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d) {
			return true;
		}
	}
	return false;
}
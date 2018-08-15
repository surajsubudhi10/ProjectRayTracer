#pragma once

#include "Light.h"
#include "../Utils/Vector3D.h"

class PointLight : public Light {
public:

	PointLight();
	PointLight(const PointLight& pl);

	PointLight& operator= (const PointLight& pl);
	Light* clone() const override;

	void scale_radiance(float b);
	void set_color(float c);
	void set_color(const RGBColor& c);
	void set_color(float r, float g, float b);
	void set_location(float x, float y, float z);

	Vector3D get_direction(ShadeRec& sr) override;
	RGBColor L(ShadeRec& sr) override;
	bool in_shadow(const Ray& ray, const ShadeRec& sr) const override;

private:
	float ls;
	RGBColor color;
	Point3D location;
};

typedef std::shared_ptr<PointLight> PointLightPtr;

// ------------------------------------------------------------------------------- scale_radiance

inline void PointLight::scale_radiance(float b)
{
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void PointLight::set_color(float c)
{
	color.r = c;
	color.g = c; 
	color.b = c;
}

// ------------------------------------------------------------------------------- set_color

inline void PointLight::set_color(const RGBColor& c) 
{
	color = c;
}

// ------------------------------------------------------------------------------- set_color

inline void PointLight::set_color(float r, float g, float b)
{
	color.r = r;
	color.g = g; 
	color.b = b;
}

inline void PointLight::set_location(float x, float y, float z)
{
	location.x = x;
	location.y = y;
	location.z = z;
}

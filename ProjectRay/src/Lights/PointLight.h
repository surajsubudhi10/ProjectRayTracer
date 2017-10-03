#pragma once

#include "Light.h"
#include "../Utils/Vector3D.h"

class PointLight : public Light {
public:

	PointLight(void);
	PointLight(const PointLight& pl);

	PointLight& operator= (const PointLight& pl);
	virtual Light* clone(void) const;

	void scale_radiance(const float b);
	void set_color(const float c);
	void set_color(const RGBColor& c);
	void set_color(const float r, const float g, const float b);
	void set_location(const float x, const float y, const float z);

	virtual Vector3D get_direction(ShadeRec& sr) override;
	virtual RGBColor L(ShadeRec& sr) override;
	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:

	float ls;
	RGBColor color;
	Point3D location;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void PointLight::scale_radiance(const float b) 
{
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void PointLight::set_color(const float c) 
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

inline void PointLight::set_color(const float r, const float g, const float b) 
{
	color.r = r;
	color.g = g; 
	color.b = b;
}

inline void PointLight::set_location(const float x, const float y, const float z) 
{
	location.x = x;
	location.y = y;
	location.z = z;
}

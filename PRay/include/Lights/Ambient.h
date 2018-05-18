#pragma once

#include "Light.h"

class Ambient : public Light
{
public:

	Ambient();
	Ambient(const Ambient& amb);
	~Ambient() override;

	Ambient& operator= (const Ambient& rhs);
	Light* clone() const override;

	void scale_radiance(float b);
	void set_color(float c);
	void set_color(const RGBColor& c);
	void set_color(float r, float g, float b);

	Vector3D get_direction(ShadeRec& sr) override;
	RGBColor L(ShadeRec& sr) override;
	bool in_shadow(const Ray& ray, const ShadeRec& sr) const override;

protected:

	float ls;
	RGBColor color;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void Ambient::scale_radiance(const float b) 
{
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void Ambient::set_color(const float c) 
{
	color.r = c;
	color.g = c;
	color.b = c;
}

// ------------------------------------------------------------------------------- set_color

inline void Ambient::set_color(const RGBColor& c) 
{
	color = c;
}

// ------------------------------------------------------------------------------- set_color

inline void Ambient::set_color(const float r, const float g, const float b) 
{
	color.r = r; color.g = g; color.b = b;
}

inline bool Ambient::in_shadow(const Ray& ray, const ShadeRec& sr) const 
{
	return false;
}


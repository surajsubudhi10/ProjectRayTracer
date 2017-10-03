#pragma once


#include "Light.h"

class Ambient : public Light {
public:

	Ambient(void);
	Ambient(const Ambient& amb);
	~Ambient(void);

	Ambient& operator= (const Ambient& rhs);
	virtual Light* clone(void) const;

	void scale_radiance(const float b);

	void set_color(const float c);
	void set_color(const RGBColor& c);
	void set_color(const float r, const float g, const float b);

	virtual Vector3D get_direction(ShadeRec& sr) override;
	virtual RGBColor L(ShadeRec& sr) override;
	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const ;

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


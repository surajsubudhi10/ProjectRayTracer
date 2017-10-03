#pragma once

#include "BRDF.h"
#include "../Samplers/Sampler.h"

class Lambertian : public BRDF 
{
public:
	Lambertian(void);
	Lambertian(const Lambertian& lamb);
	~Lambertian(void);

	Lambertian& operator= (const Lambertian& rhs);
	virtual BRDF* clone(void) const;

	void set_kd(const float the_kd);
	void set_cd(const RGBColor cd);
	void set_cd(const float r, const float g, const float b);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;


private:

	float kd;		// diffuse coefficient
	RGBColor cd;	// diffuse color
};

inline void
Lambertian::set_kd(const float the_kd) 
{
	kd = the_kd;
}

inline void Lambertian::set_cd(const RGBColor the_cd) 
{
	cd = the_cd;
}

inline void
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}


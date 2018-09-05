#pragma once

#include "BRDF.h"
#include "../Samplers/Sampler.h"

class Lambertian : public BRDF 
{
public:
	Lambertian();
	Lambertian(const Lambertian& lamb);
	~Lambertian() override;

	Lambertian& operator= (const Lambertian& rhs);
	BRDF* clone() const override;

	void set_kd(float the_kd);
	void set_cd(const RGBColor &the_cd);
	void set_cd(float r, float g, float b);

	RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const override;
	RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const override;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
	RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

private:

	float kd;		// diffuse coefficient
	RGBColor cd;	// diffuse color
};

inline void Lambertian::set_kd(const float the_kd) {
	if(kd > 1.0f) kd = 1.0f;
	if(kd < 0.0f) kd = 0.0f;
	kd = the_kd;
}

inline void Lambertian::set_cd(const RGBColor &the_cd) {
	cd = the_cd;
}

inline void Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}
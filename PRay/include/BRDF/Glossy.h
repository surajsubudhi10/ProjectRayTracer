#pragma once

#include "BRDF.h"

class Glossy : public BRDF
{
public:
	Glossy();
	Glossy(const Glossy& gloss);
	~Glossy();

	Glossy& operator= (const Glossy& rhs);
	BRDF* clone() const override;

	void set_ks(float the_ks);
	void set_exp(float the_exp);
	void set_cs(const RGBColor &the_cs);
	void set_cs(float r, float g, float b);
	void set_samples(int num_samples, float exp);
	void set_normal(const Normal& n);

	// Not used, but abstract without
	RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const override;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
	RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;
	RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const override;

private:

	float ks;			// specular coefficient
	RGBColor cs;		// specular color
	float exp;			// specular exponent
	SamplerPtr sampler_ptr;
};

inline void Glossy::set_ks(const float the_ks) 
{
	ks = the_ks;
}

inline void Glossy::set_cs(const RGBColor &the_cs)
{
	cs = the_cs;
}

inline void Glossy::set_cs(const float r, const float g, const float b) 
{
	cs.r = r; cs.g = g, cs.b = b;
}

inline void Glossy::set_exp(const float the_exp) 
{
	exp = the_exp;
}


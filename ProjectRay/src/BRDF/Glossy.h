#pragma once

#include "BRDF.h"

class Glossy : public BRDF {
public:
	Glossy(void);
	Glossy(const Glossy& lamb);
	~Glossy(void);

	Glossy& operator= (const Glossy& rhs);
	virtual BRDF* clone(void) const;

	void set_ks(const float the_ks);
	void set_exp(const float the_exp);
	void set_cs(const RGBColor cd);
	void set_cs(const float r, const float g, const float b);
	void set_samples(const int num_samples, const float exp);
	void set_normal(const Normal& n);

	// Not used, but abstract without
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;

private:

	float ks;			// specular coefficient
	RGBColor cs;		// specular color
	float exp;			// specular exponent
	Sampler* sampler_ptr;
};

inline void Glossy::set_ks(const float the_ks) 
{
	ks = the_ks;
}

inline void Glossy::set_cs(const RGBColor the_cs) 
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


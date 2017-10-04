#pragma once

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/Glossy.h"

class Phong : public Material {
public:

	Phong(void);
	Phong(const Phong&);
	~Phong(void);

	Phong& operator= (const Phong&);
	virtual Material* clone(void) const;

	virtual RGBColor shade(ShadeRec& sr);

	void set_ka(const float ka);
	void set_kd(const float kd);
	void set_ks(const float ks);
	void set_ca(const float r, const float g, const float b);
	void set_cd(const float r, const float g, const float b);
	void set_cd(const RGBColor& c);
	void set_cs(const float r, const float g, const float b);
	
	void set_exp_s(const float exp_s);
	void set_exp(const float exp_s);
	void set_k(const float k);
	void set_c(const float r, const float g, const float b);
	void set_c(const RGBColor& c);

	virtual RGBColor area_light_shade(ShadeRec& sr);

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	Glossy* specular_brdf;
};

inline void Phong::set_exp(const float exp_s) 
{
	set_exp_s(exp_s);
}

inline void Phong::set_cd(const RGBColor& c) 
{
	set_cd(c.r, c.b, c.g);
}


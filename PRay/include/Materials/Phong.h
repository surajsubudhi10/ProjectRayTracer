#pragma once

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/Glossy.h"

class Phong : public Material {
public:

	Phong();
	Phong(const Phong&);

	virtual ~Phong();

	Phong& operator= (const Phong&);
	Material* clone() const override;

	RGBColor shade(ShadeRec& sr) override;

	void set_ka(float ka);
	void set_kd(float kd);
	void set_ks(float ks);
	void set_ca(float r, float g, float b);
	void set_cd(float r, float g, float b);
	void set_cd(const RGBColor& c);
	void set_cs(float r, float g, float b);
	
	void set_exp_s(float exp_s);
	void set_exp(float exp_s);
	void set_k(float k);
	void set_c(float r, float g, float b);
	void set_c(const RGBColor& c);

	RGBColor area_light_shade(ShadeRec& sr) override;

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	Glossy* 	specular_brdf;
};

inline void Phong::set_exp(float exp_s)
{
	set_exp_s(exp_s);
}

inline void Phong::set_cd(const RGBColor& c)
{
	set_cd(c.r, c.b, c.g);
}

#pragma once


#include "Material.h"
#include "../BRDF/Lambertian.h"

class Matte : public Material {
public:

	Matte();
	Matte(const Matte& m);
	~Matte();

	Matte& operator= (const Matte& m);
	Material* clone() const override;

	void set_ka(float k);
	void set_kd(float k);
	void set_cd(const RGBColor& c);
	void set_cd(float r, float g, float b);
	void set_sampler(Sampler* sampl_ptr);

	RGBColor shade(ShadeRec& sr) override;
	RGBColor area_light_shade(ShadeRec& sr) override;
	RGBColor path_shade(ShadeRec& sr) override;
	RGBColor global_shade(ShadeRec& sr) override;

private:

	Lambertian*	ambient_ptr;
	Lambertian* diffuse_ptr;
};

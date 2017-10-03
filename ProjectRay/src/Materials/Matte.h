#pragma once


#include "Material.h"
#include "../BRDF/Lambertian.h"

class Matte : public Material {
public:

	Matte(void);
	Matte(const Matte& m);
	~Matte(void);

	Matte& operator= (const Matte& m);
	virtual Material* clone(void) const;

	void set_ka(const float k);
	void set_kd(const float k);
	void set_cd(const RGBColor& c);
	void set_cd(const float r, const float g, const float b);
	
	void set_sampler(Sampler* sampl_ptr);
	
	virtual RGBColor shade(ShadeRec& sr);
	virtual RGBColor area_light_shade(ShadeRec& sr);
	virtual RGBColor path_shade(ShadeRec& sr);
	virtual RGBColor global_shade(ShadeRec& sr);

private:

	Lambertian*	ambient_ptr;
	Lambertian* diffuse_ptr;
};

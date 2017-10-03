#pragma once

#include "../Utils/RGBColor.h"
#include "../Utils/Vector3D.h"
#include "../Utils/ShadeRec.h"
#include "../Samplers/Sampler.h"

class BRDF {
public:

	BRDF(void);
	BRDF(const BRDF& brdf);
	
	virtual BRDF* clone(void)const = 0;
	virtual	~BRDF(void);
	
	BRDF& operator= (const BRDF& rhs);
	void set_sampler(Sampler* sPtr);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const = 0;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const = 0;

protected:

	Sampler* sampler_ptr;
};

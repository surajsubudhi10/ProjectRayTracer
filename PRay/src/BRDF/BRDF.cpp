#include <utility>
#include "BRDF/BRDF.h"

BRDF::BRDF() : sampler_ptr(nullptr)
{}

BRDF::BRDF(const BRDF& brdf) 
{
	if (brdf.sampler_ptr) {
		sampler_ptr = brdf.sampler_ptr->clone(); 
	}
	else {
		sampler_ptr = nullptr;
	}
}

BRDF& BRDF::operator= (const BRDF& rhs) 
{
	if (this == &rhs)
		return (*this);

	if (rhs.sampler_ptr) {
		sampler_ptr = rhs.sampler_ptr->clone();	
	}

	return (*this);
}


BRDF::~BRDF()
{}

void BRDF::set_sampler(SamplerPtr sPtr)
{
	sampler_ptr = std::move(sPtr);
	sampler_ptr->map_samples_to_hemisphere(1);	
}

// ------------------------------------------------------------------------ f

RGBColor BRDF::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const 
{
	return (black);
}

// ------------------------------------------------------------------------ sample_f

RGBColor BRDF::sample_f(const ShadeRec& sr, Vector3D& wo, const Vector3D& wi) const 
{
	return (black);
}

// ------------------------------------------------------------------------ sample_f

//RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
//{
//	return (black);
//}


// ------------------------------------------------------------------------ rho	

RGBColor BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const 
{
	return (black);
}
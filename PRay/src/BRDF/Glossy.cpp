

#include <math.h>
#include "BRDF/Glossy.h"
#include "Samplers/MultiJittered.h"

Glossy::Glossy()
	: BRDF(), ks(0.0),
	  cs(1.0), exp(1.0),
	  sampler_ptr(nullptr)
{}

Glossy::Glossy(const Glossy& gloss)
	: BRDF(gloss), ks(gloss.ks),
	  cs(gloss.cs), exp(gloss.exp)
{
	if (gloss.sampler_ptr)
		sampler_ptr = gloss.sampler_ptr->clone();
	else
		sampler_ptr = nullptr;
}

Glossy& Glossy::operator= (const Glossy& rhs) 
{
	if (this == &rhs)
		return (*this);

	BRDF::operator= (rhs);

	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return (*this);
}

Glossy::~Glossy()
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}

BRDF* Glossy::clone() const
{
	return (new Glossy(*this));
}

// just Phong
RGBColor Glossy::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const 
{
	RGBColor L;
	auto ndotwi = static_cast<float>(sr.normal * wi);
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	auto rdotwo = static_cast<float>(r * wo);

	if (rdotwo > 0.0)
		L = ks * cs * powf(rdotwo, exp);

	return (L);
}

RGBColor Glossy::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const 
{
	return (black);
}

RGBColor Glossy::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const 
{

	auto ndotwo = static_cast<float>(sr.normal * wo);
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

	const Vector3D &w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.normalize();
	Vector3D v = u ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction

	if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	auto phong_lobe = static_cast<float>(pow(r * wi, exp));
	pdf = static_cast<float>(phong_lobe * (sr.normal * wi));

	return (ks * cs * phong_lobe);

}

RGBColor Glossy::rho(const ShadeRec& sr, const Vector3D& wo) const 
{
	return (black);
}

void Glossy::set_samples(const int num_samples, const float exp) 
{
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}


#include "Glossy.h"
#include "../Samplers/MultiJittered.h"

Glossy::Glossy(void)
	: BRDF(), ks(0.0),
	  cs(1.0), exp(1.0),
	  sampler_ptr(NULL)
{}

Glossy::Glossy(const Glossy& lamb)
	: BRDF(lamb), ks(lamb.ks),
	  cs(lamb.cs), exp(lamb.exp)
{
	if (lamb.sampler_ptr)
		sampler_ptr = lamb.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
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
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return (*this);
}

Glossy::~Glossy(void) 
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

BRDF* Glossy::clone(void) const 
{
	return (new Glossy(*this));
}

// just Phong
RGBColor Glossy::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const 
{
	RGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
	float rdotwo = r * wo;

	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp);

	return (L);
}

RGBColor Glossy::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const 
{
	return (black);
}

RGBColor Glossy::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const 
{

	float ndotwo = sr.normal * wo;
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.normalize();
	Vector3D v = u ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction

	if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	float phong_lobe = pow(r * wi, exp);
	pdf = phong_lobe * (sr.normal * wi);

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
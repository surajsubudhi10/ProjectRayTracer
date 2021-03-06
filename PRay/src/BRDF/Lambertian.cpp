#include "BRDF/Lambertian.h"

Lambertian::Lambertian()
	: BRDF(),
	kd(0.0),
	cd(0.0)
{}

Lambertian::Lambertian(const Lambertian& lamb)
	: BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{
}

Lambertian::~Lambertian()
= default;

Lambertian& Lambertian::operator= (const Lambertian& rhs) 
{
	if (this == &rhs)
		return (*this);

	BRDF::operator= (rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return (*this);
}


BRDF* Lambertian::clone() const
{
	return (new Lambertian(*this));
}


RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const 
{
	return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const 
{
	return (black);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const 
{
	return (kd * cd);
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const 
{
	Vector3D w = Vector3D(sr.normal);
	Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();
	pdf = static_cast<float>(sr.normal * wi * invPI);

	return (kd * cd * invPI);
}
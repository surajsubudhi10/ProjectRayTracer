
#include "Objects/Sphere.h"
#include <cmath>

const double Sphere::kEpsilon = 0.001;

// ---------------------------------------------------------------- default constructor

Sphere::Sphere()
	: GeometricObject(),
	  center(0.0), radius(1.0),
	  inv_area(static_cast<float>(1 / (4 * PI * exp2(radius)))), sampler_ptr(nullptr)
{}

// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
	: GeometricObject(),
	  center(c), radius(r),
	  inv_area(static_cast<float>(1 / (4 * PI * exp2(radius)))), sampler_ptr(nullptr)
{}

// ---------------------------------------------------------------- clone

Sphere* Sphere::clone() const
{
	return (new Sphere(*this));
}

// ---------------------------------------------------------------- copy constructor

Sphere::Sphere(const Sphere& sphere)
	: GeometricObject(sphere),
	center(sphere.center), radius(sphere.radius), inv_area(sphere.inv_area) 
{

	if (sphere.sampler_ptr)
		sampler_ptr = sphere.sampler_ptr->clone();
	else
		sampler_ptr = nullptr;
}

// ---------------------------------------------------------------- assignment operator

Sphere& Sphere::operator= (const Sphere& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center = rhs.center;
	radius = rhs.radius;
	inv_area = rhs.inv_area;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return (*this);
}

// ---------------------------------------------------------------- destructor

Sphere::~Sphere()
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}

//---------------------------------------------------------------- hit

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{

	double 		t;
	Vector3D	temp = ray.o - center;
	double 		a = ray.d * ray.d;
	double 		b = 2.0 * temp * ray.d;
	double 		c = temp * temp - radius * radius;
	double 		disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.hit_point = ray.o + t * ray.d;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.hit_point = ray.o + t * ray.d;
			return (true);
		}
	}

	return (false);
}

bool Sphere::shadow_hit(const Ray& ray, float& tmin) const 
{

	if (!shadows)
		return false;

	float 		t;
	Vector3D	temp = ray.o - center;
	double 		a = ray.d * ray.d;
	double 		b = 2.0 * temp * ray.d;
	double 		c = temp * temp - radius * radius;
	double 		disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = static_cast<float>((-b - e) / denom);    // smaller root

		if (t > kEpsilon)
		{
			tmin = t;
			return (true);
		}

		t = static_cast<float>((-b + e) / denom);    // larger root

		if (t > kEpsilon)
		{
			tmin = t;
			return (true);
		}
	}

	return (false);
}

// ---------------------------------------------------------------- setSampler

void Sphere::set_sampler(Sampler* sampler) 
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_sphere();
}


// ---------------------------------------------------------------- sample


Point3D Sphere::sample()
{
	Point3D sample_point = sampler_ptr->sample_sphere();
	return (center + Vector3D(sample_point * radius));// + sample_point.y * radius + sample_point.z * radius);
}


// ---------------------------------------------------------------- pdf

float Sphere::pdf(ShadeRec& sr) const 
{
	return (inv_area);
}

Normal Sphere::get_normal(const Point3D& p) const 
{
	Vector3D v = (center - p);
	v.normalize();

	return Normal(v);
}

BBox Sphere::get_bounding_box() const
{
	double delta = 0.0001;
	
	return (BBox(Point3D(center.x - radius - delta, center.y - radius - delta, center.z - radius - delta),
				 Point3D(center.x + radius + delta, center.y + radius + delta, center.z + radius + delta)));
}

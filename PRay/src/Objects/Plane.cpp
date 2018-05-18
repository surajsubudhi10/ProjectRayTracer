#include "Objects/Plane.h"

const double Plane::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Plane::Plane()
	: GeometricObject(),
	a(0.0),	n(0, 1, 0)
{}


// ----------------------------------------------------------------------  constructor

Plane::Plane(const Point3D& point, const Normal& normal)
	: GeometricObject(), a(point),n(normal)
{
	n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Plane::Plane(const Plane& plane)
	: GeometricObject(plane),
	a(plane.a),	n(plane.n)
{}


// ---------------------------------------------------------------- clone

Plane* Plane::clone() const
{
	return (new Plane(*this));
}


// ---------------------------------------------------------------- assignment operator

Plane& Plane::operator= (const Plane& rhs) 
{

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Plane::~Plane()
= default;


// ----------------------------------------------------------------- hit

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	float t = static_cast<float>((a - ray.o) * n / (ray.d * n));

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		//sr.local_hit_point = ray.o + t * ray.d;
		sr.hit_point = ray.o + t * ray.d;

		return (true);
	}

	return(false);
}

bool Plane::shadow_hit(const Ray& ray, float& tmin) const 
{

	if (!shadows)
		return false;

	float t = static_cast<float>((a - ray.o) * n / (ray.d * n));

	if (t > kEpsilon) {
		tmin = t;
		return (true);
	}

	return(false);
}
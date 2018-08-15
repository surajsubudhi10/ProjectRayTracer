
#include "Objects/Disk.h"

Disk::Disk()
	: GeometricObject(), center(1, 1, 1), radius(3), normal(0, 0, 1)
{}

Disk::Disk(const Point3D& c,const float r, const Normal& n)
	: GeometricObject(), center(c), radius(r), normal(n)
{}

Disk::Disk(const Disk& d) 
	: GeometricObject(d), center(d.center), radius(d.radius), normal(d.normal)
{}

Disk& Disk::operator=(const Disk& d) 
{
	if (this == &d)
		return (*this);

	GeometricObject::operator= (d);

	center = d.center;
	normal = d.normal;
	radius = d.radius;
	return (*this);
}

Disk* Disk::clone() const
{
	return (new Disk(*this));
}

bool Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	float t = static_cast<float>((center - ray.o) * normal / (ray.d * normal));

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < (radius*radius)) {
		tmin = t;
		sr.normal = normal;
//		sr.local_hit_point = p;
		sr.hit_point = p;
		return (true);
	}
	else
		return (false);
}

bool Disk::shadow_hit(const Ray& ray, float& tmin) const
{
	float t = static_cast<float>((center - ray.o) * normal / (ray.d * normal));

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < (radius*radius)) {
		tmin = t;
		return (true);
	}
	else
		return (false);
}

BBox Disk::get_bounding_box() const
{
	double delta = 0.0001;
	return (BBox(Point3D(center.x - radius - delta, center.y - radius - delta, center.z - radius - delta),
			   	 Point3D(center.x + radius + delta, center.y + radius + delta, center.z + radius + delta)));
}
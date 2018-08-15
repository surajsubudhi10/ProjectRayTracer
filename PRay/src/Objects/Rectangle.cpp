#include <Utils/Point2D.h>
#include <Samplers/MultiJittered.h>
#include <Samplers/Regular.h>
#include "Objects/Rectangle.h"
#include "Utils/Maths.h"

const double Rectangle::kEpsilon = 0.001;

Rectangle::Rectangle()
	: GeometricObject(), point(-1, 0, -1), a(0, 0, 2), b(2, 0, 0), normal(0, 1, 0)
{
    sampler_ptr = new MultiJittered(10);
}


Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
	: GeometricObject(), point(_p0), a(_a), b(_b)
{
	normal = a ^ b; // a.cross(b);
	normal.normalize();
    sampler_ptr = new MultiJittered(10);
}


Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
	: GeometricObject(),point(_p0), a(_a), b(_b)
{
	normal.normalize();
    sampler_ptr = new MultiJittered(10);
}

Rectangle::Rectangle(const Point3D& center, float length, float breadth)
    : GeometricObject()
{
    normal = Normal(0, 1, 0);
    point = center - Vector3D(length / 2.0f, 0.0f, breadth / 2.0f);
    a = Vector3D(0, 0, breadth);
    b = Vector3D(length, 0, 0);
    sampler_ptr = new MultiJittered(10);
}


Rectangle* Rectangle::clone() const
{
	return (new Rectangle(*this));
}


Rectangle::Rectangle(const Rectangle& r)
	: GeometricObject(r), point(r.point), a(r.a), b(r.b), normal(r.normal)
{
    sampler_ptr = r.sampler_ptr;
}


Rectangle& Rectangle::operator= (const Rectangle& rhs) 
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	point = rhs.point;
	a = rhs.a;
	b = rhs.b;
	normal = rhs.normal;
	sampler_ptr = rhs.sampler_ptr;

	return (*this);
}


Rectangle::~Rectangle()
{
    if(sampler_ptr != nullptr){
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}


BBox Rectangle::get_bounding_box() const
{
	double delta = 0.0001;

	return(BBox(min(point.x, point.x + a.x + b.x) - delta, max(point.x, point.x + a.x + b.x) + delta,
				min(point.y, point.y + a.y + b.y) - delta, max(point.y, point.y + a.y + b.y) + delta,
				min(point.z, point.z + a.z + b.z) - delta, max(point.z, point.z + a.z + b.z) + delta));
}


bool Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - point;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a.len_squared())
		return false;

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b.len_squared())
		return false;

	if(t < tmin)
	{
		tmin = t;
		sr.normal = normal;
		//sr.local_hit_point = p;
		sr.hit_point = p;
		sr.material_ptr = material_ptr;

		return true;
	}

	return false;
}

bool Rectangle::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - point;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a.len_squared())
		return false;

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b.len_squared())
		return (false);

	if(t < tmin) {
		tmin = static_cast<float>(t);
		return true;
	}

	return false;
}

// ---------------------------------------------------------------- sample
// returns a sample point on the rectangle
// Does not work well for skinny rectangles
// works best for squares

Point3D Rectangle::sample()
{
	Point2D sample_point = sampler_ptr->sample_unit_square();
	return (point + sample_point.x * a + sample_point.y * b);
}


//------------------------------------------------------------------ get_normal 

Normal Rectangle::get_normal(const Point3D& p) const 
{
	return (normal);
}


// ---------------------------------------------------------------- pdf

float Rectangle::pdf(const ShadeRec& sr) const
{
	return (1);
}

void Rectangle::set_sampler(int num_of_samples)
{
    if(num_of_samples == 1)
        sampler_ptr = new Regular();
    else{
        sampler_ptr = new MultiJittered(num_of_samples);
    }

    sampler_ptr->generate_samples();
}






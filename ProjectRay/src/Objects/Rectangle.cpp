#include "Rectangle.h"
#include "../Utils/Maths.h"

const double Rectangle::kEpsilon = 0.001;

// ----------------------------------------------------------------  default constructor

Rectangle::Rectangle(void)
	: GeometricObject(), point(-1, 0, -1), a(0, 0, 2), b(2, 0, 0), normal(0, 1, 0)
{
}


// ----------------------------------------------------------------  constructor
// this constructs the normal

Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
	: GeometricObject(), point(_p0), a(_a), b(_b)
{
	normal = a ^ b; // a.cross(b);
	normal.normalize();
}


// ----------------------------------------------------------------  constructor
// this has the normal as an argument

Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
	: GeometricObject(),point(_p0), a(_a), b(_b)
{
	normal.normalize();
}



// ---------------------------------------------------------------- clone

Rectangle* Rectangle::clone(void) const 
{
	return (new Rectangle(*this));
}


// ---------------------------------------------------------------- copy constructor

Rectangle::Rectangle(const Rectangle& r)
	: GeometricObject(r), point(r.point), a(r.a), b(r.b), normal(r.normal)
{

}



// ---------------------------------------------------------------- assignment operator

Rectangle& Rectangle::operator= (const Rectangle& rhs) 
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	point = rhs.point;
	a = rhs.a;
	b = rhs.b;
	normal = rhs.normal;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Rectangle::~Rectangle(void) {

}

//------------------------------------------------------------------ get_bounding_box 

BBox Rectangle::get_bounding_box(void) const 
{
	double delta = 0.0001;

	return(BBox(min(point.x, point.x + a.x + b.x) - delta, max(point.x, point.x + a.x + b.x) + delta,
				min(point.y, point.y + a.y + b.y) - delta, max(point.y, point.y + a.y + b.y) + delta,
				min(point.z, point.z + a.z + b.z) - delta, max(point.z, point.z + a.z + b.z) + delta));
}


//------------------------------------------------------------------ hit 

bool Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{

	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - point;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a.len_squared())
		return (false);

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b.len_squared())
		return (false);

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = p;

	return (true);
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
		return (false);

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b.len_squared())
		return (false);

	tmin = t;
	return (true);
}




// ---------------------------------------------------------------- sample
// returns a sample point on the rectangle
// Does not work well for skinny rectangles
// works best for squares

//Point3D Rectangle::sample(void) 
//{
//	Point2D sample_point = sampler_ptr->sample_unit_square();
//	return (p0 + sample_point.x * a + sample_point.y * b);
//}


//------------------------------------------------------------------ get_normal 

Normal Rectangle::get_normal(const Point3D& p) const 
{
	return (normal);
}


// ---------------------------------------------------------------- pdf

//float
//Rectangle::pdf(ShadeRec& sr) const {
//	return (inv_area);
//}






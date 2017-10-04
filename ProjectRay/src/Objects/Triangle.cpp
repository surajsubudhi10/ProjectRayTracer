#include "Triangle.h"
#include "../Utils/Maths.h"

Triangle::Triangle()
	: GeometricObject(), v0(0, 0, 0), v1(0, 0, 1), v2(1, 0, 0), normal(0, 1, 0)
{
}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
	: GeometricObject(), v0(a), v1(b), v2(c) 
{
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

Triangle::Triangle(const Triangle& tri)
	: GeometricObject(), v0(tri.v0), v1(tri.v1), v2(tri.v2), normal(tri.normal)
{
}


Triangle& Triangle::operator=(const Triangle& tri) 
{
	if (this == &tri)
		return (*this);

	v0 = tri.v0;
	v1 = tri.v1;
	v2 = tri.v2;
	normal = tri.normal;

	return (*this);
}

Triangle* Triangle::clone(void) const 
{
	return (new Triangle(*this));
}

BBox Triangle::get_bounding_box(void) const 
{
	double delta = 0.000001;

	return (BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta,
				 min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta,
				 min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta));
}


bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = ray.o + t * ray.d;

	return (true);

}

bool Triangle::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;
	return (true);
}
#include "Objects/Triangle.h"
#include "Utils/Maths.h"

Triangle::Triangle()
	: GeometricObject()//, v0(0, 0, 0), v1(0, 0, 1), v2(1, 0, 0), normal(0, 1, 0)
{
	v0.position = Point3D(0, 0, 0);
	v0.normal = Normal(0, 1, 0);

	v1.position = Point3D(0, 0, 1);
	v1.normal = Normal(0, 1, 0);

	v2.position = Point3D(1, 0, 0);
	v2.normal = Normal(0, 1, 0);
}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
	: GeometricObject()//, v0(a), v1(b), v2(c) 
{
	v0.position = a;
	v1.position = b;
	v2.position = c;

	auto normal = (v1.position - v0.position) ^ (v2.position - v0.position);
	normal.normalize();

	v0.normal = normal;
	v1.normal = normal;
	v2.normal = normal;
}

Triangle::Triangle(const Vertex & _v0, const Vertex & _v1, const Vertex & _v2) 
	: GeometricObject(), v0(_v0), v1(_v1), v2(_v2)
{}

Triangle::Triangle(const Triangle& tri)
	: GeometricObject(), v0(tri.v0), v1(tri.v1), v2(tri.v2)//, normal(tri.normal)
{}


Triangle& Triangle::operator=(const Triangle& tri) 
{
	if (this == &tri)
		return (*this);

	v0 = tri.v0;
	v1 = tri.v1;
	v2 = tri.v2;
	//normal = tri.normal;

	return (*this);
}

Triangle* Triangle::clone() const
{
	return (new Triangle(*this));
}

BBox Triangle::get_bounding_box() const
{
	double delta = 0.000001;

	return (BBox(min(min(v0.position.x, v1.position.x), v2.position.x) - delta, max(max(v0.position.x, v1.position.x), v2.position.x) + delta,
				 min(min(v0.position.y, v1.position.y), v2.position.y) - delta, max(max(v0.position.y, v1.position.y), v2.position.y) + delta,
				 min(min(v0.position.z, v1.position.z), v2.position.z) - delta, max(max(v0.position.z, v1.position.z), v2.position.z) + delta));
}


bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double a = v0.position.x - v1.position.x, b = v0.position.x - v2.position.x, c = ray.d.x, d = v0.position.x - ray.o.x;
	double e = v0.position.y - v1.position.y, f = v0.position.y - v2.position.y, g = ray.d.y, h = v0.position.y - ray.o.y;
	double i = v0.position.z - v1.position.z, j = v0.position.z - v2.position.z, k = ray.d.z, l = v0.position.z - ray.o.z;

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
		return false;

	if (beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return false;

	tmin = t;

	auto normal = (1.0 - (beta + gamma)) * v0.normal + beta * v1.normal + gamma * v2.normal;
	normal.normalize();
	sr.normal = normal;
    sr.material_ptr = material_ptr;
	sr.hit_point = ray.o + t * ray.d;

	return true;

}

bool Triangle::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	double a = v0.position.x - v1.position.x, b = v0.position.x - v2.position.x, c = ray.d.x, d = v0.position.x - ray.o.x;
	double e = v0.position.y - v1.position.y, f = v0.position.y - v2.position.y, g = ray.d.y, h = v0.position.y - ray.o.y;
	double i = v0.position.z - v1.position.z, j = v0.position.z - v2.position.z, k = ray.d.z, l = v0.position.z - ray.o.z;

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

	tmin = static_cast<float>(t);
	return (true);
}
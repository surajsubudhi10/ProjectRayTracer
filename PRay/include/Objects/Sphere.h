#pragma once

#include "GeometricObject.h"
#include "../Samplers/Sampler.h"

//-------------------------------------------------------------------------------- class Sphere

class Sphere : public GeometricObject {

public:

	Sphere();
	Sphere(Point3D center, double r);
	explicit Sphere(double rad);
	Sphere(const Sphere& sphere);
	~Sphere() override;

	Sphere* clone() const override;
	Sphere& operator= (const Sphere& sphere);

	void set_center(const Point3D& c);
	void set_center(double x, double y, double z);
	void set_radius(double r);
	void set_sampler(Sampler* sampler);

	bool hit(const Ray& ray, double& t, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;

	Point3D sample() override;
	float pdf(ShadeRec& sr) const;
	Normal get_normal(const Point3D& p) const override;
	BBox get_bounding_box() const override;

protected:

	Point3D 	center;   			// center coordinates as a point  
	double 		radius;				// the radius 
	Sampler*	sampler_ptr;		// sampler for being a light object
	static const double kEpsilon;   // for shadows and secondary rays
	float		inv_area;
};



inline void Sphere::set_center(const Point3D& c) 
{
	center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z) 
{
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Sphere::set_radius(const double r) 
{
	radius = r;
}

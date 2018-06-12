#pragma once

#include <Samplers/Sampler.h>
#include "GeometricObject.h"

class Rectangle : public GeometricObject
{
public:
	Rectangle();
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
    Rectangle(const Point3D& center, float length, float breadth);
	Rectangle(const Rectangle& r);
	~Rectangle() override;

	Rectangle* clone() const override;
	Rectangle& operator= (const Rectangle& rhs);

    void set_sampler(int num_of_samples);

	bool hit(const Ray& ray, double& t, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;

	Point3D	sample() override ;
	float pdf(const ShadeRec& sr) const override ;
	Normal get_normal(const Point3D& p) const override;
	BBox get_bounding_box() const override;

private:
	Point3D 		point;
	Vector3D		a;	
	Vector3D		b;	
	Normal			normal;
	Sampler*        sampler_ptr;

	static const double kEpsilon;
};

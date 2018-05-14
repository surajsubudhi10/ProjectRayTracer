#pragma once

#include "GeometricObject.h"

class Rectangle : public GeometricObject
{
public:
	Rectangle();
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
	Rectangle(const Rectangle& r);
	~Rectangle() override;

	Rectangle* clone() const override;
	Rectangle& operator= (const Rectangle& rhs);

	bool hit(const Ray& ray, double& t, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;

	//virtual Point3D	sample(void);
	//virtual float pdf(const ShadeRec& sr) const;
	Normal get_normal(const Point3D& p) const override;
	BBox get_bounding_box() const override;

private:
	Point3D 		point;
	Vector3D		a;	
	Vector3D		b;	
	Normal			normal;

	static const double kEpsilon;
};

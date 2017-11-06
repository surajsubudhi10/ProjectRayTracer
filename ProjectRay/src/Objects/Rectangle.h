#pragma once

#include "GeometricObject.h"

class Rectangle : public GeometricObject
{
public:
	Rectangle(void);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
	Rectangle(const Rectangle& r);
	virtual	~Rectangle(void);

	virtual Rectangle* clone(void) const override;
	Rectangle& operator= (const Rectangle& rhs);

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	bool shadow_hit(const Ray& ray, float& tmin) const;

	//virtual Point3D	sample(void);
	//virtual float pdf(const ShadeRec& sr) const;
	virtual Normal get_normal(const Point3D& p) const;
	
	virtual BBox get_bounding_box(void) const ;

private:
	Point3D 		point;
	Vector3D		a;	
	Vector3D		b;	
	Normal			normal;

	static const double kEpsilon;
};

#pragma once

#include "GeometricObject.h"

class Box : public GeometricObject {
public:
	Box();
	Box(const Point3D p0, const Point3D p1);
	Box(const Box& bbox);
	Box(double x0, double x1,
		double y0, double y1,
		double z0, double z1);

	Box& operator=(const Box& bbox);
	Box* clone() const override;

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;

	virtual Normal get_normal(int face_hit) const;
	BBox get_bounding_box() const override;

private:
	double x0, x1, y0, y1, z0, z1;
};


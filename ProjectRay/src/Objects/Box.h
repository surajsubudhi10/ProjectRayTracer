#pragma once

#include "GeometricObject.h"

class Box : public GeometricObject {
public:
	Box(void);
	Box(const Point3D p0, const Point3D p1);
	Box(const Box& bbox);
	Box(const double x0, const double x1,
		const double y0, const double y1,
		const double z0, const double z1);

	Box& operator=(const Box& bbox);
	virtual Box* clone(void) const;

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const override;

	virtual Normal get_normal(const int face_hit) const;
	virtual BBox get_bounding_box(void) const override;

private:
	double x0, x1, y0, y1, z0, z1;
};


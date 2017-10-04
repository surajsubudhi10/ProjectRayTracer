#pragma once

#include "Point3D.h"
#include "Ray.h"

class BBox {
public:

	double x0, x1, y0, y1, z0, z1;

	BBox(void);
	BBox(const Point3D p0, const Point3D p1);
	BBox(const BBox& bbox);
	BBox(const double x0, const double x1,
		 const double y0, const double y1,
		 const double z0, const double z1);
	
	~BBox(void);

	BBox& operator=(const BBox& bbox);
	BBox* clone(void) const;

	bool hit(const Ray& ray) const;
	bool inside(const Point3D& p) const;
};

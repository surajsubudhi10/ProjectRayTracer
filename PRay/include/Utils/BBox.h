#pragma once

#include "Point3D.h"
#include "Ray.h"

class BBox {
public:

	double x0, x1, y0, y1, z0, z1;

	BBox();
	BBox(Point3D p0, Point3D p1);
	BBox(const BBox& bbox);
	BBox(double x0, double x1,
		 double y0, double y1,
		 double z0, double z1);
	
	~BBox();

	BBox& operator=(const BBox& bbox);
	BBox* clone() const;

	BBox expand(const BBox& box);

	bool hit(const Ray& ray) const;
	bool inside(const Point3D& p) const;

	inline Vector3D min() { return Vector3D(x0, y0, z0);}
    inline Vector3D max() { return Vector3D(x1, y1, z1);}
};

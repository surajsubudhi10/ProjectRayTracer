#pragma once

#include "GeometricObject.h"

class Disk : public GeometricObject
{
public:
	Disk();
	Disk(const Point3D& cen, const float rad, const Normal& norm);
	Disk(const Disk& disk);

	virtual Disk* clone(void) const;
	Disk& operator= (const Disk& rhs);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const override;

	BBox get_bounding_box(void) const;

private:
	Point3D center;
	float radius;
	Normal normal;
};


#pragma once

#include "GeometricObject.h"

class Disk : public GeometricObject
{
public:
	Disk();
	Disk(const Point3D& cen, float rad, const Normal& norm);
    Disk(const Disk& disk);

	Disk* clone() const override;
	Disk& operator= (const Disk& rhs);

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;
	BBox get_bounding_box() const override;

private:
	Point3D center;
	float radius;
	Normal normal;
};

typedef std::shared_ptr<Disk> DiskPtr;


#pragma once

#include "GeometricObject.h"

struct Vertex 
{
	Point3D position;
	Normal  normal;
};

class Triangle : public GeometricObject 
{
public:
	Triangle();
	Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2);
	Triangle(const Vertex& _v0, const Vertex& _v1, const Vertex& _v2);
	Triangle(const Triangle& tri);

	Triangle& operator=(const Triangle& bbox);
	Triangle* clone() const override;

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;
	BBox get_bounding_box() const override;

public:
	Vertex v0;
	Vertex v1;
	Vertex v2;


	//Point3D v0, v1, v2;
	//Normal normal;
};

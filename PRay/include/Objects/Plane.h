#pragma once

#include "GeometricObject.h"

//-------------------------------------------------------------------- class Plane

class Plane : public GeometricObject {

public:

	Plane();   												// default constructor
	Plane(const Point3D& point, const Normal& normal);			// constructor	
	Plane(const Plane& plane); 									// copy constructor
	~Plane() override;

	Plane* clone() const override;
	Plane& operator= (const Plane& rhs);

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, float& tmin) const override;

private:

	Point3D 	a;   				// point through which plane passes 
	Normal 		n;					// normal to the plane

	static const double kEpsilon; //= 0.00001;   // for shadows and secondary rays
};

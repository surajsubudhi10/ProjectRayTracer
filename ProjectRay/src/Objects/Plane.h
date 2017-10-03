#pragma once

#include "GeometricObject.h"

//-------------------------------------------------------------------- class Plane

class Plane : public GeometricObject {

public:

	Plane(void);   												// default constructor
	Plane(const Point3D& point, const Normal& normal);			// constructor	
	Plane(const Plane& plane); 									// copy constructor
	virtual	~Plane(void);

	virtual Plane* clone(void) const;
	Plane& operator= (const Plane& rhs);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const override;

private:

	Point3D 	a;   				// point through which plane passes 
	Normal 		n;					// normal to the plane

	static const double kEpsilon; //= 0.00001;   // for shadows and secondary rays
};

// this file contains the definition of the class GeometricObject 

#include "../Utils/Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
	: color(black),
	//material_ptr(NULL),
	shadows(true)

{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject(const GeometricObject& object)
	: color(object.color),
	//material_ptr(NULL),
	shadows(object.shadows)
{}


// ---------------------------------------------------------------------- assignment operator

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {

	if (this == &rhs)
		return (*this);

	/*if (rhs.material_ptr) {
		material_ptr = rhs.material_ptr->clone();
	}*/

	color = rhs.color;
	shadows = rhs.shadows;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject(void) {}

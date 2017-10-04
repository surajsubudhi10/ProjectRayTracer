
#include "../Utils/Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
	: material_ptr(NULL), shadows(true)

{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject(const GeometricObject& object)
	: material_ptr(NULL), shadows(object.shadows)
{}


// ---------------------------------------------------------------------- assignment operator

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) 
{

	if (this == &rhs)
		return (*this);

	if (rhs.material_ptr) {
		material_ptr = rhs.material_ptr->clone();
	}

	shadows = rhs.shadows;
	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject(void) {}

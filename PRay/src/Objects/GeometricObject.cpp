
#include "Utils/Constants.h"
#include "Objects/GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject()
	: material_ptr(nullptr), shadows(true), bBox(get_bounding_box())
{}

// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject(const GeometricObject& object)
	: material_ptr(nullptr), shadows(object.shadows), bBox(object.bBox)
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
	bBox = rhs.bBox;
	return (*this);
}

// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject() = default;

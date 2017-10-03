
#include "Light.h"
#include "../Utils/Constants.h"

Light::Light(void)
	: shadows(true)
{}

Light::Light(const Light& ls)
	: shadows(ls.shadows)
{}

Light& Light::operator= (const Light& rhs) 
{
	if (this == &rhs)
		return (*this);

	shadows = rhs.shadows;

	return (*this);
}

Light::~Light(void) {}

RGBColor Light::L(ShadeRec& sr) 
{
	return (black);	
}
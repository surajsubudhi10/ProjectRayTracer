
#include "Ambient.h"
#include "../Utils/ShadeRec.h"

Ambient::Ambient(void)
	: Light(),
	ls(1.0),
	color(1.0)	
{}

Ambient::Ambient(const Ambient& amb)
	: Light(amb),
	ls(amb.ls),
	color(amb.color)
{}

Ambient& Ambient::operator= (const Ambient& amb) 
{
	if (this == &amb)
		return (*this);

	Light::operator= (amb);

	ls = amb.ls;
	color = amb.color;

	return (*this);
}

Light* Ambient::clone(void) const 
{
	return (new Ambient(*this));
}

Ambient::~Ambient(void) {}


Vector3D Ambient::get_direction(ShadeRec& sr) 
{
	return (Vector3D(0.0));					
}

RGBColor Ambient::L(ShadeRec& sr) 
{
	return (ls * color);
}
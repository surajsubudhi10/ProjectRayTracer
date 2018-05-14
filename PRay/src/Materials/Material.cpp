

#include "Materials/Material.h"
#include "Utils/Constants.h"

Material::Material()
	: shadows(true) 
{}

Material::Material(const Material& m)
	: shadows(m.shadows) 
{}

Material& Material::operator= (const Material& m) 
{
	if (this == &m)
		return *this;

	shadows = m.shadows;
	return *this;
}

Material::~Material() = default;


RGBColor Material::shade(ShadeRec& sr) 
{
	return (black);
}

RGBColor Material::area_light_shade(ShadeRec& sr) 
{
	return (black);
}

RGBColor Material::path_shade(ShadeRec& sr) 
{
	return (black);
}

RGBColor Material::global_shade(ShadeRec& sr) 
{
	return (black);
}

RGBColor Material::get_Le(ShadeRec& sr) const 
{
	return (black);
}
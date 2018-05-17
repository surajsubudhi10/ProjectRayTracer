#pragma once

#include "../Utils/ShadeRec.h"
#include "../Utils/RGBColor.h"

class Material {
public:
	
	Material();
	Material(const Material& m);

    virtual ~Material();
	
	Material& operator= (const Material& m);
	virtual Material* clone() const = 0;

	virtual RGBColor shade(ShadeRec& sr);
	virtual RGBColor area_light_shade(ShadeRec& sr);
	virtual RGBColor path_shade(ShadeRec& sr);
	virtual RGBColor global_shade(ShadeRec& sr);
	virtual RGBColor get_Le(ShadeRec& sr) const;

	void set_shadows(bool shadow);

protected:
	bool shadows;
};

inline void Material::set_shadows(bool shadow) 
{
	shadows = shadow;
}

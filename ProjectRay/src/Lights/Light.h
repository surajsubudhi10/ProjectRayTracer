#pragma once

#include "../Utils/Vector3D.h"
#include "../Utils/RGBColor.h"
#include "../Utils/Ray.h"
#include "../Utils/ShadeRec.h"

class Light {
public:

	Light(void);
	Light(const Light& l);
	virtual ~Light(void);

	Light& operator= (const Light& rhs);
	virtual Light* clone(void) const = 0;

	virtual Vector3D get_direction(ShadeRec& sr) = 0;
	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;

	virtual float G(const ShadeRec& sr) const;
	virtual float pdf(const ShadeRec& sr) const;
	virtual RGBColor L(ShadeRec& sr);

	bool casts_shadows() const;
	void set_shadows(const bool shadow);

protected:

	bool shadows;

};

inline void Light::set_shadows(const bool shadow) 
{
	shadows = shadow;
}


inline bool Light::casts_shadows() const 
{
	return shadows;
}

inline float Light::G(const ShadeRec& sr) const 
{
	return 1.0;
}

inline float Light::pdf(const ShadeRec& sr) const 
{
	return 1.0;
}


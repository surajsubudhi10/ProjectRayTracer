#pragma once

#include "../Utils/RGBColor.h"
#include "../Utils/Point3D.h"
#include "../Utils/Normal.h"
#include "../Utils/Ray.h"
#include "../Utils/ShadeRec.h"
#include "../Utils/BBox.h"
#include "../Utils/Constants.h"
#include "../Materials/Material.h"



class GeometricObject {

public:

	GeometricObject(void);									// default constructor
	GeometricObject(const GeometricObject& object);			// copy constructor

	virtual GeometricObject* clone(void) const = 0;
	virtual	~GeometricObject(void);
	
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const = 0;

	void set_material(Material* material);
	Material* get_material(void) const;

	void set_shadows(const bool shadow);
	bool get_shadows(void);

	virtual Point3D	sample(void);
	virtual float pdf(const ShadeRec& sr) const;
	virtual Normal get_normal(const Point3D& p) const;
	virtual BBox get_bounding_box(void) const;


protected:
	GeometricObject& operator= (const GeometricObject& rhs);
	
	mutable Material* material_ptr;
	bool shadows;
};



inline void GeometricObject::set_shadows(const bool do_shadow) 
{
	shadows = do_shadow;
}

inline bool GeometricObject::get_shadows(void) 
{
	return shadows;
}

inline void GeometricObject::set_material(Material* material) 
{
	material_ptr = material;
}

inline Material* GeometricObject::get_material(void) const 
{
	return material_ptr;
}

inline Point3D GeometricObject::sample(void) 
{
	return Point3D(1.0);
}

inline Normal GeometricObject::get_normal(const Point3D& p) const 
{
	return Normal(1.0);
}

inline float GeometricObject::pdf(const ShadeRec& sr) const 
{
	return (1.0);
}

inline BBox GeometricObject::get_bounding_box(void) const 
{
	return(BBox(-1, 1, -1, 1, -1, 1));
}





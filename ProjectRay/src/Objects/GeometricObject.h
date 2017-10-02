#pragma once


// this file contains the declaration of the class GeometricObject

#include "../Utils/RGBColor.h"
#include "../Utils/Point3D.h"
#include "../Utils/Normal.h"
#include "../Utils/Ray.h"
#include "../Utils/ShadeRec.h"
//#include "BBox.h"
#include "../Utils/Constants.h"
//#include "Material.h"



class GeometricObject {

public:

	GeometricObject(void);									// default constructor

	GeometricObject(const GeometricObject& object);			// copy constructor

	virtual GeometricObject*								// virtual copy constructor
		clone(void) const = 0;

	virtual 												// destructor
		~GeometricObject(void);

	virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;


	// the following three functions are only required for Chapter 3

	void
		set_color(const RGBColor& c);

	void
		set_color(const float r, const float g, const float b);

	RGBColor
		get_color(void);

	/*void
		set_material(Material* material);*/

	/*Material*
		get_material(void) const;*/

	/*virtual bool
		shadow_hit(const Ray& ray, float& tmin) const = 0;

	void
		set_shadows(const bool shadow);

	bool
		get_shadows(void);*/

	virtual Point3D
		sample(void);

	virtual Normal
		get_normal(const Point3D& p) const;

	virtual float
		pdf(const ShadeRec& sr) const;

	/*virtual BBox
		get_bounding_box(void) const;*/


protected:

	RGBColor   color;						// only used for Bare Bones ray tracing

	GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);

	//mutable Material* material_ptr;

	bool shadows;							// whether or not the object casts shadows
};


// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

// --------------------------------------------------------------------  get_colour

//inline void
//GeometricObject::set_shadows(const bool do_shadow) {
//	shadows = do_shadow;
//}

//inline bool
//GeometricObject::get_shadows(void) {
//	return shadows;
//}

inline RGBColor
GeometricObject::get_color(void) {
	return (color);
}

//inline void
//GeometricObject::set_material(Material* material) {
//	material_ptr = material;
//}

//inline Material*
//GeometricObject::get_material(void) const {
//	return material_ptr;
//}

inline Point3D
GeometricObject::sample(void) {
	return Point3D(1.0);
}

inline Normal
GeometricObject::get_normal(const Point3D& p) const {
	return Normal(1.0);
}

inline float
GeometricObject::pdf(const ShadeRec& sr) const {
	return (1.0);
}

//inline BBox
//GeometricObject::get_bounding_box(void) const {
//	//double delta = 0.0001; 
//
//	return(BBox(-1, 1, -1, 1, -1, 1));
//}





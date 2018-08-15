#pragma once

#include <memory>

#include "../Utils/RGBColor.h"
#include "../Utils/Point3D.h"
#include "../Utils/Normal.h"
#include "../Utils/Ray.h"
#include "../Utils/ShadeRec.h"
#include "../Utils/BBox.h"
#include "../Utils/Constants.h"
#include "../Materials/Material.h"

class GeometricObject
{
public:

	GeometricObject();									    // default constructor
	GeometricObject(const GeometricObject& object);			// copy constructor

	virtual GeometricObject* clone() const = 0;
	virtual	~GeometricObject();

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const = 0;

    virtual void set_material(MaterialPtr material);
	MaterialPtr get_material() const;

	void set_shadows(bool do_shadow);
	bool get_shadows();

	virtual void add_object(std::shared_ptr<GeometricObject> obj);

	virtual Point3D	sample();
	virtual float pdf(const ShadeRec& sr) const;
	virtual Normal get_normal(const Point3D& p) const;
	virtual BBox get_bounding_box() const;

	GeometricObject& operator= (const GeometricObject& rhs);
protected:

	mutable MaterialPtr material_ptr;
	bool shadows;
	BBox bBox;
};

typedef std::shared_ptr<GeometricObject> GeometricObjectPtr;

inline void GeometricObject::set_shadows(const bool do_shadow) 
{
	shadows = do_shadow;
}

inline bool GeometricObject::get_shadows()
{
	return shadows;
}

inline void GeometricObject::set_material(MaterialPtr material)
{
	material_ptr = material;
}

inline MaterialPtr GeometricObject::get_material() const
{
	return material_ptr;
}

inline Point3D GeometricObject::sample()
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

inline BBox GeometricObject::get_bounding_box() const
{
	return(BBox(-1, 1, -1, 1, -1, 1));
}

inline void GeometricObject::add_object(std::shared_ptr<GeometricObject> obj)
{}

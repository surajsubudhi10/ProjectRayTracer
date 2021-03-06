#pragma once

class World;	// only need a forward class declaration as the World data member is a reference
class Material;

#include <memory>
#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"


class ShadeRec {
public:
	ShadeRec(World& wr);					// constructor
	ShadeRec(const ShadeRec& sr);			// copy constructor

	void operator= (const ShadeRec& sr);

	bool						hit_an_object;		// did the ray hit an object?
	std::shared_ptr<Material> 	material_ptr;		// nearest object's material
	Point3D						hit_point;			// world coordinates of hit point
//	Point3D						local_hit_point;	// world coordinates of hit point
	Normal						normal;				// normal at hit point
	Ray							ray;				// for specular highlights
	float						t;					// ray parameter
	int							depth;				// recursion depth
	World&						w;					// world reference for shading
	//float					u, v;				// texture coordinates

};


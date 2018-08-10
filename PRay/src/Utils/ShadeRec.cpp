
#include "Utils/Constants.h"
#include "Utils/ShadeRec.h"
#include "Materials/Material.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(World& wr)
	: hit_an_object(false),
	material_ptr(nullptr),
	hit_point(),
	normal(),
	ray(),
	depth(0),
	w(wr),
	t(0.0)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hit_an_object(sr.hit_an_object),
	material_ptr(sr.material_ptr),
	hit_point(sr.hit_point),
	normal(sr.normal),
	ray(sr.ray),
	depth(sr.depth),
	w(sr.w),
	t(0.0)
{}


void ShadeRec::operator=(const ShadeRec& sr) 
{
	hit_an_object = sr.hit_an_object;
	material_ptr = sr.material_ptr;
	hit_point = sr.hit_point;
	normal = sr.normal;
	ray = sr.ray;
	depth = sr.depth;
	//w = sr.w;
	t = 0.0;
}








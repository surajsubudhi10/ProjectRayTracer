
#include "Constants.h"
#include "ShadeRec.h"
#include "../Materials/Material.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(World& wr)
	: hit_an_object(false),
	material_ptr(NULL),
	hit_point(),
	local_hit_point(),
	normal(),
	ray(),
	depth(0),
	//dir(),
	color(black),
	w(wr),
	t(0.0)
	//u(0),
	//v(0)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hit_an_object(sr.hit_an_object),
	material_ptr(sr.material_ptr),
	hit_point(sr.hit_point),
	local_hit_point(sr.local_hit_point),
	normal(sr.normal),
	ray(sr.ray),
	depth(sr.depth),
	//dir(sr.dir),
	color(sr.color),
	w(sr.w),
	t(0.0)
	//u(sr.u),
	//v(sr.v)
{}









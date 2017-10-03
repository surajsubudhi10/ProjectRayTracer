#pragma once



// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>

#include "ViewPlane.h"
#include "../Utils/RGBColor.h"
//#include "Tracer.h"
#include "../Objects/GeometricObject.h"
#include "../Objects/Sphere.h"
#include "../Utils/Ray.h"

#include "../Camera/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"

using namespace std;

//class RenderThread; 	//part of skeleton - wxRaytracer.h


class World {
public:

	ViewPlane					vp;
	RGBColor					background_color;
	Light*						ambient_ptr;
	vector<GeometricObject*>	objects;
	Camera*						camera_ptr;	// the camera to use
	vector<Light*>				lights;

	RGBColor* primaryBuffer;


public:

	World(void);
	~World();

	void add_object(GeometricObject* object_ptr);
	void add_light(Light* light_ptr);

	void build(void);
	void render_scene(void);// const;

	void set_camera(Camera* camera);
	void set_ambient_light(Ambient* amb);
	
	RGBColor max_to_one(const RGBColor& c) const;
	RGBColor clamp_to_color(const RGBColor& c) const;

	ShadeRec hit_bare_bones_objects(const Ray& ray);
	ShadeRec hit_objects(const Ray& ray);

	RGBColor Trace(Ray &primaryRay);
	void Savebmp(const char *filename);
	
	inline RGBColor* GetColorBuffer() { return primaryBuffer; }
	inline void SetColorAt(const int index, RGBColor _col) { primaryBuffer[index] = _col; }


private:

	void delete_objects(void);
	void delete_lights(void);

};


// ------------------------------------------------------------------ add_object

inline void World::add_object(GeometricObject* object_ptr) 
{
	objects.push_back(object_ptr);
}

inline void World::add_light(Light* light_ptr) 
{
	lights.push_back(light_ptr);
}

inline void World::set_camera(Camera* camera) 
{
	camera_ptr = camera;
}



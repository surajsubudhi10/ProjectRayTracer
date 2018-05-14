#pragma once

#include <vector>

#include "ViewPlane.h"
#include "../Utils/RGBColor.h"
#include "../Objects/GeometricObject.h"
#include "../Objects/Sphere.h"
#include "../Utils/Ray.h"

#include "../Camera/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"

using namespace std;



class World {
public:

	ViewPlane					vp;
	RGBColor					background_color;
	Light*						ambient_ptr;
	vector<GeometricObject*>	objects;
	Camera*						camera_ptr;	// the camera to use
	vector<Light*>				lights;

//	RGBColor* primaryBuffer;
	vector<RGBColor> primaryBuffer;

public:

	World();
	~World();

	void add_object(GeometricObject* object_ptr);
	void add_light(Light* light_ptr);

	void build();
	void render_scene();// const;

	void set_camera(Camera* camera);
	void set_ambient_light(Ambient* amb);
	
	RGBColor max_to_one(const RGBColor& c) const;
	RGBColor clamp_to_color(const RGBColor& c) const;

	ShadeRec hit_bare_bones_objects(const Ray& ray);
	ShadeRec hit_objects(const Ray& ray);

	void Savebmp(const char *filename);
	
	RGBColor Trace(const Ray &primaryRay);
	RGBColor Trace(const Ray& ray, int depth);
	RGBColor Trace(const Ray& ray, double& tmin, int depth);

	inline vector<RGBColor> GetColorBuffer() { return primaryBuffer; }
	inline void SetColorAt(const int index, const RGBColor &_col) { primaryBuffer[index] = _col; }

private:

	void delete_objects();
	void delete_lights();
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

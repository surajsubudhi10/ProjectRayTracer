#pragma once

#include <utility>
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
	LightPtr					ambient_ptr;
	vector<GeometricObjectPtr>	objects;
	CameraPtr					camera_ptr;	// the camera to use
	vector<LightPtr>			lights;
	vector<RGBColor>            primaryBuffer;

public:

	World();
	~World();

	void add_object(const GeometricObjectPtr &object_ptr);
	void add_light(const LightPtr &light_ptr);

	void build();
	void render_scene();// const;

	void set_camera(CameraPtr camera);
	void set_ambient_light(AmbientPtr amb);
	
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

inline void World::add_object(const GeometricObjectPtr &object_ptr)
{
	objects.push_back(object_ptr);
}

inline void World::add_light(const LightPtr &light_ptr)
{
	lights.push_back(light_ptr);
}

inline void World::set_camera(CameraPtr camera)
{
	camera_ptr = std::move(camera);
}

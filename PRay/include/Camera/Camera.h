#pragma once


#include <Utils/Point3D.h>
#include "../Utils/Vector3D.h"

class World;

class Camera
{
public:

	// constructors
	Camera();
	Camera(Point3D e, Point3D l, Vector3D u);
	virtual ~Camera();

	// access functions
	void set_eye(const Point3D &e);
	void set_eye(float x, float y, float z);
	void set_lookat(const Point3D &l);
	void set_lookat(float x, float y, float z);
	void set_up(const Vector3D &u);

	Point3D get_eye();
	Point3D	get_lookat();
	Vector3D get_up();

	void compute_uvw();
	virtual void render_scene(World& w) = 0;

protected:

	Point3D eye;
	Point3D lookat;
	Vector3D up;
	Vector3D u, v, w;
	float exposure_time;
};

inline void Camera::set_eye(const Point3D &e) {
	eye = e;
}

inline void Camera::set_eye(const float x, const float y, const float z) {
	eye = Point3D(x, y, z);
}

inline void Camera::set_lookat(const Point3D &l) {
	lookat = l;
}

inline void Camera::set_lookat(const float x, const float y, const float z) {
	lookat = Point3D(x, y, z);
}

inline void Camera::set_up(const Vector3D &u) {
	up = u;
}

inline Point3D Camera::get_eye() {
	return eye;
}

inline Point3D Camera::get_lookat() {
	return lookat;
}

inline Vector3D Camera::get_up() {
	return up;
}



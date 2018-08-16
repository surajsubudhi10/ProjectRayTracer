#pragma once

#include <memory>

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
	void eye(const Point3D &e);
	void eye(float x, float y, float z);
	void lookat(const Point3D &l);
	void lookat(float x, float y, float z);
	void up(const Vector3D &u);

	Point3D eye() const;
	Point3D	lookat() const;
	Vector3D up() const;

	void compute_uvw();
	virtual void render_scene(World& w) = 0;

protected:

	Point3D mEye;
	Point3D mLookAt;
	Vector3D mUp;
	Vector3D mU, mV, mW;
	float mExposureTime;
};

typedef std::shared_ptr<Camera> CameraPtr;

inline void Camera::eye(const Point3D &e) {
	mEye = e;
}

inline void Camera::eye(float x, float y, float z) {
	mEye = Point3D(x, y, z);
}

inline void Camera::lookat(const Point3D &l) {
	mLookAt = l;
}

inline void Camera::lookat(float x, float y, float z) {
	mLookAt = Point3D(x, y, z);
}

inline void Camera::up(const Vector3D &u) {
	mUp = u;
}

inline Point3D Camera::eye() const{
	return mEye;
}

inline Point3D Camera::lookat() const {
	return mLookAt;
}

inline Vector3D Camera::up() const {
	return mUp;
}



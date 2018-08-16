#pragma once

#include "Camera.h"
#include "../Utils/Point3D.h"
#include "../Utils/Point2D.h"
#include "../Utils/Vector3D.h"


class Pinhole : public Camera
{
public:
	// constructors
	Pinhole();
	Pinhole(const Point3D& e, const Point3D& l, const Vector3D& u, float distance, float z);
	~Pinhole() override;

	void view_plane_distance(float distance);
	void zoom(float z);
	Vector3D ray_direction(const Point2D& p) const;
	void render_scene(World& w) override;// override;

private:

	float mViewPlaneDis;		// View plane distance
	float mZoom;		// zoom factor
};

typedef std::shared_ptr<Pinhole> PinholePtr;

inline void Pinhole::view_plane_distance(float distance) {
	mViewPlaneDis = distance;
}

inline void Pinhole::zoom(float z) {
	mZoom = z;
}

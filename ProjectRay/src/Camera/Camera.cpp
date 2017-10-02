

#include "Camera.h"


Camera::Camera(void)
	: eye(Point3D(0, 0, 0)),
	lookat(Point3D(0, 10, 10)),
	up(Vector3D(0, 1, 0)),
	exposure_time(1.0) {

	compute_uvw();
}

Camera::Camera(const Point3D e, const Point3D l, const Vector3D u)
	: eye(e),
	lookat(l),
	up(u),
	exposure_time(1.0) {

	compute_uvw();
}

Camera::~Camera(void) {}

void
Camera::compute_uvw(void) {
	// avoid parallel up and look vectors (not working
	if (eye.x == lookat.x && eye.z == lookat.z) {
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}
	else {
		w = eye - lookat;
		w.normalize();
		u = up ^ w;
		u.normalize();
		v = w ^ u;
	}
}

//void
//Camera::render_stereo(World& wr, float x, int offset) {}
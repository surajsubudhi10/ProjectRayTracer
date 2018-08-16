
#include "Camera/Camera.h"


Camera::Camera()
	: mEye(Point3D(0, 0, 0)),
	mLookAt(Point3D(0, 10, 10)),
	mUp(Vector3D(0, 1, 0)),
	mExposureTime(1.0)
{
	compute_uvw();
}

Camera::Camera(const Point3D e, const Point3D l, const Vector3D u)
	: mEye(e),
	mLookAt(l),
	mUp(u),
	mExposureTime(1.0)
{
	compute_uvw();
}

Camera::~Camera() = default;

void Camera::compute_uvw()
{
	// avoid parallel mUp and look vectors (not working
	if (mEye.x == mLookAt.x && mEye.z == mLookAt.z) {
		mU = Vector3D(0, 0, 1);
		mV = Vector3D(1, 0, 0);
		mW = Vector3D(0, 1, 0);
	}
	else {
		mW = mEye - mLookAt;
		mW.normalize();
		mUp = Vector3D(0, 1, 0);
		mU = mUp ^ mW;
		mU.normalize();
		mV = mW ^ mU;
	}
}

//void
//Camera::render_stereo(World& wr, float x, int offset) {}
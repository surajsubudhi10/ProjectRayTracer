
#include "Camera/PinHole.h"
#include "Utils/RGBColor.h"
#include "World/ViewPlane.h"
#include "World/World.h"
#include "Utils/Maths.h"

Pinhole::Pinhole()
	: Camera(), mViewPlaneDis(10.0), mZoom(1.0)
{}

Pinhole::Pinhole(const Point3D& e, const Point3D& l, const Vector3D& u, float distance, float z)
	: Camera(e, l, u), mViewPlaneDis(distance), mZoom(z)
{}

Pinhole::~Pinhole()
{}

void Pinhole::render_scene(World& w)
{
	RGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0;          //vp.max_depth;			// recursion depth
	Point2D sp;				// sample point in [0, 1] x [0, 1]
	Point2D pp;				// sample point on a pixel

	vp.s /= mZoom;
	ray.o = mEye;

	for (int r = 0; r < vp.vres; r++){	// mUp
		for (int c = 0; c < vp.hres; c++)
		{
			L = black;
			int n = vp.num_samples;
			for (int j = 0; j < n; j++)
			{
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = static_cast<float>(vp.s * (c - 0.5 * vp.hres + sp.x));
				pp.y = static_cast<float>(vp.s * (r - 0.5 * vp.vres + sp.y));
				ray.d = ray_direction(pp);

				RGBColor mapped_color;
				mapped_color = w.Trace(ray, depth);
				mapped_color = RGBColor::max_to_one(mapped_color);
				L += mapped_color;

			}

			L /= vp.num_samples;
			//L *= mExposureTime;
			w.primaryBuffer.push_back(L);
		}
    }
}

Vector3D Pinhole::ray_direction(const Point2D& p) const 
{
	Vector3D dir = p.x * mU + p.y * mV - mViewPlaneDis * mW;
	dir.normalize();
	return(dir);
}
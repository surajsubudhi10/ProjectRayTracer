
#include "PinHole.h"
#include "../Utils/RGBColor.h"
#include "../World/ViewPlane.h"
#include "../World/World.h"

Pinhole::Pinhole(void)
	: Camera(),
	d(10.0),
	zoom(1.0) {}

Pinhole::Pinhole(const Point3D e, const Point3D l, const Vector3D u, float distance, float z)
	: Camera(e, l, u),
	d(distance),
	zoom(z) {}

void
Pinhole::render_scene(World& w) {
	RGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0;//vp.max_depth;			// recursion depth
	Point2D sp;				// sample point in [0, 1] x [0, 1]
	Point2D pp;				// sample point on a pixel

	vp.s /= zoom;
	ray.o = eye;
	int pixelIndex = 0;

	for (int r = 0; r < vp.vres; r++)	// up 
		for (int c = 0; c < vp.hres; c++) {
			L = black;
			int n = vp.num_samples;
			for (int j = 0; j < n; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.d = ray_direction(pp);

				//L += w.tracer_ptr->trace_ray(ray, depth);
				L += w.Trace(ray);

			}

			L /= vp.num_samples;
			L *= exposure_time;
			w.primaryBuffer[pixelIndex] = L;
			pixelIndex++;
		}
}

//void
//Pinhole::render_stereo(World& w, float x, int offset) {
//	MyRGBColor L;
//	ViewPlane vp(w.vp);
//	Ray ray;
//	int depth = 0;			// recursion depth
//	Point2D sp;				// sample point in [0, 1] x [0, 1]
//	Point2D pp;				// sample point on a pixel
//
//	vp.s /= zoom;
//	ray.o = eye;
//
//	for (int r = 0; r < vp.vres; r++)	// up 
//		for (int c = 0; c < vp.hres; c++) {
//			L = black;
//
//			for (int j = 0; j < vp.num_samples; j++) {
//				sp = vp.sampler_ptr->sample_unit_square();
//				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x) + x; // add x for stereo
//				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
//				ray.d = ray_direction(pp);
//
//				L += w.tracer_ptr->trace_ray(ray, depth);
//
//			}
//
//			L /= vp.num_samples;
//			L *= exposure_time;
//			w.display_pixel(r, c + offset, L);  // add offset for stereo
//		}
//}

Vector3D
Pinhole::ray_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	return(dir);
}
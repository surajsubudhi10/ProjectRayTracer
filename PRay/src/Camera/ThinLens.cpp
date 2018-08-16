//
// Created by Suraj on 17-05-2018.
//

#include <Camera/ThinLens.h>
#include <Samplers/MultiJittered.h>
#include <World/ViewPlane.h>
#include <World/World.h>

ThinLens::ThinLens() :
        Camera(),
        mLensRadius(1.0),
        mFocalDistance(10.0),
        mViewPlaneDistance(1.0),
        zoom(1.0),
        sampler_ptr(new MultiJittered)
{
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::ThinLens(float lens_rad, float view_plane_dis, float focal_dis, float zoom_val, SamplerPtr samp_ptr) :
        Camera(),
        mLensRadius(lens_rad),
        mViewPlaneDistance(view_plane_dis),
        mFocalDistance(focal_dis),
        zoom(zoom_val),
        sampler_ptr(samp_ptr)
{
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::ThinLens(const ThinLens &cam)
        : Camera(cam)
{
    mLensRadius = cam.mLensRadius;
    mFocalDistance = cam.mFocalDistance;
    mViewPlaneDistance = cam.mViewPlaneDistance;
    zoom = cam.zoom;
    sampler_ptr = cam.sampler_ptr;
}

void ThinLens::set_sampler(SamplerPtr sampler)
{
    sampler_ptr = sampler;
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::~ThinLens()
{}

Vector3D ThinLens::ray_direction(const Point2D &pixel_point, const Point2D &lens_point) const
{
    Point2D p;
    p.x = pixel_point.x * mFocalDistance / mViewPlaneDistance;
    p.y = pixel_point.y * mFocalDistance / mViewPlaneDistance;

    auto dir = (p.x - lens_point.x) * mU + (p.y - lens_point.y) * mV - (mFocalDistance * mW);
    dir.normalize();
    return dir;
}

void ThinLens::render_scene(World &w)
{
    RGBColor L;
    ViewPlane vp(w.vp);
    Ray ray;
    int depth = 0;          //vp.max_depth;			// recursion depth

    Point2D sp;				// sample point in [0, 1] x [0, 1]
    Point2D pp;				// sample point on a pixel
    Point2D lp;             // sample point on the lens
    Point2D dp;             // sample point on the unit disk

    vp.s /= zoom;
    w.primaryBuffer.clear();

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

                dp = sampler_ptr->sample_unit_disk();
                lp = dp * mLensRadius;

                ray.o = mEye + lp.x * mU + lp.y * mV;
                ray.d = ray_direction(pp, lp);

                RGBColor mapped_color;
                mapped_color = w.Trace(ray, depth);
                mapped_color = RGBColor::max_to_one(mapped_color);
                L += mapped_color;
            }

            L /= vp.num_samples;
            L *= mExposureTime;
            w.primaryBuffer.push_back(L);
        }
    }
}

void ThinLens::focal_distance(float dis) {
    mFocalDistance = dis;
}

float ThinLens::focal_distance() const {
    return mFocalDistance;
}

void ThinLens::view_plane_distance(float dis) {
    mViewPlaneDistance = dis;
}

float ThinLens::view_plane_distance() const {
    return mViewPlaneDistance;
}

void ThinLens::lens_radius(float rad) {
    mLensRadius = rad;
}

float ThinLens::lens_radius() const {
    return mLensRadius;
}

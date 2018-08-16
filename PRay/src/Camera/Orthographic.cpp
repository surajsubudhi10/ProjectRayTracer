//
// Created by Suraj on 17-05-2018.
//

#include <Camera/Orthographic.h>
#include <Utils/RGBColor.h>
#include <World/ViewPlane.h>
#include <World/World.h>

Orthographic::Orthographic() : Camera(), mZoom(1.0)
{}

void Orthographic::render_scene(World &world)
{
    RGBColor L;
    ViewPlane vp(world.vp);
    Ray ray;
    int depth = 0;          //vp.max_depth;			// recursion depth
    Point2D sp;				// sample point in [0, 1] x [0, 1]
    Point2D pp;				// sample point on a pixel
    ray.d = -mW;

    vp.s /= mZoom;
    world.primaryBuffer.clear();

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
                ray.o = mEye + pp.x * mU + pp.y * mV;
                //Point3D(pp.x , pp.y, mEye.z);

                RGBColor mapped_color;
                mapped_color = world.Trace(ray, depth);
                mapped_color = RGBColor::max_to_one(mapped_color);
                L += mapped_color;
            }

            L /= vp.num_samples;
            L *= mExposureTime;
            world.primaryBuffer.push_back(L);
        }
    }
}

void Orthographic::zoom(float zm) { mZoom = zm; }
float Orthographic::zoom() const { return mZoom; }

Orthographic::Orthographic(const Orthographic &ortho) :
    Camera(ortho), mZoom(ortho.mZoom)
{}

Orthographic::~Orthographic()
= default;

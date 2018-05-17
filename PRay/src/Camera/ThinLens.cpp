//
// Created by Suraj on 17-05-2018.
//

#include <Camera/ThinLens.h>
#include <Samplers/MultiJittered.h>
#include <World/ViewPlane.h>
#include <World/World.h>

ThinLens::ThinLens() :
        Camera(),
        lens_radius(1.0),
        focal_distance(10.0),
        view_plane_distance(1.0),
        zoom(1.0),
        sampler_ptr(new MultiJittered)
{
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::ThinLens(float lens_rad, float view_plane_dis, float focal_dis, float zoom_val, Sampler *samp_ptr) :
        Camera(),
        lens_radius(lens_rad),
        view_plane_distance(view_plane_dis),
        focal_distance(focal_dis),
        zoom(zoom_val),
        sampler_ptr(samp_ptr)
{
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::ThinLens(const ThinLens &cam)
        : Camera(cam)
{
    lens_radius = cam.lens_radius;
    focal_distance = cam.focal_distance;
    view_plane_distance = cam.view_plane_distance;
    zoom = cam.zoom;
    sampler_ptr = cam.sampler_ptr;
}

void ThinLens::set_sampler(Sampler *sampler)
{
    if(sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = sampler;
    sampler_ptr->map_samples_to_unit_disk();
}

ThinLens::~ThinLens()
{
    if(sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

Vector3D ThinLens::ray_direction(const Point2D &pixel_point, const Point2D &lens_point) const
{
    Point2D p;
    p.x = pixel_point.x * focal_distance / view_plane_distance;
    p.y = pixel_point.y * focal_distance / view_plane_distance;

    auto dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - (focal_distance * w);
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

    for (int r = 0; r < vp.vres; r++){	// up
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
                lp = dp * lens_radius;

                ray.o = eye + lp.x * u + lp.y * v;
                ray.d = ray_direction(pp, lp);

                RGBColor mapped_color;
                mapped_color = w.Trace(ray, depth);
                mapped_color = RGBColor::max_to_one(mapped_color);
                L += mapped_color;
            }

            L /= vp.num_samples;
            L *= exposure_time;
            w.primaryBuffer.push_back(L);
        }
    }
}


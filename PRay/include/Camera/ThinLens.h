//
// Created by Suraj on 17-05-2018.
//

#ifndef PRAY_THINLENS_H
#define PRAY_THINLENS_H

#include <Samplers/Sampler.h>
#include "Camera.h"

class ThinLens : public Camera
{
public:
    ThinLens();
    ThinLens(float lens_rad, float view_plane_dis, float focal_dis, float zoom_val, Sampler* samp_ptr);
    ThinLens(const ThinLens& cam);
    ~ThinLens() override;

    void set_sampler(Sampler* sampler);
    Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
    void render_scene(World& w) override;

private:
    float lens_radius;
    float view_plane_distance;
    float focal_distance;
    float zoom;
    Sampler* sampler_ptr;
};


#endif //PRAY_THINLENS_H

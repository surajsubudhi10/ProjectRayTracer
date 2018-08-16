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
    ThinLens(float lens_rad, float view_plane_dis, float focal_dis, float zoom_val, SamplerPtr samp_ptr);
    ThinLens(const ThinLens& cam);
    ~ThinLens() override;

    void set_sampler(SamplerPtr sampler);
    Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
    void render_scene(World& w) override;

    void focal_distance(float dis);
    float focal_distance() const;

    void view_plane_distance(float dis);
    float view_plane_distance() const;

    void lens_radius(float rad);
    float lens_radius() const;

private:
    float mLensRadius;
    float mViewPlaneDistance;
    float mFocalDistance;
    float zoom;
    SamplerPtr sampler_ptr;
};

typedef std::shared_ptr<ThinLens> ThinLensPtr;

#endif //PRAY_THINLENS_H

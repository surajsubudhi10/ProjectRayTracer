//
// Created by Suraj on 16-05-2018.
//

#include <Materials/Reflective.h>
#include <World/World.h>
#include <BRDF/PerfectSpecular.h>

Reflective::Reflective() : Phong()
{
    reflective_brdf = new PerfectSpecular();
}

Reflective::Reflective(const Reflective &ref) : Phong(), reflective_brdf(ref.reflective_brdf)
{}

RGBColor Reflective::shade(ShadeRec &sr) {
    RGBColor L(Phong::shade(sr));

    auto wo = -sr.ray.d;
    Vector3D wi;
    auto fr = reflective_brdf->sample_f(sr, wi, wo);
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.Trace(reflected_ray, sr.depth + 1) * (sr.normal * wi);
    return L;
}

Reflective::~Reflective()
{
    if(reflective_brdf != nullptr){
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }
}

void Reflective::set_kr(float the_kr) {
    if(reflective_brdf)
        reflective_brdf->set_kr(the_kr);
}

void Reflective::set_cr(const RGBColor &the_cr) {
    if(reflective_brdf)
        reflective_brdf->set_cr(the_cr);
}

void Reflective::set_cr(float r, float g, float b) {
    if(reflective_brdf)
        reflective_brdf->set_cr(r, g, b);
}


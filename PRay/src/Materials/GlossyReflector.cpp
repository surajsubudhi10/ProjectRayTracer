//
// Created by Suraj on 26/5/18.
//

#include <Materials/GlossyReflector.h>
#include <World/World.h>

GlossyReflector::GlossyReflector() : Phong()
{
    glossy_reflector_brdf = new Glossy();
}

GlossyReflector::GlossyReflector(const GlossyReflector &reflector) :
        Phong(),
        glossy_reflector_brdf(reflector.glossy_reflector_brdf)
{}

GlossyReflector::~GlossyReflector()
{
    if(glossy_reflector_brdf){
        delete glossy_reflector_brdf;
    }
}

void GlossyReflector::set_kr(float the_kr)
{
    if(glossy_reflector_brdf)
        glossy_reflector_brdf->set_ks(the_kr);
}

void GlossyReflector::set_cr(const RGBColor &the_cr)
{
    if(glossy_reflector_brdf)
        glossy_reflector_brdf->set_cs(the_cr);
}

void GlossyReflector::set_exponent(float exp)
{
    if(glossy_reflector_brdf)
        glossy_reflector_brdf->set_exp(exp);
}

void GlossyReflector::set_cr(float r, float g, float b)
{
    if(glossy_reflector_brdf)
        glossy_reflector_brdf->set_cs(r, g, b);
}

void GlossyReflector::set_samples(int num_of_samples, float exp)
{
    glossy_reflector_brdf->set_samples(num_of_samples, exp);
}

RGBColor GlossyReflector::shade(ShadeRec &sr) {
    RGBColor L(Phong::shade(sr));
    Vector3D wo(-sr.ray.d);
    Vector3D wi;
    float pdf;

    RGBColor fr(glossy_reflector_brdf->sample_f(sr, wi, wo, pdf));
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.Trace(reflected_ray, sr.depth + 1) * (sr.normal * wo) / pdf;
    return L;
}





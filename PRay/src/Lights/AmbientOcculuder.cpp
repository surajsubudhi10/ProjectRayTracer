//
// Created by Suraj on 18-05-2018.
//

#include <utility>

#include <Lights/AmbientOcculuder.h>
#include <Samplers/MultiJittered.h>
#include <World/World.h>

AmbientOcculuder::AmbientOcculuder() :
        Ambient(),
        min_amount(white),
        sampler_ptr(new MultiJittered)
{
    sampler_ptr->map_samples_to_hemisphere(1);
}

AmbientOcculuder::AmbientOcculuder(const RGBColor &col, SamplerPtr sampler) :
        Ambient(),
        min_amount(col),
        sampler_ptr(std::move(sampler))
{
    sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D AmbientOcculuder::get_direction(ShadeRec &sr)
{
    Point3D sp = sampler_ptr->sample_hemisphere();
    return (sp.x * u + sp.y * v + sp.z * w);
}

AmbientOcculuder::~AmbientOcculuder()
{}

void AmbientOcculuder::set_sampler(SamplerPtr sampler)
{
    sampler_ptr = sampler;
    sampler_ptr->map_samples_to_hemisphere(1);
}

void AmbientOcculuder::set_min_amount(const RGBColor &col)
{
    min_amount = col;
}

Light *AmbientOcculuder::clone() const
{
    return new AmbientOcculuder(*this);
}

AmbientOcculuder::AmbientOcculuder(const AmbientOcculuder &ambientOcculuder) :
        Ambient(ambientOcculuder),
        min_amount(ambientOcculuder.min_amount),
        sampler_ptr(ambientOcculuder.sampler_ptr)
{
    sampler_ptr->map_samples_to_hemisphere(1);
}

bool AmbientOcculuder::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
    auto t = (float) kHugeValue;
    auto num_objects = sr.w.objects.size();

    for(auto j = 0; j < num_objects; j++){
        if(sr.w.objects[j]->shadow_hit(ray, t)){
            return true;
        }
    }

    return false;
}

RGBColor AmbientOcculuder::L(ShadeRec &sr)
{
    w = sr.normal;
    v = w ^ Vector3D(0.0072, 1, 0.0034);
    v.normalize();
    u = v ^ w;

    Ray shadow_ray;
    shadow_ray.o = sr.hit_point;
    shadow_ray.d = get_direction(sr);

    if(in_shadow(shadow_ray, sr)){
        return (min_amount * ls * color);
    } else{
        return (ls * color);
    }
}


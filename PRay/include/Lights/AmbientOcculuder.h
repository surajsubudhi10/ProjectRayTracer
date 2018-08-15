//
// Created by Suraj on 18-05-2018.
//

#ifndef PRAY_AMBIENTOCCULUDER_H
#define PRAY_AMBIENTOCCULUDER_H

#include <memory>

#include <Samplers/Sampler.h>
#include "Ambient.h"

class AmbientOcculuder : public Ambient
{
public:
    AmbientOcculuder();
    AmbientOcculuder(const RGBColor& col, SamplerPtr sampler);
    AmbientOcculuder(const AmbientOcculuder& ambientOcculuder);
    ~AmbientOcculuder() override;

    void set_sampler(SamplerPtr sampler);
    void set_min_amount(const RGBColor& col);

    Light* clone() const override ;
    Vector3D get_direction(ShadeRec& sr) override;
    bool in_shadow(const Ray& ray, const ShadeRec& sr) const override;
    RGBColor L(ShadeRec& sr) override;

private:
    Vector3D u, v, w;
    SamplerPtr sampler_ptr;
    RGBColor min_amount;
};

typedef std::shared_ptr<AmbientOcculuder> AmbientOcculuderPtr;

#endif //PRAY_AMBIENTOCCULUDER_H

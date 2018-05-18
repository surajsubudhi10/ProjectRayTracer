//
// Created by Suraj on 18-05-2018.
//

#ifndef PRAY_AMBIENTOCCULUDER_H
#define PRAY_AMBIENTOCCULUDER_H


#include <Samplers/Sampler.h>
//#include "Light.h"
#include "Ambient.h"

class AmbientOcculuder : public Ambient
{
public:
    AmbientOcculuder();
    AmbientOcculuder(const RGBColor& col, Sampler* sampler);
    AmbientOcculuder(const AmbientOcculuder& ambientOcculuder);
    ~AmbientOcculuder() override;

    void set_sampler(Sampler* sampler);
    void set_min_amount(const RGBColor& col);

    Light* clone() const override ;
    Vector3D get_direction(ShadeRec& sr) override;
    bool in_shadow(const Ray& ray, const ShadeRec& sr) const override;
    RGBColor L(ShadeRec& sr) override;

private:
    Vector3D u, v, w;
    Sampler* sampler_ptr;
    RGBColor min_amount;
};

#endif //PRAY_AMBIENTOCCULUDER_H

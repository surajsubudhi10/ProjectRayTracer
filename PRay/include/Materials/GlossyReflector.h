//
// Created by Suraj on 26/5/18.
//

#ifndef PRAY_GLOSSYREFLECTOR_H
#define PRAY_GLOSSYREFLECTOR_H

#include "Phong.h"

class GlossyReflector : public Phong
{
public:
    GlossyReflector();
    GlossyReflector(const GlossyReflector& reflector);
    ~GlossyReflector() override ;

    RGBColor shade(ShadeRec& sr) override;

    void set_samples(int num_of_samples, float exp);
    void set_kr(float the_kr);
    void set_cr(const RGBColor& the_cr);
    void set_cr(float r, float g, float b);
    void set_exponent(float exp);

private:
    class Glossy* glossy_reflector_brdf;

};


#endif //PRAY_GLOSSYREFLECTOR_H

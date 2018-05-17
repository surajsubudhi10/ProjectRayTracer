//
// Created by Suraj on 16-05-2018.
//

#ifndef PRAY_REFLECTIVE_H
#define PRAY_REFLECTIVE_H

//#include <BRDF/PerfectSpecular.h>
#include "Phong.h"

class Reflective : public Phong
{
public:
    Reflective();
    Reflective(const Reflective& ref);
    ~Reflective() override;

    RGBColor shade(ShadeRec& sr) override;

    void set_kr(float the_kr);
    void set_cr(const RGBColor& the_cr);
    void set_cr(float r, float g, float b);

private:
    class PerfectSpecular* reflective_brdf;

};

#endif //PRAY_REFLECTIVE_H

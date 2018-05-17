//
// Created by Suraj on 16-05-2018.
//

#ifndef PRAY_PERFECTSPECULAR_H
#define PRAY_PERFECTSPECULAR_H

#include "BRDF.h"

class PerfectSpecular : public BRDF
{
public:
    PerfectSpecular();
    PerfectSpecular(const PerfectSpecular& spec);
    ~PerfectSpecular() override;

    PerfectSpecular& operator= (const PerfectSpecular& rhs);
    BRDF* clone() const override;

    void set_kr(float the_kr);
    void set_exp(float the_exp);
    void set_cr(const RGBColor &the_cr);
    void set_cr(float r, float g, float b);

    RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const override;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
    RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;
    RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const override;

private:
    float kr;
    RGBColor cr;
    float exp;
};


#endif //PRAY_PERFECTSPECULAR_H

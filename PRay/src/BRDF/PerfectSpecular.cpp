//
// Created by Suraj on 16-05-2018.
//

#include "BRDF/PerfectSpecular.h"

PerfectSpecular::PerfectSpecular() :
        BRDF(), cr(1.0f), kr(0.5f), exp(2.0f)
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular &spec) :
    BRDF(), cr(spec.cr), kr(spec.kr), exp(spec.exp)
{}

void PerfectSpecular::set_cr(const RGBColor &the_cr)
{
    cr = the_cr;
}

void PerfectSpecular::set_kr(float the_kr) {
    kr = the_kr;
}

void PerfectSpecular::set_exp(float the_exp) {
    exp = the_exp;
}

void PerfectSpecular::set_cr(float r, float g, float b) {
    cr = RGBColor(r, g, b);
}

RGBColor PerfectSpecular::sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const {
    auto ndotwo = sr.normal * wo;
    wi = -wo + 2.0f * sr.normal * ndotwo;
    return (kr * cr / (sr.normal * wi));
}

RGBColor PerfectSpecular::sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo, float &pdf) const {
    auto ndotwo = sr.normal * wo;
    wi = -wo + 2.0f * sr.normal * ndotwo;
    return (kr * cr / (sr.normal * wi));
}

RGBColor PerfectSpecular::rho(const ShadeRec &sr, const Vector3D &wo) const {
    return black;
}

RGBColor PerfectSpecular::f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const {
    return black;
}

PerfectSpecular &PerfectSpecular::operator=(const PerfectSpecular &rhs)
{
    if (this == &rhs)
        return (*this);

    BRDF::operator= (rhs);

    kr = rhs.kr;
    cr = rhs.cr;

    return (*this);
}

BRDF *PerfectSpecular::clone() const {
    return (new PerfectSpecular(*this));
}

PerfectSpecular::~PerfectSpecular()
= default;


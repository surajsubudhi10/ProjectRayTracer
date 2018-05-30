//
// Created by Suraj on 29-05-2018.
//

#include <Objects/Torus.h>
#include <cmath>
#include <Utils/Maths.h>

Torus::Torus() :
        GeometricObject(),
        _center(Point3D(0.0)),
        _inner_radius(0.5f),
        _outer_radius(1.0f)
{}


Torus::Torus(const Torus &torus) :
    GeometricObject(torus),
    _center(torus._center),
    _inner_radius(torus._inner_radius),
    _outer_radius(torus._outer_radius)
{}

Torus::Torus(const Point3D &cen, float innerRad, float outerRad) :
    GeometricObject(),
    _center(cen),
    _inner_radius(innerRad),
    _outer_radius(outerRad)
{}


Torus* Torus::clone() const
{
    return (new Torus(*this));
}

bool Torus::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bbox.hit(ray))
        return false;

    auto dx = ray.d.x; auto dy = ray.d.y; auto dz = ray.d.z;
    auto ox = ray.o.x; auto oy = ray.o.y; auto oz = ray.o.z;

    double coeffs[5];       // Coefficient Array
    double roots[4];        // Solutions Array

    auto sum_d_sqrd = dx * dx + dy * dy + dz * dz;
    auto e = ox * ox + oy * oy + oz * oz - (_outer_radius * _outer_radius) - (_inner_radius * _inner_radius);
    auto f = dx * ox + oy * dy + oz * dz;
    auto four_a_sqrd = 4.0 * _outer_radius * _outer_radius;


    coeffs[0] =  4 * e * e - (four_a_sqrd * (powf(_inner_radius, 2) - pow(oy, 2)));
    coeffs[1] = (4 * e * f) + 2 * four_a_sqrd * oy * dy;
    coeffs[2] =  2 * sum_d_sqrd * e + 4 * f * f + four_a_sqrd * dy * dy;
    coeffs[3] = 4 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;

    // Find roots
    auto num_of_real_roots = SolveQuadric(coeffs, roots);
    auto intersected = false;
    auto t = kHugeValue;

    if(num_of_real_roots == 0)
        return false;

    for(int j = 0; j < num_of_real_roots; j++)
    {
        if(roots[j] > kEpsilon)
        {
            intersected = true;
            if(roots[j] < t)
                t = roots[j];
        }
    }

    if(!intersected)
        return false;

    tmin = t;
    sr.hit_point = ray.o + t * ray.d;
    sr.normal = get_normal(sr.hit_point);
    return true;
}




BBox Torus::get_bounding_box() const
{
    double delta = 0.0001;

    return (BBox(Point3D(_center.x - _outer_radius - _inner_radius - delta, _center.y - _inner_radius - delta, _center.z - _outer_radius - _inner_radius - delta),
                 Point3D(_center.x + _outer_radius + _inner_radius + delta, _center.y + _inner_radius + delta, _center.z + _outer_radius + _inner_radius + delta)));
}

Normal Torus::get_normal(const Point3D &p) const
{
    auto square_val = (p.x * p.x + p.y * p.y + p.z * p.z - (pow(_outer_radius, 2) + pow(_inner_radius, 2)));
    auto nx = 4 * p.x *  square_val;
    auto ny = 4 * p.y * (square_val + 2 * pow(_outer_radius, 2));
    auto nz = 4 * p.z *  square_val;

    return Normal(nx, ny, nz);
}

bool Torus::shadow_hit(const Ray &ray, float &tmin) const
{
    if(!shadows)
        return false;

    auto dx = ray.d.x; auto dy = ray.d.y; auto dz = ray.d.z;
    auto ox = ray.o.x; auto oy = ray.o.y; auto oz = ray.o.z;

    double coeffs[5];       // Coefficient Array
    double roots[4];        // Solutions Array

    auto sum_d_sqrd = dx * dx + dy * dy + dz * dz;
    auto e = ox * ox + oy * oy + oz * oz - (_outer_radius * _outer_radius) - (_inner_radius * _inner_radius);
    auto f = dx * ox + oy * dy + oz * dz;
    auto four_a_sqrd = 4.0 * _outer_radius * _outer_radius;


    coeffs[0] =  4 * e * e - (four_a_sqrd * (powf(_inner_radius, 2) - pow(oy, 2)));
    coeffs[1] = (4 * e * f) + 2 * four_a_sqrd * oy * dy;
    coeffs[2] =  2 * sum_d_sqrd * e + 4 * f * f + four_a_sqrd * dy * dy;
    coeffs[3] = 4 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;

    // Find roots
    auto num_of_real_roots = SolveQuadric(coeffs, roots);
    auto intersected = false;
    auto t = kHugeValue;

    if(num_of_real_roots == 0)
        return false;

    for(int j = 0; j < num_of_real_roots; j++)
    {
        if(roots[j] > kEpsilon)
        {
            intersected = true;
            if(roots[j] < t)
                t = roots[j];
        }
    }

    return intersected;
}

void Torus::set_center(const Point3D &cen) { _center = cen; }
void Torus::set_inner_radius(float rad) {_inner_radius = rad; }
void Torus::set_outer_radius(float rad) {_outer_radius = rad; }

Point3D Torus::get_center() const { return _center;}
float Torus::get_outer_radius() const { return _outer_radius;}
float Torus::get_inner_radius() const { return _inner_radius;}

Torus::~Torus()
= default;
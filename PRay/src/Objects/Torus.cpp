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
{
    bBox = Torus::get_bounding_box();
}


Torus::Torus(const Torus &torus) :
    GeometricObject(torus),
    _center(torus._center),
    _inner_radius(torus._inner_radius),
    _outer_radius(torus._outer_radius)
{
    bBox = Torus::get_bounding_box();
}

Torus::Torus(const Point3D &cen, float innerRad, float outerRad) :
    GeometricObject(),
    _center(cen),
    _inner_radius(innerRad),
    _outer_radius(outerRad)
{
    bBox = Torus::get_bounding_box();
}


Torus* Torus::clone() const
{
    return (new Torus(*this));
}


BBox Torus::get_bounding_box() const
{
    const auto delta = 0.0001;
    return (BBox(Point3D(_center.x - _outer_radius - _inner_radius - delta, _center.y - _inner_radius - delta, _center.z - _outer_radius - _inner_radius - delta),
                 Point3D(_center.x + _outer_radius + _inner_radius + delta, _center.y + _inner_radius + delta, _center.z + _outer_radius + _inner_radius + delta)));
}

Normal Torus::get_normal(const Point3D &p) const
{
    auto rootVal = sqrt(pow(p.x, 2) + pow(p.z, 2));
    auto nx = (4 * p.x * (rootVal - _outer_radius)) / rootVal;
    auto ny = 2 * p.y;
    auto nz = (4 * p.z * (rootVal - _outer_radius)) / rootVal;

    auto norm =  Normal(nx, ny, nz);
    norm.normalize();

    return norm;
}

bool Torus::shadow_hit(const Ray &ray, float &tmin) const
{
    if(!shadows)
        return false;

    const auto origin = ray.o;
    const auto direction = ray.d;
    const auto originToCenter = origin - _center;
    const auto A = _outer_radius;
    const auto B = _inner_radius;
    const auto directionLenSq = direction.len_squared();

    const auto k1 = 2.0 * originToCenter * direction;
    const auto k2 = originToCenter.len_squared() + pow(A, 2) - pow(B, 2);
    const auto k4 = pow(originToCenter.x , 2) + pow(originToCenter.z, 2);
    const auto k5 = pow(direction.x, 2) + pow(direction.z, 2);
    const auto k6 = 2.0 * originToCenter.x * direction.x + 2.0 * originToCenter.z * direction.z;

    double coeff[5];
    double roots[4];

    coeff[4] = pow(directionLenSq, 2);
    coeff[3] = 2.0 * directionLenSq * k1;
    coeff[2] = 2.0 * directionLenSq * k2 + k1 * k1 - 4 * A * A * k5;
    coeff[1] = 2.0 * k1 * k2 - 4 * A * A * k6;
    coeff[0] = k2 * k2 - 4 * A * A * k4;

    // Find roots
    const auto numOfRealRoots = SolveQuartic(coeff, roots);
    auto intersected = false;
    auto t = kHugeValue;

    if(numOfRealRoots == 0)
        return false;

    for(auto j = 0; j < numOfRealRoots; j++)
    {
        if(roots[j] > kEpsilon)
        {
            intersected = true;
            if(roots[j] < t)
                t = roots[j];
        }
    }
    tmin = static_cast<float>(t);
    return intersected;
}

bool Torus::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bBox.hit(ray))
        return false;

    const auto origin = ray.o;
    const auto direction = ray.d;
    const auto originToCenter = origin - _center;
    const auto A = _outer_radius;
    const auto B = _inner_radius;
    const auto directionLenSq = direction.len_squared();

    const auto k1 = 2.0 * originToCenter * direction;
    const auto k2 = originToCenter.len_squared() + pow(A, 2) - pow(B, 2);
    const auto k4 = pow(originToCenter.x , 2) + pow(originToCenter.z, 2);
    const auto k5 = pow(direction.x, 2) + pow(direction.z, 2);
    const auto k6 = 2.0 * originToCenter.x * direction.x + 2.0 * originToCenter.z * direction.z;

    double coeff[5];
    double roots[4];

    coeff[4] = pow(directionLenSq, 2);
    coeff[3] = 2.0 * directionLenSq * k1;
    coeff[2] = 2.0 * directionLenSq * k2 + k1 * k1 - 4 * A * A * k5;
    coeff[1] = 2.0 * k1 * k2 - 4 * A * A * k6;
    coeff[0] = k2 * k2 - 4 * A * A * k4;

    const auto numOfRoots = SolveQuartic(coeff, roots);

    auto intersected = false;
    auto t = kHugeValue;

    if(numOfRoots == 0)
        return false;

    for (auto i = 0; i < numOfRoots; i++) {
        if(roots[i] > kEpsilon){
            intersected = true;

            if(roots[i] < t){
                t = roots[i];
            }
        }
    }

    if(!intersected)
        return false;

    tmin = t;
    sr.hit_point = origin + tmin * direction;
    sr.normal = get_normal(sr.hit_point);
    sr.material_ptr = material_ptr;
    return true;
}

void Torus::set_center(const Point3D &cen) { _center = cen; }
void Torus::set_inner_radius(float rad) {_inner_radius = rad; }
void Torus::set_outer_radius(float rad) {_outer_radius = rad; }

Point3D Torus::get_center() const { return _center;}
float Torus::get_outer_radius() const { return _outer_radius;}
float Torus::get_inner_radius() const { return _inner_radius;}

Torus::~Torus()
= default;

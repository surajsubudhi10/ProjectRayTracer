//
// Created by Suraj on 1/6/18.
//

#include <cmath>
#include "Objects/OpenCone.h"

OpenCone::OpenCone() :
    GeometricObject(),
    _center(),
    _radius(10.0f),
    _height(50.0f)
{
    bBox = OpenCone::get_bounding_box();
}


OpenCone::OpenCone(const Point3D &cen, float rad, float height) :
    GeometricObject(),
    _center(cen),
    _radius(rad),
    _height(height)
{
    bBox = OpenCone::get_bounding_box();
}

OpenCone::OpenCone(const OpenCone &cone) :
    GeometricObject(cone),
    _center(cone._center),
    _radius(cone._radius),
    _height(cone._height)
{
    bBox = cone.bBox;
}

OpenCone* OpenCone::clone() const
{
    return (new OpenCone(*this));
}

bool OpenCone::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bBox.hit(ray))
        return false;

    const auto dir = ray.d;
    const auto origin = ray.o;
    const auto originToCenter = origin - _center;

    const auto K3 = (pow(_height, 2) + pow(_radius, 2));
    const auto K1 = pow(_height, 2) / K3;
    const auto K2 = pow(_radius, 2) / K3;

    const auto a = K1 * (pow(dir.x, 2) + pow(dir.z, 2)) - (K2 * pow(dir.y, 2));
    const auto b = 2 * K1 * ((originToCenter.x * dir.x) + originToCenter.z * dir.z) - (2 * K2 * originToCenter.y * dir.y);
    const auto c = K1 * (pow(originToCenter.x, 2) + pow(originToCenter.z, 2)) - (K2 * pow(originToCenter.y, 2));

    const auto disc = pow(b, 2) - (4 * a * c);

    if(disc < 0)
        return false;

    const auto  e = sqrt(disc);
    const auto denom = 2.0 * a;
    auto t = (-b - e) / denom;    // smaller root

    if (t > kEpsilon)
    {
        tmin = t;
        auto hitPoint = ray.o + t * ray.d;
        const auto angle = (hitPoint - _center) * Vector3D(0, -1, 0);
        const auto dis = (hitPoint - _center).len_squared();
        if(angle > 0  && dis <= K3) {
            sr.hit_point = hitPoint;
            sr.normal = get_normal(sr.hit_point);
            return true;
        }
    }

    t = (-b + e) / denom;    // larger root

    if (t > kEpsilon)
    {
        tmin = t;
        auto hitPoint = ray.o + t * ray.d;
        const auto angle = (hitPoint - _center) * Vector3D(0, -1, 0);
        const auto dis = (hitPoint - _center).len_squared();
        if(angle > 0 && dis <= K3) {
            sr.hit_point = hitPoint;
            sr.normal = get_normal(sr.hit_point);
            return true;
        }
    }

    return false;
}

Normal OpenCone::get_normal(const Point3D &p) const
{
    const auto K3 = (pow(_height, 2) + pow(_radius, 2));
    const auto K1 = pow(_height, 2) / K3;
    const auto K2 = pow(_radius, 2) / K3;

    const auto nx = 2 * K1 * (p.x - _center.x);
    const auto ny = -1 * 2 * K2 * (p.y - _center.y);
    const auto nz = 2 * K1 * (p.z - _center.z);

    auto norm = Normal(nx, ny, nz);
    norm.normalize();
    return norm;
}

void OpenCone::set_height(float height) {_height = height; }
void OpenCone::set_radius(float rad) { _radius = rad; }
void OpenCone::set_center(const Point3D &cen) {_center = cen; }

Point3D OpenCone::get_center() const { return _center; }
float OpenCone::get_radius() const { return _radius; }
float OpenCone::get_height() const { return  _height; }

bool OpenCone::shadow_hit(const Ray &ray, float &tmin) const
{

    if(!shadows)
        return false;

    const auto dir = ray.d;
    const auto origin = ray.o;
    const auto originToCenter = origin - _center;

    const auto K3 = pow(_height, 2) + pow(_radius, 2);
    const auto K1 = pow(_height, 2) / K3;
    const auto K2 = pow(_radius, 2) / K3;

    const auto a = K1 * (pow(dir.x, 2) + pow(dir.z, 2)) - (K2 * pow(dir.y, 2));
    const auto b = 2 * K1 * ((originToCenter.x * dir.x) + originToCenter.z * dir.z) - (2 * K2 * originToCenter.y * dir.y);
    const auto c = K1 * (pow(originToCenter.x, 2) + pow(originToCenter.z, 2)) - (K2 * pow(originToCenter.y, 2));

    const auto disc = pow(b, 2) - (4 * a * c);

    if(disc < 0)
        return false;

    const auto  e = sqrt(disc);
    const auto denom = 2.0 * a;
    auto t = (-b - e) / denom;    // smaller root

    if (t > kEpsilon)
    {
        tmin = static_cast<float>(t);
        auto hitPoint = ray.o + t * ray.d;
        const auto angle = (hitPoint - _center) * Vector3D(0, -1, 0);
        const auto dis = (hitPoint - _center).len_squared();
        if(angle > 0 && dis <= K3) {
            return true;
        }
    }

    t = (-b + e) / denom;    // larger root

    if (t > kEpsilon)
    {
        tmin = static_cast<float>(t);
        auto hitPoint = ray.o + t * ray.d;
        const auto angle = (hitPoint - _center) * Vector3D(0, -1, 0);
        const auto dis = (hitPoint - _center).len_squared();
        if(angle > 0 && dis <= K3) {
            return true;
        }
    }

    return false;

}

BBox OpenCone::get_bounding_box() const
{
    const auto delta = 0.0001;

    return BBox(Point3D(_center.x - _radius - delta, _center.y - _height - delta, _center.z - _radius - delta),
                Point3D(_center.x + _radius + delta, _center.y           + delta, _center.z + _radius + delta));

}

OpenCone::~OpenCone()
= default;

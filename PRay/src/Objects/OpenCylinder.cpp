//
// Created by Suraj on 28/5/18.
//

#include <Objects/OpenCylinder.h>
#include <cmath>

OpenCylinder::OpenCylinder():
    GeometricObject(), _radius(2.0f), _height(5.0), _center(Point3D(0.0))
{
    bBox = OpenCylinder::get_bounding_box();
}

OpenCylinder::OpenCylinder(float rad, float height, const Point3D& center, Material *mat):
    GeometricObject(), _radius(rad), _height(height), _center(center)
{
    set_material(mat);
    bBox = OpenCylinder::get_bounding_box();
}


OpenCylinder::OpenCylinder(const OpenCylinder &cylinder) :
    GeometricObject(cylinder), _radius(cylinder._radius), _height(cylinder._height), _center(cylinder._center)
{
    bBox = OpenCylinder::get_bounding_box();
}

bool OpenCylinder::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if (!bBox.hit(ray))
        return false;

    const auto originToCenter = ray.o - _center;
    const auto dx = ray.d.x;
    const auto dz = ray.d.z;

    const auto a = pow(dx, 2) + pow(dz, 2);
    const auto b = 2 * (originToCenter.x * dx + originToCenter.z * dz);
    const auto c = pow(originToCenter.x, 2) + pow(originToCenter.z, 2) - pow(_radius, 2);
    
    const auto disc = b * b - (4 * a * c);
    double t;

    if(disc < 0)
        return false;

    const auto e = sqrt(disc);
    const auto denom = 2.0 * a;
    t = (-b - e) / denom;    // smaller root
        
    if (t > kEpsilon)
    {
        tmin = t;
        const auto hitPoint = ray.o + tmin * ray.d;
        if((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
        {
            sr.hit_point = hitPoint;
            sr.normal = get_normal(sr.hit_point);
            return (true);
        }
    }        

    t = (-b + e) / denom;    // larger root

    if (t > kEpsilon) {
        tmin = t;
        const auto hitPoint = ray.o + tmin * ray.d;
        if ((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
        {
            sr.hit_point = hitPoint;
            sr.normal = get_normal(sr.hit_point);
            return (true);
        }
    }

    return false;

}



//
//bool OpenCylinder::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
//{
//    /*if(!bBox.hit(ray))
//        return false;*/
//
//    double t;
//    const auto a = (ray.d.x * ray.d.x) + (ray.d.z * ray.d.z);
//    const auto b = 2 * (ray.o.x * ray.d.x + ray.o.z * ray.d.z);
//    const auto c = ray.o.x * ray.o.x + ray.d.x * ray.d.y - _radius * _radius;
//
//    const auto disc = b * b - 4.0 * a * c;
//
//    if (disc < 0.0)
//        return(false);
//    else {
//        const auto e = sqrt(disc);
//        const auto denom = 2.0 * a;
//        t = (-b - e) / denom;    // smaller root
//
//        if (t > kEpsilon)
//        {
//            tmin = t;
//            const auto hitPoint = ray.o + tmin * ray.d;
//            if((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
//            {
//                sr.hit_point = ray.o + t * ray.d;
//                sr.normal = get_normal(sr.hit_point);
//                return (true);
//            }
//        }
//
//        t = (-b + e) / denom;    // larger root
//
//        if (t > kEpsilon) {
//            tmin = t;
//            const auto hitPoint = ray.o + tmin * ray.d;
//            if((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
//            {
//                sr.hit_point = ray.o + t * ray.d;
//                sr.normal = get_normal(sr.hit_point);
//                return (true);
//            }
//        }
//    }
//
//    return (false);
//}

Normal OpenCylinder::get_normal(const Point3D &p) const
{
    auto norm = Normal(p.x / _radius, 0, p.z / _radius);
    norm.normalize();

    return norm;
}

BBox OpenCylinder::get_bounding_box() const
{
    const auto delta = 0.0001;
    return (BBox(Point3D(_center.x - _radius - delta, _center.y - _height - delta, _center.z - _radius - delta),
                 Point3D(_center.x + _radius + delta, _center.y + _height + delta, _center.z + _radius + delta)));
}

OpenCylinder *OpenCylinder::clone() const
{
    return (new OpenCylinder(*this));
}

bool OpenCylinder::shadow_hit(const Ray &ray, float &tmin) const
{
    if (!shadows)
        return false;

    const auto originToCenter = ray.o - _center;
    const auto dx = ray.d.x;
    const auto dz = ray.d.z;

    const auto a = pow(dx, 2) + pow(dz, 2);
    const auto b = 2 * (originToCenter.x * dx + originToCenter.z * dz);
    const auto c = pow(originToCenter.x, 2) + pow(originToCenter.z, 2) - pow(_radius, 2);

    const auto disc = b * b - (4 * a * c);
    double t;

    if (disc < 0.0)
        return(false);
    

    const auto e = sqrt(disc);
    const auto denom = 2.0 * a;
    t = static_cast<float>((-b - e) / denom);    // smaller root

    if (t > kEpsilon)
    {
        tmin = t;
        const auto hitPoint = ray.o + tmin * ray.d;
        if((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
            return (true);
    }

    t = static_cast<float>((-b + e) / denom);    // larger root

    if (t > kEpsilon)
    {
        tmin = t;
        const auto hitPoint = ray.o + tmin * ray.d;
        if((hitPoint.y <= _center.y + _height / 2.0f) && (hitPoint.y >= _center.y - _height / 2.0f))
            return (true);
    }

    return (false);
}


Point3D OpenCylinder::get_center() const { return _center; }
float   OpenCylinder::get_radius() const { return _radius; }
float   OpenCylinder::get_height() const { return _height; }

void OpenCylinder::set_center(const Point3D &cen) { _center = cen; }
void OpenCylinder::set_radius(float rad) {_radius = rad; }
void OpenCylinder::set_height(float height) {_height = height; }

OpenCylinder::~OpenCylinder()
= default;

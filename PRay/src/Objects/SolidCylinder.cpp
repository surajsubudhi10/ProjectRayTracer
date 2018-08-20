//
// Created by Suraj on 10/6/18.
//

#include <Objects/SolidCylinder.h>
#include <Objects/Disk.h>
#include <Objects/OpenCylinder.h>

SolidCylinder::SolidCylinder() :
    Compound(), _height(20.0f), _radius(10.0f), _center(Point3D(0, 0, 0))
{
    init();
}


SolidCylinder::SolidCylinder(float height, float rad, const Point3D& cen) :
    Compound(), _height(height), _radius(rad), _center(cen)
{
    init();
}

SolidCylinder::SolidCylinder(const SolidCylinder &solidCylinder) :
    Compound(solidCylinder), _height(solidCylinder._height), _radius(solidCylinder._radius), _center(solidCylinder._center)
{}

bool SolidCylinder::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(bBox.hit(ray)) {
        return Compound::hit(ray, tmin, sr);
    }

    return false;
}

void SolidCylinder::set_height(float height) { _height = height; init(); }
void SolidCylinder::set_radius(float radius) {_radius = radius;  init(); }
void SolidCylinder::set_center(const Point3D &cen) {_center = cen; init();}

float SolidCylinder::get_height() const { return _height; }
float SolidCylinder::get_radius() const { return _radius; }
Point3D SolidCylinder::get_center() const { return _center; }

void SolidCylinder::init()
{
//    const DiskPtr topDisk(new Disk(_center + Vector3D(0, _height / 2, 0), _radius, Normal(0, 1, 0)));
//    add_object(topDisk);
//
//    const DiskPtr bottomDisk(new Disk(_center + Vector3D(0, -_height / 2, 0), _radius, Normal(0, -1, 0)));
//    add_object(bottomDisk);

    const OpenCylinderPtr body(new OpenCylinder(_height, _radius, _center));
    add_object(body);
}


SolidCylinder::~SolidCylinder()
= default;

//
// Created by Suraj on 11-06-2018.
//

#include <Objects/BevelCylinder.h>
#include <Objects/Disk.h>
#include <Objects/OpenCylinder.h>
#include <Objects/Torus.h>

BevelCylinder::BevelCylinder():
    Compound(),
    _center(Point3D()),
    _base_radius(50.0f),
    _bevel_radius(10.0f),
    _height(70.0f)
{
    init();
}

BevelCylinder::BevelCylinder(const Point3D &cen, float base_rad, float bevel_rad, float height) :
    Compound(),
    _center(cen),
    _base_radius(base_rad),
    _bevel_radius(bevel_rad),
    _height(height)
{
    init();
}

BevelCylinder::BevelCylinder(const BevelCylinder &cylinder) :
    Compound(cylinder),
    _center(cylinder._center),
    _base_radius(cylinder._base_radius),
    _bevel_radius(cylinder._bevel_radius),
    _height(cylinder._height)
{
    init();
}

float   BevelCylinder::get_base_radius()    const { return _base_radius;    }
float   BevelCylinder::get_bevel_radius()   const { return _bevel_radius;   }
Point3D BevelCylinder::get_center()         const { return _center;         }
float   BevelCylinder::get_height()         const { return _height;         }

void BevelCylinder::set_base_radius(float rad) { _base_radius = rad; init(); }
void BevelCylinder::set_bevel_radius(float rad) { _bevel_radius = rad; init(); }
void BevelCylinder::set_height(float height) { _height = height; init(); }
void BevelCylinder::set_center(const Point3D &cen) { _center = cen;  init(); }

BevelCylinder::~BevelCylinder()
= default;

bool BevelCylinder::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
	if (bBox.hit(ray)) {
		return Compound::hit(ray, tmin, sr);
	}

	return false;
}


void BevelCylinder::init()
{
    const DiskPtr topDisk(new Disk(_center + Vector3D(0,  _height / 2.0f, 0), _base_radius - _bevel_radius, Normal(0, 1, 0)));
	add_object(topDisk);

    const DiskPtr buttomDisk(new Disk(_center + Vector3D(0, -_height / 2.0f, 0), _base_radius - _bevel_radius, Normal(0, -1, 0)));
    add_object(buttomDisk);

    const OpenCylinderPtr body(new OpenCylinder(_height - (2.0f * _bevel_radius), _base_radius,  _center));
	add_object(body);

    const TorusPtr topTorus(new Torus(_center + Vector3D(0, ( _height / 2.0f) - _bevel_radius, 0), _bevel_radius, _base_radius - _bevel_radius));
	add_object(topTorus);

    const TorusPtr bottomTorus(new Torus(_center + Vector3D(0, (-_height / 2.0f) + _bevel_radius, 0), _bevel_radius, _base_radius - _bevel_radius));
	add_object(bottomTorus);
}


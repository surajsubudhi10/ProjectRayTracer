//
// Created by dark-lapi on 28/5/18.
//

#ifndef PRAY_OPENCYLINDER_H
#define PRAY_OPENCYLINDER_H

#include <BRDF/Lambertian.h>
#include "GeometricObject.h"

class OpenCylinder : public GeometricObject
{
public:
    OpenCylinder();
    OpenCylinder(float rad, float height, const Point3D& center, Material* mat);
    OpenCylinder(const OpenCylinder& cylinder);
    ~OpenCylinder() override;

    OpenCylinder* clone() const override;
    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    bool shadow_hit(const Ray& ray, float& tmin) const override ;

    void set_center(const Point3D& cen);
    void set_radius(float rad);
    void set_height(float height);

    float   get_height() const;
    float   get_radius() const;
    Point3D get_center() const;
    Normal  get_normal(const Point3D& p) const override;
    BBox    get_bounding_box() const override ;

private:
    Point3D  _center;
    float    _radius;
    float    _height;
};


#endif //PRAY_OPENCYLINDER_H

//
// Created by Suraj on 1/6/18.
//

#ifndef PRAY_OPENCONE_H
#define PRAY_OPENCONE_H

#include "GeometricObject.h"

class OpenCone : public GeometricObject
{
public:
    OpenCone();
    OpenCone(const Point3D& cen, float rad, float height);
    OpenCone(const OpenCone& cone);

    ~OpenCone() override;

    OpenCone* clone() const override;
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
    Point3D _center;
    float _radius;
    float _height;

};


#endif //PRAY_OPENCONE_H

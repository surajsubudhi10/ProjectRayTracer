//
// Created by Suraj on 10/6/18.
//

#ifndef PRAY_SOLIDCYLINDER_H
#define PRAY_SOLIDCYLINDER_H

#include "Compound.h"

class SolidCylinder : public Compound
{

public:
    SolidCylinder();
    SolidCylinder(float height, float rad, const Point3D& cen);
    SolidCylinder(const SolidCylinder& solidCylinder);

    ~SolidCylinder() override;

    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

    void set_height(float height);
    void set_radius(float radius);
    void set_center(const Point3D& cen);

    float   get_height() const;
    float   get_radius() const;
    Point3D get_center() const;

private:
    float   _height;
    float   _radius;
    Point3D _center;

    void init();

}; // End of Class SolidCylinder

typedef std::shared_ptr<SolidCylinder> SolidCylinderPtr;

#endif //PRAY_SOLIDCYLINDER_H

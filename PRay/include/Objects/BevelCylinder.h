//
// Created by Suraj on 11-06-2018.
//

#ifndef PRAY_BEVELCYLINDER_H
#define PRAY_BEVELCYLINDER_H

#include "Compound.h"

class BevelCylinder : public Compound
{
public:
    BevelCylinder();
    BevelCylinder(const Point3D& cen, float base_rad, float bevel_rad, float height);
    BevelCylinder(const BevelCylinder& cylinder);
    ~BevelCylinder() override;

    void set_base_radius(float rad);
    void set_bevel_radius(float rad);
    void set_height(float height);
    void set_center(const Point3D& cen);

    float   get_base_radius() const;
    float   get_bevel_radius() const;
    Point3D get_center() const;
    float   get_height() const;


private:
    Point3D _center;
    float   _base_radius;
    float   _bevel_radius;
    float   _height;

    void init();

}; // End of Class BevelCylinder

#endif //PRAY_BEVELCYLINDER_H

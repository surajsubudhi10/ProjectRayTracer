//
// Created by Suraj on 29-05-2018.
//

#ifndef PRAY_TORUS_H
#define PRAY_TORUS_H

#include "GeometricObject.h"

class Torus : public GeometricObject
{
public:
    Torus();
    Torus(const Point3D& cen, float innerRad, float outerRad);
    Torus(const Torus& torus);
    ~Torus() override;

    Torus* clone() const override ;

    void set_center(const Point3D& cen);
    void set_outer_radius(float rad);
    void set_inner_radius(float rad);

    Point3D get_center() const;
    float get_outer_radius() const;
    float get_inner_radius() const;

    bool hit(const Ray& ray, double& t, ShadeRec& s) const override ;
    bool shadow_hit(const Ray& ray, float& tmin) const override;

    Normal get_normal(const Point3D& p) const override ;
    BBox get_bounding_box() const override ;

private:
    Point3D _center;
    float _inner_radius;
    float _outer_radius;
}; // End of class Torus

typedef std::shared_ptr<Torus> TorusPtr;

#endif //PRAY_TORUS_H

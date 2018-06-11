//
// Created by Suraj on 10/6/18.
//

#ifndef PRAY_COMPOUND_H
#define PRAY_COMPOUND_H

#include <vector>
#include "GeometricObject.h"

class Compound : public GeometricObject
{
public:
    Compound();
    Compound(const Compound& obj);

    ~Compound() override ;

    Compound* clone() const override;
    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    bool shadow_hit(const Ray& ray, float& tmin) const override ;

    BBox    get_bounding_box();

    void add_object(GeometricObject* obj);
    void set_material(Material* material) override;

protected:
    std::vector<GeometricObject* > _objects;

}; // End of class Compound

#endif //PRAY_COMPOUND_H

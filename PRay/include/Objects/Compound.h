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

    BBox get_bounding_box() const override;

    void add_object(GeometricObjectPtr obj) override;
    void set_material(MaterialPtr material) override;

protected:
    std::vector<GeometricObjectPtr > _objects;
    void build_bounding_box();


}; // End of class Compound

typedef std::shared_ptr<Compound> CompoundPtr;


#endif //PRAY_COMPOUND_H

//
// Created by Suraj on 11/6/18.
//

#ifndef PRAY_INSTANCE_H
#define PRAY_INSTANCE_H

#include <memory>

#include "GeometricObject.h"

class Instance : public GeometricObject
{
public:
    Instance();
    explicit Instance(GeometricObjectPtr object_ptr);

    Instance* clone() const override ;
    ~Instance() override;

    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override ;
    bool shadow_hit(const Ray& ray, float& tmin) const override ;

    void translate(float x, float y, float z);
    void translate(const Vector3D& vec);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void scale(float x, float y, float z);
    void scale(float s);

	void set_material(MaterialPtr mat) override;

    void compute_bounding_box();
    BBox get_bounding_box() const override;

private:
    GeometricObjectPtr _object_ptr;
    Matrix inv_matrix;

    static Matrix forward_matrix;

}; // End of Class Instance

typedef std::shared_ptr<Instance> InstancePtr;

#endif //PRAY_INSTANCE_H

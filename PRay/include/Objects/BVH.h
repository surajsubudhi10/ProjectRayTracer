//
// Created by Suraj Subudhi on 8/14/2018.
//

#ifndef PRAY_BVH_H
#define PRAY_BVH_H

#include <vector>
#include "GeometricObject.h"

int qsplit(GeometricObjectPtr* objectList, int size, float pivotVal, int axis);

class BVH : public GeometricObject
{
public:
    BVH();
    BVH(GeometricObjectPtr* obj, int numOfObjects);
    //BVH(std::vector<GeometricObject> obj, int numOfObjects);
    BVH(GeometricObjectPtr obj1, GeometricObjectPtr obj2);
    BVH(GeometricObjectPtr obj1, GeometricObjectPtr obj2, const BBox& boundingBox);

    BVH& operator=(const BVH& bvh);
    BVH* clone() const override;

    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    bool shadow_hit(const Ray& ray, float& tmin) const override;
    BBox get_bounding_box() const override;

    GeometricObjectPtr build_branch(GeometricObjectPtr* objects, int numOfObjects, int axis = 0);

private:
    BBox bbox;
    GeometricObjectPtr leftObject;
    GeometricObjectPtr rightObject;
};

typedef std::shared_ptr<BVH> BVHPtr;

#endif //PRAY_BVH_H

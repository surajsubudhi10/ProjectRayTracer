//
// Created by Suraj Subudhi on 8/14/2018.
//

#include <Objects/BVH.h>

int qsplit(GeometricObjectPtr* objectList, int size, float pivotVal, int axis)
{
    int retVal = 0;
    for(auto i = 0; i < size; i++)
    {
        BBox bbox = objectList[i]->get_bounding_box();
        double minVal = 0, maxVal = 0;
        if (axis == 0) {
            minVal = bbox.x0;
            maxVal = bbox.x1;
        } else if (axis == 1) {
            minVal = bbox.y0;
            maxVal = bbox.y1;
        } else if (axis == 2) {
            minVal = bbox.z0;
            maxVal = bbox.z1;
        }

        double centroid = (minVal + maxVal) / 2.0;
        if (centroid < pivotVal)
        {
            // Swap Objects basically keeping the left objects at the start of object list and right ones at the end of the array/list
            auto tempObject = objectList[i];
            objectList[i] = objectList[retVal];
            objectList[retVal] = tempObject;
            retVal++;
        }
    }

    if(retVal == 0 || retVal == size){
        retVal = size / 2;
    }
    return retVal;
}

BVH::BVH()
{}

BVH::BVH(GeometricObjectPtr obj1, GeometricObjectPtr obj2, const BBox &boundingBox)
{
    bbox = boundingBox;
    leftObject = obj1;
    rightObject = obj2;
}

BVH::BVH(GeometricObjectPtr obj1, GeometricObjectPtr obj2)
{
    leftObject = std::move(obj1);
    rightObject = std::move(obj2);
    bbox = leftObject->get_bounding_box();
    bbox = bbox.expand(rightObject->get_bounding_box());
}

BVH::BVH(GeometricObjectPtr *obj, int numOfObjects)
{
    if(numOfObjects == 1){
        *this = BVH(obj[0], obj[0]);
    }

    if(numOfObjects == 2){
        *this = BVH(obj[0], obj[1]);
    }

    // find the mid-point the bounding box to use as a qsplit pivot
    bbox = obj[0]->get_bounding_box();
    for(auto i = 1; i < numOfObjects; i++){
        bbox = bbox.expand(obj[i]->get_bounding_box());
    }

    Vector3D pivot = (bbox.min() + bbox.max()) / 2.0f;
    int midPoint = qsplit(obj, numOfObjects, static_cast<float>(pivot.x), 0);

    // create new bounding volume
    leftObject = build_branch(obj, midPoint, 1);
    rightObject = build_branch(&obj[midPoint], numOfObjects - midPoint, 1);
}

BBox BVH::get_bounding_box() const { return  bbox;}

bool BVH::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bbox.hit(ray)){
        return false;
    }

    // else call hit on both the functions
    bool isLeftHit  = false;
    bool isRightHit = false;
    sr.t = (float) kHugeValue;

    ShadeRec srLeft(sr);
    ShadeRec srRight(sr);
    double tLeft = kHugeValue;
    double tRight = kHugeValue;

    isLeftHit  = leftObject->hit(ray, tLeft, srLeft);
    isRightHit = rightObject->hit(ray, tRight, srRight);

    if(tLeft < tRight){
        sr = srLeft;
        tmin = tLeft;
    }else{
        sr = srRight;
        tmin = tRight;
    }

    return (isLeftHit || isRightHit);
}

bool BVH::shadow_hit(const Ray &ray, float &tmin) const
{
    if(!bbox.hit(ray))
        return false;

    if(rightObject->shadow_hit(ray, tmin))
        return true;

    return leftObject->shadow_hit(ray, tmin);
}

GeometricObjectPtr BVH::build_branch(GeometricObjectPtr* objects, int numOfObjects, int axis)
{
    if(numOfObjects == 1)
        return objects[0];

    if(numOfObjects == 2){
        BVHPtr bvh(new BVH(objects[0], objects[1]));
        return bvh;
    }

    BBox rootBBox = objects[0]->get_bounding_box();
    for (int i = 1; i < numOfObjects; ++i) {
        rootBBox = rootBBox.expand(objects[i]->get_bounding_box());
    }

    const Vector3D pivotPoint = (rootBBox.min() + rootBBox.max()) / 2.0f;

    auto pivot_axis = static_cast<float>(pivotPoint.x);
    if(axis == 1)
        pivot_axis = static_cast<float>(pivotPoint.y);
    if(axis == 2)
        pivot_axis = static_cast<float>(pivotPoint.z);

    const int midPoint = qsplit(objects, numOfObjects, pivot_axis, axis);

    GeometricObjectPtr left = build_branch(objects, midPoint, (axis + 1) % 3);
    GeometricObjectPtr right = build_branch(&objects[midPoint], numOfObjects - midPoint, (axis + 1) % 3);

    BVHPtr newBVH(new BVH(left, right, rootBBox));
    return newBVH;
}

BVH &BVH::operator=(const BVH &bvh)
{
    if (this == &bvh)
        return (*this);

    leftObject = bvh.leftObject;
    rightObject = bvh.rightObject;
    bbox = bvh.bbox;

    return (*this);
}

BVH *BVH::clone() const
{
    return (new BVH(*this));
}


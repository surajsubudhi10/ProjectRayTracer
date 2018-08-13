//
// Created by Suraj on 10/6/18.
//

#include <Utils/Maths.h>
#include "Objects/Compound.h"


Compound::Compound() :
    GeometricObject()
{
    build_bounding_box();
}

Compound::Compound(const Compound &obj):
    GeometricObject(obj)
{
    for(auto object : obj._objects){
        _objects.push_back(object);
    }

    bBox = obj.bBox;
}

Compound::~Compound()
{
    for(auto object : _objects){
        delete object;
    }
}

Compound *Compound::clone() const
{
    return new Compound(*this);
}

void Compound::add_object(GeometricObject *obj)
{
    _objects.push_back(obj);
    build_bounding_box();
}

void Compound::set_material(Material *material)
{
    for(auto obj : _objects){
        obj->set_material(material);
    }
}

void Compound::build_bounding_box()
{
    BBox tempBox;
    for (auto obj : _objects) {
        const auto boundBox = obj->get_bounding_box();

        if (tempBox.x0 > boundBox.x0)
            tempBox.x0 = boundBox.x0;

        if (tempBox.y0 > boundBox.y0)
            tempBox.y0 = boundBox.y0;

        if (tempBox.z0 > boundBox.z0)
            tempBox.z0 = boundBox.z0;

        if (tempBox.x1 < boundBox.x1)
            tempBox.x1 = boundBox.x1;

        if (tempBox.y1 < boundBox.y1)
            tempBox.y1 = boundBox.y1;

        if (tempBox.z1 < boundBox.z1)
            tempBox.z1 = boundBox.z1;
    }

    bBox = tempBox;
}

bool Compound::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bBox.hit(ray))
        return false;

    double t = kHugeValue;
    Normal normal;
    Point3D hit_point;
    bool hit = false;
    tmin = kHugeValue;

    for(auto obj : _objects)
    {
        if(obj->hit(ray, t, sr) && t < tmin)
        {
            hit = true;
            tmin = t;
            material_ptr = obj->get_material();
            normal = sr.normal;
            hit_point = sr.hit_point;
        }
    }

    if(hit)
    {
        sr.t = static_cast<float>(tmin);
        sr.normal = normal;
        sr.hit_point = hit_point;
    }

    return hit;
}

bool Compound::shadow_hit(const Ray &ray, float &tmin) const
{
    if(!shadows)
        return false;

    float t;
    auto hit = false;
    tmin = static_cast<float>(kHugeValue);

    for(auto obj : _objects)
    {
        if(obj->shadow_hit(ray, t) && t < tmin)
        {
            hit = true;
            tmin = t;
        }
    }

    return hit;
}

BBox Compound::get_bounding_box() const
{
    return bBox;
}







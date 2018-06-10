//
// Created by Suraj on 10/6/18.
//

#include <Utils/Maths.h>
#include "Objects/Compound.h"


Compound::Compound() :
    GeometricObject()
{
    bBox = Compound::get_bounding_box();
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
    bBox = Compound::get_bounding_box();
}

void Compound::set_material(Material *material)
{
    for(auto obj : _objects){
        obj->set_material(material);
    }
}

bool Compound::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    if(!bBox.hit(ray))
        return false;

    double t;
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
    bool hit = false;
    tmin = (float) kHugeValue;

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

BBox Compound::get_bounding_box()
{
    BBox tempBox;
    BBox bound_box;
    for(auto obj : _objects){
        bound_box = obj->get_bounding_box();

        if(Abs(tempBox.x0) < Abs(bound_box.x0))
            tempBox.x0 = bound_box.x0;

        if(Abs(tempBox.y0) < Abs(bound_box.y0))
            tempBox.y0 = bound_box.y0;

        if(Abs(tempBox.z0) < Abs(bound_box.z0))
            tempBox.z0 = bound_box.z0;

        if(Abs(tempBox.x1) < Abs(bound_box.x1))
            tempBox.x1 = bound_box.x1;

        if(Abs(tempBox.y1) < Abs(bound_box.y1))
            tempBox.y1 = bound_box.y1;

        if(Abs(tempBox.z1) < Abs(bound_box.z1))
            tempBox.z1 = bound_box.z1;
    }

    return tempBox;
}







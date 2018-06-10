//
// Created by Suraj on 11/6/18.
//

#include <cmath>
#include <Objects/Instance.h>
#include <cassert>
#include <Utils/Maths.h>


Instance::Instance() :
    GeometricObject()
{
    inv_matrix.set_identity();
}

Instance::Instance(GeometricObject *object_ptr) :
    GeometricObject()
{
    _object_ptr = object_ptr;
}

Instance* Instance::clone() const
{
    return new Instance(*this);
}

Instance::~Instance()
{
    delete _object_ptr;
}

bool Instance::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    Ray inv_ray(ray);
    inv_ray.o = inv_matrix * inv_ray.o;
    inv_ray.d = inv_matrix * inv_ray.d;

    if(_object_ptr->hit(inv_ray, tmin, sr))
    {
        sr.normal = inv_matrix * sr.normal;
        sr.normal.normalize();

        if(_object_ptr->get_material()){
            material_ptr = _object_ptr->get_material();
        }

        sr.hit_point = ray.o + tmin * ray.d;

        return true;
    }

    return false;
}


bool Instance::shadow_hit(const Ray &ray, float &tmin) const
{
    Ray inv_ray(ray);
    inv_ray.o = inv_matrix * inv_ray.o;
    inv_ray.d = inv_matrix * inv_ray.d;

    return _object_ptr->shadow_hit(inv_ray, tmin);
}

void Instance::translate(float x, float y, float z)
{
    Matrix inv_trans_matrix;
    inv_trans_matrix[0][3] = -x;
    inv_trans_matrix[1][3] = -y;
    inv_trans_matrix[2][3] = -z;

    inv_matrix = inv_matrix * inv_trans_matrix;
}

void Instance::translate(const Vector3D &vec)
{
    translate(static_cast<float>(vec.x), static_cast<float>(vec.y), static_cast<float>(vec.z));
}

void Instance::rotateX(float angle)
{
    Matrix inv_trans_matrix;
    auto _angle = to_randian(angle);
    inv_trans_matrix[1][1] =  cosf(_angle);
    inv_trans_matrix[1][2] =  sinf(_angle);
    inv_trans_matrix[2][1] = -sinf(_angle);
    inv_trans_matrix[2][2] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
}

void Instance::rotateY(float angle)
{
    Matrix inv_trans_matrix;
    auto _angle = to_randian(angle);
    inv_trans_matrix[0][0] =  cosf(_angle);
    inv_trans_matrix[0][2] = -sinf(_angle);
    inv_trans_matrix[2][0] =  sinf(_angle);
    inv_trans_matrix[2][2] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
}

void Instance::rotateZ(float angle)
{
    Matrix inv_trans_matrix;
    auto _angle = to_randian(angle);
    inv_trans_matrix[0][0] =  cosf(_angle);
    inv_trans_matrix[0][1] =  sinf(_angle);
    inv_trans_matrix[1][0] = -sinf(_angle);
    inv_trans_matrix[1][1] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
}

void Instance::scale(float x, float y, float z)
{
    assert(x != 0 || y != 0 || z != 0);

    Matrix inv_trans_matrix;
    inv_trans_matrix[0][0] =  1 / x;
    inv_trans_matrix[1][1] =  1 / y;
    inv_trans_matrix[2][2] =  1 / z;

    inv_matrix = inv_matrix * inv_trans_matrix;
}

void Instance::scale(float s)
{
    scale(s, s, s);
}

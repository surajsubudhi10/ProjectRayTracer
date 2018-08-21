//
// Created by Suraj on 11/6/18.
//

#include <cmath>
#include <Objects/Instance.h>
#include <cassert>
#include <Utils/Maths.h>
#include <iostream>

Matrix Instance::forward_matrix = Matrix(1.0f);

Instance::Instance() :
    GeometricObject()
{
    inv_matrix.set_identity();
}

Instance::Instance(GeometricObjectPtr object_ptr) :
    GeometricObject()
{
    _object_ptr = object_ptr;
    bBox = _object_ptr->get_bounding_box();
}

Instance* Instance::clone() const
{
    return new Instance(*this);
}

Instance::~Instance()
{}

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

        sr.material_ptr = material_ptr;
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
    Matrix transform_matrix;

    inv_trans_matrix[0][3] = -x;
    inv_trans_matrix[1][3] = -y;
    inv_trans_matrix[2][3] = -z;

    transform_matrix[0][3] = x;
    transform_matrix[1][3] = y;
    transform_matrix[2][3] = z;

    inv_matrix = inv_matrix * inv_trans_matrix;
    forward_matrix = transform_matrix * forward_matrix;
}

void Instance::translate(const Vector3D &vec)
{
    translate(static_cast<float>(vec.x), static_cast<float>(vec.y), static_cast<float>(vec.z));
}

void Instance::rotateX(float angle)
{
    Matrix inv_trans_matrix;
    Matrix transform_matrix;

    auto _angle = to_randian(angle);
    inv_trans_matrix[1][1] =  cosf(_angle);
    inv_trans_matrix[1][2] =  sinf(_angle);
    inv_trans_matrix[2][1] = -sinf(_angle);
    inv_trans_matrix[2][2] =  cosf(_angle);

    transform_matrix[1][1] =  cosf(_angle);
    transform_matrix[1][2] = -sinf(_angle);
    transform_matrix[2][1] =  sinf(_angle);
    transform_matrix[2][2] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
    forward_matrix = transform_matrix * forward_matrix;
}

void Instance::rotateY(float angle)
{
    Matrix inv_trans_matrix;
    Matrix transform_matrix;

    auto _angle = to_randian(angle);
    inv_trans_matrix[0][0] =  cosf(_angle);
    inv_trans_matrix[0][2] = -sinf(_angle);
    inv_trans_matrix[2][0] =  sinf(_angle);
    inv_trans_matrix[2][2] =  cosf(_angle);

    transform_matrix[0][0] =  cosf(_angle);
    transform_matrix[0][2] =  sinf(_angle);
    transform_matrix[2][0] = -sinf(_angle);
    transform_matrix[2][2] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
    forward_matrix = transform_matrix * forward_matrix;
}

void Instance::rotateZ(float angle)
{
    Matrix inv_trans_matrix;
    Matrix transform_matrix;

    auto _angle = to_randian(angle);
    inv_trans_matrix[0][0] =  cosf(_angle);
    inv_trans_matrix[0][1] =  sinf(_angle);
    inv_trans_matrix[1][0] = -sinf(_angle);
    inv_trans_matrix[1][1] =  cosf(_angle);

    transform_matrix[0][0] =  cosf(_angle);
    transform_matrix[0][1] = -sinf(_angle);
    transform_matrix[1][0] =  sinf(_angle);
    transform_matrix[1][1] =  cosf(_angle);

    inv_matrix = inv_matrix * inv_trans_matrix;
    forward_matrix = transform_matrix * forward_matrix;
}

void Instance::scale(float x, float y, float z)
{
    assert(x != 0 || y != 0 || z != 0);

    Matrix inv_trans_matrix;
    Matrix transform_matrix;

    inv_trans_matrix[0][0] =  1 / x;
    inv_trans_matrix[1][1] =  1 / y;
    inv_trans_matrix[2][2] =  1 / z;

    transform_matrix[0][0] =  x;
    transform_matrix[1][1] =  y;
    transform_matrix[2][2] =  z;

    inv_matrix = inv_matrix * inv_trans_matrix;
    forward_matrix = transform_matrix * forward_matrix;
}

void Instance::scale(float s)
{
    scale(s, s, s);
}

void Instance::set_material(MaterialPtr mat)
{
	_object_ptr->set_material(mat);
}

BBox Instance::get_bounding_box() const
{
    return bBox;
}

void Instance::compute_bounding_box()
{
    auto p0 = forward_matrix * Point3D(bBox.x0, bBox.y0, bBox.z0);
    auto p1 = forward_matrix * Point3D(bBox.x1, bBox.y1, bBox.z1);
    auto p2 = forward_matrix * Point3D(bBox.x0, bBox.y0, bBox.z1);
    auto p3 = forward_matrix * Point3D(bBox.x1, bBox.y0, bBox.z1);
    auto p4 = forward_matrix * Point3D(bBox.x1, bBox.y0, bBox.z0);
    auto p5 = forward_matrix * Point3D(bBox.x1, bBox.y1, bBox.z0);
    auto p6 = forward_matrix * Point3D(bBox.x0, bBox.y1, bBox.z0);
    auto p7 = forward_matrix * Point3D(bBox.x0, bBox.y1, bBox.z1);

    auto xmin = min(p0.x, min(p1.x, min(p2.x, min(p3.x, min(p4.x, min(p5.x, min(p6.x, p7.x)))))));
    auto ymin = min(p0.y, min(p1.y, min(p2.y, min(p3.y, min(p4.y, min(p5.y, min(p6.y, p7.y)))))));
    auto zmin = min(p0.z, min(p1.z, min(p2.z, min(p3.z, min(p4.z, min(p5.z, min(p6.z, p7.z)))))));

    auto xmax = max(p0.x, max(p1.x, max(p2.x, max(p3.x, max(p4.x, max(p5.x, max(p6.x, p7.x)))))));
    auto ymax = max(p0.y, max(p1.y, max(p2.y, max(p3.y, max(p4.y, max(p5.y, max(p6.y, p7.y)))))));
    auto zmax = max(p0.z, max(p1.z, max(p2.z, max(p3.z, max(p4.z, max(p5.z, max(p6.z, p7.z)))))));

    // Temp ymin and ymax val
//    ymin = -50;
//    ymax = - ymin;

    std::cout << "Min : (" << xmin << ", " << ymin << ", " << zmin << ") \n";
    std::cout << "Max : (" << xmax << ", " << ymax << ", " << zmax << ") \n";

    bBox = BBox(xmin, xmax, ymin, ymax, zmin, zmax);

    forward_matrix = Identity;
}

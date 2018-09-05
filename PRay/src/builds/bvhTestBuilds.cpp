//
// Created by Suraj Subudhi on 8/14/2018.
//

#include <World/World.h>
#include <Samplers/MultiJittered.h>
#include <Lights/AmbientOcculuder.h>
#include <Lights/PointLight.h>
#include <Camera/Orthographic.h>
#include <Objects/Grid.h>
#include <Materials/Matte.h>
#include <Objects/Instance.h>
#include <Objects/BVH.h>
#include "Objects/Plane.h"
#include "Objects/Triangle.h"
#include "Objects/Rectangle.h"
#include "Materials/Phong.h"
#include "Objects/Mesh.h"

#define USE_ACCEL

void World::build()
{
    const auto numOfSamples = 1;

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_pixel_size(1.0);
    vp.set_samples(numOfSamples);
    vp.set_gamma(1.0);
    vp.set_gamut_display(true);
    vp.set_max_depth(2);

    background_color = black;

    MultiJitteredPtr multiJitteredPtr(new MultiJittered(numOfSamples));
    AmbientOcculuderPtr occluder_ptr(new AmbientOcculuder(black, multiJitteredPtr));
    occluder_ptr->scale_radiance(3.0);
    set_ambient_light(occluder_ptr);

    //// ================ Camera ===================== ////

    OrthographicPtr pinhole_ptr(new Orthographic());
    pinhole_ptr->set_eye(200, 200, 00);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_zoom(1.0f);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);

    //// ====================== LIGHTS ======================= ////

    PointLightPtr point_light_ptr(new PointLight());
    point_light_ptr->set_location(040, 540, 040);
    point_light_ptr->scale_radiance(2.0);
    add_light(point_light_ptr);

    PointLightPtr point_light_ptr2(new PointLight());
    point_light_ptr2->set_location(0, 740, 0);
    point_light_ptr2->scale_radiance(2.0);
    add_light(point_light_ptr2);

    //// ============================================= ////

    int numOfSphere = 1;
    auto radius = 5.0f;
    set_rand_seed(15);

    std::vector<GeometricObjectPtr> renderObjects;

    for(auto i = 0; i < numOfSphere; i++)
        for(auto j = 0; j < numOfSphere; j++)
    {
        MattePtr matte_ptr(new Matte);
        matte_ptr->set_ka(0.25f);
        matte_ptr->set_kd(0.75f);
        matte_ptr->set_cd(rand_float(), rand_float(), rand_float());

        SpherePtr sphere_ptr(new Sphere);
        sphere_ptr->set_radius(radius);

        const auto center = Point3D((j - numOfSphere/2) * (2 * radius + 2.0f), 100.0f, (i - numOfSphere/2) * (2 * radius + 2.0f));
        sphere_ptr->set_center(center);
        sphere_ptr->set_material(matte_ptr);

#ifdef USE_ACCEL
        //renderObjects.push_back(sphere_ptr);
#else
        add_object(sphere_ptr);
#endif
    }

    MattePtr cornerSpherMat(new Matte);
    cornerSpherMat->set_ka(0.25f);
    cornerSpherMat->set_kd(0.75f);
    cornerSpherMat->set_cd(0.0, 0.0, 1.0);

    //auto cornerSpherePtr = new Instance(new Sphere(50));
    //auto cornerSpherePtr = new Instance(new Triangle());
    MeshPtr meshPtr(new Mesh(R"(D:\Code_Stuff\RayTracer\ProjectRay\PRay\Resources\basic\bunny_mod.obj)"));
    InstancePtr cornerSpherePtr( new Instance(meshPtr));
    cornerSpherePtr->set_material(cornerSpherMat);
    cornerSpherePtr->rotateY(90.0f);
    cornerSpherePtr->scale(5, 5, 5);
    cornerSpherePtr->compute_bounding_box();

    //// ================ Ground Plane ===================== ////

    MattePtr matte_ptr01(new Matte());
    matte_ptr01->set_ka(0.25);
    matte_ptr01->set_kd(0.65);
    matte_ptr01->set_cd(0.5, 0.5, 0.5);

    RectanglePtr groundPlanePtr(new Rectangle(Point3D(0, -150, 0), 1500, 1500));
    groundPlanePtr->set_material(matte_ptr01);

#ifdef USE_ACCEL
    renderObjects.push_back(cornerSpherePtr);
    renderObjects.push_back(groundPlanePtr);
    BVHPtr bvh(new BVH(&renderObjects[0], static_cast<int>(renderObjects.size())));
    add_object(bvh);
#else
    add_object(cornerSpherePtr);
    add_object(groundPlanePtr);
#endif


}

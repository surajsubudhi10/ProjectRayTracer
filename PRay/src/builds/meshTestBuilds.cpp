//
// Created by Suraj Subudhi on 8/13/2018.
//

#include <World/World.h>
#include <Samplers/MultiJittered.h>
#include <Lights/AmbientOcculuder.h>
#include <Lights/PointLight.h>
#include <Camera/Orthographic.h>
#include <Objects/Grid.h>
#include <Materials/Matte.h>
#include <Objects/Instance.h>
#include "Objects/Plane.h"
#include "Objects/Triangle.h"
#include "Objects/Rectangle.h"
#include "Materials/Phong.h"
#include "Objects/Mesh.h"

void World::build()
{
    const auto numOfSamples = 4;

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_pixel_size(1.0);
    vp.set_samples(numOfSamples);
    vp.set_gamma(1.0);
    vp.set_gamut_display(true);
    vp.set_max_depth(2);

    background_color = black;

    auto* occluder_ptr = new AmbientOcculuder(black, new MultiJittered(numOfSamples));
    occluder_ptr->scale_radiance(3.0);
    set_ambient_light(occluder_ptr);

    //// ================ Camera ===================== ////

    auto * pinhole_ptr = new Orthographic();
    pinhole_ptr->set_eye(800, 800, 00);
    pinhole_ptr->set_lookat(0, 0, 0);
    pinhole_ptr->set_zoom(0.5f);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);

    //// ====================== LIGHTS ======================= ////

    auto * point_light_ptr = new PointLight();
    point_light_ptr->set_location(240, 1240, 240);
    point_light_ptr->scale_radiance(2.0);
    add_light(point_light_ptr);

    auto * point_light_ptr2 = new PointLight();
    point_light_ptr2->set_location(0, 1840, 0);
    point_light_ptr2->scale_radiance(4.0);
    add_light(point_light_ptr2);

    //// ============================================= ////

    auto cornerSpherMat = new Matte;
    cornerSpherMat->set_ka(0.25f);
    cornerSpherMat->set_kd(0.75f);
    cornerSpherMat->set_cd(0.0, 0.0, 1.0);

    Mesh* meshPtr = new Mesh(R"(D:\Code_Stuff\RayTracer\ProjectRay\PRay\Resources\basic\cube.obj)");
    auto cornerSpherePtr = new Instance(meshPtr);
    cornerSpherePtr->set_material(cornerSpherMat);
    cornerSpherePtr->rotateX(45.0f);
    cornerSpherePtr->rotateY(45.0f);
    cornerSpherePtr->scale(200, 200, 200);
    cornerSpherePtr->translate(0, 150, 0);
    cornerSpherePtr->compute_bounding_box();
    add_object(cornerSpherePtr);

    //// ================ Ground Plane ===================== ////

    auto* matte_ptr01 = new Matte();
    matte_ptr01->set_ka(0.25);
    matte_ptr01->set_kd(0.65);
    matte_ptr01->set_cd(0.5, 0.5, 0.5);

    auto groundPlanePtr = new Rectangle(Point3D(0, -150, 0), 800, 800);
    groundPlanePtr->set_material(matte_ptr01);
    add_object(groundPlanePtr);

}

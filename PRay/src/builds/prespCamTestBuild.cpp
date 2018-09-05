//
// Created by Suraj Subudhi on 8/15/2018.
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
#include <Camera/PinHole.h>
#include <Camera/ThinLens.h>
#include "Objects/Plane.h"
#include "Objects/Triangle.h"
#include "Objects/Rectangle.h"
#include "Materials/Phong.h"
#include "Objects/Mesh.h"

#define USE_ACCEL
//#define USE_PRESPECTIVE

#ifdef USE_PRESPECTIVE
//#define USE_THIN_LENS
#define USE_PIN_HOLE
#else
#define ORTHO
#endif

void World::build()
{
    const auto numOfSamples = 50;

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
#ifdef ORTHO
    OrthographicPtr orthoCam_ptr(new Orthographic);
    orthoCam_ptr->eye(250, 0, 0);
    orthoCam_ptr->lookat(0, -70, 0);
    //orthoCam_ptr->zoom(0.5f);
    orthoCam_ptr->compute_uvw();
    set_camera(orthoCam_ptr);

#endif

#ifdef USE_PIN_HOLE
    PinholePtr pinhole_ptr(new Pinhole);
    pinhole_ptr->eye(250, 00, 00);
    pinhole_ptr->lookat(0, -70, 0);
    pinhole_ptr->zoom(1.0f);
    const auto viewPlaneDis = (pinhole_ptr->lookat() - pinhole_ptr->eye()).length();
    pinhole_ptr->view_plane_distance((float) viewPlaneDis);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);
#endif

#ifdef USE_THIN_LENS
    ThinLensPtr thinLensPtr(new ThinLens);
    thinLensPtr->eye(250, 0, 0);
    thinLensPtr->lookat(0, -70, 0);
    const auto viewPlaneDis = (thinLensPtr->lookat() - thinLensPtr->eye()).length();
    thinLensPtr->view_plane_distance((float) viewPlaneDis);
    thinLensPtr->focal_distance((float) viewPlaneDis);
    thinLensPtr->lens_radius(20.0f);
    thinLensPtr->compute_uvw();
    set_camera(thinLensPtr);
#endif

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

    std::vector<GeometricObjectPtr> renderObjects;

    MattePtr cornerSpherMat(new Matte);
    cornerSpherMat->set_ka(0.25f);
    cornerSpherMat->set_kd(0.75f);
    cornerSpherMat->set_cd(0.0, 0.0, 1.0);

    MeshPtr meshPtr(new Mesh(R"(D:\Code_Stuff\RayTracer\ProjectRay\PRay\Resources\basic\bunny_mod.obj)"));
    InstancePtr cornerSpherePtr( new Instance(meshPtr));
    cornerSpherePtr->set_material(cornerSpherMat);
    cornerSpherePtr->rotateY(90);
    cornerSpherePtr->scale(5, 5, 5);
    cornerSpherePtr->translate(0, -100, 0);
    cornerSpherePtr->compute_bounding_box();


    /// Front Sphere
    MattePtr frontSphereMat(new Matte);
    frontSphereMat->set_ka(0.25f);
    frontSphereMat->set_kd(0.75f);
    frontSphereMat->set_cd(0.0, 1.0, 0.0);

    SpherePtr frontSpherePtr(new Sphere);
    frontSpherePtr->set_radius(30.0f);
    frontSpherePtr->set_center(Point3D(0.0, -70.0, 0.0));
    frontSpherePtr->set_material(frontSphereMat);

    /// Mid Sphere
    MattePtr midSphereMat(new Matte);
    midSphereMat->set_ka(0.25f);
    midSphereMat->set_kd(0.75f);
    midSphereMat->set_cd(1.0, 1.0, 0.0);

    SpherePtr midSpherePtr(new Sphere);
    midSpherePtr->set_radius(30.0f);
    midSpherePtr->set_center(Point3D(40.0, -70.0, 60.0));
    midSpherePtr->set_material(midSphereMat);

    /// Back Sphere
    MattePtr backSphereMat(new Matte);
    backSphereMat->set_ka(0.25f);
    backSphereMat->set_kd(0.75f);
    backSphereMat->set_cd(1.0, 0.0, 1.0);

    SpherePtr backSpherePtr(new Sphere);
    backSpherePtr->set_radius(30.0f);
    backSpherePtr->set_center(Point3D(-40.0, -70.0, -60.0));
    backSpherePtr->set_material(backSphereMat);

    //// ================ Ground Plane ===================== ////

    MattePtr matte_ptr01(new Matte());
    matte_ptr01->set_ka(0.25);
    matte_ptr01->set_kd(0.65);
    matte_ptr01->set_cd(0.5, 0.5, 0.5);

    RectanglePtr groundPlanePtr(new Rectangle(Point3D(0, -100, 0), 400, 400));
    groundPlanePtr->set_material(matte_ptr01);

#ifdef USE_ACCEL
//    renderObjects.push_back(cornerSpherePtr);
    renderObjects.push_back(frontSpherePtr);
    renderObjects.push_back(midSpherePtr);
    renderObjects.push_back(backSpherePtr);
    renderObjects.push_back(groundPlanePtr);
    BVHPtr bvh(new BVH(&renderObjects[0], static_cast<int>(renderObjects.size())));
    add_object(bvh);
#else
    add_object(cornerSpherePtr);
    add_object(groundPlanePtr);
#endif


}

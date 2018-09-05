//
// Created by Suraj Subudhi on 8/18/2018.
//

#include <World/World.h>
#include <Samplers/MultiJittered.h>

#include <Lights/AmbientOcculuder.h>
#include <Lights/PointLight.h>

#include <Materials/Matte.h>
#include <Materials/Phong.h>

#include <Camera/PinHole.h>

#include <Camera/Orthographic.h>
#include <Objects/Instance.h>
#include <Objects/BVH.h>
#include <Objects/Rectangle.h>
#include <Materials/Reflective.h>
#include <Materials/GlossyReflector.h>

#define USE_ACCEL
#define USE_PRESPECTIVE

#ifdef USE_PRESPECTIVE
#define USE_PIN_HOLE
#else
#define ORTHO
#endif

void World::build()
{
    const auto numOfSamples = 10;

    vp.set_hres(400);
    vp.set_vres(400);
    vp.set_pixel_size(1.0);
    vp.set_samples(numOfSamples);
    vp.set_gamma(1.0);
    vp.set_gamut_display(true);
    vp.set_max_depth(3);

    background_color = black;

    MultiJitteredPtr multiJitteredPtr(new MultiJittered(numOfSamples));
    AmbientOcculuderPtr occluder_ptr(new AmbientOcculuder(black, multiJitteredPtr));
    occluder_ptr->scale_radiance(0.75f);
    set_ambient_light(occluder_ptr);

    //// ================ Camera ===================== ////
#ifdef ORTHO
    OrthographicPtr orthoCam_ptr(new Orthographic);
    orthoCam_ptr->eye(200, 100, 0);
    orthoCam_ptr->lookat(0, 0, 0);
    orthoCam_ptr->compute_uvw();
    set_camera(orthoCam_ptr);

#endif

#ifdef USE_PIN_HOLE
    PinholePtr pinhole_ptr(new Pinhole);
    pinhole_ptr->eye(0, 300, 500);
    pinhole_ptr->lookat(0, -70, 0);
    pinhole_ptr->zoom(1.0f);
    const auto viewPlaneDis = (pinhole_ptr->lookat() - pinhole_ptr->eye()).length();
    pinhole_ptr->view_plane_distance((float) viewPlaneDis);
    pinhole_ptr->compute_uvw();
    set_camera(pinhole_ptr);
#endif

    //// ====================== LIGHTS ======================= ////

    PointLightPtr point_light_right_ptr(new PointLight());
    point_light_right_ptr->set_location(100, 50, 100);
    point_light_right_ptr->scale_radiance(2.0);
    add_light(point_light_right_ptr);

    PointLightPtr point_light_left_ptr(new PointLight());
    point_light_left_ptr->set_location(-100, 50, 100);
    point_light_left_ptr->scale_radiance(5.0);
    add_light(point_light_left_ptr);

    //// ============================================= ////

    std::vector<GeometricObjectPtr> renderObjects;

    /// Matte Sphere
    MattePtr sphereMatteMat(new Matte);
    sphereMatteMat->set_ka(0.25f);
    sphereMatteMat->set_kd(0.75f);
    sphereMatteMat->set_cd(0.0, 1.0, 0.0);

    SpherePtr sphereMattePtr(new Sphere(Point3D(0.0, 0.0, 0.0), 30.0f));
    InstancePtr sphereMatteInstancePtr( new Instance(sphereMattePtr));
    sphereMatteInstancePtr->set_material(sphereMatteMat);
    sphereMatteInstancePtr->translate(100, -70, 0);
    sphereMatteInstancePtr->compute_bounding_box();

    /// Phong Sphere
    PhongPtr spherePhongMat(new Phong);
    spherePhongMat->set_ka(0.25f);
    spherePhongMat->set_kd(0.65f);
    spherePhongMat->set_ks(0.25f);
    spherePhongMat->set_exp(10.0f);
    spherePhongMat->set_cd(1.0, 0.0, 0.0);
    spherePhongMat->set_cs(0.0, 0.0, 1.0);

    SpherePtr spherePhongPtr(new Sphere(Point3D(0.0, 0.0, 0.0), 30.0f));
    InstancePtr spherePhongInstancePtr( new Instance(spherePhongPtr));
    spherePhongInstancePtr->set_material(spherePhongMat);
    spherePhongInstancePtr->translate(-100, -70, 0);
    spherePhongInstancePtr->compute_bounding_box();

    /// Middle Sphere
    //PhongPtr sphereTestMat(new Phong);
    ReflectivePtr sphereRefMat(new Reflective);
    sphereRefMat->set_ka(0.25f);
    sphereRefMat->set_kd(0.5f);
    sphereRefMat->set_ks(0.15f);
    sphereRefMat->set_kr(0.75f);
    sphereRefMat->set_cd(0.5, 0.5, 0.5);
    sphereRefMat->set_cs(0.75, 0.5, 0.25);
    sphereRefMat->set_cr(white);
    sphereRefMat->set_exp(100);

    SpherePtr sphereRefPtr(new Sphere(Point3D(0.0, 0.0, 0.0), 50.0f));
    InstancePtr sphereRefInstancePtr( new Instance(sphereRefPtr));
    sphereRefInstancePtr->set_material(sphereRefMat);
    sphereRefInstancePtr->translate(0, -50, -50);
    sphereRefInstancePtr->compute_bounding_box();

    /// Glossy Sphere
    GlossyReflectorPtr sphereGlossyMat(new GlossyReflector);
    sphereGlossyMat->set_ka(0.0);//25f);
    sphereGlossyMat->set_kd(0.0);//5f);
    sphereGlossyMat->set_ks(0.0);//15f);
    sphereGlossyMat->set_kr(0.9);//5f);
    sphereGlossyMat->set_cd(0.5, 0.0, 0.5);
    sphereGlossyMat->set_cs(0.75, 0.75, 0.75);
    sphereGlossyMat->set_cr(0.75, 0.75, 0.0);
    sphereGlossyMat->set_exp(100);
    sphereGlossyMat->set_samples(200, 100);

    SpherePtr sphereGlossyPtr(new Sphere(Point3D(0.0, 0.0, 0.0), 30.0f));
    InstancePtr sphereGlossyInstancePtr( new Instance(sphereGlossyPtr));
    sphereGlossyInstancePtr->set_material(sphereGlossyMat);
    sphereGlossyInstancePtr->translate(1, -70, 100);
    sphereGlossyInstancePtr->compute_bounding_box();

    //// ================ Ground Plane ===================== ////

    //MattePtr matte_ptr01(new Matte());
    GlossyReflectorPtr ground_material_ptr01(new GlossyReflector);
    ground_material_ptr01->set_ka(0.25f);
    ground_material_ptr01->set_kd(0.5f);
    ground_material_ptr01->set_ks(0.15f);
    ground_material_ptr01->set_kr(0.75f);
    ground_material_ptr01->set_cd(0.5, 0.5, 0.5);
    ground_material_ptr01->set_cs(0.5, 0.5, 0.5);
    ground_material_ptr01->set_cr(white);
    ground_material_ptr01->set_samples(70, 1000);

    RectanglePtr groundPlanePtr(new Rectangle(Point3D(0, -100, 0), 1600, 1200));
    groundPlanePtr->set_material(ground_material_ptr01);

#ifdef USE_ACCEL
    renderObjects.push_back(sphereMatteInstancePtr);
    renderObjects.push_back(spherePhongInstancePtr);
    renderObjects.push_back(sphereRefInstancePtr);
    renderObjects.push_back(sphereGlossyInstancePtr);
    renderObjects.push_back(groundPlanePtr);
    BVHPtr bvh(new BVH(&renderObjects[0], static_cast<int>(renderObjects.size())));
    add_object(bvh);
#else
    add_object(sphereInstancePtr);
    add_object(groundPlanePtr);
#endif


}

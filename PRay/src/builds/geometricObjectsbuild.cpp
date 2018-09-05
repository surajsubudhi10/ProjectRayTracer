//
// Created by Suraj Subudhi on 8/18/2018.
//

#include <World/World.h>
#include <Samplers/MultiJittered.h>

#include <Lights/AmbientOcculuder.h>
#include <Lights/PointLight.h>

#include <Materials/Matte.h>

#include <Camera/PinHole.h>
#include <Camera/Orthographic.h>

#include <Objects/Instance.h>
#include <Objects/BVH.h>
#include <Objects/SolidCylinder.h>
#include <Objects/BevelCylinder.h>
#include <Objects/Box.h>
#include <Objects/Rectangle.h>
#include <Objects/Mesh.h>
#include <Objects/OpenCylinder.h>
#include <Objects/Torus.h>
#include <Objects/Disk.h>
#include <Objects/OpenCone.h>

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
    vp.set_max_depth(2);

    background_color = black;

    MultiJitteredPtr multiJitteredPtr(new MultiJittered(numOfSamples));
    AmbientOcculuderPtr occluder_ptr(new AmbientOcculuder(black, multiJitteredPtr));
    occluder_ptr->scale_radiance(0.75f);
    set_ambient_light(occluder_ptr);
//    AmbientPtr ambientPtr(new Ambient);
//    ambientPtr->scale_radiance(0.5);
//    set_ambient_light(ambientPtr);

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

    PointLightPtr point_light_ptr(new PointLight());
    point_light_ptr->set_location(00, 50, 00);
    point_light_ptr->scale_radiance(2.0);
    add_light(point_light_ptr);

    //// ============================================= ////

    std::vector<GeometricObjectPtr> renderObjects;

    MattePtr cornerSpherMat(new Matte);
    cornerSpherMat->set_ka(0.25f);
    cornerSpherMat->set_kd(0.75f);
    cornerSpherMat->set_cd(0.0, 0.0, 1.0);

    MeshPtr meshPtr(new Mesh(R"(D:\Code_Stuff\RayTracer\ProjectRay\PRay\Resources\basic\bunny_mod.obj)"));
    InstancePtr cornerSpherePtr( new Instance(meshPtr));
    cornerSpherePtr->set_material(cornerSpherMat);
    cornerSpherePtr->scale(3, 3, 3);
    cornerSpherePtr->translate(0, -100, 0);
    cornerSpherePtr->compute_bounding_box();

    /// Sphere
    MattePtr sphereMat(new Matte);
    sphereMat->set_ka(0.25f);
    sphereMat->set_kd(0.75f);
    sphereMat->set_cd(0.0, 1.0, 0.0);

    SpherePtr spherePtr(new Sphere(Point3D(0.0, 0.0, 0.0), 30.0f));
    InstancePtr sphereInstancePtr( new Instance(spherePtr));
    sphereInstancePtr->set_material(sphereMat);
    sphereInstancePtr->translate(-100, -70, 100);
    sphereInstancePtr->compute_bounding_box();

    /// Torus
    MattePtr torusMat(new Matte);
    torusMat->set_ka(0.25f);
    torusMat->set_kd(0.75f);
    torusMat->set_cd(1.0, 1.0, 0.0);

    TorusPtr torusPtr(new Torus(Point3D(-0.0, 0.0, -0.0), 20.0, 50.0));
    InstancePtr torusInstancePtr( new Instance(torusPtr));
    torusInstancePtr->set_material(torusMat);
    torusInstancePtr->scale(0.5f);
    torusInstancePtr->translate(0, -80, 100);
    torusInstancePtr->compute_bounding_box();

    /// Box
    MattePtr boxMat(new Matte);
    boxMat->set_ka(0.25f);
    boxMat->set_kd(0.75f);
    boxMat->set_cd(1.0, 0.0, 1.0);

    BoxPtr boxPtr(new Box(-20, 20, -20, 20, -20, 20));
    InstancePtr boxInstancePtr( new Instance(boxPtr));
    boxInstancePtr->set_material(boxMat);
    boxInstancePtr->translate(100, -80, 100);
    boxInstancePtr->compute_bounding_box();

    /// OpenCylinder
    MattePtr openCylinderMat(new Matte);
    openCylinderMat->set_ka(0.25f);
    openCylinderMat->set_kd(0.75f);
    openCylinderMat->set_cd(0.25, 0.25, 1.0);

    OpenCylinderPtr openCylinderPtr(new OpenCylinder(80, 30, Point3D()));
    InstancePtr openCylinderInstancePtr( new Instance(openCylinderPtr));
    openCylinderInstancePtr->set_material(openCylinderMat);
	openCylinderInstancePtr->translate(-100, -60, -100);
    openCylinderInstancePtr->compute_bounding_box();

    /// CloseCylinder
    MattePtr solidCylinderMat(new Matte);
    solidCylinderMat->set_ka(0.25f);
    solidCylinderMat->set_kd(0.75f);
    solidCylinderMat->set_cd(0.0, 0.25, 0.0);

    SolidCylinderPtr solidCylinderPtr(new SolidCylinder(80, 30, Point3D()));
    InstancePtr solidCylinderInstancePtr( new Instance(solidCylinderPtr));
    solidCylinderInstancePtr->set_material(solidCylinderMat);
    solidCylinderInstancePtr->translate(0, -60, -100);
    solidCylinderInstancePtr->compute_bounding_box();

	/// BevelCylinder
	MattePtr bevelCylinderMat(new Matte);
	bevelCylinderMat->set_ka(0.25f);
	bevelCylinderMat->set_kd(0.75f);
	bevelCylinderMat->set_cd(0.95, 0.25, 0.15);

	BevelCylinderPtr bevelCylinderPtr(new BevelCylinder(Point3D(), 30, 10, 80));
	InstancePtr bevelCylinderInstancePtr(new Instance(bevelCylinderPtr));
	bevelCylinderInstancePtr->set_material(bevelCylinderMat);
	bevelCylinderInstancePtr->translate(100, -60, -100);
	bevelCylinderInstancePtr->compute_bounding_box();

    /// Triangle
    MattePtr triangleMat(new Matte);
    triangleMat->set_ka(0.25f);
    triangleMat->set_kd(0.75f);
    triangleMat->set_cd(0.25, 0.75, 0.75);

    TrianglePtr trianglePtr(new Triangle(Point3D(0, 0, 5), Point3D(0, 0, -5), Point3D(-5, 0, 0)));
    InstancePtr triangleInstancePtr( new Instance(trianglePtr));
    triangleInstancePtr->set_material(triangleMat);
    triangleInstancePtr->scale(10.0f);
    triangleInstancePtr->translate(-100, -99, 0);
    triangleInstancePtr->compute_bounding_box();

    /// Disc
    MattePtr discMat(new Matte);
    discMat->set_ka(0.25f);
    discMat->set_kd(0.75f);
    discMat->set_cd(0.25, 0.75, 0.75);

    DiskPtr discPtr(new Disk(Point3D(0, 0, 0), 30.0f, Normal(0, 1, 0)));
    InstancePtr discInstancePtr( new Instance(discPtr));
    discInstancePtr->set_material(discMat);
    discInstancePtr->translate(00, -99, 0);
    discInstancePtr->compute_bounding_box();

    /// OpenCone
    MattePtr openConeMat(new Matte);
    openConeMat->set_ka(0.25f);
    openConeMat->set_kd(0.75f);
    openConeMat->set_cd(0.75, 0.15, 0.35);

    OpenConePtr openConePtr(new OpenCone(Point3D(0, 0, 0), 30.0f, 80.0f));
    InstancePtr coneInstancePtr( new Instance(openConePtr));
    coneInstancePtr->set_material(openConeMat);
    coneInstancePtr->translate(100, -20, 0);
    coneInstancePtr->compute_bounding_box();

    //// ================ Ground Plane ===================== ////

    MattePtr matte_ptr01(new Matte());
    matte_ptr01->set_ka(0.25);
    matte_ptr01->set_kd(0.65);
    matte_ptr01->set_cd(0.5, 0.5, 0.5);

    RectanglePtr groundPlanePtr(new Rectangle(Point3D(0, -100, 0), 1600, 1200));
    groundPlanePtr->set_material(matte_ptr01);

#ifdef USE_ACCEL
    renderObjects.push_back(cornerSpherePtr);
    renderObjects.push_back(torusInstancePtr);
    renderObjects.push_back(sphereInstancePtr);
    renderObjects.push_back(boxInstancePtr);
    renderObjects.push_back(openCylinderInstancePtr);
    renderObjects.push_back(solidCylinderInstancePtr);
	renderObjects.push_back(bevelCylinderInstancePtr);
    renderObjects.push_back(triangleInstancePtr);
    renderObjects.push_back(discInstancePtr);
    renderObjects.push_back(coneInstancePtr);
    renderObjects.push_back(groundPlanePtr);
    BVHPtr bvh(new BVH(&renderObjects[0], static_cast<int>(renderObjects.size())));
    add_object(bvh);
#else
//    add_object(cornerSpherePtr);
    add_object(torusInstancePtr);
    add_object(sphereInstancePtr);
    add_object(boxInstancePtr);
    add_object(openCylinderInstancePtr);
    add_object(solidCylinderInstancePtr);
	add_object(bevelCylinderInstancePtr);
    add_object(triangleInstancePtr);
    add_object(discInstancePtr);
    add_object(coneInstancePtr);
    add_object(groundPlanePtr);
#endif


}

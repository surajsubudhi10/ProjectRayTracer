include_directories(${PROJECT_SOURCE_DIR}/include/)

# Application source
set(PRAY_SOURCE
        "main.cpp"

        ## Camera
        "src/Camera/Camera.cpp"
        "src/Camera/PinHole.cpp"
        "src/Camera/Orthographic.cpp"
        "src/Camera/ThinLens.cpp"

        ## World
        "src/World/ViewPlane.cpp"
        "src/World/World.cpp"

        ## Samplers
        "src/Samplers/MultiJittered.cpp"
        "src/Samplers/Regular.cpp"
        "src/Samplers/Sampler.cpp"

        ## Objects
        "src/Objects/Box.cpp"
        "src/Objects/Disk.cpp"
        "src/Objects/GeometricObject.cpp"
        "src/Objects/Plane.cpp"
        "src/Objects/Rectangle.cpp"
        "src/Objects/Sphere.cpp"
        "src/Objects/Triangle.cpp"
        "src/Objects/Torus.cpp"
        "src/Objects/OpenCylinder.cpp"
        "src/Objects/OpenCone.cpp"
        "src/Objects/Compound.cpp"
        "src/Objects/SolidCylinder.cpp"
        "src/Objects/Instance.cpp"
        "src/Objects/BevelCylinder.cpp"
        "src/Objects/Grid.cpp"

        ## Materials
        "src/Materials/Material.cpp"
        "src/Materials/Matte.cpp"
        "src/Materials/Phong.cpp"
        "src/Materials/Reflective.cpp"
        "src/Materials/GlossyReflector.cpp"

        ## Lights
        "src/Lights/Ambient.cpp"
        "src/Lights/Light.cpp"
        "src/Lights/PointLight.cpp"
        "src/Lights/AmbientOcculuder.cpp"

        ## BRDF
        "src/BRDF/BRDF.cpp"
        "src/BRDF/Glossy.cpp"
        "src/BRDF/Lambertian.cpp"
        "src/BRDF/PerfectSpecular.cpp"

        ## Utils
        "src/Utils/BBox.cpp"
        "src/Utils/Maths.cpp"
        "src/Utils/Matrix.cpp"
        "src/Utils/Normal.cpp"
        "src/Utils/Point2D.cpp"
        "src/Utils/Point3D.cpp"
        "src/Utils/Ray.cpp"
        "src/Utils/RGBColor.cpp"
        "src/Utils/ShadeRec.cpp"
        "src/Utils/Vector3D.cpp"

        ## builds
        #"src/builds/bareBoneBuild.cpp"
        #"src/builds/geometricObjectsbuild.cpp"
        "src/builds/gridRandomSphere.cpp"
   )

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
        ${PRAY_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Add executable
#-------------------------------------------------------------------------------
add_executable(PRAY ${PRAY_SOURCE})

if (WIN32)
    target_link_libraries( PRAY )# glew32 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} assimp)
elseif(LINUX)
    target_link_libraries( PRAY) # GLEW glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} assimp)
endif ()

message(STATUS "RESOURCE_FILE : " ${RESOURCE_FILE})

set_target_properties(PRAY PROPERTIES
        RESOURCE "${RESOURCE_FILE}"
        )

# Install to project root
install(TARGETS PRAY DESTINATION ${PRAY_SOURCE_DIR})
cmake_minimum_required(VERSION 2.6)
project(PRAY)

message(STATUS "PRAY_SOURCE_DIR : " ${PRAY_SOURCE_DIR})

#-------------------------------------------------------------------------------
# PRAY paths
#-------------------------------------------------------------------------------
set(PRAY_INCLUDE_DIRS "${PRAY_SOURCE_DIR}/PRay/include")


##################
# Build on Linux #
##################
set(LINUX UNIX AND NOT APPLE)
if(UNIX)

    # GCC configuration
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

        set(GCC_CXX_FLAGS "-std=gnu++11 -m64")

        message(STATUS "0")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lpthread")

        # Debug configuration
        if(BUILD_DEBUG)
            set(CMAKE_BUILD_TYPE Debug)
        else(BUILD_DEBUG)
            set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -O3")
            set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -fopenmp")
        endif(BUILD_DEBUG)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")

    endif()

    # Clang configuration (experimental)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        set(CLANG_CXX_FLAGS "-std=c++11 -m64")

        if(BUILD_DEBUG)
            set(CMAKE_BUILD_TYPE Debug)
        else(BUILD_DEBUG)
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -O3")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -funroll-loops")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-narrowing")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-register")
        endif(BUILD_DEBUG)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")

    endif()

endif(UNIX)

####################
# Build on Windows #
####################
if(WIN32)

    if(MSVC)

#        set(MSVC_CXX_FLAGS "-std=gnu++11")
        set(CMAKE_BUILD_TYPE Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

    endif(MSVC)

    if(MINGW)

        set(MSVC_CXX_FLAGS "-std=gnu++11")
        set(CMAKE_BUILD_TYPE Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

    endif(MINGW)

endif(WIN32)

#-------------------------------------------------------------------------------
# Find dependencies
#-------------------------------------------------------------------------------

# stb_image
#include_directories("${PRAY_SOURCE_DIR}/deps/Extras")

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
        ${PRAY_INCLUDE_DIRS}
)


#-------------------------------------------------------------------------------
# Set Resources directories
#-------------------------------------------------------------------------------
set(RESOURCES_DIR "${PRAY_SOURCE_DIR}/Resources")
set(RESOURCE_FILE ${RESOURCES_DIR}/objects/rock/cubeEdit.obj)

#-------------------------------------------------------------------------------
# Add subdirectories
#-------------------------------------------------------------------------------

# PRAY library source directory
add_subdirectory("PRay")


#-------------------------------------------------------------------------------
# Packing
#-------------------------------------------------------------------------------

# Install settings
set(CMAKE_INSTALL_PREFIX "${PRAY_SOURCE_DIR}")
cmake_minimum_required ( VERSION 3.2.0 )
project ( SubtractiveTerrain )

# namespace used for project
set ( PROJECT_NAMESPACE srt )

# The version number.
set ( PROJECT_VERSION_MAJOR 1 )
set ( PROJECT_VERSION_MINOR 0 )
set ( PROJECT_VERSION_PATCH 0 )

# required before DefaultProjectLibrary.cmake
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )

# other paths
set( SHARED_PATH ${PROJECT_SOURCE_DIR}/shared )
set( RES_PATH    ${PROJECT_SOURCE_DIR}/res    )
set( SHADER_PATH ${RES_PATH}/shaders          )

set( PROJECT_CONFIG_FILE ${SHARED_PATH}/src/common/ProjectConfig.hpp.in )


set( USE_GLFW   ON CACHE BOOL "" FORCE )
set( USE_VULKAN ON CACHE BOOL "" FORCE )
#set( USE_GLM  ON CACHE BOOL "" FORCE )

# set variables from shared simulation project
add_subdirectory( ${SHARED_PATH} )


# system header dirs
set(
    PROJECT_SYSTEM_INCLUDE_DIRS
    ${SHARED_SYSTEM_INCLUDE_DIRS}
    )

# libraries to link against
set(
    PROJECT_LINK_LIBS
    ${SHARED_LINK_LIBS}
    )

# must be built before project lib
set(
    PROJECT_DEP_TARGETS
    ${SHARED_DEP_TARGETS}
    )


# header dirs
set(
    PROJECT_INCLUDE_DIRS

    ${SHARED_INCLUDE_DIRS}

    ${SRC_DIR}/io
    )

# cpp files
set(
    PROJECT_SOURCE

    ${SHARED_SOURCE}

    # rendering
    ${SRC_DIR}/io/TerrainIOHandler.cpp


    )

## headers to install
#set(
#    PROJECT_INSTALL_HEADERS
#    ${SRC_DIR}/driver/Driver.hpp
#    ${SRC_DIR}/io/IOHandler.hpp
#    ${SRC_DIR}/world/World.hpp
#    )

# file with main function
set( PROJECT_MAIN ${SRC_DIR}/TerrainMain.cpp )

include( common/cmake/DefaultProjectLibrary.cmake )


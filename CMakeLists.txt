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
set( RES_PATH    ${PROJECT_SOURCE_DIR}/res        )
set( SHADER_PATH ${RES_PATH}/shaders              )
set( THIRDPARTY  ${PROJECT_SOURCE_DIR}/thirdparty )

set( PROJECT_CONFIG_FILE ${SRC_DIR}/common/ProjectConfig.hpp.in )


#
# add glfw3 functionality
#
set( GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory( ${THIRDPARTY}/glfw )

#
# add vulkan functionality
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     ${THIRDPARTY}/glfw/CMake/modules )

find_package( Vulkan REQUIRED )


# system header dirs
set(
    PROJECT_SYSTEM_INCLUDE_DIRS
    ${THIRDPARTY}/include
    ${THIRDPARTY}/glfw/include
    ${VULKAN_INCLUDE_DIR}
    )

# libraries to link against
set(
    PROJECT_LINK_LIBS
    glfw
    ${VULKAN_LIBRARY}
    )

# must be built before project lib
set(
    PROJECT_DEP_TARGETS
    glfw
    )

# header dirs
set(
    PROJECT_INCLUDE_DIRS
    ${SRC_DIR}/common
    ${SRC_DIR}/driver
    ${SRC_DIR}/rendering
    ${SRC_DIR}/graphics
    ${SRC_DIR}/graphics/vulkan
    ${SRC_DIR}/world
    )

# cpp files
set(
    PROJECT_SOURCE

    # driver
    ${SRC_DIR}/driver/Driver.cpp

    # rendering
    ${SRC_DIR}/rendering/IOHandler.cpp

    # graphics/vulkan
    ${SRC_DIR}/graphics/vulkan/VulkanGlfwWrapper.cpp

    # graphics/dx12
    # ${SRC_DIR}/graphics/vulkan/DX12Wrapper.cpp

    # world
    ${SRC_DIR}/world/World.cpp

    )

# headers to install
set(
    PROJECT_INSTALL_HEADERS
    ${SRC_DIR}/driver/Driver.hpp
    ${SRC_DIR}/rendering/IOHandler.hpp
    ${SRC_DIR}/world/World.hpp
    )

# file with main function
set( PROJECT_MAIN ${SRC_DIR}/ExampleMain.cpp )

include( common/cmake/DefaultProjectLibrary.cmake )


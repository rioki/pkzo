cmake_minimum_required(VERSION 3.21)

project(pkzo VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(Iconv REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(tinyformat CONFIG REQUIRED)
find_package(fkYAML CONFIG REQUIRED)
find_package(rsig CONFIG REQUIRED)
find_package(FreeImage CONFIG REQUIRED)


function(pkzo_link_first_available target)
  set(options)
  set(one_value_args)
  set(multi_value_args CANDIDATES)
  cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "${one_value_args}" "${multi_value_args}")

  foreach(candidate IN LISTS ARG_CANDIDATES)
    if(TARGET "${candidate}")
      target_link_libraries(${target} PUBLIC "${candidate}")
      return()
    endif()
  endforeach()

  message(FATAL_ERROR "Could not find any usable target for ${target}. Tried: ${ARG_CANDIDATES}")
endfunction()

function(pkzo_install_headers target source_dir)
  install(
    DIRECTORY "${source_dir}/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${target}"
    FILES_MATCHING
      PATTERN "*.h"
  )
endfunction()

set(PKZO_SOURCES
  pkzo/Bounds.cpp
  pkzo/CubeMap.cpp
  pkzo/debug.cpp
  pkzo/events.cpp
  pkzo/Font.cpp
  pkzo/FreeImageTexture.cpp
  pkzo/FreeTypeFont.cpp
  pkzo/GraphicContext.cpp
  pkzo/Keyboard.cpp
  pkzo/MemoryMesh.cpp
  pkzo/Mesh.cpp
  pkzo/Mouse.cpp
  pkzo/OpenGLBuffer.cpp
  pkzo/OpenGLCubeMap.cpp
  pkzo/OpenGLFrameBuffer.cpp
  pkzo/OpenGLGraphicContext.cpp
  pkzo/OpenGLMesh.cpp
  pkzo/OpenGLShader.cpp
  pkzo/OpenGLTexture.cpp
  pkzo/SdlSentry.cpp
  pkzo/strconv.cpp
  pkzo/Texture.cpp
  pkzo/Window.cpp
)

add_library(pkzo ${PKZO_SOURCES})
add_library(pkzo::pkzo ALIAS pkzo)

target_compile_definitions(pkzo PRIVATE BUILD_PKZO STRCONV_DLL BUILD_STRCONV)
target_include_directories(pkzo
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(pkzo
  PUBLIC
    glm::glm
    nlohmann_json::nlohmann_json
    Iconv::Iconv
)

pkzo_link_first_available(pkzo CANDIDATES magic_enum::magic_enum magic_enum::magic_enum-header-only)
pkzo_link_first_available(pkzo CANDIDATES tinyformat::tinyformat tinyformat::tinyformat-header-only)
pkzo_link_first_available(pkzo CANDIDATES fkYAML::fkYAML fkYAML::fkYAML-header-only)
pkzo_link_first_available(pkzo CANDIDATES rsig::rsig unofficial::rsig::rsig)
pkzo_link_first_available(pkzo CANDIDATES FreeImage::FreeImage freeimage::FreeImage unofficial::freeimage::FreeImage)
pkzo_link_first_available(pkzo CANDIDATES Freetype::Freetype freetype)
pkzo_link_first_available(pkzo CANDIDATES GLEW::GLEW GLEW::glew unofficial::glew::glew)
pkzo_link_first_available(pkzo CANDIDATES SDL3::SDL3 SDL3::SDL3-static)

set(PKZO2D_SOURCES
  pkzo2d/Group.cpp
  pkzo2d/HitArea.cpp
  pkzo2d/Node.cpp
  pkzo2d/Rectangle.cpp
  pkzo2d/Renderer.cpp
  pkzo2d/Screen.cpp
  pkzo2d/Shape.cpp
  pkzo2d/Text.cpp
)

add_library(pkzo2d ${PKZO2D_SOURCES})
add_library(pkzo::pkzo2d ALIAS pkzo2d)

target_compile_definitions(pkzo2d
  PRIVATE
    BUILD_PKZO2D
    SOLUTION_DIR="${CMAKE_SOURCE_DIR}/"
    PROJECT_DIR="${CMAKE_SOURCE_DIR}/pkzo2d/"
)

target_include_directories(pkzo2d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(pkzo2d PUBLIC pkzo)

set(PKZO3D_SOURCES
  pkzo3d/AmbientLight.cpp
  pkzo3d/Body.cpp
  pkzo3d/BoxGeometry.cpp
  pkzo3d/BulletPhysicsSimulation.cpp
  pkzo3d/Camera.cpp
  pkzo3d/CylinderGeometry.cpp
  pkzo3d/DirectionalLight.cpp
  pkzo3d/Geometry.cpp
  pkzo3d/Ghost.cpp
  pkzo3d/Group.cpp
  pkzo3d/Light.cpp
  pkzo3d/Material.cpp
  pkzo3d/MeshGeometry.cpp
  pkzo3d/Model.cpp
  pkzo3d/ModelInstance.cpp
  pkzo3d/Node.cpp
  pkzo3d/PhysicsSimulation.cpp
  pkzo3d/PointLight.cpp
  pkzo3d/Renderer.cpp
  pkzo3d/Scene.cpp
  pkzo3d/SkyBox.cpp
  pkzo3d/SphereGeometry.cpp
  pkzo3d/SpotLight.cpp
)

add_library(pkzo3d ${PKZO3D_SOURCES})
add_library(pkzo::pkzo3d ALIAS pkzo3d)

target_compile_definitions(pkzo3d
  PRIVATE
    BUILD_PKZO3D
    SOLUTION_DIR="${CMAKE_SOURCE_DIR}/"
    PROJECT_DIR="${CMAKE_SOURCE_DIR}/pkzo3d/"
)

target_include_directories(pkzo3d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(pkzo3d
  PUBLIC
    pkzo
    assimp::assimp
)

pkzo_link_first_available(pkzo3d CANDIDATES Bullet::BulletDynamics BulletDynamics)
pkzo_link_first_available(pkzo3d CANDIDATES Bullet::BulletCollision BulletCollision)
pkzo_link_first_available(pkzo3d CANDIDATES Bullet::LinearMath LinearMath)

if(WIN32)
  target_link_libraries(pkzo PRIVATE dbghelp)
endif()

install(TARGETS pkzo pkzo2d pkzo3d
  EXPORT pkzoTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

pkzo_install_headers(pkzo pkzo)
pkzo_install_headers(pkzo2d pkzo2d)
pkzo_install_headers(pkzo3d pkzo3d)

install(
  EXPORT pkzoTargets
  NAMESPACE pkzo::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pkzo
)

configure_package_config_file(
  cmake/pkzoConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/pkzoConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pkzo
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/pkzoConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pkzoConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/pkzoConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pkzo
)

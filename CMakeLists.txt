cmake_minimum_required(VERSION 3.21)
project(pkzo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(fkYAML CONFIG REQUIRED)
find_package(FreeImage CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Iconv CONFIG REQUIRED)
find_package(magic-enum CONFIG REQUIRED)
find_package(nlohmann-json CONFIG REQUIRED)
find_package(rsig CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(tinyformat CONFIG REQUIRED)

# pkzo

set(SOURCES_PKZO
    pkzo\Bounds.cpp
    pkzo\CubeMap.cpp
    pkzo\debug.cpp
    pkzo\events.cpp
    pkzo\Font.cpp
    pkzo\FreeImageTexture.cpp
    pkzo\FreeTypeFont.cpp
    pkzo\GraphicContext.cpp
    pkzo\Keyboard.cpp
    pkzo\MemoryMesh.cpp
    pkzo\Mesh.cpp
    pkzo\Mouse.cpp
    pkzo\OpenGLBuffer.cpp
    pkzo\OpenGLCubeMap.cpp
    pkzo\OpenGLFrameBuffer.cpp
    pkzo\OpenGLGraphicContext.cpp
    pkzo\OpenGLMesh.cpp
    pkzo\OpenGLShader.cpp
    pkzo\OpenGLTexture.cpp
    pkzo\SdlSentry.cpp
    pkzo\strconv.cpp
    pkzo\Texture.cpp
    pkzo\Window.cpp
)

add_library(pkzo ${SOURCES_PKZO})
add_library(pkzo::pkzo ALIAS pkzo)
target_compile_definitions(pkzo PRIVATE BUILD_PKZO STRCONV_DLL BUILD_STRCONV)
target_link_libraries(pkzo PUBLIC assimp::assimp)
target_link_libraries(pkzo PUBLIC bullet3::bullet3)
target_link_libraries(pkzo PUBLIC fkyaml::fkyaml)
target_link_libraries(pkzo PUBLIC freeimage::freeimage)
target_link_libraries(pkzo PUBLIC freetype::freetype)
target_link_libraries(pkzo PUBLIC GLEW::GLEW)
target_link_libraries(pkzo PUBLIC glm::glm)
target_link_libraries(pkzo PUBLIC libiconv::libiconv)
target_link_libraries(pkzo PUBLIC magic-enum::magic-enum)
target_link_libraries(pkzo PUBLIC nlohmann-json::nlohmann-json)
target_link_libraries(pkzo PUBLIC rsig::rsig)
target_link_libraries(pkzo PUBLIC sdl3::sdl3)
target_link_libraries(pkzo PUBLIC tinyformat::tinyformat)

# pkzo2d

set(SOURCES_PKZO2D
    pkzo2d\Group.cpp
    pkzo2d\HitArea.cpp
    pkzo2d\Node.cpp
    pkzo2d\Rectangle.cpp
    pkzo2d\Renderer.cpp
    pkzo2d\Screen.cpp
    pkzo2d\Shape.cpp
    pkzo2d\Text.cpp
)

add_library(pkzo2d ${SOURCES_PKZO2D})
target_link_libraries(pkzo2d PUBLIC assimp::assimp)
target_link_libraries(pkzo2d PUBLIC bullet3::bullet3)
target_link_libraries(pkzo2d PUBLIC fkyaml::fkyaml)
target_link_libraries(pkzo2d PUBLIC freeimage::freeimage)
target_link_libraries(pkzo2d PUBLIC freetype::freetype)
target_link_libraries(pkzo2d PUBLIC GLEW::GLEW)
target_link_libraries(pkzo2d PUBLIC glm::glm)
target_link_libraries(pkzo2d PUBLIC libiconv::libiconv)
target_link_libraries(pkzo2d PUBLIC magic-enum::magic-enum)
target_link_libraries(pkzo2d PUBLIC nlohmann-json::nlohmann-json)
target_link_libraries(pkzo2d PUBLIC rsig::rsig)
target_link_libraries(pkzo2d PUBLIC sdl3::sdl3)
target_link_libraries(pkzo2d PUBLIC tinyformat::tinyformat)

# pkzo3d

set(SOURCES_PKZO3D
    pkzo3d\AmbientLight.cpp
    pkzo3d\Body.cpp
    pkzo3d\BoxGeometry.cpp
    pkzo3d\BulletPhysicsSimulation.cpp
    pkzo3d\Camera.cpp
    pkzo3d\CylinderGeometry.cpp
    pkzo3d\DirectionalLight.cpp
    pkzo3d\Geometry.cpp
    pkzo3d\Ghost.cpp
    pkzo3d\Group.cpp
    pkzo3d\Light.cpp
    pkzo3d\Material.cpp
    pkzo3d\MeshGeometry.cpp
    pkzo3d\Model.cpp
    pkzo3d\ModelInstance.cpp
    pkzo3d\Node.cpp
    pkzo3d\PhysicsSimulation.cpp
    pkzo3d\PointLight.cpp
    pkzo3d\Renderer.cpp
    pkzo3d\Scene.cpp
    pkzo3d\SkyBox.cpp
    pkzo3d\SphereGeometry.cpp
    pkzo3d\SpotLight.cpp
)

add_library(pkzo3d ${SOURCES_PKZO2D})
target_link_libraries(pkzo3d PUBLIC assimp::assimp)
target_link_libraries(pkzo3d PUBLIC bullet3::bullet3)
target_link_libraries(pkzo3d PUBLIC fkyaml::fkyaml)
target_link_libraries(pkzo3d PUBLIC freeimage::freeimage)
target_link_libraries(pkzo3d PUBLIC freetype::freetype)
target_link_libraries(pkzo3d PUBLIC GLEW::GLEW)
target_link_libraries(pkzo3d PUBLIC glm::glm)
target_link_libraries(pkzo3d PUBLIC libiconv::libiconv)
target_link_libraries(pkzo3d PUBLIC magic-enum::magic-enum)
target_link_libraries(pkzo3d PUBLIC nlohmann-json::nlohmann-json)
target_link_libraries(pkzo3d PUBLIC rsig::rsig)
target_link_libraries(pkzo3d PUBLIC sdl3::sdl3)
target_link_libraries(pkzo3d PUBLIC tinyformat::tinyformat)

# install

install(
  TARGETS pkzo pkzo2d pkzo3d
  EXPORT pkzoTargets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(
  DIRECTORY "pkzo/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pkzo"
  FILES_MATCHING
    PATTERN "*.h"
)

install(
  DIRECTORY "pkzo2d/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pkzo2d"
  FILES_MATCHING
    PATTERN "*.h"
)


install(
  DIRECTORY "pkzo3d/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pkzo3d"
  FILES_MATCHING
    PATTERN "*.h"
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(${PROJECT_SOURCE_DIR}/pkzoConfig.cmake.in
                                rioki_glowConfig.cmake
                                INSTALL_DESTINATION share/pkzo)

install(FILES
        "${PROJECT_BINARY_DIR}/pkzoConfig.cmake"
        "${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
        DESTINATION share/pkzo
)

install(EXPORT pkzoTargets
        NAMESPACE pkzo::
        DESTINATION share/pkzo
)

cmake_minimum_required(VERSION 3.21)
project(pkzo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

find_path(RSIG_INCLUDE_DIRS "rsig/rsig.h")
find_path(RSIG_INCLUDE_DIRS "tinyformat.h")

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(fkYAML CONFIG REQUIRED)
find_package(FreeImage CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Iconv REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

# pkzo

file(GLOB PKZO_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/pkzo/*.cpp"
)

add_library(pkzo ${PKZO_SOURCES})
target_compile_definitions(pkzo PRIVATE BUILD_PKZO STRCONV_DLL BUILD_STRCONV)
target_include_directories(pkzo PUBLIC ${RSIG_INCLUDE_DIRS} ${TINYFORMAT_INCLUDE_DIRS})
target_link_libraries(pkzo PRIVATE freetype::freetype)
target_link_libraries(pkzo PRIVATE GLEW::GLEW)
target_link_libraries(pkzo PUBLIC glm::glm)
target_link_libraries(pkzo PRIVATE Iconv::Iconv)
target_link_libraries(main PUBLIC magic_enum::magic_enum)
target_link_libraries(pkzo PUBLIC rsig::rsig)
target_link_libraries(pkzo PRIVATE sdl3::sdl3)

# pkzo2d

file(GLOB PKZO2D_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/pkzo2d/*.cpp"
)

add_library(pkzo2d ${PKZO2D_SOURCES})
target_compile_definitions(pkzo PRIVATE BUILD_PKZO2D)
target_link_libraries(pkzo2d PUBLIC pkzo)

# pkzo3d

file(GLOB PKZO3D_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/pkzo3d/*.cpp"
)

add_library(pkzo3d ${PKZO3D_SOURCES})
target_compile_definitions(pkzo PRIVATE BUILD_PKZO3D)
target_link_libraries(pkzo2d PUBLIC pkzo)
target_link_libraries(pkzo3d PRIVATE assimp::assimp)
target_link_libraries(pkzo3d PRIVATE ${BULLET_LIBRARIES})
target_link_libraries(pkzo3d PUBLIC fkYAML::fkYAML )
target_link_libraries(pkzo3d PUBLIC nlohmann_json::nlohmann_json)

# build config 

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(${PROJECT_SOURCE_DIR}/pkzoConfig.cmake.in
                                rioki_glowConfig.cmake
                                INSTALL_DESTINATION share/pkzo)

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

install(FILES
        "${PROJECT_BINARY_DIR}/pkzoConfig.cmake"
        "${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
        DESTINATION share/pkzo
)

install(EXPORT pkzoTargets
        NAMESPACE pkzo::
        DESTINATION share/pkzo
)

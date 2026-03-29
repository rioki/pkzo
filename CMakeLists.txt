cmake_minimum_required(VERSION 3.21)
project(pkzo VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

find_path(RSIG_INCLUDE_DIRS "rsig/rsig.h")
find_path(TINYFORMAT_INCLUDE_DIRS "tinyformat.h")

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(fkYAML CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Iconv REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

# pkzo

file(GLOB PKZO_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/pkzo/*.cpp")
add_library(pkzo SHARED ${PKZO_SOURCES})

target_compile_definitions(pkzo PRIVATE BUILD_PKZO STRCONV_DLL BUILD_STRCONV)

target_include_directories(pkzo
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(pkzo PRIVATE ${RSIG_INCLUDE_DIRS} ${TINYFORMAT_INCLUDE_DIRS})

target_link_libraries(pkzo PUBLIC glm::glm)
target_link_libraries(pkzo PUBLIC magic_enum::magic_enum)

target_link_libraries(pkzo PRIVATE Freetype::Freetype)
target_link_libraries(pkzo PRIVATE freeimage::FreeImage freeimage::FreeImagePlus)
target_link_libraries(pkzo PRIVATE GLEW::GLEW)
target_link_libraries(pkzo PRIVATE Iconv::Iconv)
target_link_libraries(pkzo PRIVATE SDL3::SDL3)
target_link_libraries(pkzo PRIVATE assimp::assimp)
target_link_libraries(pkzo PRIVATE ${BULLET_LIBRARIES})
target_link_libraries(pkzo PRIVATE fkYAML::fkYAML)
target_link_libraries(pkzo PRIVATE nlohmann_json::nlohmann_json)

# package config
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/pkzoConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/pkzoConfig.cmake"
  INSTALL_DESTINATION "share/pkzo"
)

# install
install(TARGETS pkzo pkzo2d pkzo3d
  EXPORT pkzoTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(DIRECTORY pkzo/   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pkzo"   FILES_MATCHING PATTERN "*.h")

install(FILES
  "${PROJECT_BINARY_DIR}/pkzoConfig.cmake"
  "${PROJECT_BINARY_DIR}/pkzoConfigVersion.cmake"
  DESTINATION "share/pkzo"
)

install(EXPORT pkzoTargets
  NAMESPACE pkzo::
  DESTINATION "share/pkzo"
)

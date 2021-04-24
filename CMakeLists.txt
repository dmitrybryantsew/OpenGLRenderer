cmake_minimum_required(VERSION 3.5)

set(HUNTER_ROOT  "E://.hunter")


#SET(GCC_COVERAGE_COMPILE_FLAGS -shared -nostartfiles)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/HunterGate.cmake)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.253.tar.gz"
    SHA1 "88ea6d37c897a81a080eb9ae0f69d7807bbb3c73"
    LOCAL
)



project(templateProject)


hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)
#include_directories(${GLEW_ROOT})
message("trying to get glfw")
hunter_add_package(glfw)
find_package(glfw3 REQUIRED)
message("Done")
#find_package(SDL2)

hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

#assimp
hunter_add_package(Assimp)
#include_directories( vendor/assimp-5.0.1/include/)
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
find_package(Assimp CONFIG REQUIRED)

#boost
hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(stb_image 
        vendor/stb_image/stb_image.cpp
        )
#file(GLOB_RECURSE IMGUI_SOURCES vendor/imgui/*.cpp)
#message(${IMGUI_SOURCES})

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
    message("glew found at ${GLEW_INCLUDE_DIRS}")
endif()

hunter_add_package(glbinding)
find_package(glbinding CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)

add_library(imgui
        STATIC
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_impl_glfw_gl3.cpp)
target_link_libraries (imgui ${OPENGL_LIBRARY} glfw glew::glew)

message("trying to BUILD unistd ")
add_library(unistd INTERFACE)
target_include_directories(unistd
INTERFACE
${PROJECT_SOURCE_DIR}/vendor/libunistd/unistd)
message("Done ")

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} src/Texture.cpp src/Texture.hpp src/AmbientLight.cpp src/AmbientLight.hpp)
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARY} stb_image imgui glew::glew glm unistd Assimp::assimp Boost::boost)

include_directories(vendor/stb_image)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor/stb_image)

include_directories(vendor/imgui)
target_link_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor/imgui )

include_directories(vendor/libunistd/unistd)
target_include_directories(${PROJECT_NAME} 
PUBLIC
${PROJECT_SOURCE_DIR}/vendor/libunistd/unistd)

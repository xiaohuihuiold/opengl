cmake_minimum_required(VERSION 3.13)
project(opengl_glfw03)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_INCLUDE ./include)
set(PROJECT_LIBRARIES ./lib)

include_directories(${PROJECT_INCLUDE})
link_directories(${PROJECT_LIBRARIES})

add_library(glad SHARED ./src/glad/glad.c)
add_library(stb_image SHARED ./src/stb_image/stb_image.cpp)

add_executable(opengl_glfw03 src/main.cpp)

target_link_libraries(opengl_glfw03 glad)
target_link_libraries(opengl_glfw03 stb_image)
target_link_libraries(opengl_glfw03 glfw3)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(opengl_glfw02 GLEW)
    target_link_libraries(opengl_glfw02 GL)
    target_link_libraries(opengl_glfw02 X11)
    target_link_libraries(opengl_glfw02 pthread)
    target_link_libraries(opengl_glfw02 Xrandr)
    target_link_libraries(opengl_glfw02 Xi)
    target_link_libraries(opengl_glfw02 Xxf86vm)
    target_link_libraries(opengl_glfw02 Xinerama)
    target_link_libraries(opengl_glfw02 Xcursor)
    target_link_libraries(opengl_glfw02 rt)
    target_link_libraries(opengl_glfw02 m)
    target_link_libraries(opengl_glfw02 dl)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")

ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
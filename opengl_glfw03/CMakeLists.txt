cmake_minimum_required(VERSION 3.13)
project(opengl_glfw03)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_INCLUDE ./include)

include_directories(${PROJECT_INCLUDE})

add_library(glad SHARED ./src/glad/glad.c)
add_library(stb_image SHARED ./src/stb_image/stb_image.cpp)

add_executable(opengl_glfw03 src/main.cpp)

target_link_libraries(opengl_glfw03 glad)
target_link_libraries(opengl_glfw03 stb_image)
target_link_libraries(opengl_glfw03 GLEW)
target_link_libraries(opengl_glfw03 glfw3)
target_link_libraries(opengl_glfw03 GL)
target_link_libraries(opengl_glfw03 X11)
target_link_libraries(opengl_glfw03 pthread)
target_link_libraries(opengl_glfw03 Xrandr)
target_link_libraries(opengl_glfw03 Xi)
target_link_libraries(opengl_glfw03 Xxf86vm)
target_link_libraries(opengl_glfw03 Xinerama)
target_link_libraries(opengl_glfw03 Xcursor)
target_link_libraries(opengl_glfw03 rt)
target_link_libraries(opengl_glfw03 m)
target_link_libraries(opengl_glfw03 dl)
cmake_minimum_required(VERSION 3.15)
project(opengl_model)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件目录
set(PROJECT_INCLUDE ./include)
include_directories(${PROJECT_INCLUDE})
# 添加库目录
set(PROJECT_LIBRARY ./lib)
link_directories(${PROJECT_LIBRARY})

# 添加glad
add_library(glad SHARED ./src/glad/glad.c)
# 添加stb image
add_library(stb_image SHARED ./src/stb_image/stb_image.cpp)

# 添加项目主程序
add_executable(opengl_model ./src/main.cpp)

# 连接库 (通用)
target_link_libraries(opengl_model glad)
target_link_libraries(opengl_model stb_image)
target_link_libraries(opengl_model glfw3)

# 连接库 (按平台)
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Linux需要的库
    target_link_libraries(opengl_model GLEW)
    target_link_libraries(opengl_model GL)
    target_link_libraries(opengl_model X11)
    target_link_libraries(opengl_model pthread)
    target_link_libraries(opengl_model Xrandr)
    target_link_libraries(opengl_model Xi)
    target_link_libraries(opengl_model Xxf86vm)
    target_link_libraries(opengl_model Xinerama)
    target_link_libraries(opengl_model Xcursor)
    target_link_libraries(opengl_model rt)
    target_link_libraries(opengl_model m)
    target_link_libraries(opengl_model dl)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Windows需要的库
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    # MacOS?
ELSE ()
    # 运行在未知的系统
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF ()
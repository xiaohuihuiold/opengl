cmake_minimum_required(VERSION 3.13)
project(opengl01)

set(CMAKE_CXX_STANDARD 14)

add_executable(opengl01 main.cpp)

target_link_libraries(opengl01 glut)
target_link_libraries(opengl01 GL)
target_link_libraries(opengl01 GLU)
target_link_libraries(opengl01 m)
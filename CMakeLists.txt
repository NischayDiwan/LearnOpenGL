cmake_minimum_required(VERSION 3.22)

project(LearnOpenGL)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(learnOpenGL src/main.cpp src/glad.c)

target_include_directories(learnOpenGL PUBLIC include)
target_link_libraries(learnOpenGL PUBLIC glfw OpenGL::GL)

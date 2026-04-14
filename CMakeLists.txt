cmake_minimum_required(VERSION 4.2)
project(LearningOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

find_package(OpenGL REQUIRED)

if(WIN32)
  set(GLFW_LIB "${LIB_DIR}/windows/glfw3.lib")
  set(PLATFORM_LIBS opengl32)
elseif(UNIX)
  set(GLFW_LIB "${LIB_DIR}/linux/libglfw3.a")
  set(PLATFORM_LIBS GL dl X11 Xrandr Xi Xxf86vm Xcursor pthread)
else()
  message(FATAL_ERROR "Unsupported platform for GLFW linking")
endif()

if(NOT EXISTS "${GLFW_LIB}")
  message(FATAL_ERROR "Missing GLFW library: ${GLFW_LIB}")
endif()

#add_library(glad STATIC "${CMAKE_SOURCE_DIR}/src/glad.c")
#target_include_directories(glad PUBLIC "${INCLUDE_DIR}")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/0_Getting_Started")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Exercises")

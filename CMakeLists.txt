cmake_minimum_required(VERSION 3.14)
project(LearningOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)

include(FetchContent)

find_package(glfw3 3.4 QUIET)

if(NOT glfw3_FOUND)
  message(STATUS "GLFW not found. Downloading...")

  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(
          glfw
          GIT_REPOSITORY https://github.com/glfw/glfw.git
          GIT_TAG        3.4
  )
  FetchContent_MakeAvailable(glfw)
else()
  message(STATUS "GLFW found locally.")
endif()

add_library(glad STATIC "${CMAKE_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${INCLUDE_DIR}")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/0_Getting_Started")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Exercises")

cmake_minimum_required(VERSION 4.2)
project(LearningOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(GLFW_STATIC_LIB "${LIB_DIR}/libglfw3.a")

find_package(OpenGL REQUIRED)

if(NOT EXISTS "${GLFW_STATIC_LIB}")
  message(FATAL_ERROR "Missing GLFW static library: ${GLFW_STATIC_LIB}")
endif()

add_library(glad STATIC "${CMAKE_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${INCLUDE_DIR}")

file(GLOB_RECURSE SAMPLE_MAIN_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*/main.cpp")
if(NOT SAMPLE_MAIN_FILES)
  message(WARNING "No sample main.cpp files found under src/")
endif()

foreach(sample_source IN LISTS SAMPLE_MAIN_FILES)
  get_filename_component(sample_dir "${sample_source}" DIRECTORY)
  get_filename_component(sample_name "${sample_dir}" NAME)
  string(REPLACE " " "_" sample_name "${sample_name}")

  set(target_name "${sample_name}_x86_64")
  add_executable(${target_name} "${sample_source}")
  set_target_properties(${target_name} PROPERTIES OUTPUT_NAME "${sample_name}.x86_64")

  target_include_directories(${target_name} PRIVATE "${INCLUDE_DIR}")
  target_link_libraries(
    ${target_name}
    PRIVATE
      glad
      "${GLFW_STATIC_LIB}"
      OpenGL::GL
      dl
      X11
      Xrandr
      Xi
      Xxf86vm
      Xcursor
      pthread
  )
endforeach()

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

add_library(CoreGL STATIC
        "${CMAKE_SOURCE_DIR}/src/WindowManager.cpp"
        "${CMAKE_SOURCE_DIR}/src/VAO.cpp"
        "${CMAKE_SOURCE_DIR}/src/VBO.cpp"
        "${CMAKE_SOURCE_DIR}/src/EBO.cpp"
        "${CMAKE_SOURCE_DIR}/src/Shader.cpp"
        "${CMAKE_SOURCE_DIR}/src/stb_image.cpp"
)

# Al usar PUBLIC, cualquier ejecutable que enlace CoreGL heredará automáticamente
# los includes, glad, glfw y OpenGL. No tendrás que especificarlos de nuevo.
target_include_directories(CoreGL PUBLIC "${INCLUDE_DIR}")
target_link_libraries(CoreGL PUBLIC glfw glad OpenGL::GL)

# 2. Crear una función para automatizar la creación de ejecutables y copia de recursos
function(add_opengl_exercise TARGET_NAME SOURCE_FILE RESOURCE_DIR)
  add_executable(${TARGET_NAME} ${SOURCE_FILE})
  set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${TARGET_NAME}.x86_64")

  # Enlazamos únicamente con nuestra nueva librería
  target_link_libraries(${TARGET_NAME} PRIVATE CoreGL)

  # Si se proporciona un directorio de recursos válido, configurar la copia automática
  if(EXISTS "${RESOURCE_DIR}")
    add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${RESOURCE_DIR}"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/resources"
            COMMENT "Syncing resources directory for ${TARGET_NAME}..."
    )
  endif()
endfunction()

add_subdirectory("${CMAKE_SOURCE_DIR}/0_Getting_Started")
add_subdirectory("${CMAKE_SOURCE_DIR}/Exercises")



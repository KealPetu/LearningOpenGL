cmake_minimum_required(VERSION 3.16)

project(LearningOpenGL LANGUAGES C CXX)

include(FetchContent)

# =========================
# Paths
# =========================
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

# =========================
# Dependencies
# =========================
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 QUIET)
find_package(glm 1.0.3 QUIET)

# GLFW
if(NOT glfw3_FOUND)
  message(STATUS "Fetching GLFW...")
  FetchContent_Declare(
          glfw
          GIT_REPOSITORY https://github.com/glfw/glfw.git
          GIT_TAG 3.4
  )
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(glfw)
endif()

# GLM
if(NOT glm_FOUND)
  message(STATUS "Fetching GLM...")
  FetchContent_Declare(
          glm
          GIT_REPOSITORY https://github.com/g-truc/glm.git
          GIT_TAG 1.0.3
  )
  FetchContent_MakeAvailable(glm)
endif()

# ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.7
)
FetchContent_MakeAvailable(imgui)

add_library(ImGui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(ImGui PUBLIC glfw OpenGL::GL)

# =========================
# Core Engine
# =========================
add_library(CoreGL STATIC
        ${SRC_DIR}/glad.c
        ${SRC_DIR}/stb_image.cpp
        ${SRC_DIR}/WindowManager.cpp
        ${SRC_DIR}/VAO.cpp
        ${SRC_DIR}/VBO.cpp
        ${SRC_DIR}/EBO.cpp
        ${SRC_DIR}/Shader.cpp
        ${SRC_DIR}/Texture.cpp
)

target_include_directories(CoreGL PUBLIC ${INC_DIR})

target_compile_features(CoreGL PUBLIC cxx_std_20)

target_link_libraries(CoreGL PUBLIC
        glfw
        glm
        OpenGL::GL
        ImGui
)

# =========================
# Helper
# =========================
function(add_opengl_exercise NAME FILE RESOURCE_DIR)
  add_executable(${NAME} ${FILE})
  target_link_libraries(${NAME} PRIVATE CoreGL)

  if(EXISTS ${RESOURCE_DIR})
    add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCE_DIR}
            $<TARGET_FILE_DIR:${NAME}>/resources
    )
  endif()
endfunction()

# =========================
# Subdirs
# =========================
add_subdirectory(0_Getting_Started)
add_subdirectory(Exercises)
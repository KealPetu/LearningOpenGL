add_executable(Triangles_x86_64 Triangles.cpp ../../WindowManager.cpp ../../glad.c)
set_target_properties(Triangles_x86_64 PROPERTIES OUTPUT_NAME "Triangles.x86_64")

target_include_directories(Triangles_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles_x86_64 PRIVATE "${GLFW_LIB}" OpenGL::GL ${PLATFORM_LIBS})

add_executable(Triangles2_x86_64 Triangles2.cpp ../../WindowManager.cpp ../../glad.c)
set_target_properties(Triangles2_x86_64 PROPERTIES OUTPUT_NAME "Triangles2.x86_64")

target_include_directories(Triangles2_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles2_x86_64 PRIVATE "${GLFW_LIB}" OpenGL::GL ${PLATFORM_LIBS})
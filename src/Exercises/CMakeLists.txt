add_executable(Triangles_x86_64 Triangles.cpp ../WindowManager.cpp ../glad.c)
set_target_properties(Triangles_x86_64 PROPERTIES OUTPUT_NAME "Triangles.x86_64")

target_include_directories(Triangles_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles_x86_64 PRIVATE glfw OpenGL::GL)

add_executable(Triangles2_x86_64 Triangles2.cpp ../WindowManager.cpp ../glad.c)
set_target_properties(Triangles2_x86_64 PROPERTIES OUTPUT_NAME "Triangles2.x86_64")

target_include_directories(Triangles2_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles2_x86_64 PRIVATE glfw OpenGL::GL)

add_executable(Triangles3_x86_64 Triangles3.cpp ../WindowManager.cpp ../glad.c)
set_target_properties(Triangles3_x86_64 PROPERTIES OUTPUT_NAME "Triangles3.x86_64")

target_include_directories(Triangles3_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles3_x86_64 PRIVATE glfw OpenGL::GL)

add_executable(Polygon_x86_64 Polygon.cpp ../WindowManager.cpp ../VAO.cpp ../VBO.cpp ../glad.c)
set_target_properties(Polygon_x86_64 PROPERTIES OUTPUT_NAME "Polygon.x86_64")

target_include_directories(Polygon_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Polygon_x86_64 PRIVATE glfw OpenGL::GL)

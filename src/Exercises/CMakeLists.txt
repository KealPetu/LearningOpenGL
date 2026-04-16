add_executable(Triangles Triangles.cpp ../WindowManager.cpp)
set_target_properties(Triangles PROPERTIES OUTPUT_NAME "Triangles.x86_64")

target_include_directories(Triangles PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles PRIVATE glfw glad OpenGL::GL)

add_executable(Triangles2 Triangles2.cpp ../WindowManager.cpp)
set_target_properties(Triangles2 PROPERTIES OUTPUT_NAME "Triangles2.x86_64")

target_include_directories(Triangles2 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles2 PRIVATE glfw glad OpenGL::GL)

add_executable(Triangles3 Triangles3.cpp ../WindowManager.cpp)
set_target_properties(Triangles3 PROPERTIES OUTPUT_NAME "Triangles3.x86_64")

target_include_directories(Triangles3 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Triangles3 PRIVATE glfw glad OpenGL::GL)

add_executable(Polygon Polygon.cpp ../WindowManager.cpp ../VAO.cpp ../VBO.cpp ../EBO.cpp)
set_target_properties(Polygon PROPERTIES OUTPUT_NAME "Polygon.x86_64")

target_include_directories(Polygon PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Polygon PRIVATE glfw glad OpenGL::GL)

add_executable(ReversedTriangle ReversedTriangle.cpp ../WindowManager.cpp ../VAO.cpp ../VBO.cpp ../EBO.cpp ../Shader.cpp)
set_target_properties(ReversedTriangle PROPERTIES OUTPUT_NAME "ReversedTriangle.x86_64")

target_include_directories(ReversedTriangle PRIVATE "${INCLUDE_DIR}")
target_link_libraries(ReversedTriangle PRIVATE glfw glad OpenGL::GL)

add_executable(Offset Offset.cpp ../WindowManager.cpp ../VAO.cpp ../VBO.cpp ../EBO.cpp ../Shader.cpp)
set_target_properties(Offset PROPERTIES OUTPUT_NAME "Offset.x86_64")

target_include_directories(Offset PRIVATE "${INCLUDE_DIR}")
target_link_libraries(Offset PRIVATE glfw glad OpenGL::GL)


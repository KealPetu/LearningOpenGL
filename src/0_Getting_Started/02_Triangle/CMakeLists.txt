add_executable(02_Triangle_x86_64 Triangle.cpp ../../WindowManager.cpp ../../glad.c)
set_target_properties(02_Triangle_x86_64 PROPERTIES OUTPUT_NAME "02_Triangle.x86_64")

target_include_directories(02_Triangle_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(02_Triangle_x86_64 PRIVATE glfw glad OpenGL::GL)

add_executable(02_EBO_x86_64 EBO.cpp ../../WindowManager.cpp ../../glad.c)
set_target_properties(02_EBO_x86_64 PROPERTIES OUTPUT_NAME "02_EBO.x86_64")

target_include_directories(02_EBO_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(02_EBO_x86_64 PRIVATE glfw glad OpenGL::GL)


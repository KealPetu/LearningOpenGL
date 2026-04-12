add_executable(02_Triangle_x86_64 main.cpp Window.cpp)
set_target_properties(02_Triangle_x86_64 PROPERTIES OUTPUT_NAME "02_Triangle.x86_64")

target_include_directories(02_Triangle_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(02_Triangle_x86_64 PRIVATE glad "${GLFW_LIB}" OpenGL::GL ${PLATFORM_LIBS})

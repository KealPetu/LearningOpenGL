add_executable(03_Shaders_x86_64 Shaders.cpp ../../WindowManager.cpp ../../glad.c)
set_target_properties(03_Shaders_x86_64 PROPERTIES OUTPUT_NAME "03_Shaders.x86_64")

target_include_directories(03_Shaders_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(03_Shaders_x86_64 PRIVATE glfw OpenGL::GL)

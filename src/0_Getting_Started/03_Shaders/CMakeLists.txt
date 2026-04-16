add_executable(03_Shaders Shaders.cpp ../../WindowManager.cpp)
set_target_properties(03_Shaders PROPERTIES OUTPUT_NAME "03_Shaders.x86_64")

target_include_directories(03_Shaders PRIVATE "${INCLUDE_DIR}")
target_link_libraries(03_Shaders PRIVATE glfw glad OpenGL::GL)

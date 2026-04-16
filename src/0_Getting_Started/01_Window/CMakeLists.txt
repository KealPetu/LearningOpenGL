add_executable(01_Window Window.cpp)
set_target_properties(01_Window PROPERTIES OUTPUT_NAME "01_Window.x86_64")

target_include_directories(01_Window PRIVATE "${INCLUDE_DIR}")
target_link_libraries(01_Window PRIVATE glfw glad OpenGL::GL)

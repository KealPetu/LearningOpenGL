add_executable(01_Window_x86_64 main.cpp)
set_target_properties(01_Window_x86_64 PROPERTIES OUTPUT_NAME "01_Window.x86_64")

target_include_directories(01_Window_x86_64 PRIVATE "${INCLUDE_DIR}")
target_link_libraries(01_Window_x86_64 PRIVATE glad "${GLFW_LIB}" OpenGL::GL ${PLATFORM_LIBS})

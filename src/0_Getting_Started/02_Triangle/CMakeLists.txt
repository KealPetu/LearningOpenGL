add_executable(02_Triangle Triangle.cpp ../../WindowManager.cpp)
set_target_properties(02_Triangle PROPERTIES OUTPUT_NAME "02_Triangle.x86_64")

target_include_directories(02_Triangle PRIVATE "${INCLUDE_DIR}")
target_link_libraries(02_Triangle PRIVATE glfw glad OpenGL::GL)

add_executable(02_EBO EBO.cpp ../../WindowManager.cpp)
set_target_properties(02_EBO PROPERTIES OUTPUT_NAME "02_EBO.x86_64")

target_include_directories(02_EBO PRIVATE "${INCLUDE_DIR}")
target_link_libraries(02_EBO PRIVATE glfw glad OpenGL::GL)


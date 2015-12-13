include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(glfw-sample
                  main.cc)
target_link_libraries(glfw-sample ${OPENGL_LIBRARIES} ${EIGEN_LIBS} ${GLFW_LIBRARIES})

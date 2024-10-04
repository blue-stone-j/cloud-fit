
add_library(line_fit SHARED
  src/line.cpp)
target_link_libraries(line_fit
  ${PCL_LIBRARIES}
)
install(TARGETS line_fit
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(BUILD_TEST)
  add_executable(line_node test/line_node.cpp src/line.cpp)
  target_link_libraries(line_node ${PCL_LIBRARIES})
endif()
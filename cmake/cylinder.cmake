
add_library(cylinder_fit SHARED
  src/cylinder.cpp)
target_link_libraries(cylinder_fit
  ${PCL_LIBRARIES}
)
install(TARGETS cylinder_fit
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(BUILD_TEST)
  add_executable(cylinder_node test/cylinder_node.cpp src/cylinder.cpp)
  target_link_libraries(cylinder_node ${PCL_LIBRARIES})
endif()
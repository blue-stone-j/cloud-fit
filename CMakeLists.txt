cmake_minimum_required(VERSION 3.10)
project(cloud_fit)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pthread")

find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(plane_node test/plane_node.cpp src/plane.cpp)

target_link_libraries(plane_node ${PCL_LIBRARIES})

cmake_minimum_required(VERSION 2.6)
project (UniverseViewer)

if(CMAKE_BUILD_TYPE STREQUAL Release)
  SET(CMAKE_BUILD_TYPE Release)
  message("Release mode")
else()
  SET(CMAKE_BUILD_TYPE Debug)
  SET(CMAKE_CXX_FILES "-g -Wall")
  message("Debug mode")
endif()

add_subdirectory(engine)
add_subdirectory(gui)

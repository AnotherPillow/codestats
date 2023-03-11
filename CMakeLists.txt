# CMakeList.txt : CMake project for codestats, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("codestats")

# Add source to this project's executable.
add_executable (codestats "codestats.cpp" "codestats.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET codestats PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

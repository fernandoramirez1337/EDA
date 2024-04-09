cmake_minimum_required(VERSION 3.5)
project(OctreeExample)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add executable
add_executable(OctreeExample main.cpp src/octree.cpp)

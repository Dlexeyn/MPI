cmake_minimum_required(VERSION 3.26)
project(lab0)

set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(lab0 mod_main.cpp)
target_link_libraries(lab0 PUBLIC MPI::MPI_CXX)

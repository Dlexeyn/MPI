cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 PUBLIC MPI::MPI_CXX)
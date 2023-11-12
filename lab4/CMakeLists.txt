cmake_minimum_required(VERSION 3.26)
project(lab4)

set(CMAKE_CXX_STANDARD 17)
find_package(MPI REQUIRED)

add_executable(lab4 main.cpp)
target_link_libraries(lab4 PUBLIC MPI::MPI_CXX)
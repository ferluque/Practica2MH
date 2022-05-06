cmake_minimum_required(VERSION 3.5)

project(MDD)

include_directories(comun)

add_library(Problem comun/Problem.cpp)
add_library(Solution comun/Solution.cpp)

add_executable(AGG-uniforme src/AGG-uniforme.cpp)
target_link_libraries(AGG-uniforme Problem)
target_link_libraries(AGG-uniforme Solution)

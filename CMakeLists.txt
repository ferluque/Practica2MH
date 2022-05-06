cmake_minimum_required(VERSION 3.5)

project(MDD)

include_directories(comun)

add_library(Problem comun/Problem.cpp)
add_library(Solution comun/Solution.cpp)

add_executable(AGG-uniforme src/AGG-uniforme.cpp)
add_executable(AGG-posicion src/AGG-posicion.cpp)
target_link_libraries(AGG-uniforme Problem)
target_link_libraries(AGG-uniforme Solution)
target_link_libraries(AGG-posicion Problem)
target_link_libraries(AGG-posicion Solution)

set_property(TARGET AGG-uniforme PROPERTY CXX_STANDARD 11)
set_property(TARGET AGG-posicion PROPERTY CXX_STANDARD 11)


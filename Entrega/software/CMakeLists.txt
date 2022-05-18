cmake_minimum_required(VERSION 3.5)

project(MDD)

include_directories(comun)

add_library(Problem comun/Problem.cpp)
add_library(Solution comun/Solution.cpp)
add_library(Solution_enteros comun/Solution_enteros.cpp)
add_library(bl comun/bl.cpp)


add_executable(AGG-uniforme src/AGG-uniforme.cpp)
add_executable(AGG-posicion src/AGG-posicion.cpp)

add_executable(AGE-posicion src/AGE-posicion.cpp)
add_executable(AGE-uniforme src/AGE-uniforme.cpp)

add_executable(AM-10-1 src/AM-10-1.cpp)

add_executable(AM-10-0.1 src/AM-10-0.1.cpp)

add_executable(AM-10-0.1mej src/AM-10-0.1mej.cpp)

add_executable(pruebas src/pruebas.cpp)

target_link_libraries(AGG-uniforme Problem)
target_link_libraries(AGG-uniforme Solution)

target_link_libraries(AGG-posicion Problem)
target_link_libraries(AGG-posicion Solution)

target_link_libraries(pruebas Problem)
target_link_libraries(pruebas Solution)
target_link_libraries(pruebas Solution_enteros)

target_link_libraries(AGE-posicion Problem)
target_link_libraries(AGE-posicion Solution)

target_link_libraries(AGE-uniforme Problem)
target_link_libraries(AGE-uniforme Solution)

target_link_libraries(AM-10-1 Problem)
target_link_libraries(AM-10-1 Solution_enteros)
target_link_libraries(AM-10-1 bl)

target_link_libraries(AM-10-0.1 Problem)
target_link_libraries(AM-10-0.1 Solution_enteros)
target_link_libraries(AM-10-0.1 bl)

target_link_libraries(AM-10-0.1mej Problem)
target_link_libraries(AM-10-0.1mej Solution_enteros)
target_link_libraries(AM-10-0.1mej bl)
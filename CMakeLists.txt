cmake_minimum_required(VERSION 3.8)
project(ode VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()

add_executable (main main.cpp solver.cpp utils.cpp)

add_executable (tests test.cpp solver.cpp catch.cpp utils.cpp)
add_test(NAME mytest COMMAND tests)
cmake_minimum_required(VERSION 3.8)
project(ode VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

add_executable (main main.cpp solver.cpp)

add_executable (tests test.cpp solver.cpp catch.cpp)
add_test(NAME mytest COMMAND tests)
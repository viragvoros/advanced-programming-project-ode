# Advanced Programming Project: My own ODE solver

## Performance analysis

First step is to implement `chrono` is `test.cpp` to be able to measure performance (performance gain\loss in `test.cpp` applies for `.\main` as well, because both are using the same solvers). The program ran in less than 1 sec without any optimization.
`./make` has a significant disadvantage in terms of final compilation times, due to the usage of the amalgamated header and amalgamated source file. Speed of compilation time can be improved with installed Catch2 from system package manager.

### Restructuring code to check references to avoid unnecessary copies
The code written in Sprint 2 is not easy to read, maintain and debug, so restructuring was needed. In this way correctness of references was possible to check and they were added in several missig places.

### Deleting branches of `else if` in `main.cpp`
Due to the implementation of `utils.h` and `utils.cpp` the `std::cin` only returns valid values, therefore in `main.cpp` in case of user defined ODE, we do not have to check if retuned values are correct and else if branches can be removed, and several if conditions can be removed.

### Expensive operations
`From Solver::accuracy`, `std::pow(...,2)` can be removed.

### Enabling O3 compiler optimization
`set(CMAKE_CXX_FLAGS_RELEASE "-O3")` in CMakeLists.txt.

### Note: Vectorization
`Exp_Euler::solver_ode` cannot be vectorized, `p` depend on previous value.
`Imp_Euler::solver_ode` cannot be vectorized, `p` depend on previous value.
`Solver::accuracy` cannot vectorized due to function call.
`Solver::write_csv` iostream vectorization not possible.
`Imp_Euler::secant` cannot be vectorized due to uncountable loops.





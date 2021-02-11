# Advanced Programming Project: My own ODE solver

## Sprint 1

The solver can solve first order ODEs either specified directly in the code as lamdba function ( in code mode - *Press 0* ) or defined at runtime via keyboard ( user defined mode - *Press 1* ).
The project contains an ODE solver, which is used through an abstract base class "Solver". The ODE can be solved with explicit Euler method ( *Press 0* ) and with implicit Euler method ( *Press 1* ).
"Exp_ Euler" class is derived from the base class using the same interface, "Exp_ Euler" class is going to be implemented in Sprint 2.

The user defined mode can solve non-time-dependent first order ODEs in the form `x' = a + bx + cx^2 + ... + mx^n`, where n is the maximum power and `a, b, c,..., n` are the coefficients. In user defined mode, additional parameters (initial time, end time, initial value of x in t0, time step size) are provided by the user via keyboard as well.

In code defined mode the solver can solve any first order time-dependent and non-time-dependent ODEs.

The solver returns an `std::vector` of the solution and prints it into a .csv file.
The project contains a unit test which compares an ODE `dx / dt = (7 * p *(1 - (p / 10)))` with its analytic solution `x(t) = (200 / (20 - (10 * exp(-7 * t))))` for correctness.

In the following, a step-to-step example is going to be discussed for the ODE `x' = 1 + 7x - 2x^2` with explicit Euler method.
To use CMake and run the main.cpp programm, the following commands have to be typed into a Linux terminal:

```
$ cmake .
$ make 
$ ./main

Press 0 and ENTER: default first order ODE defined in code
Press 1 and ENTER: user defined first order, non-time-dependent ODE
$ 1
Press 0 and ENTER: explicit Euler method
Press 1 and ENTER: implicit Euler method
$ 0   
Enter maximum degree of polynomial (dx / dt = polynomial) and press ENTER
$ 2
Enter coefficient of x^0 and press ENTER
$ 1
Enter coefficient of x^1 and press ENTER
$ 7
Enter coefficient of x^2 and press ENTER
$ -2
Enter initial time (>= 0) and press ENTER
$ 0
Enter end time (> t_init) and press ENTER
$ 5
Enter initial value in t0 and press ENTER
$ 20
Enter step size (> 0) and press ENTER
$ 0.0125
Calculating solution of user defined ODE with explicit Euler method
```
The program will provide a file named "explicit_ euler_ODE.csv" with time and x values in two colums, while invalid inputs result in an error message and the programm stops.
To use the testing function, instead of `./main` command `./tests` command can be used on the terminal.


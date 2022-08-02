# Advanced Programming Project: My own ODE solver

## Sprint 1

The solver can solve first order ODEs either specified directly in the code as lamdba function ( in code mode - *Press 0* ) or defined at runtime via keyboard ( user defined mode - *Press 1* ).
The project contains an ODE solver, which is used through an abstract base class "Solver". The ODE can be solved with explicit Euler method ( *Press 0* ) and with implicit Euler method ( *Press 1* ).
"Exp_ Euler" class is derived from the base class using the same interface.

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
The program will provide a file named "explicit_ euler_userdef _ODE.csv" with time and x values in two colums, while invalid inputs are given, the program is going to keep asking for the correct ones.

To define ODE in code, the parameters can be added in `main.cpp`:
```
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ADD MORE COMPLICATED TIME-DEPENDENT(t) ODE(Var p) HERE TO USE DEFAULT EQUATION IN CODE
// Do not modify code from here above!
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Default ODE defined in code dependent on x (here p) and t
std::function<double(double&, double&)> def_ode = [](double &p, double &t){return (7 * p *(1 - (p / 10)));};

// Initial time (>= 0)
double t_init = 0;

// End time (> t_init) defined by user
double t_end = 5;

// Initial value of x in t0 defined by user
double p0 = 20;

// Step size (> 0)
double step_size = 0.0625;

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Do not modify code from here below!
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
```
The program will provide a file named "explicit_ euler_ default_ ODE.csv" or "implicit_ euler_ default_ ODE.csv", if invalid inputs are given, the program is going to stop and give an error message "Invalid input definition in code!".
To use the testing function, instead of `./main` command `./tests` command can be used on the terminal.

## Sprint 2

In this sprint, the solver was extended to be able to solve ODEs with implicit Euler scheme. The discretization scheme / solver was encapsulated into a class, deriving from an abstract base class, which all the schemes share.
The main() function accesses the solvers through an interface common to all solvers. The scheme is configurable at runtime through keyboard or it can be modified in the code. The results are written into a file.

Unit tests were implemented, similarly to "Exp_ Euler" in Sprint 1, now "Imp_ Euler" is tested as well with analytical solutions using `./tests` command.

To solve ODEs with implicit Euler method, a root-finding algorithm was needed, namely secant method was used in this project. Secant method was implemented as a new function of class "Imp_Euler".
New solvers have to be generally defined in `solver.h` header file and they have to be derived from "Solver" class:
```
class New_Solver: public Solver{
    public:
        New_Solver() : Solver(){}
        New_Solver(Solver &solve) : Solver(solve){}
        ~New_Solver(){};

        void solver_ode(std::vector<double> &num_sol) override;
        void new_method();
};
```
its methods are implemented in `solver.cpp` file:
```
void New_Solver::solver_ode(std::vector<double> &num_sol)
    {
    // insert implementation here
    }
    
void New_Solver::new_method()
    {
    // insert implementation here
    }
```
and they can be called both in `main.cpp` and in `test.cpp` with the corresponding name e.g `New_Solver::new_method`.

## Sprint 3

In this sprint, the code was completely restructured, "cleaned up" and improved. `utils.h` and `utils.cpp` were implemented to prevent invalid inputs and make the code more readable. The findings and observations were presented in `performance.md`.




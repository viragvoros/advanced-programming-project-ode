#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>

#include "catch.hpp"
#include "solver.h"

   // Test ODE 
    std::function<double(double, double, int&, std::vector<double>&)> func = [](double p, double t, int &max_pow, std::vector<double> &coefficients)
                {return (7 * p *(1 - (p / 10)));};

    // Analytical solution of test ODE
    std::function<double(double)> analytical_sol = [](double t) {return (200 / (20 - (10 * exp(-7 * t))));};

    // Initial time (>= 0)
    double t_init = 0;
    // End time (> t_init)
    double t_end = 5;
    // Initial value in t0
    double p0 = 20;
    // Step size (> 0)
    double step_size = 0.0625;
    // Tolerance for the accuracy
    double tolerance = 2;

    // Maximum power of polynom, input parameter of runtime defined ODE (needed to define func)
    int max_pow;
    // Coefficients of polynom, input parameter of runtime defined ODE (needed to define func)
    std::vector<double> coefficients;


TEST_CASE("Testing numerical methods"){
    
    REQUIRE(t_init >= 0);
    REQUIRE(t_end > t_init);
    REQUIRE(step_size > 0);

    // Create object of abstract "Solver" base class
    Solver solve(func, t_init, t_end, step_size, p0, max_pow, coefficients);

    SECTION("Testing accuracy of explicit Euler method"){

        std::vector<double> num_sol;

        // Deriving "Exp_Euler" method from abstract "Solver" base class
        Exp_Euler *exp = new Exp_Euler(solve);
        
        exp->solver_ode(num_sol);

        REQUIRE(exp->accuracy(num_sol, analytical_sol) < tolerance); 

        std::cout << "Explicit Euler is accurate with step_size = " << step_size << std::endl;
    }
}
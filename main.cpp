#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include <limits>

#include "utils.h"
#include "solver.h"

int main() {
    
    // Definition of the ODE (user or default in code)
    int user = get_ode_def();

    if(user == 0){
        
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

        // Defining method of solving the ODE defined in code
        int method = get_method();

        // Maximum power of polynom defined by user
        int max_pow;

        // Coefficients of polynom defined by user
        std::vector<double> coefficients; 

        // Create object of abstract "Solver" base class
        Solver solve(user, t_init, t_end, step_size, p0, max_pow, coefficients, def_ode);

        // Initializing vector for the numerical solution
        std::vector<double> num_sol;

        // Explicit Euler method
        if(method == 0 && t_init >= 0 && t_end > t_init && step_size > 0){
            std::cout << "Calculating solution of default ODE defined in code with explicit Euler method" << std::endl;

            // Deriving "Exp_Euler" method from abstract "Solver" base class
            Exp_Euler *exp = new Exp_Euler(solve);
            exp->solver_ode(num_sol);
            exp->write_csv(num_sol, "explicit_euler_default_ODE.csv");
        }
        // Implicit Euler method
        else if(method == 1 && t_init >= 0 && t_end > t_init && step_size > 0){
            std::cout << "Calculating solution of default ODE defined in code with implicit Euler method" << std::endl;

            // Deriving "Imp_Euler" method from abstract "Solver" base class
            Imp_Euler *imp = new Imp_Euler(solve);
            imp->solver_ode(num_sol);
            imp->write_csv(num_sol, "implicit_euler_default_ODE.csv");
        }
        else{
            std::cout << "Invalid input definition in code!" <<std::endl;
        }
    }            
    else{
        // Defining method of solving the ODE defined in code
        int method = get_method();

        // Maximum power of polynom defined by user
        int max_pow = get_max_pow();

        // Coefficients of polynom defined by user
        std::vector<double> coefficients = get_coefficients(max_pow); 

        // Initial time (>= 0) defined by user
        double t_init = get_t_init();

        // End time (> t_init) defined by user
        double t_end = get_t_end(t_init);

        // Initial value of x in t0 defined by user
        double p0 = get_p0();

        // Step size (> 0)
        double step_size = get_step_size();

        // Default ODE defined in code
        std::function<double(double&, double&)> def_ode = [](double &p, double &t){return 0;};

        // Create object of abstract "Solver" base class
        Solver solve(user, t_init, t_end, step_size, p0, max_pow, coefficients, def_ode);

        // Initializing vector for the numerical solution
        std::vector<double> num_sol;

        // Explicit Euler method
        if(method == 0){
            std::cout << "Calculating solution of user defined ODE with explicit Euler method" << std::endl;

            // Deriving "Exp_Euler" method from abstract "Solver" base class
            Exp_Euler *exp = new Exp_Euler(solve);
            exp->solver_ode(num_sol);
            exp->write_csv(num_sol, "explicit_euler_userdef_ODE.csv");
        }

        // Implicit Euler method
        else{
            std::cout << "Calculating solution of user defined ODE with implicit Euler method" << std::endl;

            // Deriving "Imp_Euler" method from abstract "Solver" base class
            Imp_Euler *imp = new Imp_Euler(solve);
            imp->solver_ode(num_sol);
            imp->write_csv(num_sol, "implicit_euler_userdef_ODE.csv");

        }
    }    

    return 0;
}

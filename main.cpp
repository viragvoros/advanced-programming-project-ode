#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>

#include "solver.h"

int main() {

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // ADD PARAMETERS HERE FOR MORE COMPLICATED ODE DEFINED IN CODE
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    // Default first order ODE defined in code
    std::function<double(double, double, int&, std::vector<double>&)> func = [](double p, double t, int &max_pow, std::vector<double> &coefficients){return (7 * p *(1 - (p / 10)));};

    // Default initial time (>= 0)
    double t_init = 0;
    // Default end time (> t_init)
    double t_end = 5;
    // Default initial value in t0
    double p0 = 20;
    // Default step size (> 0)
    double step_size = 0.0625;

    // DO NOT CHANGE CODE FROM HERE BELOW
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    // Parameter to define input of the ODE
    int user;

    // Parameter to define method of solving the ODE
    int method;

    // Maximum power of polynom, input parameter of runtime defined ODE
    int max_pow;
    // Coefficients of polynom, input parameter of runtime defined ODE
    std::vector<double> coefficients;

    std::cout<< "Press 0 and ENTER: default first order ODE defined in code" <<std::endl;
    std::cout<< "Press 1 and ENTER: user defined first order, non-time-dependent ODE" <<std::endl;
    std::cin >> user;

    std::cout<< "Press 0 and ENTER: explicit Euler method" <<std::endl;
    std::cout<< "Press 1 and ENTER: implicit Euler method" <<std::endl;
    std::cin >> method;

    // Calculating results of ODE in case of runtime definition
    if (user != 0) {

        std::cout << "Enter maximum degree of polynomial (dx / dt = polynomial) and press ENTER"<<std::endl;
        std::cin >> max_pow;

        if(max_pow < 0){
            std::cout << "Invalid input for maximum power"<<std::endl;
        }
        else{
            for (int i=0; i<=max_pow; i++){
            std::cout<<"Enter coefficient of x^" << i << " and press ENTER" << std::endl;
            double coeff;
            std::cin>>coeff;
            coefficients.push_back(coeff);
            }

            // Defining ODE with foor loop based on coefficients and power
            std::function<double(double, double, int&, std::vector<double>&)> func = [](double p, double t, int &max_pow, std::vector<double> &coefficients){
                double result = 0.0;
                int power = 0;
                for (auto elem : coefficients){
                result += elem*std::pow(p, power);
                power++;
                }
                return result;
            };

            std::cout<<"Enter initial time (>= 0) and press ENTER" << std::endl;
            std::cin>>t_init;
            std::cout<<"Enter end time (> t_init) and press ENTER" << std::endl;
            std::cin>>t_end;
            std::cout<<"Enter initial value in t0 and press ENTER" << std::endl;
            std::cin>>p0;
            std::cout<<"Enter step size (> 0) and press ENTER" << std::endl;
            std::cin>>step_size;

            // Testing requirements
            if(t_init >= 0 && t_end > t_init && step_size > 0){
                
                // Create object of abstract "Solver" base class
                Solver solve(func, t_init, t_end, step_size, p0, max_pow, coefficients);

                // Calculating results of ODE in case of explicit Euler method
                if (method == 0) {
                    std::cout << "Calculating solution of user defined ODE with explicit Euler method" << std::endl;
                    std::vector<double> num_sol;

                    // Deriving "Exp_Euler" method from abstract "Solver" base class
                    Exp_Euler *exp = new Exp_Euler(solve);
                    exp->solver_ode(num_sol);
                    exp->write_csv(num_sol, "explicit_euler_ODE.csv");
                }  
                // Calculating results of ODE in case of implicit Euler method
                else {
                    std::cout << "Calculating solution of user defined ODE with implicit Euler method" << std::endl;
                    std::vector<double> num_sol;

                    // Deriving "Imp_Euler" method from abstract "Solver" base class
                    Imp_Euler *imp = new Imp_Euler(solve);
                    imp->solver_ode(num_sol);
                    imp->write_csv(num_sol, "implicit_euler_ODE.csv");
                }
            }
            else{
                std::cout << "Input parameters are incorrect!" << std::endl;
            }
        }
    }     

    // Calculating results of ODE in case of definition in code
    else {
        // Testing requirements
        if(t_init >= 0 && t_end > t_init && step_size > 0){

            // Create object of abstract "Solver" base class
            Solver solve(func, t_init, t_end, step_size, p0, max_pow, coefficients);

            // Calculating results of ODE in case of explicit Euler method
            if (method == 0) {
                std::cout << "Calculating solution of default ODE in code with explicit Euler method" << std::endl;
                std::vector<double> num_sol;

                // Deriving "Exp_Euler" method from abstract "Solver" base class
                Exp_Euler *exp = new Exp_Euler(solve);
                exp->solver_ode(num_sol);
                exp->write_csv(num_sol, "explicit_euler_ODE.csv");
            }  
            // Calculating results of ODE in case of implicit Euler method
            else {
                std::cout << "Calculating solution of default ODE in code with implicit Euler method" << std::endl;
                std::vector<double> num_sol;

                // Deriving "Imp_Euler" method from abstract "Solver" base class
                Imp_Euler *imp = new Imp_Euler(solve);
                imp->solver_ode(num_sol);
                imp->write_csv(num_sol, "implicit_euler_ODE.csv");
            }
        }
        else{
            std::cout << "Input parameters are incorrect!" << std::endl;
        }
    }

    return 0;
}

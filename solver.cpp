#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include <limits>

#include "solver.h"

// Generating ODE based on user defined parameters or defined in code
double Solver::get_func_value(double &p, double &t){
    if(_user != 1){
        return (_def_ode(p, t)); 
    }

    else {
        double result = 0.0;
        int power = 0;
        for (auto elem : _coefficients){
            result += elem*std::pow(p, power);
            power++;
        }
        return result;
    }
}

// Override forward (explicit) Euler method solver
void Exp_Euler::solver_ode(std::vector<double> &num_sol){
    double t = _t_init;
    double p = _p0;
    num_sol.push_back(p);

    while (t < _t_end){
        t += _step_size;
        p += _step_size * get_func_value(p, t);
        num_sol.push_back(p);
    }
}

// Override backward (implicit) Euler method solver
void Imp_Euler::solver_ode(std::vector<double> &num_sol){
    double t = _t_init + _step_size;

    double p0 = _p0;
    num_sol.push_back(p0);
    // Without a second initial value, little perturbation is needed in practice
    double p1 = _p0 + 0.01;
    num_sol.push_back(p1);

    int max_iter = 1000;
    double tol = 0.001;

    while (t < _t_end){
        t += _step_size;

        double p = Imp_Euler::secant(p0, p1, max_iter, tol, t);
        num_sol.push_back(p);

        p0 = p1;
        p1 = p;
    }
}

// Calculating accuracy of the solver
double Solver::accuracy(std::vector<double> &num_sol, std::function<double(double&)> &analytical_sol){
    double error = 0;
    double t = _t_init;
    for (auto elem : num_sol){
        error += (elem - analytical_sol(t)) * (elem - analytical_sol(t));
        t += _step_size;
    }
    return std::sqrt((_step_size / _t_end) * error);
}

// Saving results to a .csv file
void Solver::write_csv(std::vector<double> &num_sol, std::string filename){
    std::ofstream myFile(filename);
    double t = _t_init;
    for (auto elem : num_sol){
        myFile << t << ","<< elem << std::endl;
        t += _step_size;
    }
    myFile.close();
}

// Implementing Secant method to be able to calculate implicit Euler method
double Imp_Euler::secant(double &p0, double &p1, int &max_iter, double &tol, double &t){
    int num_iter = 0;
    double x0 = p0;
    double x1 = p1;
    double x2;

    while (std::abs(p1 + (_step_size * get_func_value(x2, t)) - x2) >= tol && num_iter < max_iter){
        x2 = x1 - (((p1 + (_step_size * get_func_value(x1, t)) - x1) * (x1 - x0)) /
                  ((p1 + (_step_size * get_func_value(x1, t)) - x1) - (p1 + (_step_size * get_func_value(x0, t)) - x0)));
        x0 = x1;
        x1 = x2;
        num_iter++;
    }
    return x2;
}
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include "solver.h"

// Override forward (explicit) Euler method solver
void Exp_Euler::solver_ode(std::vector<double> &num_sol){
    double t = _t_init;
    double p = _p0;
    num_sol.push_back(p);

    while (t < _t_end){
        t += _step_size;
        p += _step_size * _func(p, t, _max_pow, _coefficients);
        num_sol.push_back(p);
    }
}

// Override backward (implicit) Euler method solver
void Imp_Euler::solver_ode(std::vector<double> &num_sol){
    double t = _t_init + _step_size;

    double p0 = _p0;
    num_sol.push_back(p0);
    // Without a second initial value, little perturbation is needed in practice
    double p1 = _p0 + 0.0001;
    num_sol.push_back(p1);

    int max_iter = 1000;
    double tol = 0.0001;

    while (t < _t_end){
        t += _step_size;

        double p = Imp_Euler::secant(p0, p1, max_iter, tol, t);
        num_sol.push_back(p);

        p0 = p1;
        p1 = p;
    }
}

// Calculating accuracy of the solver
double Solver::accuracy(std::vector<double> &num_sol, std::function<double(double)> &analytical_sol){
    double error = 0;
    double t = _t_init;
    for (auto elem : num_sol){
        error += std::pow(elem - analytical_sol(t), 2);
        t += _step_size;
    }
    return std::sqrt((_step_size / _t_end) * error);
}

// Saving results to a .csv file
void Solver::write_csv(std::vector<double> &numsol, std::string filename){
    std::ofstream myFile(filename);
    double t = _t_init;
    for (auto elem : numsol){
        myFile << t << ","<< elem << std::endl;
        t += _step_size;
    }
    myFile.close();
}

// Implementing Secant method to ba able to calculate implicit Euler method
double Imp_Euler::secant(double &p0, double &p1, int &max_iter, double &tol, double &t){
    int num_iter = 0;
    double x0 = p0;
    double x1 = p1;
    double x2;

    while (std::abs(p1 + (_step_size * _func(x2, t, _max_pow, _coefficients)) - x2) >= tol && num_iter < max_iter){
        x2 = x1 - (((p1 + (_step_size * _func(x1, t, _max_pow, _coefficients)) - x1) * (x1 - x0)) /
                  ((p1 + (_step_size * _func(x1, t, _max_pow, _coefficients)) - x1) - (p1 + (_step_size * _func(x0, t, _max_pow, _coefficients)) - x0)));
        x0 = x1;
        x1 = x2;
        num_iter++;
    }
    return x2;
}

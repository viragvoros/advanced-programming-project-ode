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
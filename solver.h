#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cmath>

// Abstract base solver class
class Solver{
    public:
        Solver(std::function<double(double p, double t, int &max_pow, std::vector<double> &coefficients)> &func, double &t_init, double &t_end, double &step_size, double &p0, 
                int &max_pow, std::vector<double> &coefficients) : 
                _func(func), _t_init(t_init), _t_end(t_end), _step_size(step_size), _p0(p0), _max_pow(max_pow), _coefficients(coefficients){}
        virtual ~Solver(){};

        virtual void solver_ode(std::vector<double> &num_sol){};
        virtual double accuracy(std::vector<double> &num_sol, std::function<double(double)> &analytical_sol);
        virtual void write_csv(std::vector<double> &numsol, std::string name);

    protected:
        std::function<double(double p, double t, int &max_pow, std::vector<double> &coefficients)> _func;
        double _t_init;
        double _t_end;
        double _step_size;
        double _p0;
        int _max_pow;
        std::vector<double> _coefficients;
};

// Forward (explicit) Euler method
class Exp_Euler: public Solver{
    public:
        Exp_Euler(std::function<double(double p, double t, int &max_pow, std::vector<double> &coefficients)> &func, double &t_init, double &t_end, double &step_size, double &p0, 
                int &max_pow, std::vector<double> &coefficients) : Solver(func, t_init, t_end, step_size, p0, max_pow, coefficients){}
        Exp_Euler(Solver &solve) : Solver(solve){}
        ~Exp_Euler(){};

        void solver_ode(std::vector<double> &num_sol) override;
};

#endif
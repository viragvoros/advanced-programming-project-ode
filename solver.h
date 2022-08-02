#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include <limits>

// Abstract base solver class
class Solver{
    public:
        Solver(int &user, double &t_init, double &t_end, double &step_size, double &p0, int &max_pow, std::vector<double> &coefficients, std::function<double(double&, double&)> &def_ode) : 
                _user(user), _t_init(t_init), _t_end(t_end), _step_size(step_size), _p0(p0), _max_pow(max_pow), _coefficients(coefficients), _def_ode(def_ode){}
        virtual ~Solver(){};

        virtual void solver_ode(std::vector<double> &num_sol){};
        virtual double accuracy(std::vector<double> &num_sol, std::function<double(double&)> &analytical_sol);
        virtual void write_csv(std::vector<double> &numsol, std::string name);
        virtual double get_func_value(double &p, double &t);
        
    protected:
        int _user;
        double _t_init;
        double _t_end;
        double _step_size;
        double _p0;
        int _max_pow;
        std::vector<double> _coefficients;
        std::function<double(double&, double&)> _def_ode;
};

// Forward (explicit) Euler method
class Exp_Euler: public Solver{
    public:
        Exp_Euler(int &user, double &t_init, double &t_end, double &step_size, double &p0, int &max_pow, std::vector<double> &coefficients, std::function<double(double&, double&)> &test_ode) : 
                Solver(user, t_init, t_end, step_size, p0, max_pow, coefficients, test_ode){}
        Exp_Euler(Solver &solve) : Solver(solve){}
        ~Exp_Euler(){};

        void solver_ode(std::vector<double> &num_sol) override;
};

// Backward (implicit) Euler method
class Imp_Euler: public Solver{
    public:
        Imp_Euler(int &user, double &t_init, double &t_end, double &step_size, double &p0, int &max_pow, std::vector<double> &coefficients, std::function<double(double&, double&)> &test_ode) : 
                Solver(user, t_init, t_end, step_size, p0, max_pow, coefficients, test_ode){}
        Imp_Euler(Solver &solve) : Solver(solve){}
        ~Imp_Euler(){};

        void solver_ode(std::vector<double> &num_sol) override;
        double secant(double &p0, double &p1, int &max_iter, double &tol, double &t);
};

#endif
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include <limits>

int get_ode_def();
int get_method();
int get_max_pow();
std::vector<double> get_coefficients(int &max_pow);
double get_t_init();
double get_t_end(double &t_init);
double get_p0();
double get_step_size();

#endif
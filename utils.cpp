#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>
#include <limits>

#include "utils.h"

int get_ode_def(){
    int user;
    while(true){
        std::cout<< "Press 0 and ENTER: default first order ODE defined in code" <<std::endl;
        std::cout<< "Press 1 and ENTER: user defined first order, non-time-dependent ODE" <<std::endl;
        std::cin >> user;
        if(!std::cin.fail()){
            if(user == 1 || user == 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return user;
            }
        }
        std::cout << "Invalid input, it has to be either 1 or 0!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}

int get_method(){
    int method;
    while(true){
        std::cout<< "Press 0 and ENTER: explicit Euler method" <<std::endl;
        std::cout<< "Press 1 and ENTER: implicit Euler method" <<std::endl;
        std::cin >> method;
        if(!std::cin.fail()){
            if(method == 1 || method == 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return method;
            }
        }
        std::cout << "Invalid input, it has to be either 1 or 0!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}

int get_max_pow(){
    int max_pow;
    while(true){
        std::cout << "Enter maximum degree of polynomial (>= 0, dx / dt = polynomial) and press ENTER"<<std::endl;
        std::cin >> max_pow;
        if(!std::cin.fail()){
            if(max_pow >= 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return max_pow;
            }
        }
        std::cout << "Invalid input!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}

std::vector<double> get_coefficients(int &max_pow){  
    std::vector<double> coefficients;
    double input;;
    for (int i=0; i<=max_pow; i++){
        while(true){
            std::cout << "Enter coefficient of x^" << i << " and press ENTER" << std::endl;
            std::cin >> input;
            if(!std::cin.fail()){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                coefficients.push_back(input);
                break;
            }
            std::cout << "Invalid input!" <<std::endl;
            std::cin.clear(); // reset failed state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
        }
    }
    return coefficients;
}

double get_t_init(){
    double t_init;
    while(true){
        std::cout<<"Enter initial time (>= 0) and press ENTER" << std::endl;
        std::cin>>t_init;
        if(!std::cin.fail()){
            if(t_init >= 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return t_init;
            }
        }
        std::cout << "Invalid input!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}

double get_t_end(double &t_init){
    double t_end;
    while(true){
        std::cout<<"Enter end time (> t_init) and press ENTER" << std::endl;
        std::cin>>t_end;
        if(!std::cin.fail()){
            if(t_end > t_init){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return t_end;
            }
        }
        std::cout << "Invalid input!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}

double get_p0(){
    double p0;
    while(true){
        std::cout<<"Enter initial value of x in t0 and press ENTER" << std::endl;
        std::cin>>p0;
        if(!std::cin.fail()){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            return p0;
        }
        std::cout << "Invalid input!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}
    
double get_step_size(){
    double step_size;
    while(true){
        std::cout<<"Enter step size (> 0) and press ENTER" << std::endl;
        std::cin>>step_size;
        if(!std::cin.fail()){
            if(step_size > 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return step_size;
            }
        }
        std::cout << "Invalid input!" <<std::endl;
        std::cin.clear(); // reset failed state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // flush buffer
    }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PDE_bs.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef __ADE_H
#define __ADE_H

#include <Eigen/Dense>

#include "payoff.h"
#include "pde.h"
#include <vector>

class PseudoFactory;
// Finite Difference Method - Abstract Base Class
class ADEBase {
 protected:
  PayOff* opt;
  ConvectionDiffusionPDE* pde;
  
  // Space discretisation
  
  std::vector<double> x_values;  // Stores the coordinates of the x dimension
 
  double r_;            // risk free rate
  double dx;            // space mesh 
  double X_;            //  
  double x_dom_;       // the domain of the x[0,1]
  double t_dom_;      // Temporal extent [0.0, t_dom]
  unsigned long J_;    // Number of temporal differencing points
  unsigned long N_;   // Temporal step size (calculated from above)
  double dt;         // Time discretisation
  double a_;         // the factor for transformation to unite interval
  
  double prev_t, cur_t;   // Current and previous times

  // Differencing coefficients
  double alpha, beta, gamma,zeta;
  

  // Storage
  std::vector<double> new_U;       // storage of the result in upwordsweep(time n+1)
  std::vector<double> new_V;       // storage of the result in downwardsweep(time n+1)
  std::vector<double> old_U;       //storage of the result in upwordsweep(time n)
  std::vector<double> old_V;       //storage of the result in downwardsweep(time n)
  std::vector<double> Average;      //calculate the average of two sweeps
  std::vector<double> Call_Value; 
  std::vector<double> Gamma_up;     // the Gamma value in  upwordsweep
  std::vector<double> Gamma_down;   // the Gamma value in  downwardsweep
  
   
  // Constructor
  ADEBase(PseudoFactory & fac);

  // Override these virtual methods in derived classes for 
  // specific ADE techniques, such as explicit Euler, Crank-Nicolson, etc.
  virtual void calculate_step_sizes() = 0;         //  calculation of the mesh sizes 
  virtual void set_initial_conditions() = 0;       //  set the initial conditions 
  virtual void calculate_boundary_conditions() = 0; // the boundary conditions
  virtual void calculate_Upword() = 0;              //  upward sweep
  virtual void calculate_Downword() = 0;            //  downward sweep
  virtual void calculate_average() = 0;// the average of the two sweeps 
  virtual void calculate_Gamma_Up(int j) = 0;  // Gamma in upward sweep
  virtual void calculate_Gamma_Down(int j) = 0; // Gamma in downward sweep
  virtual void early_exercise(int j) = 0;// early exercise calculation
  

 public:
  // Carry out the actual time-stepping
  virtual void main_calculation() = 0;  // main calculation of the price
  virtual void print_values() = 0;      // output the prices 
  virtual double Option_Price(int j) = 0;  // return option prices
  double vol;
  
  
};

class ADE : public ADEBase {
 protected:
    bool IsEarlyExercise_;
    void calculate_step_sizes();
    void set_initial_conditions();
    void calculate_boundary_conditions();
    void calculate_Upword();
    void calculate_Downword();
    void calculate_average();
    void calculate_Gamma_Up(int j);
    void calculate_Gamma_Down(int j);
    void early_exercise(int j);

 public:
 
    ConvectionDiffusionPDE* pde;
    ADE(PseudoFactory & fac);

    void main_calculation();
    void print_values();
    double Option_Price(int j);  
};


 
 
 

#endif 



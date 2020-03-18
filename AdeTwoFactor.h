//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PDE_bs.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef __ADETWOFACTOR_H
#define __ADETWOFACTOR_H

#include <Eigen/Dense>
#include "payoff.h"
#include "TwoFactorOption.h"
#include "Ade.h"
#include <vector>
class PseudoFactory;
// Finite Difference Method - Abstract Base Class
class ADETwoFactorBase {
 protected:
  PayOff* opt;
  TwoFactorOption* pde_two;
  ADEBase* ade_one_factor;
  // Space discretisation
  
  std::vector<double> x_values;  // Stores the coordinates of the x dimension
  std::vector<double> y_values;  // Stores the coordinates of the y dimension

  double r_;
  double dx;
  double dy;
  double X_;
  double x_dom_;       // the domain of the x[0,1]
  double t_dom_;      // Temporal extent [0.0, t_dom]
  unsigned long J_;   // Number of temporal differencing points
  unsigned long N_;   // Temporal step size (calculated from above)
  double dt;         // Time discretisation
  double a_;
  double b_;
  
  double prev_t, cur_t;   // Current and previous times

  // Differencing coefficients
  double alpha_x,alpha_y, beta_x,beta_y, gamma,zeta;

  
  
  //matrix declarations(storage)
  
   Eigen::MatrixXd U_new;
   Eigen::MatrixXd U_old;
   Eigen::MatrixXd V_new;
   Eigen::MatrixXd V_old;
   Eigen::MatrixXd Average;
    
  std::vector<double> Gamma_up_S1;  // Gamma in upward for S1
  std::vector<double> Gamma_up_S2;  // Gamma in upward for S2
  std::vector<double> Gamma_up_S1S2;  // Gamma in upward for cross term
  std::vector<double> Gamma_down_S1;  // Gamma in downward for S1
  std::vector<double> Gamma_down_S2;  // Gamma in downward for S2
  std::vector<double> Gamma_down_S1S2;  // Gamma in downward for cross term

  // Constructor
  ADETwoFactorBase(PseudoFactory & fac);

  // Override these virtual methods in derived classes for 
  // specific FDM techniques, such as explicit Euler, Crank-Nicolson, etc.
  virtual void calculate_step_sizes() = 0;
  virtual void set_initial_conditions() = 0;
  virtual void calculate_boundary_conditions(int i) = 0;
  virtual void calculate_Upword(int j,int i) = 0;
  virtual void calculate_Downword(int j,int i) = 0;
  virtual void calculate_average(int j,int i) = 0;
  virtual void early_exercise(int j,int i) = 0;
  virtual void calculate_current_spot_x(int i,double cur_y) = 0;
  
  
  virtual void calculate_Gamma_Up_S1(int j,int i) = 0;
  virtual void calculate_Gamma_Up_S2(int j,int i) = 0;
  virtual void calculate_Gamma_Down_S1(int j,int i) = 0;
  virtual void calculate_Gamma_Down_S2(int j,int i) = 0;
  virtual void calculate_Gamma_Cross_Up(int j,int i) = 0;
  virtual void calculate_Gamma_Cross_Down(int j,int i) = 0;

 public:
  // Carry out the actual time-stepping
  virtual void main_calculation() = 0;
  double vol;
  
  
};



class ADETwoFactor : public ADETwoFactorBase {
 protected:
           
  bool IsEarlyExercise_;        
  
  void calculate_step_sizes();
  void set_initial_conditions();
  void calculate_boundary_conditions(int i);
  void calculate_Upword(int j,int i);
  void calculate_Downword(int j,int i);
  void calculate_average(int j,int i);
  void early_exercise(int j,int i);
  void calculate_current_spot_x(int i,double cur_y);
  void calculate_Gamma_Up_S1(int j,int i);
  void calculate_Gamma_Up_S2(int j,int i);
  void calculate_Gamma_Down_S1(int j,int i);
  void calculate_Gamma_Down_S2(int j,int i);
  void calculate_Gamma_Cross_Up(int j,int i);
  void calculate_Gamma_Cross_Down(int j,int i);
  

 public:     
  ADETwoFactor(PseudoFactory & fac);

  void main_calculation();
  
 
 
    
};

#endif 



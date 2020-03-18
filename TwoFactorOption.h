//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PDE_bs.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef __TWOFACTOROPTION_H
#define __TWOFACTOROPTION_H

#include "payoff.h"

//class PseudoFactory;

// Convection Diffusion Equation - Second-order PDE
class TwoFactorOption {
 public:
  // PDE Coefficients 
  virtual double diff_coeff_1(double Gamma,double x,double y) const = 0;
  virtual double diff_coeff_2(double Gamma,double x,double y) const = 0;
  virtual double conv_coeff_1(double Gamma,double x,double y) const = 0;
  virtual double conv_coeff_2(double Gamma,double x,double y) const = 0;
  virtual double crossTerm(double Gamma,double x,double y) const = 0;
  virtual double zero_coeff(double x, double y, double t) const = 0;
  virtual double source_coeff(double x, double y, double t) const = 0;
 
  // Boundary and initial conditions
  virtual double boundary_left(double t, double x) const = 0;
  virtual double boundary_right(double t, double x) const = 0;
  virtual double boundary_under(double t, double y) const = 0;
  virtual double boundary_upper(double t, double y) const = 0;
  virtual double init_cond(double x,double y) const = 0;
  virtual double Constraint(double x,double y) const = 0;
  virtual double claculate_option_value(double U,double x, double t) const  = 0;
};

//  two factor Black-Scholes PDE
class BSTwoFactor : public TwoFactorOption {
 public:
  PayOff* option;
  BSTwoFactor(PseudoFactory & fac);
  
  double diff_coeff_1(double Gamma,double x,double y) const;
   double diff_coeff_2(double Gamma,double x,double y) const;
  double conv_coeff_1(double Gamma,double x,double y) const;
  double conv_coeff_2(double Gamma,double x,double y) const;
  double crossTerm(double Gamma,double x,double y) const;
  double zero_coeff(double x, double y, double t) const;
  double source_coeff(double x, double y, double t) const;
  
  double boundary_left(double t, double x) const;
  double boundary_right(double t, double x) const;
  double boundary_under(double t, double y) const;
  double boundary_upper(double t, double y) const;
  double init_cond(double x,double y) const;
  double Constraint(double x,double y) const;
  double claculate_option_value(double U,double x, double t) const;
   private:
           double r_;
           double K_;
           double T_;
           double sigma_1;
           double sigma_2;
           double a_;
           double b_;
           double w_1;
           double w_2;
           double rho;
           long opt_type;
           double stock_price;
};

class BSTwoFactorUVM : public TwoFactorOption {
 public:
  PayOff* option;
  BSTwoFactorUVM(PseudoFactory & fac);
  
  double diff_coeff_1(double Gamma,double x,double y) const;
   double diff_coeff_2(double Gamma,double x,double y) const;
  double conv_coeff_1(double Gamma,double x,double y) const;
  double conv_coeff_2(double Gamma,double x,double y) const;
  double crossTerm(double Gamma,double x,double y) const;
  double zero_coeff(double x, double y, double t) const;
  double source_coeff(double x, double y, double t) const;
  
  double boundary_left(double t, double x) const;
  double boundary_right(double t, double x) const;
  double boundary_under(double t, double y) const;
  double boundary_upper(double t, double y) const;
  double init_cond(double x,double y) const;
  double Constraint(double x,double y) const;
  double claculate_option_value(double U,double x, double t) const;
   private:
           double r_;
           double K_;
           double T_;
           double sigma_1;
           double sigma_2;
           double a_;
           double b_;
           double w_1;
           double w_2;
           double v_min_;
           double v_max_;
           double rho;
           double stock_price;
};

#endif

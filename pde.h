//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PDE_bs.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef __PDE_H
#define __PDE_H

#include "payoff.h"

class PseudoFactory;

// Convection Diffusion Equation - Second-order PDE
class ConvectionDiffusionPDE {
 public:
  // PDE Coefficients 
  virtual double diff_coeff(double Gamma, double x) const = 0;  // diffusion coefficent
  virtual double conv_coeff(double Gamma, double x) const = 0;  // convection coefficent
  virtual double zero_coeff(double t, double x) const = 0;  // zero coefficent
  virtual double source_coeff(double t, double x) const = 0;  // source term coefficent
 
  // Boundary and initial conditions
  virtual double boundary_left(double t, double x) const = 0;
  virtual double boundary_right(double t, double x) const = 0;
  virtual double init_cond(double x) const = 0;
  virtual double Constraint(double x) const = 0;
  virtual double claculate_Diffusion_equation(double U,double x, double t) const  = 0;
};

// Black-Scholes PDE
class BlackScholesPDE : public ConvectionDiffusionPDE {
 public:
    PayOff* pay_off;
    BlackScholesPDE(PseudoFactory & fac);
  
    double diff_coeff(double Gamma, double x) const;
    double conv_coeff(double Gamma, double x) const;
    double zero_coeff(double t, double x) const;
    double source_coeff(double t, double x) const;
  
    double boundary_left(double t, double x) const;
    double boundary_right(double t, double x) const;
    double init_cond(double x) const;
    double Constraint(double x) const;
    double claculate_Diffusion_equation(double U,double x, double t) const;
   private:
    double r_;
    double K_;
    double T_;
    double sigma_1;
    double sigma_;
    double a_;
};
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	heatequation
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


class heatequation : public ConvectionDiffusionPDE {
 public:
  PayOff* pay_off;
  heatequation(PseudoFactory & fac);
 
  
  double diff_coeff(double Gamma, double x) const;
  double conv_coeff(double Gamma, double x) const;
  double zero_coeff(double t, double x) const;
  double source_coeff(double t, double x) const;

  double boundary_left(double t, double x) const;
  double boundary_right(double t, double x) const;
  double init_cond(double x) const;
  double Constraint(double x) const;
  double claculate_Diffusion_equation(double U,double x, double t) const;
  private:
           double r_;
           double K_;
           double T_;
           double sigma_1;
};
class UVMPde : public ConvectionDiffusionPDE {
 public:
    PayOff* pay_off;
  UVMPde (PseudoFactory & fac);
  
  double diff_coeff(double Gamma, double x) const;
  double conv_coeff(double Gamma, double x) const;
  double zero_coeff(double t, double x) const;
  double source_coeff(double t, double x) const;
  
  double boundary_left(double t, double x) const;
  double boundary_right(double t, double x) const;
  double init_cond(double x) const;
   double Constraint(double x) const;
   double claculate_Diffusion_equation(double U,double x, double t) const;
   private:
           double v_min_;
           double v_max_;
           double r_;
           double K_;
           double T_;
           double sigma_1;
           double a_;
           //double vol;
};
#endif



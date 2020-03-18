#ifndef __PDE_CPP
#define __PDE_CPP

#include "PseudoFactory.h"
#include "pde.h"
#include "Ade.h"

#include <stdexcept>
#include <math.h>
#include <iostream>

BlackScholesPDE::BlackScholesPDE(PseudoFactory & fac) :  r_(fac.Getr()),T_(fac.GetT())
,   K_(fac.GetK()), a_(fac.Geta()), sigma_1(fac.Getsigma1()) 
{pay_off = fac.CreatePayOff();sigma_=fac.Getsigma(sigma_);}


// Diffusion coefficient
double BlackScholesPDE::diff_coeff(double Gamma, double x) const {
  
     return 0.5*x*x*sigma_1*sigma_1*(1.0 - x)*(1.0 - x);  // \frac{1}{2} \sigma^2 S^2
}

// Convection coefficient
double BlackScholesPDE::conv_coeff(double Gamma, double x) const {
  
     return (r_)*x*(1.0 - x) - x*x*sigma_1*sigma_1*(1.0 - x); 
   // rS
}

// Zero-term coefficient
double BlackScholesPDE::zero_coeff(double t, double x) const {
       
    return -(r_);  // -r
}

// Source coefficient
double BlackScholesPDE::source_coeff(double t, double x) const {
       
  return 0.0;
}

// Left boundary-condition (vanilla call option)
double BlackScholesPDE::boundary_left(double t, double x) const {
       
  return (K_)*exp((r_)*((T_)-t));
    // Specifically for a PUT option
}

// Right boundary-condition (vanilla call option)
double BlackScholesPDE::boundary_right(double t, double x) const {
  // This is right boundary for put option
  return  0.0; 
}

// Initial condition (vanilla put option)
double BlackScholesPDE::init_cond(double x) const {
       
     return pay_off->operator()(a_*x/(1.0-x));
}
double BlackScholesPDE::Constraint(double x) const {
     // Test in American put option
        
     return pay_off->operator()(a_*x/(1.0-x));
    }
double BlackScholesPDE::claculate_Diffusion_equation(double U,double x, double t) const {
       
     return 0.0;
    }
   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	heatequation
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

heatequation::heatequation(PseudoFactory & fac) :  r_(fac.Getr()),T_(fac.GetT())
,   K_(fac.GetK()), sigma_1(fac.Getsigma1())  {pay_off = fac.CreatePayOff();}
// Diffusion coefficient
double heatequation::diff_coeff(double Gamma, double x) const {
  
      return 1.0;  // \frac{1}{2} \sigma^2 S^2
}

// Convection coefficient
double heatequation::conv_coeff(double Gamma, double x) const {
       
      return 0.0; 
   // rS
}

// Zero-term coefficient
double heatequation::zero_coeff(double t, double x) const {
      
      return 0.0;  // -r
}

// Source coefficient
double heatequation::source_coeff(double t, double x) const {
      
      return 0.0;// source coeffiecent
}

// Left boundary-condition (vanilla call option)
double heatequation::boundary_left(double t, double x) const {
      
      return 0.0;
    // Specifically for a CALL option
}

// Right boundary-condition (vanilla call option)
double heatequation::boundary_right(double t, double x) const {
  // This is for  option
         double vol =sigma_1;
         double k = 2.0 * (r_)/(vol*vol);
         double tau = vol*vol*(T_ - t);
     return exp(0.5*(k + 1.0)*x)*exp((0.25*(k + 1.0)*(k + 1.0))*(tau)); 
}

// Initial condition (vanilla call option)
double heatequation::init_cond(double x) const {
          double vol = sigma_1;
          double k = 2.0 * (r_)/(vol*vol);
     return  (1.0/K_)* exp(0.5*(k - 1.0)*x)*(pay_off->operator()(K_*exp(x)));
}

double heatequation::Constraint(double x) const {
     // Test in American put option
          double vol = sigma_1;
          double k = 2.0 * (r_)/(vol*vol);
      return (1.0/K_)*exp(0.5*(k - 1.0)*x)*pay_off->operator() (K_*exp(x));
    }  
double heatequation::claculate_Diffusion_equation(double U,double x, double t) const {
          double vol = sigma_1;
          double k = 2.0 * (r_)/(vol*vol);
          double tau = vol*vol*(T_ - t);
       return (K_)*U*exp(-0.5*(k - 1.0)*x - .25*(k + 1.0)*(k + 1.0)*tau);
    }
     
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	UVM pde
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

UVMPde::UVMPde(PseudoFactory & fac) :  r_(fac.Getr()),T_(fac.GetT())
, v_min_(fac.Getv_min()),v_max_(fac.Getv_max()),  K_(fac.GetK()), a_(fac.Geta()), 
sigma_1(fac.Getsigma1()) {pay_off = fac.CreatePayOff();}

// Diffusion coefficient
double UVMPde::diff_coeff(double Gamma, double x) const {
    double vol;
  
    if (Gamma >= 0.0)
    {
        vol = v_min_;
    }
    else
    {
        vol = v_max_;
    }

  return 0.5*x*x*vol*vol*(1.0 - x)*(1.0 - x);  // \frac{1}{2} \sigma^2 S^2
}

// Convection coefficient
double UVMPde::conv_coeff(double Gamma, double x) const {
  
    double vol;
  
  if (Gamma >= 0.0)
    {
        vol = v_min_;
    }
    else
    {
        vol = v_max_;
    }
  
  return (r_)*x*(1.0 - x) - x*x*vol*vol*(1.0 - x); 
   // rS
}

// Zero-term coefficient
double UVMPde::zero_coeff(double t, double x) const {
  return -(r_);  // -r
}

// Source coefficient
double UVMPde::source_coeff(double t, double x) const {
  return 0.0;
}

// Left boundary-condition (vanilla call option)
double UVMPde::boundary_left(double t, double x) const {
  return  (K_)*exp((r_)*((T_)-t));
    // Specifically for a CALL option
}

// Right boundary-condition (vanilla call option)
double UVMPde::boundary_right(double t, double x) const {
  // This is via Put-Call Parity and works for a call option
  return 0.0; 
}

// Initial condition (vanilla put option)
double UVMPde::init_cond(double x) const {
       
  return pay_off->operator()(a_*x/(1.0-x));
}
double UVMPde::Constraint(double x) const {
     // Test in American put option
        
     return pay_off->operator()(a_*x/(1.0-x));
    }
double  UVMPde::claculate_Diffusion_equation(double U,double x, double t) const {
       
      return 0.0;
    }
    
#endif

 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#ifndef __TWOFACTOROPTION_CPP
#define __TWOFACTOROPTION_CPP
#include "TwoFactorOption.h"

#include "PseudoFactory.h"

#include "Ade.h"

#include <stdexcept>
#include <math.h>
#include <iostream>

BSTwoFactor::BSTwoFactor(PseudoFactory & fac) :  r_(fac.Getr()),T_(fac.GetT())
,   K_(fac.GetK()), a_(fac.Geta()), b_(fac.Getb()), sigma_1(fac.Getsigma1()),
sigma_2(fac.Getsigma2()),w_2(fac.Getw_2()),w_1(fac.Getw_1()),rho(fac.Getrho())
 {option = fac.CreatePayOff();}


// Diffusion coefficient_1
double BSTwoFactor::diff_coeff_1(double Gamma,double x,double y) const {
   
  return 0.5*x*x*sigma_1*sigma_1*(1.0 - x)*(1.0 - x);  // \frac{1}{2} \sigma^2 S^2
}

// Diffusion coefficient_2
double BSTwoFactor::diff_coeff_2(double Gamma,double x,double y) const {
  
  return 0.5*y*y*sigma_2*sigma_2*(1.0 - y)*(1.0 - y); // \frac{1}{2} \sigma^2 S^2
  
}

// Convection coefficient_1+
double BSTwoFactor:: conv_coeff_1(double Gamma,double x,double y) const {
  
  return (r_)*x*(1.0 - x) - x*x*sigma_1*sigma_1*(1.0 - x); 
   // rS
}
// Convection coefficient_2
double BSTwoFactor:: conv_coeff_2(double Gamma,double x,double y) const {
  
  return (r_)*y*(1.0 - y) - y*y*sigma_2*sigma_2*(1.0 - y); 
   // rS
}

 // cross term coefiecent
double BSTwoFactor:: crossTerm(double Gamma,double x,double y) const  {
       
  return rho*sigma_1*sigma_2*x*y*(1.0 - x)*(1.0 - y); 
  
}

// Zero-term coefficient
double BSTwoFactor::zero_coeff(double x, double y, double t) const {
  return -(r_);  // -r
}

// Source coefficient
double BSTwoFactor::source_coeff(double x, double y, double t) const {
  return 0.0;
}

// Left boundary-condition (vanilla call option)
double BSTwoFactor::boundary_left(double t, double x) const {
      
  return  0.0;  // boundaries for under are calculatd in ADETwoFactor class
    
}

// Right boundary-condition (vanilla call option)
double BSTwoFactor::boundary_right(double t, double x) const {
  
  return 0.0;  // Specifically for a Max/min-put option (max/min of two assets)
}

double BSTwoFactor::boundary_under(double t, double y) const {
  
    return  0.0;// boundaries for under are calculatd in ADETwoFactor class
  
    // Specifically for a CALL option
}

double BSTwoFactor::boundary_upper(double t, double y) const {
       
  return  0.0; // 
    // Specifically for a Max/min-put option (max/min of two assets)
}

// Initial condition (vanilla put option)

double BSTwoFactor::init_cond(double x,double y) const {
       
    double stock_price = std::max(a_*x/(1.0-x),b_*y/(1.0-y)); 
    
        return option->operator()(stock_price);
}

double BSTwoFactor::Constraint(double x,double y) const {
     // Test in American put option
        double stock_price = std::max(a_*x/(1.0-x),b_*y/(1.0-y)); 
        
            return option->operator()(stock_price);
    }
    
double  BSTwoFactor::claculate_option_value(double U,double x, double t) const {
       
       return 0.0;
    }
   

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	UVM pde
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
BSTwoFactorUVM::BSTwoFactorUVM(PseudoFactory & fac) :  r_(fac.Getr()),T_(fac.GetT())
, v_min_(fac.Getv_min()),v_max_(fac.Getv_max()),K_(fac.GetK()), a_(fac.Geta()),
  b_(fac.Getb()),sigma_1(fac.Getsigma1()),sigma_2(fac.Getsigma2()),w_2(fac.Getw_2())
 ,w_1(fac.Getw_1()) {option = fac.CreatePayOff();}


// Diffusion coefficient_1
double BSTwoFactorUVM::diff_coeff_1(double Gamma,double x,double y) const {
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

// Diffusion coefficient_2
double BSTwoFactorUVM::diff_coeff_2(double Gamma,double x,double y) const {
  double vol;
  
  if (Gamma >= 0.0)
      {
         vol = v_min_;
         }
          else
          {
          vol = v_max_;
          }
  return 0.5*y*y*vol*vol*(1.0 - y)*(1.0 - y); // \frac{1}{2} \sigma^2 S^2
  
}

// Convection coefficient_1+
double BSTwoFactorUVM:: conv_coeff_1(double Gamma,double x,double y) const {
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
// Convection coefficient_2
double BSTwoFactorUVM:: conv_coeff_2(double Gamma,double x,double y) const {
  double vol;
  
  if (Gamma >= 0.0)
      {
         vol = v_min_;
         }
          else
          {
          vol = v_max_;
          }
  return (r_)*y*(1.0 - y) - y*y*vol*vol*(1.0 - y); 
   // rS
}

 // cross term coefiecent
double BSTwoFactorUVM:: crossTerm(double Gamma,double x,double y) const  {
      
       double vol;
  
  if (Gamma >= 0.0)
      {
         vol = 0.3*v_min_;
         }
          else
          {
          vol = 0.5*v_max_;
          }
  return vol*vol*x*y*(1.0 - x)*(1.0 - y); 
  
}

// Zero-term coefficient
double BSTwoFactorUVM::zero_coeff(double x, double y, double t) const {
       
    return -(r_);  // -r
}

// Source coefficient
double BSTwoFactorUVM::source_coeff(double x, double y, double t) const {
  return 0.0;
}

// Left boundary-condition (vanilla call option)
double BSTwoFactorUVM::boundary_left(double t, double x) const {
      
  return  0.0; // boundaries for under are calculatd in ADETwoFactor class
   
}

// Right boundary-condition (vanilla call option)
double BSTwoFactorUVM::boundary_right(double t, double x) const {
  
  return 0.0;  // Specifically for a Max/min-put option (max/min of two assets)
}

double BSTwoFactorUVM::boundary_under(double t, double y) const {
  return  0.0;
    // boundaries for under are calculatd in ADETwoFactor class
}

double BSTwoFactorUVM::boundary_upper(double t, double y) const {
  return  0.0;
  // Specifically for a Max/min-put option (max/min of two assets)
}

// Initial condition (vanilla put option)

double BSTwoFactorUVM::init_cond(double x,double y) const {
       
      double stock_price = std::max(a_*x/(1.0-x),b_*y/(1.0-y)); 
      
          return option->operator()(stock_price);
}
double BSTwoFactorUVM::Constraint(double x,double y) const {
     // Test in American put option
     
        double stock_price = std::min(a_*x/(1.0-x),b_*y/(1.0-y)); 
        
        return option->operator()(stock_price);
    }
    
double BSTwoFactorUVM::claculate_option_value(double U,double x, double t) const {
       
       return 0.0;
    }  

#endif

 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

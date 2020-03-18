

#ifndef __ADE_CPP
#define __ADE_CPP

#include <fstream>
#include <iostream>
#include "Input.h"
#include "Ade.h"
#include "PseudoFactory.h"


ADEBase::ADEBase(PseudoFactory & fac) 
  :r_(fac.Getr()),X_(fac.GetX()),a_(fac.Geta()),
  N_(fac.GetN()),J_(fac.GetJ()),x_dom_(fac.Getx_dom()),t_dom_(fac.Gett_dom()){}

ADE::ADE(PseudoFactory & fac) 
: ADEBase(fac) {
opt = fac.CreatePayOff();
pde = fac.CreatePDE();              
calculate_step_sizes();
set_initial_conditions();
   
}

void ADE::calculate_step_sizes() {
  dx = x_dom_/static_cast<double>(J_-1);
  dt = t_dom_/static_cast<double>(N_-1); 
}

void ADE::set_initial_conditions() {
  // Spatial settings
    double cur_spot = 0.0;

    old_U.resize(J_);
    new_U.resize(J_);
    old_V.resize(J_);
    new_V.resize(J_);
    x_values.resize(J_); 
    Gamma_up.resize(J_);
    Gamma_down.resize(J_);
    Average.resize(J_);
    Call_Value.resize(J_);

    for (unsigned long j=0; j<J_; j++) {
       cur_spot = -X_ + static_cast<double>(j)*dx;
       old_U[j] = pde->init_cond(cur_spot);
       old_V[j] = pde->init_cond(cur_spot);
       x_values[j] = cur_spot;
   
   }

  // Temporal settings
  prev_t = t_dom_;
  cur_t =t_dom_;
}

void ADE::calculate_boundary_conditions() {
  new_U[0] = pde->boundary_left(prev_t, x_values[0]);
  new_U[J_ - 1] = pde->boundary_right(prev_t, x_values[J_-1]);
  
  new_V[0] =  pde->boundary_left(prev_t, x_values[0]);
  new_V[J_- 1] = pde->boundary_right(prev_t, x_values[J_-1]);
}

void ADE::calculate_Upword() {
  // Only use inner result indices (1 to J-2)
  for (unsigned long j=1; j<J_-1; ++j) {
      
     calculate_Gamma_Up(j);     
     
    // Temporary variables used throughout
    double A = dt*(pde->diff_coeff(Gamma_down[j ], x_values[j]))/(dx*dx);
    double B = dt*(pde->conv_coeff(Gamma_down[j ], x_values[j]))/(2.0*dx);
    // Differencing coefficients (see \alpha, \beta and \gamma in text)
    alpha = A - B;
    beta =  A + B;
    gamma = 1.0 - A;
    zeta = 1.0 + A + r_*dt;
     
    // Update inner values of spatial discretisation grid (ADE)
    new_U[j] = ((alpha*new_U[j-1]) +
                      (beta * old_U[j+1]) + 
                      (gamma * (old_U[j]) ))/zeta;//upward sweep
      
    // Early exercise  
    IsEarlyExercise_ = opt->IsEarlyExercise();                        
    if (IsEarlyExercise_) early_exercise(j);
      
  }
 
}

void ADE::calculate_Downword() {
  // Only use inner result indices (J-2 to 1)
  for (unsigned long j=1; j<J_ - 1; ++j) {
      
     calculate_Gamma_Down(J_-j-1);    
                  
    // Temporary variables used throughout
    double A = dt*(pde->diff_coeff( Gamma_down[J_- j- 1 ], x_values[J_-j-1]))/(dx*dx);
    double B = dt*(pde->conv_coeff( Gamma_down[J_ - j -1 ], x_values[J_-j-1]))/(dx*2.0);
    
    // Differencing coefficients (see \alpha, \beta and \gamma in text)
    alpha = A - B;
    beta =  A + B;
    gamma = 1.0 - A;
    zeta = 1.0 + A + r_*dt;
     
    new_V[J_-j-1] =  ((alpha*old_V[J_-j-2]) +
                      (beta * new_V[J_-j]) + 
                      (gamma * (old_V[J_-j-1]) ))/zeta;//downward sweep
       
       // Early exercise  
       IsEarlyExercise_ = opt->IsEarlyExercise();              
      if (IsEarlyExercise_) early_exercise(J_-j-1);
      
  }
  
}

   void ADE:: calculate_Gamma_Up(int j) {
       double S =a_*x_values[j]/(1.0 - x_values[j]);
       Gamma_up[j] =((-2.0*a_)/((S + a_)*(S + a_)*(S + a_)))*(old_U[j+1] - old_U[j-1])/(2.0*dx) + 
                    ((a_*a_)/((S + a_)*(S + a_)*(S + a_)*(S + a_)))* (old_U[j+1]
                     - old_U[j] - old_U[j] + new_U[j-1]) /(dx*dx) ;//gamma of the option  
   }   
   
    void ADE:: calculate_Gamma_Down(int j) {
        double S =a_*x_values[j]/(1.0 - x_values[j]);
        Gamma_down[j] =((-2.0*a_)/((S + a_)*(S + a_)*(S + a_)))*(old_V[j+1] - old_V[j-1])/(2.0*dx) + 
                       ((a_*a_)/((S + a_)*(S + a_)*(S + a_)*(S + a_)))*(old_V[j-1]
                        - old_V[j] - old_V[j] + new_V[j+1]) /(dx*dx);//gamma of the option
   }   
   
void ADE::early_exercise(int j){
        
    double tmp = pde->Constraint(x_values[j]);
        if (new_U[j]  < tmp)
            {
                new_U[j] = tmp;
            }
                  
            if (new_V[j] < tmp)
            {
                new_V[j] = tmp;
            }    
    }         

void ADE::calculate_average() {
    
    for(int j=0;j<J_;j++){             
            
    Average[j] = 0.5*(new_U[j] + new_V[j]);
   
    }               
  }  
void ADE::main_calculation() { 
 
 for(int i=1; i<=N_; i++) {
    cur_t = prev_t - dt;
    calculate_boundary_conditions();
    calculate_Upword();
    calculate_Downword();
    calculate_average();
    
    old_U = new_U;
    old_V= new_V;
    prev_t = cur_t;
   
   }   
  
}

double ADE::Option_Price(int j) {
    
    return Average[j];         

}

void ADE::print_values() {
     
std::ofstream ade_out("Excell_results.csv");

for (int j=0; j<J_; j++) {
    
   // V[j] = pde->claculate_option_value(u[j],x_values[j],cur_t);  
    double S =  (a_*x_values[j]/(1.0 - x_values[j]));
    Call_Value[j] = S + Average[j] - 100.0*exp(-r_*t_dom_);
    ade_out << x_values[j] << "      " << cur_t << "      " << new_U[j] << "      " <<new_V[j]  << std::endl;
      
 }
  
    std::cout << " option_value  " << new_U[(J_ -1)/2] <<  "      " <<new_V[(J_ - 1)/2] <<  "      " <<Average[(J_ - 1)/2] <<std::endl; 
    ade_out.close(); 
}
    
#endif
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

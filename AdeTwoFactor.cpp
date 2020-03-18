

#ifndef __ADETWOFACTOR_CPP
#define __ADETWOFACTOR_CPP

#include <fstream>
#include <iostream>
#include "Input.h"
#include "AdeTwoFactor.h"
#include "PseudoFactory.h"

ADETwoFactorBase::ADETwoFactorBase(PseudoFactory & fac) 
  :r_(fac.Getr()),X_(fac.GetX()),a_(fac.Geta()),b_(fac.Getb()),
   N_(fac.GetN()),J_(fac.GetJ()),x_dom_(fac.Getx_dom()),t_dom_(fac.Gett_dom()) {}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//Ade_two factor 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
ADETwoFactor::ADETwoFactor(PseudoFactory & fac) 
: ADETwoFactorBase(fac) {
                        
    opt = fac.CreatePayOff();
    ade_one_factor = fac.CreateADE();
    ade_one_factor->main_calculation();   
    pde_two = fac.CreateTwoFactorPDE();                        
    calculate_step_sizes();
    set_initial_conditions();

}; 
  

void ADETwoFactor::calculate_step_sizes() {
     
    dx = x_dom_/static_cast<double>(J_-1);
    dy = x_dom_/static_cast<double>(J_-1);
    dt = t_dom_/static_cast<double>(N_-1);
  
}

void ADETwoFactor::set_initial_conditions() {
   // Spatial settings
    double cur_spot_x = 0.0;
    double cur_spot_y = 0.0;

    U_old.resize(J_,J_);
    U_new.resize(J_,J_);
    V_old.resize(J_, J_);
    V_new.resize(J_,J_);
    Gamma_up_S1.resize(J_);
    Gamma_up_S2.resize(J_);
    Gamma_up_S1S2.resize(J_);
    Gamma_down_S1.resize(J_);
    Gamma_down_S2.resize(J_);
    Gamma_down_S1S2.resize(J_);
    Average.resize(J_,J_);
    
    x_values.resize(J_); 
    y_values.resize(J_);
  
    for (unsigned long i=0; i<J_; i++) {
    
         cur_spot_y =  static_cast<double>(i)*dy;
         calculate_current_spot_x(i,cur_spot_y);
         y_values[i] = cur_spot_y;
    }
    // Temporal settings
    prev_t = t_dom_;
    cur_t =t_dom_;
}

void ADETwoFactor::calculate_current_spot_x(int i,double cur_y) {
double cur_spot_x = 0.0;

for (unsigned long j=0; j<J_; j++) {
    cur_spot_x =   static_cast<double>(j)*dx;
    U_old(j,i) = pde_two->init_cond(cur_spot_x,cur_y);
    V_old(j,i) = pde_two->init_cond(cur_spot_x,cur_y);
   
    x_values[j] = cur_spot_x;
   
  }
}  

void ADETwoFactor::calculate_boundary_conditions(int i) {
   
    U_new(0,i) = V_new(0,i)= ade_one_factor->Option_Price(i);
    U_new(J_ - 1,i) = V_new(J_ - 1,i)= pde_two->boundary_right(prev_t, x_values[J_-1]);
  
    U_new(i,0) = V_new(i,0)= U_new(0,i);
    U_new(i,J_ - 1) =  V_new(i,J_ - 1)= pde_two->boundary_upper(prev_t,y_values[J_-1]); 
    
}

void ADETwoFactor::calculate_Upword(int j,int i) {
     // Only use inner result indices (1 to J-2)
     calculate_Gamma_Up_S1(j,i);     
     calculate_Gamma_Up_S2(j,i);
     calculate_Gamma_Cross_Up(j,i);          
    
    // Temporary variables used throughout
    double A_1 = dt*(pde_two->diff_coeff_1(Gamma_up_S1[j], x_values[j],y_values[i]))/(dx*dx);
    double B_1 = dt*(pde_two->conv_coeff_1(Gamma_up_S1[j], x_values[j],y_values[i]))/(2.0*dx);
    
    double A_2 = dt*(pde_two->diff_coeff_2(Gamma_up_S2[j],x_values[j], y_values[i]))/(dy*dy);
    double B_2 = dt*(pde_two->conv_coeff_2(Gamma_up_S2[j],x_values[j],y_values[i]))/(2.0*dy);
    double C =   dt*(pde_two->crossTerm(Gamma_up_S1S2[j],x_values[j],y_values[i]))/(dy*dx);
   
    // Differencing coefficients (alpha_x,alpha_y \beta and \gamma in text)
    alpha_x =  A_1  - B_1  ;
    alpha_y =  A_2  - B_2 + C ;
    beta_x = A_1 +B_1+ C ;
    beta_y = A_2 + B_2 ;
    gamma = 1.0 - A_1 - A_2 ; 
    zeta = 1.0 + A_1 + A_2 + C + r_*dt;
    // Update inner values of spatial discretisation grid (ADE)
    U_new(j,i) = ((alpha_x*U_new(j-1,i)) + (alpha_y*U_new(j,i-1))+
                  (beta_x * U_old(j+1,i)) + (beta_y * U_old(j,i+1))+
                  (gamma * (U_old(j,i)))- C*(U_old(j+1,i-1)))/zeta;//upward sweep
      
      
      IsEarlyExercise_ = opt->IsEarlyExercise();                        
      if (IsEarlyExercise_) early_exercise(j,i); 

}
 


void ADETwoFactor::calculate_Downword(int j,int i) {
     // Only use inner result indices (1 to J-2)
     calculate_Gamma_Down_S1(j,i); 
     calculate_Gamma_Down_S2(j,i); 
     calculate_Gamma_Cross_Down(j,i);    
                  
    
    // Temporary variables used throughout
    double A_1 = dt*(pde_two->diff_coeff_1( Gamma_down_S1[j], x_values[j],y_values[j]))/(dx*dx);
    double B_1 = dt*(pde_two->conv_coeff_1(  Gamma_down_S1[j],x_values[j],y_values[j]))/(2.0*dx);
    
    double A_2 = dt*(pde_two->diff_coeff_2( Gamma_down_S2[j],x_values[j], y_values[j]))/(dy*dy);
    double B_2 = dt*(pde_two->conv_coeff_2( Gamma_down_S2[j],x_values[j],y_values[j]))/(2.0*dy);
    double C =   dt*(pde_two->crossTerm(Gamma_down_S1S2[j],x_values[j],y_values[j]))/(dy*dx);

    // Differencing coefficients (see \alpha, \beta and \gamma in text)
    alpha_x =  A_1  - B_1;
    alpha_y =  A_2  - B_2 + C;
    beta_x = A_1 +B_1 + C ;
    beta_y = A_2 + B_2  ;
    gamma = 1.0 - A_1 - A_2; 
    zeta = 1.0 + A_1 + A_2 + C + r_*dt;
    V_new(j,i) = ((alpha_x*V_old(j-1,i)) + (alpha_y*V_old(j,i-1))+
                  (beta_x * V_new(j+1,i)) + (beta_y * V_new(j,i+1))+
                  (gamma * (V_old(j,i))) - (C*(V_old(j+1,i-1))))/zeta;
    
    IsEarlyExercise_ = opt->IsEarlyExercise();              
    if (IsEarlyExercise_) early_exercise(J_-j-1,J_-i-1);
      
  
}
  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Gamma calculations
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


void ADETwoFactor:: calculate_Gamma_Up_S1(int j,int i) {
        double S_1 =a_*x_values[j]/(1.0 - x_values[j]);
        Gamma_up_S1[j] =((-2.0*a_)/((S_1 + a_)*(S_1 + a_)*(S_1 + a_)))*(U_old(j+1,i) 
        - U_old(j-1,i))/(2.0*dx) + ((a_*a_)/((S_1 + a_)*(S_1 + a_)*(S_1 + a_)*(S_1 + a_)))*
        (U_old(j+1,i) - U_old(j,i) - U_old(j,i) + U_new(j-1,i)) /(dx*dx) ;//gamma of the option  
   }   
void ADETwoFactor:: calculate_Gamma_Up_S2(int j,int i) {
       double S_2 =b_*y_values[i]/(1.0 - y_values[i]);
       Gamma_up_S2[j] =((-2.0*b_)/((S_2 + b_)*(S_2 + b_)*(S_2 + b_)))*(U_old(j,i+1) 
       - U_old(j,i-1))/(2.0*dx) + ((b_*b_)/((S_2 + b_)*(S_2 + b_)*(S_2 + b_)*(S_2 + b_)))*
        (U_old(j,i+1) - U_old(j,i) - U_old(j,i) + U_new(j,i-1)) /(dy*dy) ;//gamma of the option  
   }   
  
void ADETwoFactor:: calculate_Gamma_Down_S1(int j,int i) {
        
        double S_1 =a_*x_values[j]/(1.0 - x_values[j]);
       Gamma_down_S1[j] =((-2.0*a_)/((S_1 + a_)*(S_1 + a_)*(S_1 + a_)))*(V_old(j+1,i)
        - V_old(j-1,i))/(2.0*dx) + ((a_*a_)/((S_1 + a_)*(S_1 + a_)*(S_1 + a_)*(S_1 + a_)))*
        (V_old(j-1,i)- V_old(j,i)- V_old(j,i) + V_new(j+1,i)) /(dx*dx);//gamma of the option
   }
   
void ADETwoFactor:: calculate_Gamma_Down_S2(int j,int i) {
        
        double S_2 =b_*y_values[i]/(1.0 - y_values[i]);
        Gamma_down_S2[j] =((-2.0*b_)/((S_2 + b_)*(S_2 + b_)*(S_2 + b_)))*(V_old(j,i+1)
        - V_old(j,i-1))/(2.0*dx) + ((b_*b_)/((S_2 + b_)*(S_2 + b_)*(S_2 + b_)*(S_2 + b_)))*
        (V_old(j,i-1)- V_old(j,i)- V_old(j,i) + V_new(j,i+1)) /(dy*dy);//gamma of the option
   }  
 
void ADETwoFactor:: calculate_Gamma_Cross_Up(int j,int i) {
        
        double S_1 =a_*x_values[j]/(1.0 - x_values[j]);
        double S_2 =a_*y_values[i]/(1.0 - y_values[i]);
        Gamma_up_S1S2[j] =((b_*a_)/((S_1 + a_)*(S_1 + a_)*(S_2 + b_)*(S_2 + b_)))*
        (U_new(j - 1,i)- U_old(j + 1,i - 1)- U_new(j,i) + U_old(j + 1,i)) /(dx*dy);//gamma of the option
   }   
   
 void ADETwoFactor:: calculate_Gamma_Cross_Down(int j,int i) {
        
        double S_1 =a_*x_values[j]/(1.0 - x_values[j]);
        double S_2 =a_*y_values[i]/(1.0 - y_values[i]);
        Gamma_down_S1S2[j] =((a_*b_)/((S_1 + a_)*(S_1 + a_)*(S_2 + b_)*(S_2 + b_)))* 
        (V_old(j-1,i)- V_old(j,i)- V_old(j + 1,i - 1) + V_new(j+1,i)) /(dx*dy);//gamma of the option
   } 
     
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	early_exercise
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
     
void ADETwoFactor::early_exercise(int j,int i){
        
        double tmp = pde_two->Constraint(x_values[j],y_values[i]);
        if (U_new(j,i) < tmp)
            {
                U_new(j,i) = tmp;
            }
                  
            if (V_new(j,i) < tmp)
            {
                V_new(j,i) = tmp;
            }     
    }  
          

void ADETwoFactor::calculate_average(int j,int i) {
               
    Average(j,i) = 0.5*(U_new(j,i) + V_new(j,i));                 
}  

void ADETwoFactor::main_calculation() { 
    std::ofstream ade_out("Excell_results.csv");

       for(int k=1; k <= N_; k++) {
       cur_t = prev_t - dt;
       for(int j=0; j<=J_-1; j++) {
       calculate_boundary_conditions(j);
       }
       for (int i=1; i<J_-1; ++i){
       for(int j=1; j<J_-1; ++j) {
       calculate_Upword(j,i);
       calculate_Downword(J_ - j- 1,J_ - i- 1);
       
       }  
   }
   for (int j=0; j<J_; j++) {
      
     // V[j] = pde->claculate_option_value(u[j],x_values[j],cur_t);   
    ade_out << x_values[j] << "      " << cur_t << "      " << U_new((J_ -1)/2,(J_ - 1)/2) << "      " <<V_new((J_ - 1)/2,(J_ - 1)/2)<< std::endl;
 
    }
    U_old = U_new;
    V_old= V_new;
    prev_t = cur_t;
   
}   

  calculate_average((J_ - 1)/2,(J_ - 1)/2);
  
  std::cout << " option_value  " << U_new((J_ - 1)/2,(J_ - 1)/2) <<  "      " <<V_new((J_ - 1)/2,(J_ - 1)/2) <<  "      " <<Average((J_ - 1)/2,(J_-1)/2) <<std::endl;
  
  ade_out.close();
}

#endif
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

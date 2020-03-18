//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Input.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#include <math.h>
#include "Input.h"
#include <iostream>
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{
   
             
   //Parametr values 
    K_ = 65.0;    // Strike price
    E_ = 60.0;   // second strike price
    r_ = 0.08;   // Risk-free rate ()
   
    v_min_ = 0.3;    // Volatility of the underlying ()
    v_max_ = 0.5;    // the uncertain volatility model
   
    sigma_1 = 0.3;   // the volatility of S1
    sigma_2 = 0.5;   // the volatilty of S2
    rho_ = 0.3;      // the corelation coeficient between S1 and S2
   
    a_ = 60.0;   // a is for S1(the first equity)
    b_ = 40.0;  // b is for S2(the second equity) 
  	 
    kappa_ = 0.0; 	// branching parameter for Lattice (0 means use default value)
    
    w_1 = 0.5;     //weights for basket options
    w_2 = 0.5;
   
    T_ = 0.25;    //  years until expiry
    
    double tau_ = 0.5*sigma_1*sigma_1*T_;  // tau is for heat equation 
    
    t_dom_ = T_;         // Time period as for the option
   
    X_ = 0.0;  

  //ADE and Lattice discretisation parameters
    x_dom_ =0.999999999;       // Spot goes from [0.0, 1.0]
    J_ =801;
    N_ = 100;
    
    
    
    
        // Application identification 
   	
        O_type_ = 'c';   	// c for call,  p  for put, 
						// s for call spread,  d for put spread,P for American put
       
   
        Meth_type_ = 'l';    // p for ADE one factor, k for ADE two factor,l for lattice,t for two factor Lattice
    
    
    
        // choose based on the kind of method
    
        pde_type_ = 'n';     // n for normal bse,k for UVM one factor
    
        twofactorpde_type_ = 'g';  	// n for normal two factor bse, g for UVM two factor				
   	
        ADE_type_ = 'p';  	// p for Ade one factor 
        se_Meth_type_ = 'p'; // p for the ADE two factor method
   
   	    app_type_ = 'v';   	// v for valuation application
   	
   
        bch_type_ = '1';  	// 1 for trinomial UVM, 3 for normal trinomial, 4 for twofactor Lattice
    
        slc_type_ = 'm';  	// m for trinomial 1-dim multiplicative,t for Binomial Lattice two Factor

}
  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

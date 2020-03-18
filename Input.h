//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef InputH
#define InputH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  class Input
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class Input
{
    public:
        Input();
        
        double Getv_min() const {return v_min_;}
        double Getv_max() const {return v_max_;}
        
        double Getr() const {return r_;}
        double GetK() const {return K_;}
        double GetE() const {return E_;}
        double GetX() const {return X_;}
        double Getw_1() const {return w_1;}
        double Getw_2() const {return w_2;}
        double GetT() const {return T_;}
        double Geta() const {return a_;}
        double Getb() const {return b_;}
        double Getrho() const {return rho_;}
        double Getsigma1() const {return sigma_1;}
        double Getsigma2() const {return sigma_2;}
        double Getx_dom() const {return x_dom_;}
        double Gett_dom() const {return t_dom_;}
        long GetN() const {return N_;}
        long GetJ() const {return J_;}
         
        double GetKappa() const {return kappa_;}
        char GetOtype() const {return O_type_;}
        char GetPtype() const {return p_type_;}
        char GetpdeType() const {return pde_type_;}
        char GettwofactorPdetype() const {return twofactorpde_type_;}
        char GetMethodType() const {return Meth_type_;}
        char GetTwoFactorMethodType() const {return se_Meth_type_;}
        char GetApplicationtype() const {return app_type_;}
        char GetADEtype() const {return ADE_type_;}
        
        char GetBranchingType() const {return bch_type_;}
        char GetSliceType() const {return slc_type_;}
         
        
                
    private:
        double kappa_;  	// lattice branching parameter
        double K_;
        double E_;
        double r_;   // Risk-free rate (5%)
        double v_min_;   // Volatility of the underlying (20%)
        double v_max_;
        double sigma_1;
        double sigma_2;
        double a_;
        double b_;
        double w_1;
        double w_2;
        
    
   
        double rho_ ;
   
        double T_;
        //double tau = 0.5*v*v*T;
        double X_;   // One year until expiry

        // FDM discretisation parameters
        double x_dom_;       // Spot goes from [0.0, 1.0]
        long J_;
        double t_dom_;        // Time period as for the option
        long N_;
   
        char O_type_;		//  type
        char p_type_;	
        char pde_type_;
        char ADE_type_;
        char twofactorpde_type_;
        char Meth_type_;   	// method type
        char se_Meth_type_;
        char app_type_;    	// application type
  
        char bch_type_;		// branching type (lattice)
        char slc_type_;  	    // slice type (lattice)
  
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

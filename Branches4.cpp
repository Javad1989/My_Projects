//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Branches3.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>

#include "Branches4.h"
#include <Eigen/Dense>
#include <iostream>
#include "PseudoFactory.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  un-named namespace
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace
{
    const long NumBranches = 4;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Branches4::Branches4(PseudoFactory & fact)
:   CRITICAL_KAPPA_(1.0)
,   branches_(NumBranches)
,   up_branches_(1)
,   kappa_(fact.GetKappa())
,   sig_1(fact.Getsigma1())
,   sig_2(fact.Getsigma2())
,   rho(fact.Getrho())
,    r(fact.Getr())
{
    
	if (kappa_ == 0) kappa_ = CRITICAL_KAPPA_;
	
     double dt = fact.GetT()/fact.GetN();
     dz_ = std::sqrt(kappa_*dt);
     probs_.resize(branches_);
     ComputeProbs(); 
   
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void Branches3::ComputeProbs()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void  Branches4::ComputeProbs() 
{
       
     /*double vol = sig_ * dz_;
     double p=0;
     double l   = (1.0 + 0.5*vol)*vec[i - 1] + (1.0 - 0.5*vol)*  vec[i +1] - 2.0*vec[i]; 
  
        if (l > 0.0)
        {
        p =0.5;
        }
        else 
        {
        p = sig2_*sig2_/(2.0*sig_*sig_);
        }
    
      double ptemp[] = {p*(1.0 + (vol/2.0)),1.0 - 2.0*p,p*(1.0 - (vol/2.0))};
      vd probs_(ptemp, ptemp + 3);*/
     

   //probs_.resize(4);
   probs_[0] = (1.0/4.0)*(1.0 + (((r - (sig_1*sig_1/2.0))/(sig_1) + (r - (sig_2*sig_2/2.0))/(sig_2)))*dz_ +rho);
   probs_[1] = (1.0/4.0)*(1.0 + (((r - (sig_1*sig_1/2.0))/(sig_1) - (r - (sig_2*sig_2/2.0))/(sig_2)))*dz_ -rho);
   probs_[2] = (1.0/4.0)*(1.0 + ((-(r - (sig_1*sig_1/2.0))/(sig_1) - (r - (sig_2*sig_2/2.0))/(sig_2)))*dz_ +rho);
   probs_[3] = (1.0/4.0)*(1.0 + ((-(r - (sig_1*sig_1/2.0))/(sig_1) + (r - (sig_2*sig_2/2.0))/(sig_2)))*dz_ - rho);
   
    
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  NextValue()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Branches4::NextV(long i,long j, Eigen::MatrixXd & vec) const
{
    double v = 0.0;
    
    
  v = probs_[0] * vec(i + 1,j+1)+probs_[1] * vec(i + 1,j)
  +probs_[2] * vec(i ,j)+ probs_[3] * vec(i ,j+1); 
         
    return v;
}

double Branches4::NextValue(long j, std::vector<double> & vec) const{
       
       return 0.0;
}       
       

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


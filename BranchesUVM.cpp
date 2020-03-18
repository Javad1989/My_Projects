//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Branches3.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>

#include "BranchesUVM.h"
#include <iostream>
#include "PseudoFactory.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  un-named namespace
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace
{
    const long NumBranches = 3;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

BranchesUVM::BranchesUVM(PseudoFactory & fact)
:   CRITICAL_KAPPA_(1.0)
,   branches_(NumBranches)
,   up_branches_(long(0.5*(branches_ - 1)))
,   kappa_(fact.GetKappa())
,   sig_1(fact.Getsigma1())
,   sig_2(fact.Getsigma2())
,   r_(fact.Getr())
{
    
	if (kappa_ == 0) kappa_ = CRITICAL_KAPPA_;
	drift_= r_;
    double dt = fact.GetT()/fact.GetN();
    dz_ = std::sqrt(kappa_*dt);
    probs_.resize(branches_);
   
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void Branches3::ComputeProbs()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double  BranchesUVM::ComputeProbs(long i,long j,std::vector<double> & vec ) const
{
       
     double vol = sig_1 * dz_;
     double p;
     double l   = (1.0 + 0.5*vol)*vec[i - 1] + (1.0 - 0.5*vol)*  vec[i +1] - 2.0*vec[i] ; 
     
        if (l > 0.0)
        {
        p =0.5;
        }
        else 
        {
        p = sig_2*sig_2/(2.0*sig_1*sig_1);
        }
    
      double ptemp[] = {p*(1.0 + (vol/2.0)),1.0 - 2.0*p,p*(1.0 - (vol/2.0))};
      vd probs_(ptemp, ptemp + 3);
      
   
    return probs_[j];
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  NextValue()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double BranchesUVM::NextValue(long j, std::vector<double> & vec) const
{
    double v = 0.0;
    
  
    for(long k = 0; k != branches_; ++k)
    {
            
        double m =ComputeProbs(j,k,vec);

        v += m * vec[j + k - up_branches_];
    }
    
    return v;
}
double BranchesUVM::NextV(long i,long j, Eigen::MatrixXd & vec) const{
       
       return 0.0;
}      

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


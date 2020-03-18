//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Branches3.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>

#include "Branches3.h"

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

Branches3::Branches3(PseudoFactory & fact)
:   CRITICAL_KAPPA_(4.0)
,   branches_(NumBranches)
,   up_branches_(long(0.5*(branches_ - 1)))
,   kappa_(fact.GetKappa())
,   r_(fact.Getr())
,   sig(fact.Getsigma1())
{
	if (kappa_ == 0) kappa_ = CRITICAL_KAPPA_;
	drift_=r_-0.5*sig*sig;
    double dt = fact.GetT()/fact.GetN();
    dz_ = std::sqrt(kappa_*dt);
    ComputeProbs();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void Branches3::ComputeProbs()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Branches3::ComputeProbs()
{
    probs_.resize(branches_);
    probs_[2] = 0.5/kappa_;                 // branches hardwired at three
	probs_[1] = (kappa_ - 1)/kappa_;        // index of middle branch
    probs_[0] = probs_[2];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  NextValue()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Branches3::NextValue(long j, std::vector<double> & vec) const
{
    double v = 0.0;
    
    for(long k = 0; k != branches_; ++k)
    {
        v += probs_[k] * vec[j + k - up_branches_];
    }
    
    return v;
}

double Branches3::NextV(long i,long j, Eigen::MatrixXd & vec) const{
       
       return 0.0;
}   

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


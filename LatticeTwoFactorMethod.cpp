//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	LatticeMethod.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>



#include "LatticeTwoFactorMethod.h"

#include "PseudoFactory.h"

#include "PayOff.h"
#include "BranchesBase.h"
#include "SliceBase.h"



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	constructor()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

LatticeTwoFactorMethod::LatticeTwoFactorMethod(PseudoFactory & fac)
:	prb_(0)
,   slc_(0)
,   N_(fac.GetN())
{
	opt = fac.CreatePayOff();
    prb_ = fac.CreateBranches();    // Owns
    slc_ = fac.CreateSlice();       // Owns
    
    slc_->SetBranches(*prb_);       // passes prb_ over to the slice
    
    double T = fac.GetT();
    dt_ = T/N_;
}
                     
LatticeTwoFactorMethod::~LatticeTwoFactorMethod()
{
    delete prb_;
    delete slc_;
}
                     
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	run()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void LatticeTwoFactorMethod::run()
{
    slc_->SetValues(); 
    
    IsEarlyExercise_ = opt->IsEarlyExercise();

    for(long j = N_ - 1; j >= 0; --j)
    {
        
        
    	slc_->roll_back(j);
    	
		//if (IsEarlyExercise_) slc_->Early_update(j);
		
        slc_->roll_over(j);
    }
    double c = slc_->GetOValue();
    std::cout << " option_value  " << c << std::endl;
}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	RegisterOutput()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX








//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SliceMultiplicative.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>



#include "SliceMultiplicative.h"

#include "PseudoFactory.h"


#include "BranchesBase.h"
//#include "payoff.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	constructor()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

SliceMultiplicative::SliceMultiplicative(PseudoFactory & fact)
:   N_(fact.GetN())
,   S_0_(fact.Geta())
,   sig(fact.Getsigma1())
,   r_(fact.Getr())
,   T(fact.GetT())
,   this_value_(0)
,   next_value_(0)
{
    opt_ = fact.CreatePayOff();
     
    this_value_ = new std::vector<double>;
    next_value_ = new std::vector<double>;
}
                     
SliceMultiplicative::~SliceMultiplicative()
{
	delete this_value_;
	delete next_value_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SetBranches()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::SetBranches(const BranchesBase & ptb)
{
    prb_ = &ptb;
   
    
    upbranches_ = prb_->GetUpBranches();
    adj_ = N_ ;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SetValues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::SetValues()
{
    
    current_t_ = T;  // initial value
    dt_ = current_t_/N_;
    
    long Vsize = 2*adj_ + 1;

    this_value_->resize(Vsize);
    next_value_->resize(Vsize);
    
    ComputeSvalues(Vsize);
    ComputePayoffValues(Vsize);

	*this_value_ = payoffs_;

    dis_dt_ = std::exp(-r_*dt_);
    scale_s_ = std::exp(r_* dt_);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_back()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::roll_back(long j)
{
    current_t_ -= dt_;

	long ub = j*upbranches_;
    for(long i = -ub; i <= ub; ++i)
    {
         
        (*next_value_)[i + adj_] = dis_dt_ * prb_->NextValue(i + adj_, *this_value_);
        
    }            
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXvXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Bermudan_update()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::Early_update(long j)
{
    roll_back_S(j);
	if (opt_->IsEarlyExercise()) Bermudan_update(j);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXvXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  GetOValue()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


double SliceMultiplicative::GetOValue() const {
     
     return (*this_value_)[adj_];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_back_S()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::roll_back_S(long j)
{
	long ub = j*upbranches_;
    for(long i = -ub; i <= ub; ++i) S_values_[i + adj_] *= scale_s_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Bermudan_update()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::Bermudan_update(long j)
{
	long ub = j*upbranches_;
    for(long i = -ub; i <= ub; ++i)
    {
        payoffs_[i + adj_] = opt_->operator()(S_values_[i + adj_]);

        if (payoffs_[i + adj_] > (*next_value_)[i + adj_])
		{
  		    (*next_value_)[i + adj_] = payoffs_[i + adj_];
		}
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_over().  swap over the two pointers:  rolls over to the next time.
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::roll_over(long j){std::swap(this_value_, next_value_);}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ComputeSvalues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::ComputeSvalues(long Vsize)
{
    double dz = prb_->Getdz();

    std::vector<double> Z_values(Vsize);  // 'Wiener' values for the final time
   
    for(long i = -adj_; i <= adj_; ++i)
    {
        Z_values[i + adj_] = i*dz;
    }

    S_values_.resize(Vsize);
    long N = Z_values.size();
    
    for(long i = 0;  i !=N ; ++i)       //for each time step
    {
             drift = prb_->GetDrift();
        S_values_[i] = S_0_ * std::exp(drift*T+ sig*Z_values[i]) ;
    }
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ComputeSvalues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceMultiplicative::ComputePayoffValues(long Vsize)
{
     payoffs_.resize(Vsize);
     for(long i = 0;  i != Vsize; ++i)
    {
        payoffs_[i] = opt_->operator()(S_values_[i]);
    }
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX






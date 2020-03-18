//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SliceMultiplicative.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <Eigen/Dense>



#include "SliceTwoFactor.h"

#include "PseudoFactory.h"


#include "BranchesBase.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	constructor()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

SliceTwoFactor::SliceTwoFactor(PseudoFactory & fact)
:   N(fact.GetN())
,   T(fact.GetT())
,   r_(fact.Getr())
,   sig_1(fact.Getsigma1())
,   sig_2(fact.Getsigma2())
,   S1_0(fact.Geta())
,   S2_0(fact.Getb())
,   this_value_(0)
,   next_value_(0)

{
    opt_ = fact.CreatePayOff();
    
    this_value_ = new  Eigen::MatrixXd;
    next_value_ = new  Eigen::MatrixXd;
}
                     
SliceTwoFactor::~SliceTwoFactor()
{
	delete this_value_;
	delete next_value_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SetBranches()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::SetBranches(const BranchesBase & ptb)
{
    prb_ = &ptb;
    
    upbranches_ = prb_->GetUpBranches();
    adj_ = N * upbranches_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SetValues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::SetValues()
{
    
    
    current_t_ = T;  // initial value
    dt_ = current_t_/N;
    
    long Vsize = 2*adj_ + 1;
     
     
    this_value_->resize(Vsize,Vsize);
    next_value_->resize(Vsize,Vsize);
    
    ComputeSvalues(Vsize);
    ComputePayoffValues(Vsize);

	*this_value_ = payoffs_;

    dis_dt_ = std::exp(-r_*dt_);
    scale_s_ = std::exp(r_*dt_);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_back()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::roll_back(long j)
{
    current_t_ -=dt_;

	long ub = j*upbranches_;
	for(long k = 0; k <= j; ++k) { 
    for(long i = 0; i <= j; ++i)
    {
          
        (*next_value_)(k ,i ) = dis_dt_ * prb_->NextV(k ,i , *this_value_);
        
    }  
}          
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXvXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Bermudan_update()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::Early_update(long j)
{
    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_back_S()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::roll_back_S(long j)
{

    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Bermudan_update()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


void SliceTwoFactor::Bermudan_update(long j)
{
	
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  roll_over().  swap over the two pointers:  rolls over to the next time.
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::roll_over(long j){std::swap(this_value_, next_value_);}

double SliceTwoFactor::GetOValue() const {
     
     return (*this_value_)(0,0);
}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ComputeSvalues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::ComputeSvalues(long Vsize)
{ 
    dz_ = prb_->Getdz();
     
    vol_1 = dz_* sig_1;
    vol_2 = dz_* sig_2;
    
    u1 = exp(vol_1); /* assign the jump sizes */
    u2 = exp(vol_2);
   
    d1 = exp(-vol_1);
    d2 = exp(-vol_2);
    
    S1_values.resize(2*N+1);
    S2_values.resize(2*N+1);
    
    S1_values[N] =S1_0; /* assign the 2*M+1 asset values for s1 */
    for (long i = 1; i <= N; ++i) {
        
        S1_values[N+i] = u1*S1_values[N+i-1];
        S1_values[N-i] = d1*S1_values[N-i+1];
    
    }
    S2_values[N] = S2_0; /* assign the 2*M+1 asset values for s2 */
    for (long i = 1; i <= N; ++i) {
        
        S2_values[N+i] = u2*S2_values[N+i-1];
        S2_values[N-i] = d2*S2_values[N-i+1];
    
    }   
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ComputeSvalues()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SliceTwoFactor::ComputePayoffValues(long Vsize)
{
    payoffs_.resize(Vsize,Vsize);
    p1=0;
        for(long i = 0; i <= N; ++i){
            p2=0;
            for(long j = 0; j <= N; ++j){
               
                double s = std::max(S1_values[p1] ,S2_values[p2]);
                    
                payoffs_(i,j) = opt_->operator()(s);
        
                p2 = p2 +2;
            }
        p1 = p1 +2;
        }
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX






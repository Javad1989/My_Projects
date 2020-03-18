#ifndef __PAY_OFF_CPP
#define __PAY_OFF_CPP

#include "payoff.h"
#include "PseudoFactory.h"

PayOff::PayOff() {}

// ==========
// PayOffCall
// ==========

 // Constructor with single strike parameter
 
PayOffEuroCall::PayOffEuroCall(PseudoFactory & fac) :  K_(fac.GetK()),
E_(fac.GetE()),T_(fac.GetT()),r_(fac.Getr()), J_(fac.GetJ()),early_(false) {}
 
    // Over-ridden operator() method, which turns PayOffCall into a function object
    double PayOffEuroCall::operator() (const double& S) const {
  
    return std::max(S - K_, 0.0); // Standard European call pay-off

} 

double PayOffEuroCall::calculate_Call_value(const double& S,std::vector<double>& P,long j)  const {
        
    return   S + P[j] - K_*exp(-r_*T_); //from put-call parity
}  
// =========
// PayOffPut
// =========

// Constructor with single strike parameter
PayOffEuroPut::PayOffEuroPut(PseudoFactory & fac) 
: K_(fac.GetK()),early_(false)
{}

// Over-ridden operator() method, which turns PayOffPut into a function object
double PayOffEuroPut::operator() (const double& S) const {
       
    return std::max(K_ - S, 0.0); // Standard European put pay-off
}

// =========
// PayOffAmericanPut
// =========

// Constructor with single strike parameter
PayOffAmericanPut::PayOffAmericanPut(PseudoFactory & fac) 
: K_(fac.GetK()),early_(true)
{}

// Over-ridden operator() method, which turns PayOffPut into a function object
double PayOffAmericanPut::operator() (const double& S) const {
       
    return std::max(K_ - S, 0.0); // Standard European put pay-off
}
// =========
// PayOffCallSpread
// =========

PayOffCallSpread::PayOffCallSpread(PseudoFactory & fac) 
 : K_(fac.GetK()),E_(fac.GetE()),early_(false)
{}

// Over-ridden operator() method, which turns PayOffCallSpread into a function object
double PayOffCallSpread::operator() (const double& S) const {
       
    return  (std::max(S - E_, 0.0) - std::max(S - K_,0.0));// 
}
// =========
// PayOffPutSpread
// =========

PayOffPutSpread::PayOffPutSpread(PseudoFactory & fac) 
 : K_(fac.GetK()),E_(fac.GetE()),early_(false)
{}

// Over-ridden operator() method, which turns PayOffPutSpread into a function object
double PayOffPutSpread::operator() (const double& S) const {
       
    return (std::max(K_ - S, 0.0) - std::max(E_ - S,0.0)); // 

}


// =========
// PayOff Max of Twoassets
// =========



#endif
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

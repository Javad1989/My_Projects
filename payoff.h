//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PDE_bs.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef __PAY_OFF_HPP
#define __PAY_OFF_HPP
#include <vector>
#include <math.h>
#include <algorithm> // This is needed for the std::max comparison function, used in the pay-off calculations

class PseudoFactory;

class PayOff {
 public:
        PayOff(); // Default (no parameter) constructor
        virtual ~PayOff() {}; // Virtual destructor

        // Overloaded () operator, turns the PayOff into an abstract function object
        virtual double operator() (const double& S) const = 0;
        virtual bool IsEarlyExercise() const = 0;
 
};

class PayOffEuroCall : public PayOff {
 private:
        double K_; // Strike price
        double E_;
        double T_;
        double r_;
        double J_;
        bool early_;
  
 public:
        PayOffEuroCall(PseudoFactory & fac);
        virtual ~PayOffEuroCall() {};
 
        // Virtual function is now over-ridden (not pure-virtual anymore)
        virtual double operator() (const double& S) const;
        virtual bool IsEarlyExercise() const {return early_;}
        virtual double calculate_Call_value(const double& S,std::vector<double>& P,long j) const;
};

class PayOffEuroPut : public PayOff {
 private:
        double K_; // Strike
        bool early_;
  
 public:
        PayOffEuroPut(PseudoFactory & fac);
        virtual ~PayOffEuroPut() {};
        virtual double operator() (const double& S) const;
        virtual bool IsEarlyExercise() const {return early_;}
};

class PayOffAmericanPut : public PayOff {
 private:
        double K_; // Strike
        bool early_;
  
 public:
        PayOffAmericanPut(PseudoFactory & fac);
        virtual ~PayOffAmericanPut() {};
        virtual double operator() (const double& S) const;
        virtual bool IsEarlyExercise() const {return early_;}
};

class PayOffCallSpread : public PayOff {
 private:
  double K_; // Strike
  double E_;
  bool early_;
 public:
  
  PayOffCallSpread(PseudoFactory & fac);
  virtual ~PayOffCallSpread() {};
  virtual double operator() (const double& S) const;
  virtual bool IsEarlyExercise() const {return early_;}
};

class PayOffPutSpread : public PayOff {
 private:
  
  double K_; // Strike
  double E_;
  bool early_;
 
 public:
  PayOffPutSpread(PseudoFactory & fac);
  virtual ~PayOffPutSpread() {};
  virtual double operator() (const double& S) const;
  virtual bool IsEarlyExercise() const {return early_;}
};


#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

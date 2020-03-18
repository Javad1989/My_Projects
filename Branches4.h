//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Branches3.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef Branches4H
#define Branches4H
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>

#include "BranchesBase.h"

class PseudoFactory;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Class Branches3 : public BranchesBase
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class Branches4 : public BranchesBase
{
	public:
		explicit Branches4(PseudoFactory &);

        long GetBranches() const {return branches_;}
        long GetUpBranches() const {return up_branches_;}
        double Getdz() const {return dz_;}
        double GetDrift() const {return 0.0;}
        double NextV(long i,long j, Eigen::MatrixXd & vec)  const;
        double NextValue(long j, std::vector<double> & vec) const;
   
    private:
        const double CRITICAL_KAPPA_;             //The critical value of kappa
         typedef std::vector<double> vd;
		//virtual double vsqubra( long) const; // implements []
         void ComputeProbs() ;
        //void ComputeProbs();
        const long branches_;                     // # branches
        const long up_branches_;                  // # up branches
        double kappa_;                            // branching parameter
        double p ;
        double dt_;                               // time step
        double dz_;                               // space step
        double sig_1;
        double sig_2;
        double rho;
        double r;
       std::vector<double> probs_;  
        std::vector <double> probs;             //branching probs
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Branches3.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef Branches3H
#define Branches3H
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>
#include <Eigen/Dense>

#include "BranchesBase.h"

class PseudoFactory;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Class Branches3 : public BranchesBase
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class Branches3 : public BranchesBase
{
	public:
		explicit Branches3(PseudoFactory &);

        long GetBranches() const {return branches_;}
        long GetUpBranches() const {return up_branches_;}
        double Getdz() const {return dz_;}
        double GetDrift() const{return drift_;}
        double NextValue(long j, std::vector<double> & vec) const;
        double NextV(long i,long j, Eigen::MatrixXd & vec) const ;
    private:
        const double CRITICAL_KAPPA_;             //The critical value of kappa

	
        void ComputeProbs();
        
        const long branches_;                     // # branches
        const long up_branches_;                  // # up branches
        double kappa_;                            // branching parameter
        
        double r_;
        double sig;
        double dt_;                               // time step
        double dz_;                               // space step
        double drift_;
        std::vector<double> probs_;               //branching probs
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




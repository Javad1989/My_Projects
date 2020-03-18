//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Branches3.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef BranchesUVMH
#define BranchesUVMH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>
#include <Eigen/Dense>
#include "BranchesBase.h"

class PseudoFactory;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Class Branches3 : public BranchesBase
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class BranchesUVM : public BranchesBase
{
	public:
		explicit BranchesUVM(PseudoFactory &);

        long GetBranches() const {return branches_;}
        long GetUpBranches() const {return up_branches_;}
        double Getdz() const {return dz_;}
        double GetDrift() const{return drift_;}
        double NextValue(long j, std::vector<double> & vec) const;
        double NextV(long i,long j, Eigen::MatrixXd & vec) const;

    private:
        const double CRITICAL_KAPPA_;             //The critical value of kappa
         typedef std::vector<double> vd;
        double ComputeProbs(long i,long j,std::vector<double> & this_value) const;
        
        const long branches_;                     // # branches
        const long up_branches_;                  // # up branches
        double kappa_;                            // branching parameter
        double dt_;                               // time step
        double dz_;                               // space step
        double sig_1;
        double sig_2;
        double drift_;
        double r_;
        std::vector<double> probs_;  
       
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




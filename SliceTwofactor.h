//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SliceMultiplicative.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef SliceTwoFactorH
#define SliceTwoFactorH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>
#include <Eigen/Dense>
#include "payoff.h"
#include "SliceBase.h"

class PseudoFactory;

class BranchesBase;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Slice
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class SliceTwoFactor: public SliceBase
{
    public:
        explicit SliceTwoFactor(PseudoFactory &);
        ~SliceTwoFactor();
       
        void SetValues();
        void SetBranches(const BranchesBase & ptb);

        void roll_back(long j);     // rolls back option values (European)
        void Early_update(long j);  // updates for early exercise
        void roll_over(long j);     // rolls over to the next time

        double GetOValue() const ;
       
    private:
        PayOff * opt_;        // Does not own
        const BranchesBase * prb_;      // Does not own
        
         Eigen::MatrixXd  * this_value_;  // pointers so can swap cheaply
         Eigen::MatrixXd * next_value_;
        
        long p1,p2;
        double u1,u2,d1,d2;
        
        std::vector<double> S1_values;
        std::vector<double> S2_values;
        Eigen::MatrixXd payoffs_;

        long N;                  // time steps
        double dis_dt_;           // discount factor over time dt
        double scale_s_;          // scaling factor for S-rollback
        
        long upbranches_;         // # of up-branches
        long adj_;         		  // adjustment to go from logical to physical indexes

    	double current_t_;   	  // current value of time
    	double T;
    	double dt_;   	  		  // time step
        double sig_1;
        double sig_2;
        double r_;
        double dz_;
        double S1_0,S2_0;
        double vol_1,vol_2;
        void roll_back_S(long j);
        void Bermudan_update(long j);

        void ComputeSvalues(long Vsize);
        void ComputePayoffValues(long Vsize);
        
        // included for illustration only
        double NextValue(long j, std::vector<double> & vec);
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX






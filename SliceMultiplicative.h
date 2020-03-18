//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	SliceMultiplicative.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef SliceMultiplicativeH
#define SliceMultiplicativeH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>

#include "SliceBase.h"
#include "payoff.h"

class PseudoFactory;
class BranchesBase;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Slice
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class SliceMultiplicative : public SliceBase
{
    public:
        explicit SliceMultiplicative(PseudoFactory & );
        ~SliceMultiplicative();
       
        void SetValues();
        void SetBranches(const BranchesBase & ptb);

        void roll_back(long j);     // rolls back option values (European)
        void Early_update(long j);  // updates for early exercise
        void roll_over(long j);     // rolls over to the next time

        double GetOValue() const ;
       
    private:
         PayOff * opt_;        // Does not own
         const BranchesBase * prb_;      // Does not own
        
        std::vector<double> * this_value_;  // pointers so can swap cheaply
        std::vector<double> * next_value_;
        
        std::vector<double> S_values_;
        std::vector<double> payoffs_;

        long N_;                  // time steps
        double S_0_;
        double r_;
        double T;
        double sig;
        double dis_dt_;           // discount factor over time dt
        double scale_s_;          // scaling factor for S-rollback
        
        long upbranches_;         // # of up-branches
        long adj_;         		  // adjustment to go from logical to physical indexes

    	double current_t_;   	  // current value of time
    	double dt_;   	  		  // time step
    	double drift;

        void roll_back_S(long j);
        void Bermudan_update(long j);

        void ComputeSvalues(long Vsize);
        void ComputePayoffValues(long Vsize);
        
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX






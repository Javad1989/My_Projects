//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PseudoFactory.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef PseudoFactoryH
#define PseudoFactoryH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class PayOff;
class ConvectionDiffusionPDE;
class TwoFactorOption;
class ADEBase;
class ADETwoFactorBase;
class ValuationMethodBase;
class ValuationApplication;;
class BranchesBase;
class SliceBase;

class Input;


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  class PseudoFactory
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class PseudoFactory
{
    public:
        
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//  Creation methods
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
         PayOff*  CreatePayOff();
        
        ConvectionDiffusionPDE* CreatePDE();
        TwoFactorOption* CreateTwoFactorPDE();
        
        ValuationMethodBase * CreateMethod();
        ADETwoFactorBase * CreateTwoFactorADE();
        ValuationApplication* CreateApplication();
        ADEBase * CreateADE();
        BranchesBase * CreateBranches();
		SliceBase * CreateSlice();
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//  IO stuff
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

        void SetInput(Input * inp){inp_ = inp;}
       // void SetOutput(Output * out){out_ = out;}

        //Output * GetOutput() const {return out_;}

		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//  parameter getters
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

        double GetK() const;
        double GetE() const;
        double Getr() const;
        double Getsigma(double sigma) const;
        double Getsigma1() const;
        double Getsigma2() const;
        double Getv_min() const;
        double Getv_max() const;
        double Getx_dom() const;
        double Gett_dom() const;
        double GetT() const;
        double Getw_1() const;
        double Getw_2() const;
        double Geta() const;
        double Getb() const;
        double GetX() const;
        double Getrho() const;
        
        long GetJ() const;
        long GetN() const;
        
        
        char GetPtype() const;
        char GetOtype() const;
        double GetKappa() const;                // lattice branching parameter

    private:
        Input * inp_;
       // Output * out_;
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

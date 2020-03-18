//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	PseudoFactory.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <stdexcept>
#include "PseudoFactory.h"

#include "Input.h"

#include "ValuationApplication.h"
#include "ValuationMethodBase.h"

#include "payoff.h"
#include "pde.h"

#include "TwoFactorOption.h"
#include "Ade.h"
#include "AdeTwoFactor.h"
#include "ADEMethod.h"
#include "LatticeMethod.h"
#include "LatticeTwoFactorMethod.h"
#include "ADETwoFactorMethod.h"
#include "BranchesBase.h"
#include "BranchesUVM.h"
#include "Branches3.h"
#include "Branches4.h"
#include "SliceBase.h"
#include "SliceMultiplicative.h"
#include "SliceTwoFactor.h"



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	getter
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double PseudoFactory::GetK() const {return inp_->GetK();}
double PseudoFactory::GetT() const {return inp_->GetT();}
double PseudoFactory::GetE() const {return inp_->GetE();}
double PseudoFactory::Getr() const {return inp_->Getr();}
double  PseudoFactory::Getsigma(double sigma) const {return sigma;}
double PseudoFactory::Getsigma1() const {return inp_->Getsigma1();}
double PseudoFactory::Getsigma2() const {return inp_->Getsigma2();}
double PseudoFactory::Getv_min() const {return inp_->Getv_min();}
double PseudoFactory::Getv_max() const {return inp_->Getv_max();}
double PseudoFactory::Getw_1() const {return inp_->Getw_1();}
double PseudoFactory::Getw_2() const {return inp_->Getw_2();}
double PseudoFactory::Getx_dom() const {return inp_->Getx_dom();}
double PseudoFactory::Gett_dom() const {return inp_->Gett_dom();}
double PseudoFactory::Geta() const {return inp_->Geta();}
double PseudoFactory::Getb() const {return inp_->Getb();}
double PseudoFactory::Getrho() const {return inp_->Getrho();}
double PseudoFactory::GetX() const {return inp_->GetX();}

long PseudoFactory::GetJ() const {return inp_->GetJ();}
long PseudoFactory::GetN() const {return inp_->GetN();}


char PseudoFactory::GetOtype() const {return inp_->GetOtype();}
double PseudoFactory::GetKappa() const {return inp_->GetKappa();}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	CreateOption
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

PayOff * PseudoFactory::CreatePayOff()
{
    char o_type = inp_->GetOtype();
    
    switch(o_type)
    {
        case 'p':  return new PayOffEuroPut(*this); 		    break;
        case 'c':  return new PayOffEuroCall(*this);      	    break;
        case 'P':  return new PayOffAmericanPut(*this);      	break;
        case 's':  return new PayOffCallSpread(*this);   	    break;
        case 'd':  return new PayOffPutSpread(*this);   	    break;
        default:   throw std::runtime_error("PseudoFactory::CreateOption:  Bad character");
    }
}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	CreateAccumulator
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 ConvectionDiffusionPDE * PseudoFactory::CreatePDE()
{
    char pde_type = inp_->GetpdeType();
    
    switch(pde_type)
    {
        case 'n':  return new BlackScholesPDE(*this);         break;
        case 'g':  return new heatequation(*this);            break;
        case 'k':  return new UVMPde(*this);                  break;
        default:   throw std::runtime_error("PseudoFactory::CreatePDE:  Bad character");
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	CreateMethod
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

TwoFactorOption * PseudoFactory::CreateTwoFactorPDE()
{
    char twofactorpde_type = inp_->GettwofactorPdetype();
    
    switch(twofactorpde_type)
    {
        case 'n':  return new BSTwoFactor(*this);         break;
        case 'g':  return new BSTwoFactorUVM(*this);         break;
        default:   throw std::runtime_error("PseudoFactory::CreateTwoFactorPDE:  Bad character");
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	CreateMethod
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

ValuationMethodBase * PseudoFactory::CreateMethod()
{
   char meth_type = inp_->GetMethodType();
    
    switch(meth_type)
    {
        case 'p':  return new ADEMethod(*this);                  break;
        case 'k':  return new ADETwoFactorMethod(*this);         break;
        case 'l':  return new LatticeMethod(*this);		         break;
        case 't':  return new LatticeTwoFactorMethod(*this);     break;
        default:   throw std::runtime_error("PseudoFactory::CreateMethod:  Bad character");
    }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Two Factor method ADE
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

 ADETwoFactorBase * PseudoFactory::CreateTwoFactorADE()
{
    char se_meth_type = inp_-> GetTwoFactorMethodType();
    
    switch(se_meth_type)
    {
        case 'p':  return new ADETwoFactor(*this);         break;
        default:   throw std::runtime_error("PseudoFactory::CreateTwoFactorADE:  Bad character");
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	CreateValuation
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

ValuationApplication * PseudoFactory::CreateApplication()
{
    char app_type = inp_->GetApplicationtype();
    
    switch(app_type)
    {
        case 'v':  return new ValuationApplication(*this);         break;
        default:   throw std::runtime_error("PseudoFactory::CreateApplication:  Bad character");
    }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	createADE()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


ADEBase * PseudoFactory::CreateADE()
{
    char ADE_type = inp_->GetADEtype();
    
    switch(ADE_type)
    {
        case 'p':  return new ADE(*this);         break;
       
        default:   throw std::runtime_error("PseudoFactory::CreateADE:  Bad character");
    }
}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetBranches()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

BranchesBase * PseudoFactory::CreateBranches()
{
	char bch_type = inp_->GetBranchingType();

	switch (bch_type)
	{
		case '1':   return new BranchesUVM(*this);
  			 		break;
  		case '3':   return new Branches3(*this);
  			 		break;	 		
        case '4':   return new Branches4(*this);
		default:	throw std::runtime_error("PseudoFactory::CreateBranches:  bad character");
					break;
	}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetSlice()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

SliceBase * PseudoFactory::CreateSlice()
{
	char slc_type = inp_->GetSliceType();

	switch (slc_type)
	{
		case 'm':   return new SliceMultiplicative(*this);
  			 		break;
  		
        case 't':   return new SliceTwoFactor(*this);
  			 		break;	 		

		default:	throw std::runtime_error("PseudoFactory::CreateSlice:  bad character");
					break;
	}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

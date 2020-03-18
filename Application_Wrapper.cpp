//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Application_Wrapper.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Application_Wrapper.h"

#include "PseudoFactory.h"
#include "Input.h"
#include "Stopwatch.h"
#include "ValuationApplication.h"
#include <iostream>
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


  Application_Wrapper::Application_Wrapper()
:	app_(0)
{  
    fac_ = new PseudoFactory;      // owns this pointer
    inp_ = new Input;              // owns this pointer
    stw_ = new Stopwatch;                                  
   
 
  fac_->SetInput(inp_);
  
  app_ = fac_->CreateApplication();
}    
    
  Application_Wrapper::~Application_Wrapper()
 {
   delete fac_;
   delete inp_;
   delete stw_;
   delete app_;
 }

  void Application_Wrapper::run()
{
   
  stw_->StartStopwatch();
 
  app_->run();
  
  std::cout << "elapsed time " << stw_->GetRunTime() <<std::endl;	  	
                                       
}
 
 
                                                
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

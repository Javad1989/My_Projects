
#include <iostream>
#include "Application_Wrapper.h"
#include "Errorhandler.h"

int main(int argc, char **argv) {
   
   std::cout << "   ADE method project   "<<std::endl;     
  
   
    ErrorHandler the_handler;
    
    try
    {
        Application_Wrapper app;    
        app.run();
    }
    catch(const std::runtime_error & e)
    {
        the_handler.HandleRunTimeError(e);
    }
    catch(...)
    {
        the_handler.HandleUnknownError();
    }
   
      char quit = '\0';
    while (quit != 'q')
    {
        std::cout << "Enter q to quit: ";
        std::cin >> quit;
    }

    return 0;
}

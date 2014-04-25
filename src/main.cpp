//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell, S Jenkins, R F L Evans 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <iostream>

// Program headers
#include "yeti.hpp"

int main(){

   // Output Program Header
   //----------------------------------------------------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "                                             /\\\\" << std::endl;
   std::cout << "                                             /\\\\   /\\" << std::endl;
   std::cout << "                        /\\\\   /\\\\   /\\\\    /\\/\\ /\\" << std::endl;
   std::cout << "                         /\\\\ /\\\\  /\\   /\\\\   /\\\\  /\\\\" << std::endl;
   std::cout << "                           /\\\\\\  /\\\\\\\\\\ /\\\\  /\\\\  /\\\\" << std::endl;
   std::cout << "                            /\\\\  /\\          /\\\\  /\\\\" << std::endl;
   std::cout << "                           /\\\\     /\\\\\\\\      /\\\\ /\\\\" << std::endl;
   std::cout << "                         /\\\\" << std::endl;   
   std::cout << std::endl;
   std::cout << "                     York Electron Transmission Imager" << std::endl;
   std::cout << std::endl;
   std::cout << "                     Version 1.0.0 " << __DATE__ << " " << __TIME__ << std::endl;
   std::cout << std::endl;

   std::cout << "  Licensed under the BSD (2-Clause) License. See licence file for details." << std::endl;
   std::cout << std::endl;
   std::cout << "  Lead Developers: Holly Hathrell, Sarah Jenkins, Richard F L Evans" << std::endl;
   std::cout << std::endl;
   std::cout << "--------------------------------------------------------------------------------" << std::endl;

   // Initialise system
   yeti::initialise();

   // Simulate system
   yeti::simulate();

   return 0;

}
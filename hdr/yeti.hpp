//-----------------------------------------------------------------------------
//
// This header file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell, S. Jenkins, R F L Evans 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <vector>

// Program headers

#ifndef YETI_H_
#define YETI_H_
//-----------------------------------------------------------------------------
// Functions and variables shared throughout program
//-----------------------------------------------------------------------------
namespace yeti{

   // main functions
   void initialise();
   void create();
   void simulate();
   
   // rng for scatter algorithm
   extern double grnd();
   
}

#endif /*YETI_H_*/

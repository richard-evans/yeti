//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) R F L Evans 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <functional>
#include <random>

// Program headers

namespace yeti{

   // Integrator random numbers
   std::mt19937 eng(12345); // This is the Mersenne Twister

   // Uniform distribution, min = 0, max=1.0
   std::uniform_real_distribution<> dist(0.0,1.0);

   // Create bound auto object for rng, get new numbers using grnd()
   auto grnd = std::bind (dist,eng);

}

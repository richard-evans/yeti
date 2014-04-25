//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) S Jenkins, R F L Evans 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <cmath>
#include <iostream>
#include <vector>

// Program headers
#include "material.hpp"

namespace yeti{

//------------------------------------------------------------------------------
// Slowly increases x,y,z by the unit vectors until the step length is reached.
//------------------------------------------------------------------------------
void propagate(material_t& material, std::vector<double>& unitvectors, double& x, double& y, double& z,double& potential, double& E){

   material = get_material_properties(x,y,z);

   const double Z=material.Z;
   const double A=material.A;
   const double p=material.p;

   const double NA = 6.0221413e23;
   const double defect = 3.4*1e-3 * pow(Z,0.67)/E;
   const double cs = (Z*Z/(E*E)) * 5.21e-21 * ((4.0*M_PI )/(defect*(defect+1.0))) * pow(((E + 511.0)/(E+1024.0)),2.0);
   double meansteplength = A/(NA * p * cs)*(1e7);

   if(A < 1.0e-10 && Z < 1.0e-10 && p < 1.0e-10) meansteplength = 1.0e10;

   x += unitvectors[0];
   y += unitvectors[1];
   z += unitvectors[2];

   //dP is the change is potential, each step has a random amount of potential
   // For heavier elements dP is larger so the step length is shorter as it takes less Dp's to take it to the step length 
   double distance = -meansteplength*(log(potential));

   // Now update the potential
   potential = exp(-(distance+1.0)/meansteplength);

   return;

}

} // End of yeti namespace

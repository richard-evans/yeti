//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) S Jenkins, R F L Evans 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <iostream>

// Program headers
#include "material.hpp"
#include "object.hpp"
#include "yeti.hpp"

namespace yeti{

//-----------------------------------------------------------------------------
// Function to calculate scattering event
//-----------------------------------------------------------------------------
void scatter(material_t& material, int& num_scattering_events, std::vector<double>& unitvectors, double&steplength, double& probability, double& potential, double& E){

   //a new scattering event means a new step so this resets the step length
   num_scattering_events ++;

   //a new scatter means a new step so this resets the step length
   potential = 1.0;

   // Generate random numbers for scattering event
   double rnd = ((yeti::grnd()));
   double rnd2 = ((yeti::grnd())*2)-1;
   double rnd3 = yeti::grnd();
   steplength = yeti::grnd();

   // Calculate quantum defect
   const double defect = 3.4*1e-3 * pow(material.Z,0.67)/E;

   // Calculate scattering angles in 0,0,1 reference frame
   double phi = rnd2*M_PI;                              //Calculates phi and a completely random angle between 0 and 2PI
   double theta = acos(1 - ((2*defect* rnd)/(1+defect-rnd))); // Calculates theta, using a probability distribution

   //sets the thetas to be negative and positive
   if(rnd3>0.5) theta = -theta;

   // generate new random step length
   steplength = yeti::grnd();

   // Determine cumulative probability of scatering events
   probability *= (1 - rnd); //calculates the probability of this angles being chosen

   // Create matrix to rotate unit vectors to 0,0,1 reference frame
   yeti::scattering_rotation_matrix = yeti::create_rotation_matrix(pacos(unitvectors[2]),atan2(unitvectors[1],unitvectors[0]));

   // Transpose it to do the reverse operation
   yeti::scattering_transpose = yeti::create_transpose_matrix(yeti::scattering_rotation_matrix);

   // rotate scattering direction to electron frame 
   unitvectors = yeti::new_unit_vectors(theta, phi, yeti::scattering_transpose);      // Uses the Transpose matrix to calculate the new unit vectors with the added angles

   // calculate energy loss from scattering event
   double J = ((9.76*material.Z) + (58.5/pow(material.Z,0.19)))*10e-3;

   //Takes energy dE off the energy value, electron with lower energies scatter less.
   double dE = -78500.0*(material.p*material.Z/(material.A*E*1e7))*log((1.166*E/J) +1.0);

   E = E + dE;

   return;

}

} // End of yeti namespace

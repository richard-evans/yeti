//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) S Jenkins 2014. All rights reserved.
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
// Definition of shared variables
//-----------------------------------------------------------------------------
unsigned int electrons_per_pixel = 10;
unsigned int x_pixels = 1000;
unsigned int y_pixels = 1000;
double scan_size_x = 40.0; // nm
double scan_size_y = 40.0; // nm
double initial_electron_energy=100.0; // units?
double sample_angle_y = 0.0; //M_PI/2;
double sample_angle_z = 0.0; //M_PI/2;
double tip_height = -250.0; // nm
double simulation_sphere_radius = 300.0; // nm

//double p,A,Z, meansteplength,cs,defect;

//-----------------------------------------------------------------------------
// Function to generate electrons and propagate through the sample
//-----------------------------------------------------------------------------
void simulate(){

   // Define simulation radius sq
   const double simulation_sphere_radius_sq = yeti::simulation_sphere_radius*yeti::simulation_sphere_radius;

   // Define object of material_t to contain current material properties
   material_t material;

   // Initialise matrices
   initialise_matrices(sample_angle_y,sample_angle_z);

   // initialise detector
   initialise_detector(x_pixels,y_pixels);

   // Loop over all pixel coordinates
   for (unsigned int px=0; px<x_pixels; ++px){
      for (unsigned int py=0; py<y_pixels; ++py){

         // For each pixel generate electrons
         for (unsigned int n=0; n<electrons_per_pixel; n++){

            //------------------------------
            // Set electron properties
            //------------------------------
            // Determine initial electron positions from -scan_size_x -> +scan_size_x 
            double x = (double(px)/double(x_pixels) - 0.5)*scan_size_x;
            double y = (double(py)/double(y_pixels) - 0.5)*scan_size_y;
            double z = yeti::tip_height;

            std::vector<double> unitvectors(3); // Electron trajectory
            unitvectors[0]=0.0;
            unitvectors[1]=0.0;
            unitvectors[2]=1.0;
            // Each new electron starts with the full Energy - has not yet lost any due to scattering
            double electron_energy = yeti::initial_electron_energy;
            // The potential is initially set to 0 for a new electron to force a scattering event
            double potential = 1.0;
            // Resets the Culmative probability to 1, so when for the first scatter is has a probability equal to only that scatter. 
            double probability = 1.0;
            // define initial random steplength
            double steplength = yeti::grnd();
            // reset number of scattering events
            int num_scattering_events = 0;

            // Rotate the starting electron around y and z angles
            yeti::rotation(unitvectors, x, y, z);

            // While inside the sample sphere propagate the electron normally
            while(x*x + y*y + z*z < simulation_sphere_radius_sq ){

               //if the step length has reached the maxium step length a scattering event occours.
               if(potential<steplength){  // step length between 0 and 1 
                  scatter(material, num_scattering_events, unitvectors, steplength, probability, potential, electron_energy);
               }
               //else the event carries on in the same direction in unit steps
               else{
                  propagate(material, unitvectors,x, y, z, potential, electron_energy);
               }
            }

            // Electron has left sample sphere, propagate to detector
            detector(x,y,z,unitvectors, probability, px, py);

         } // End of electron loop
      } // End of y-loop
   } // End of x-loop

   // Analyse output data and output to file
   analyse_detector_data();

   return;

}

} // End of yeti namespace

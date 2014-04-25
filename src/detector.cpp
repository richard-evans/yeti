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
#include <fstream>
#include <iostream> 
#include <vector>

// Program headers
#include "yeti.hpp"

namespace yeti{
/*
            |
            |
            |
            _
           |_|
             \
              \
               \
     --------------
     |    |  |    |
     |   min
    max

*/

//-----------------------------------------------------------------------------
// Detector variables   
//-----------------------------------------------------------------------------
double detector_distance = 3.0e7; // nm
double minimum_detector_radius = 1.0e6; // nm 1e3 =um, e6 = mm, e9 = m
double maximum_detector_radius = 1.0e7; // nm
   
// array to store detector information
std::vector<std::vector<double> > detector_intensity(0);

//-----------------------------------------------------------------------------
// Initialisation detector array   
//-----------------------------------------------------------------------------
void initialise_detector(int sample_size_x, int sample_size_y){
   
   yeti::detector_intensity.resize(sample_size_x);
   for(unsigned int i=0; i<yeti::detector_intensity.size(); i++) yeti::detector_intensity[i].resize(sample_size_y);  

   return;
   
}

//-----------------------------------------------------------------------------
// Calculate electon path to detector and save counts 
//-----------------------------------------------------------------------------
void detector(double x, double y, double z, std::vector<double> unitvectors, double probability, int pixel_x, int pixel_y){

   //defines a vector to store the unit vectors to use in the multiplication so they dont overwrite themselves.
   std::vector<double> initialunitvector(3,0.0);

   std::vector<double> xyz(3,0.0);

   //Defines a vector to store the new x y z coordinates in the rotated frame 
   std::vector<double> xyzdash(3,0.0);

   //stores the unit vectors in the xyz matrix.
   initialunitvector = unitvectors;

   //multiplies the rotation matrix by the old unit vectors to create the new rotated unit vectors
   unitvectors = matrix_multiplication(initialunitvector, initial_transpose);

   //stores the x, y,z values in xyz so they can be matrix multiplied.
   xyz[0] = x;
   xyz[1] = y;
   xyz[2] = z;

   //multiplies the position vector by the rotation matrix to create the rotated unit vectors,
   xyzdash = matrix_multiplication(xyz, initial_transpose);

   //re-defines x,y,z as the rotated postion
   x = xyzdash[0];
   y = xyzdash[1];
   z = xyzdash[2];

   //the screen is xx cm away
   xyz[2] = detector_distance;

   //calculate the distance from the electron to the screen
   double r = ((xyzdash[2]) - xyz[2])/unitvectors[2];

   //calculate the final position on the screen
   xyz[0] = xyzdash[0] + unitvectors[0]*r;
   xyz[1] = xyzdash[1] + unitvectors[1]*r;

   double radius = sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);

   //std::cout << xyz[0] << "\t" << xyz[1] << "\t" << xyz[2] << "\t" << radius << std::endl;
   
   // If within allowed range then add count to detector
   if(radius >= minimum_detector_radius && radius <= maximum_detector_radius){
      detector_intensity[pixel_x][pixel_y]++;
   }
   //std::cout<<xyz[0]*xyz[0] + xyz[1]*xyz[1]<<"\t"<<Minimum_Detector_Radius<<"\t"<<Maxium_Detector_Radius<<endl;
   //myfile11 << xyz[0] <<"\t" << xyz[1] << "\t" <<Probability <<"\t" << xyz[0]*xyz[0] + xyz[1]*xyz[1]<<endl; 
   //if (((xyz[0]*xyz[0] + xyz[1]*xyz[1]) > Minimum_Detector_Radius))// & ((xyz[0]*xyz[0] + xyz[1]*xyz[1]) <Maxium_Detector_Radius))

   return;

}

//-----------------------------------------------------------------------------
// Initialisation rotational matrices   
//-----------------------------------------------------------------------------
void analyse_detector_data(){

   std::ofstream ofile("detector_data");
   
   for(unsigned int i=0; i<yeti::detector_intensity.size(); i++){
      for(unsigned int j=0; j<yeti::detector_intensity[i].size(); j++){   
         ofile << i << "\t" << j << "\t" << yeti::detector_intensity[i][j] << std::endl;
      }
      ofile << std::endl;
   }
   
   ofile.close();
   
   return;
   
}

}
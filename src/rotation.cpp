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
#include "material.hpp"
#include "object.hpp"
#include "yeti.hpp"

namespace yeti{

//-----------------------------------------------------------------------------
// Definitions of program rotational matrices   
//-----------------------------------------------------------------------------
std::vector< std::vector<double> > detectiongrid;         //sets up an array to count how many electrons hit the detector from each pixel.
std::vector< std::vector<double> > initial_transpose; //defines the Transpose Matrix
std::vector< std::vector<double> > initial_rotation_matrix; //defines the Transpose Matrix
std::vector< std::vector<double> > scattering_transpose; //defines the Transpose Matrix
std::vector< std::vector<double> > scattering_rotation_matrix; //defines the Transpose Matrix

//-----------------------------------------------------------------------------
// Initialisation rotational matrices   
//-----------------------------------------------------------------------------
void initialise_matrices(double yangle, double zangle){

   //resizes the Transpose and Rotation matrix matrix's to be 3x3
   yeti::initial_transpose.resize(3);
   for(unsigned int i=0; i<yeti::initial_transpose.size(); i++) yeti::initial_transpose[i].resize(3);

   yeti::initial_rotation_matrix.resize(3);
   for(unsigned int i=0; i<yeti::initial_rotation_matrix.size(); i++) yeti::initial_rotation_matrix[i].resize(3);

   yeti::scattering_transpose.resize(3);                                   //resizes the Transpose and Rotation matrix matrix's to be 3x3
   for(unsigned int i=0; i<yeti::scattering_transpose.size(); i++) yeti::scattering_transpose[i].resize(3);

   yeti::scattering_rotation_matrix.resize(3);
   for(unsigned int i=0; i<yeti::scattering_rotation_matrix.size(); i++) yeti::scattering_rotation_matrix[i].resize(3);

   yeti::initial_rotation_matrix = create_rotation_matrix(yangle,zangle);  
   yeti::initial_transpose = create_transpose_matrix(yeti::initial_rotation_matrix);

   return;

}

//------------------------------------------------------------------------------------------------------------
// rotates the incoming electron so they come in from a different x,y,z position with different unit vectors. 
//------------------------------------------------------------------------------------------------------------
void rotation(std::vector<double>& unitvectors, double& x, double& y, double& z){

   std::vector<double> xyz(3,0.0);       //defines a vector to store the unit vectors to use in the multiplication so they dont  overwrite themselves.
   std::vector<double> xyzdash(3,0.0);   //Defines a vector to store the new x y z coordinates. 

   xyz = unitvectors;                    //stores the unit vectors in the xyz matrix.

   //multiply the rotation matrix by the old unit vectors to create the new rotated unit vectors
   unitvectors = matrix_multiplication(xyz, yeti::initial_rotation_matrix);   

   xyz[0] = x;                           //stores the x, y,z values in xyz so they can be matrix multiplied.
   xyz[1] = y;
   xyz[2] = z;

   // multiply the position vector by the rotation matrix to create the rotated unit vectors,
   xyzdash = matrix_multiplication(xyz, yeti::initial_rotation_matrix);

   x = xyzdash[0];                       //re-defines x,y,z as the rotated postion
   y = xyzdash[1];
   z = xyzdash[2];

   return;

}

//-----------------------------------------------------------------------------
// Protected acos function to correct for rounding errors   
//-----------------------------------------------------------------------------
double pacos(double z){
  if ((z>=-1.0) & (z<= 1.0)) return acos(z);
  else if (z> 1.0) return 0.0;
  else return M_PI;
}

//-----------------------------------------------------------------------------
// Function to set rotation matrix for rotation around y and z axes (radians)
//-----------------------------------------------------------------------------
std::vector< std::vector<double> > create_rotation_matrix(double dy, double dz){

   // rotated unit vector
   std::vector<double> rotated(3,0.0);

   double sin_y = sin(dy); // by setting all the angles now they dont have to be re-caculated everytime they are used
   double cos_y = cos(dy); // we need the negative of the angle as we are rotating back towards the axis'.
   double sin_z = sin(dz);
   double cos_z = cos(dz);

   //sets up a matrix to store the y rotation matrix
   std::vector< std::vector<double> > y_rotation_matrix;
   y_rotation_matrix.resize(3);
   for(unsigned int i=0; i<y_rotation_matrix.size(); i++) y_rotation_matrix[i].resize(3);

   //sets up a matrix to store the z rotation matrix
   std::vector< std::vector<double> > z_rotation_matrix;
   z_rotation_matrix.resize(3);
   for(unsigned int i=0; i<z_rotation_matrix.size(); i++) z_rotation_matrix[i].resize(3);

   //sets up a matrix to store the rotation matrix
   std::vector< std::vector<double> > rotation_matrix;
   rotation_matrix.resize(3);
   for(unsigned int i=0; i<rotation_matrix.size(); i++) rotation_matrix[i].resize(3);  

   // rotates from r to (0,0,1) 
   rotation_matrix[0][0] = 0.0;           //The rotation matrix needs to be reset to 0, everytime
   rotation_matrix[0][1] = 0.0;
   rotation_matrix[0][2] = 0.0;
   rotation_matrix[1][0] = 0.0;
   rotation_matrix[1][1] = 0.0;
   rotation_matrix[1][2] = 0.0;
   rotation_matrix[2][0] = 0.0;
   rotation_matrix[2][1] = 0.0;
   rotation_matrix[2][2] = 0.0;

   y_rotation_matrix[0][0] = cos_y;       //Calculates the y rotation matrix
   y_rotation_matrix[1][0] = 0.0;
   y_rotation_matrix[2][0] = sin_y;
   y_rotation_matrix[0][1] = 0.0;
   y_rotation_matrix[1][1] = 1.0;
   y_rotation_matrix[2][1] = 0.0;
   y_rotation_matrix[0][2] = -sin_y;
   y_rotation_matrix[1][2] = 0.0;
   y_rotation_matrix[2][2] = cos_y;

   z_rotation_matrix[0][0] = cos_z;       //calculates the z rotation matrix
   z_rotation_matrix[1][0] = -sin_z;
   z_rotation_matrix[2][0] = 0.0;
   z_rotation_matrix[0][1] = sin_z;
   z_rotation_matrix[1][1] = cos_z;
   z_rotation_matrix[2][1] = 0.0;
   z_rotation_matrix[0][2] = 0.0;
   z_rotation_matrix[1][2] = 0.0;
   z_rotation_matrix[2][2] = 1.0;

   // the rotation matrix is z rotation * y rotation
   for(unsigned int i=0;i<3;i++){
      for(unsigned int j=0;j<3;j++){
         for(unsigned int k=0; k<3 ;k++){
            rotation_matrix[i][j]+=z_rotation_matrix[k][i]*y_rotation_matrix[j][k];
         }
      }
   }

   return rotation_matrix;     
}

//-----------------------------------------------------------------------------
// Function to create transpose of input matrix
//-----------------------------------------------------------------------------
std::vector< std::vector<double> > create_transpose_matrix(std::vector< std::vector<double> > matrix){    

   //sets up a matrix to store the Transpose matrix
   std::vector< std::vector<double> > transpose;
   transpose.resize(3);
   for(unsigned int i=0; i<transpose.size(); i++) transpose[i].resize(3);

   // Calculate the Transpose matrix
   for(unsigned int i=0;i<3;i++){
      for(unsigned int j=0;j<3;j++){
         transpose[i][j]=matrix[j][i];
      }
   }
   return transpose;
}

//---------------------------------------------------------------------------------------
// Function to rotate unit vector along theta, phi to coordinate space defines by matrix
//---------------------------------------------------------------------------------------
std::vector<double> new_unit_vectors(double theta, double phi, std::vector< std::vector<double> >& matrix){

   std::vector<double> initialunitvectors(3,0.0); //sets up vectors to store initial unit vectors and finalunit vectors
   std::vector<double> unitvectors(3,0.0);

   //calculates the initial unit vectors
   initialunitvectors[0] = sin(theta)*cos(phi);
   initialunitvectors[1] = sin(theta)*sin(phi);
   initialunitvectors[2] = cos(theta);

   // Multiplies the initial unit vector by the rotation matrix
   for(int j=0;j<3;j++){
      for(int k=0; k<3 ;k++){
         unitvectors[j]+=initialunitvectors[k]*matrix[k][j];
      }
   }
   return unitvectors;
}

//---------------------------------------------------------------------------------------
// Function to multiply vector with 3x3  matrix
//---------------------------------------------------------------------------------------
std::vector<double> matrix_multiplication(std::vector<double>& vect, std::vector< std::vector<double> >& matrix){

   std::vector<double> result_vect(3,0.0);

   for (int i = 0; i<3; i++){                                                         
      double total2 = 0;
      for (int j = 0; j<3; j++){
         total2 = total2 + vect[j]*matrix[i][j];
         result_vect[i] = total2;
      }
   }
      
   return result_vect;

}

} // end of yeti namespace

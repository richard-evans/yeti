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
#include "material.hpp"

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
   void scatter(material_t& material, int& num_scattering_events, std::vector<double>& unitvectors, double&steplength, double& probability, double& potential, double& E);
   void propagate(material_t& material, std::vector<double>& unitvectors, double& x, double& y, double& z, double& potential, double& E);

   // rng for scatter algorithm
   extern double grnd();

   // matrix functions
   extern void initialise_matrices(double yangle, double zangle);
   extern double pacos(double z);
   extern void rotation(std::vector<double>& unitvectors, double& x, double& y, double& z);
   extern std::vector< std::vector<double> > create_rotation_matrix(double dy, double dz);
   extern std::vector< std::vector<double> > create_transpose_matrix(std::vector< std::vector<double> > matrix);
   extern std::vector<double> new_unit_vectors(double theta, double phi, std::vector< std::vector<double> >& matrix);
   extern std::vector<double> matrix_multiplication(std::vector<double>& vect, std::vector< std::vector<double> >& matrix);
   
   // matrix variables
   extern std::vector< std::vector<double> > initial_transpose; //defines the Transpose Matrix
   extern std::vector< std::vector<double> > initial_rotation_matrix; //defines the Transpose Matrix
   extern std::vector< std::vector<double> > scattering_transpose; //defines the Transpose Matrix
   extern std::vector< std::vector<double> > scattering_rotation_matrix; //defines the Transpose Matrix

   // detector functions
   extern void detector(double x, double y, double z, std::vector<double> unitvectors, double probability, int pixel_x, int pixel_y);
   extern void initialise_detector(int sample_size_x, int sample_size_y);
   extern void analyse_detector_data();

}

#endif /*YETI_H_*/

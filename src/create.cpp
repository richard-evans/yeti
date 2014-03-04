//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <iostream>

// Program headers
#include "object.hpp"
#include "yeti.hpp"

namespace yeti{
   
//-----------------------------------------------------------------------------
// Function to generate objects
//-----------------------------------------------------------------------------
void create(){
      
    // create some objects
    double ix;
    double iy;
    double iz;
    double ip;
    double iZ;
    double iA;
    double isizex;
    double isizey;
    double isizez;
    double iecc;
    int iorder;

    // process shapes.dat file to generate objects
    
    /*
    // Note this will not work here
    double thetax=object_parameters::object_list[i]->thetax;
    double thetay=object_parameters::object_list[i]->thetay;
    double thetaz=object_parameters::object_list[i]->thetaz;

    
    double rotation[3][3]={double xx,double xy,double xz,double yx,double yy,double yz,double zx,double zy,double zz};
    // Define anticlockwise rotation matrices
    double rotX[3][3]={{1.0,0.0,0.0},{0.0,cos(thetax),-sin(thetax)},{0.0,sin(thetax),cos(thetax)};
        double rotY[3][3]={{cos(thetay),0.0,sin(thetay)},{0.0,1.0,0.0},{-sin(thetay),0.0,cos(thetay)}};
        double rotZ[3][3]={{cos(thetaz),-sin(thetaz),0.0},{sin(thetaz),cos(thetaz),0.0},{0.0,0.0,1.0}};
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                rotation[i][l]= rotX[i][j] * rotY[j][k] * rotZ[k][l];; //???
                }}}}
     */
    
    
    
    sphere_t temp_sphere;
    temp_sphere.set(20.0, 20.0, 20.0, 19.2, 196.0, 79.0, 20.0, 20.0, 20.0, 2, 1, M_PI/2, M_PI/2, M_PI/2);
    //set(double ix,double iy,double iz,double ip,double iZ,double iA,double isizex, double isizey, double isizez, double ecc, int order, double thetax, double thetay, double thetaz)
    //change // Richard needs external access to this - new shared namespace "yeti" header file the same in all code bits allows you to share, declared everywhere, but only defined once.
    yeti::objects::sphere_list.push_back(temp_sphere); //increases size of array by one, copies into end
    yeti::objects::object_list.push_back(&objects::sphere_list[0]); //saving address in object list -- hmm - reference instead of pointer, interesting...
    
    cuboid_t temp_cuboid;
    temp_cuboid.set(50.0, 50.0, 50.0, 19.2, 196.0, 79.0, 70.0, 20.0, 10.0, 2, 2, M_PI/2, M_PI/2, M_PI/2);
    objects::cuboid_list.push_back(temp_cuboid);
    objects::object_list.push_back(&objects::cuboid_list[0]);
    
    cigar_t temp_cigar;
    temp_cigar.set(50.0, 50.0, 50.0, 19.2, 196.0, 79.0, 10.0, 20.0, 10.0, 3, 3, M_PI/2, M_PI/2, M_PI/2);
    objects::cigar_list.push_back(temp_cigar);
    objects::object_list.push_back(&objects::cigar_list[0]);
    
    return;
      
}

   
}
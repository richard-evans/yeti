//-----------------------------------------------------------------------------
//
// This header file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <vector>
#include <cmath>

// Program headers

#ifndef OBJECT_H_
#define OBJECT_H_

namespace yeti{

// Define a base class containing Common parameters(x,y,z,p,Z,A,sizex, sizez, sizey, ecc, order)
class object_t{
public:
    double x;
    double y;
    double z;
    double p;       // Density
    double Z;       // Proton number
    double A;       // Atomic mass number
    double sizex;   // size=diameter for sphere, edge width for rectangle
    double sizey;
    double sizez;
    double ecc;     // Define eccentricity of cigar ends
    int order;
    double thetax;
    double thetay;
    double thetaz;
    void set(double ix,double iy,double iz,double ip,double iZ,double iA,double isizex, double isizey, double isizez, double iecc, int iorder, double ithetax, double ithetay, double ithetaz){
        x=ix;
        y=iy;
        z=iz;
        p=ip;
        Z=iZ;
        A=iA;
        sizex=isizex;   // Assumes axis set up inline with parameters - rotation needed
        sizey=isizey;
        sizez=isizez;
        ecc=iecc;
        order=iorder;   // Heirachy of shapes
        thetax=ithetax;
        thetay=ithetay;
        thetaz=ithetaz;
    }
    virtual bool inshape(double bx,double by,double bz){
        return false;   // Allows access and redefintion outside class - sphere
    }
};

//------Define the objects------
class sphere_t: public object_t{    //defines a new class for shape sphere
public:
    bool inshape(double bx,double by,double bz){
        double bxc = bx-x;      // Shift everything to centre of coordinate system
        double byc = by-y;      // x,y,z are predefined object coordinates (centre of mass)
        double bzc = bz-z;
        if (bxc*bxc + byc*byc + bzc*bzc <= (sizex/2.0)*(sizex/2.0)) return true; // Just set as sizex for now
        else return false;      // If inside the sphere =true, outside =false
    }
};

class cuboid_t: public object_t{ //defines a class for shape cuboid derived from object_t
public:
    bool inshape(double bx,double by,double bz){
        double bxc = bx-x;     // Shift everything to centre of coordinate system
        double byc = by-y;
        double bzc = bz-z;
        if ((fabs(bxc) - sizex/2 <= 0) && (fabs(byc) - sizey/2 <= 0) && (fabs(bzc) - sizez/2 <= 0)) return true;
        else return false;
    }
};

class cigar_t: public object_t{
public:
    bool inshape(double bx,double by,double bz){    // Defines a cigar with major axis along y: Assumes size x=size z!!!
        double bxc = bx-x;     // Shift everything to centre of coordinate system
        double byc = by-y;
        double bzc = bz-z;
        if ( (bxc*bxc + ((fabs(byc)-sizey/2)/ecc)*((fabs(byc)-sizey/2)/ecc) + bzc*bzc <= (sizex/2.0)*(sizex/2.0)) || ((fabs(byc)- fabs(byc/ecc)/2 - sizey/2 <=0) && (bxc*bxc + bzc*bzc <= (sizex/2)*(sizex/2))) )return true;
        else return false;
    }
};

// Declaration of object arrays
namespace objects {
    extern std::vector<object_t*> object_list;  // Number of different objects in the list
    extern std::vector<sphere_t> sphere_list;   // Each vector contains one kind of shape
    extern std::vector<cuboid_t> cuboid_list;
    extern std::vector<cigar_t> cigar_list;
}

}
#endif /*OBJECT_H_*/
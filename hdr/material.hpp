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

// Program headers

#ifndef MATERIAL_H_
#define MATERIAL_H_
//-----------------------------------------------------------------------------
// Functions and variables local to system creation
//-----------------------------------------------------------------------------
namespace yeti{

class material_t{   // Input class returned to main code
public:
    double p;
    double A;
    double Z;
    
    // Constructor
    material_t();
};

// Constructor to set initial values
material_t::material_t() {  // Take material_t from class
    p=0.0;
    A=0.0;
    Z=0.0;
}

// Function declaration to determine material properties
material_t get_material_properties(double x,double y,double z);

}

#endif /*MATERIAL_H_*/

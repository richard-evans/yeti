//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell 2014. All rights reserved.
//
//-----------------------------------------------------------------------------

// System headers
#include <iostream>

// Program headers
#include "object.hpp"
#include "yeti.hpp"

namespace yeti{
   
//-----------------------------------------------------------------------------
// Definition of arrays of objects
//-----------------------------------------------------------------------------
namespace objects {
    std::vector<object_t*> object_list(0);  // Number of different objects in the list
    std::vector<sphere_t> sphere_list(0);   // Each vector contains one kind of shape
    std::vector<cuboid_t> cuboid_list(0);
    std::vector<cigar_t> cigar_list(0);
}

}

//-----------------------------------------------------------------------------
//
// This source file is part of the YETI open source package under the
// BSD (2-clause) licence (see LICENCE file for details).
//
// (c) H Hathrell, R F L Evans 2014. All rights reserved.
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
// Function to determine material properties as a function of position
//-----------------------------------------------------------------------------
material_t get_material_properties(double x,double y,double z){ //determine pAZ from inshape

   // declare temporary object to store result
   material_t result;

   // define negative starting order
   int maxorder = -1;

   // loop over all objects in list
   for (unsigned int i=0; i<objects::object_list.size(); i++){

      // Test if point x,y,z is within object
      bool test_inside = objects::object_list[i]->inshape(x,y,z);

      // Test if object has greater hierarchy
      bool test_hierarchy = objects::object_list[i]->order>maxorder;

      // check for both conditions true
      if (test_inside && test_hierarchy ){

         // update result with copy of object
         result.p = objects::object_list[i]->p;

         // update max order
         maxorder=objects::object_list[i]->order;

      }

   }

   // return final parameters
   return result;

}

}

// Copyright (c) 2002,2011 Utrecht University (The Netherlands).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Spatial_searching/include/CGAL/Plane_separator.h $
// $Id: Plane_separator.h 0fe3ed8 2019-01-17T14:38:41+01:00 Andreas Fabri
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)

#ifndef CGAL_PLANE_SEPARATOR_H
#define CGAL_PLANE_SEPARATOR_H

#include <CGAL/license/Spatial_searching.h>


#include <iostream>

namespace CGAL {
template < class FT> class Plane_separator {

  public:

  int cutting_dim;
  FT cutting_val;

  inline int cutting_dimension() const { return cutting_dim;}
  inline FT cutting_value() const { return cutting_val;}

  void set_cutting_dimension(int d) {
	  cutting_dim=d;
  }

  void set_cutting_value(FT val) {
	  cutting_val=val;
  }  
//commented this is not used
//  template <class Point>  
//  inline bool has_on_negative_side(const Point& i) {
//    return i[cutting_dimension()] < cutting_value();
//  }

  Plane_separator(const int d, const FT& v) : 
		cutting_dim(d), cutting_val(v) {}

  explicit Plane_separator() : cutting_dim(0), cutting_val(0) {}

  // Added as workaround for VC2017 with /arch:AVX to fix
  // https://cgal.geometryfactory.com/CGAL/testsuite/CGAL-4.14-I-95/Spatial_searching/TestReport_afabri_x64_Cygwin-Windows10_MSVC2017-Release-64bits.gz
  Plane_separator& operator=(const Plane_separator& ps)
  {
    cutting_dim = ps.cutting_dim;
    cutting_val = ps.cutting_val;
    return *this;
  }

};


 template < class FT> 
 std::ostream& operator<< (std::ostream& s, Plane_separator<FT>& x) {
   s << "\n Separator coordinate: " << x.cutting_dimension() <<
     " value: " << x.cutting_value() << "\n";
   return s;
 }
} // namespace CGAL
#endif // CGAL_PLANE_SEPARATOR_H

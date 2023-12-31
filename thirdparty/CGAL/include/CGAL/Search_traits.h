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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Spatial_searching/include/CGAL/Search_traits.h $
// $Id: Search_traits.h ee57fc2 2017-10-21T01:03:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_KD_TREE_TRAITS_POINT_H
#define CGAL_KD_TREE_TRAITS_POINT_H

#include <CGAL/license/Spatial_searching.h>

#include <CGAL/Dimension.h>


namespace CGAL {
  template <class FT_, class Point, class CartesianCoordinateIterator, class ConstructCartesianCoordinateIterator, typename D = Dynamic_dimension_tag>
  class Search_traits {
    
  public:

    typedef D Dimension;

    typedef CartesianCoordinateIterator Cartesian_const_iterator_d;
    typedef ConstructCartesianCoordinateIterator Construct_cartesian_const_iterator_d;
    typedef Point Point_d;
    typedef FT_ FT;
    
    Construct_cartesian_const_iterator_d construct_cartesian_const_iterator_d_object() const {
       return Construct_cartesian_const_iterator_d();
    }
  
  };

  
} // namespace CGAL
#endif //  KD_TREE_TRAITS_POINT_H

// Copyright (c) 2006-2007  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Surface_mesher/include/CGAL/Multi_surface_3.h $
// $Id: Multi_surface_3.h 07b0ddf 2018-02-13T14:15:38+00:00 Andreas Fabri
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_MULTI_SURFACE_3_H
#define CGAL_MULTI_SURFACE_3_H

#include <CGAL/license/Surface_mesher.h>

#include <CGAL/disable_warnings.h>

namespace CGAL {

  template<
    typename Surface_a,
    typename Surface_b
    >
  class Multi_surface_3 
  {
    const Surface_a& surf_a;
    const Surface_b& surf_b;
  public:
    Multi_surface_3(const Surface_a& surface_a, const Surface_b& surface_b)
      : surf_a(surface_a), surf_b(surface_b)
    {
    }

    const Surface_a& surface_a() const
    {
      return surf_a;
    }
    
      
    const Surface_b& surface_b() const
    {
      return surf_b;
    }
  };
} // end namespace CGAL

#include <CGAL/Surface_mesher/Combining_oracle.h>
#include <CGAL/Surface_mesh_traits_generator_3.h>

namespace CGAL {
  template <typename Surface_a, typename Surface_b>
  struct Surface_mesh_traits_generator_3 <
    Multi_surface_3<Surface_a, Surface_b>
  >
  {
    typedef typename Surface_mesh_traits_generator_3<Surface_a>::type Oracle_a;
    typedef typename Surface_mesh_traits_generator_3<Surface_b>::type Oracle_b;

    typedef typename Surface_mesher::Combining_oracle<
      Oracle_a,
      Oracle_b
      > Type;
    
    typedef Type type; // Boost meta-programming compatibility
  };
} // end namespace CGAL, second occurrence.

#include <CGAL/enable_warnings.h>

#endif // CGAL_MULTI_SURFACE_3_H

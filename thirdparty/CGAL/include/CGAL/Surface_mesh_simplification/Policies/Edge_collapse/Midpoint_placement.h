// Copyright (c) 2006  GeometryFactory (France). All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Surface_mesh_simplification/include/CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Midpoint_placement.h $
// $Id: Midpoint_placement.h f2b1e70 2018-01-16T09:53:29+01:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Fernando Cacciola <fernando.cacciola@geometryfactory.com>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_MIDPOINT_PLACEMENT_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_MIDPOINT_PLACEMENT_H 1

#include <CGAL/license/Surface_mesh_simplification.h>


#include <CGAL/Surface_mesh_simplification/Detail/Common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_profile.h>

namespace CGAL {

namespace Surface_mesh_simplification
{

  template<class TM_>
class Midpoint_placement
{
public:

  typedef TM_ TM;
  
  Midpoint_placement()
  {}
  
  template <typename Profile>
  optional<typename Profile::Point> operator()( Profile const& aProfile ) const
  {
    return optional<typename Profile::Point> (midpoint(aProfile.p0(),aProfile.p1()));
  }

};

} // namespace Surface_mesh_simplification

} //namespace CGAL

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_MIDPOINT_PLACEMENT_H //
// EOF //
 

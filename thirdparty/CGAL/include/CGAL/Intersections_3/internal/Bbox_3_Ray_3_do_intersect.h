// Copyright (c) 2008 ETH Zurich (Switzerland)
// Copyright (c) 2008-2009 INRIA Sophia-Antipolis (France)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Intersections_3/include/CGAL/Intersections_3/internal/Bbox_3_Ray_3_do_intersect.h $
// $Id: Bbox_3_Ray_3_do_intersect.h 4111e3e 2018-02-20T16:48:11+00:00 Andreas Fabri
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Camille Wormser, Jane Tournois, Pierre Alliez, Stephane Tayeb

#ifndef CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_RAY_3_DO_INTERSECT_H
#define CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_RAY_3_DO_INTERSECT_H

#include <CGAL/Ray_3.h>
#include <CGAL/Bbox_3.h>

#include <CGAL/Intersections_3/internal/Bbox_3_Segment_3_do_intersect.h>
// for CGAL::internal::do_intersect_bbox_segment_aux

// inspired from http://cag.csail.mit.edu/~amy/papers/box-jgt.pdf

namespace CGAL {
  
namespace Intersections {

namespace internal {

  template <class K>
  bool do_intersect(const typename K::Ray_3& ray,
                    const CGAL::Bbox_3& bbox,
                    const K&)
  {
    typedef typename K::FT FT;
    typedef typename K::Point_3 Point_3;

    const Point_3& source = ray.source();
    const Point_3& point_on_ray = ray.second_point();

    return do_intersect_bbox_segment_aux
      <FT,
       true,  // bounded at t=0 
       false, // not bounded at t=1
       false> // do not use static filters
      (
       source.x(), source.y(), source.z(),
       point_on_ray.x(), point_on_ray.y(), point_on_ray.z(),
       bbox
       );
  }

  template <class K>
  bool do_intersect(const CGAL::Bbox_3& bbox,
                    const typename K::Ray_3& ray,
                    const K&) {
    return do_intersect(ray, bbox, K());
  }
  
} // namespace internal
} // namespace Intersections
} //namespace CGAL

#endif  // CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_RAY_3_DO_INTERSECT_H

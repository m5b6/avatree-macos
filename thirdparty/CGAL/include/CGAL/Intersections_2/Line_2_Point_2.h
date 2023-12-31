// Copyright (c) 2000  
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved. 
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Intersections_2/include/CGAL/Intersections_2/Line_2_Point_2.h $
// $Id: Line_2_Point_2.h 43f8490 2018-03-04T17:27:28+00:00 Andreas Fabri
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Geert-Jan Giezeman


#ifndef CGAL_INTERSECTIONS_2_POINT_2_LINE_2_H
#define CGAL_INTERSECTIONS_2_POINT_2_LINE_2_H

#include <CGAL/Line_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Intersection_traits_2.h>

namespace CGAL {
  
namespace Intersections {

namespace internal {

template <class K>
inline bool
do_intersect(const typename K::Point_2 &pt, 
	     const typename K::Line_2 &line,
	     const K&)
{
    return line.has_on(pt);
}

template <class K>
inline bool
do_intersect(const typename K::Line_2 &line,
	     const typename K::Point_2 &pt, 
	     const K&)
{
    return line.has_on(pt);
}

template <class K>
typename CGAL::Intersection_traits
<K, typename K::Point_2, typename K::Line_2>::result_type
intersection(const typename K::Point_2 &pt, 
	     const typename K::Line_2 &line,
	     const K& k)
{
    if (do_intersect(pt,line, k)) {
        return intersection_return<typename K::Intersect_2, typename K::Point_2, typename K::Line_2>(pt);
    }
    return intersection_return<typename K::Intersect_2, typename K::Point_2, typename K::Line_2>();
}

template <class K>
typename CGAL::Intersection_traits
<K, typename K::Line_2, typename K::Point_2>::result_type
intersection(const typename K::Line_2 &line,
	     const typename K::Point_2 &pt, 
	     const K& k)
{
  return internal::intersection(pt, line, k);
}

} // namespace internal
} // namespace Intersections


CGAL_INTERSECTION_FUNCTION(Point_2, Line_2, 2)
CGAL_DO_INTERSECT_FUNCTION(Point_2, Line_2, 2)

} //namespace CGAL

#endif

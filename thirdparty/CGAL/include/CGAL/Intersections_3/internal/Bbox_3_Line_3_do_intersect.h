// Copyright (c) 2008 ETH Zurich (Switzerland)
// Copyright (c) 2008-2011 INRIA Sophia-Antipolis (France)
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Intersections_3/include/CGAL/Intersections_3/internal/Bbox_3_Line_3_do_intersect.h $
// $Id: Bbox_3_Line_3_do_intersect.h 4111e3e 2018-02-20T16:48:11+00:00 Andreas Fabri
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Camille Wormser, Jane Tournois, Pierre Alliez, Stephane Tayeb


#ifndef CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_LINE_3_DO_INTERSECT_H
#define CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_LINE_3_DO_INTERSECT_H

#include <CGAL/Line_3.h>
#include <CGAL/Bbox_3.h>

// inspired from http://cag.csail.mit.edu/~amy/papers/box-jgt.pdf

namespace CGAL {
  
namespace Intersections {

namespace internal {

  template <typename FT>
  inline
  bool
  bbox_line_do_intersect_aux(const FT& px, const FT& py, const FT& pz,
                             const FT& vx, const FT& vy, const FT& vz,
                             const FT& bxmin, const FT& bymin, const FT& bzmin,
                             const FT& bxmax, const FT& bymax, const FT& bzmax)
  {
    // -----------------------------------
    // treat x coord
    // -----------------------------------
    FT dmin, tmin, tmax;
    if ( vx >= 0 )
    {
      tmin = bxmin - px;
      tmax = bxmax - px;
      dmin = vx;
    }
    else
    {
      tmin = px - bxmax;
      tmax = px - bxmin;
      dmin = -vx;
    }

    //if px is not in the x-slab
    if ( dmin == FT(0) && (tmin > FT(0) || tmax < FT(0)) ) return false;

    FT dmax = dmin;

    // -----------------------------------
    // treat y coord
    // -----------------------------------
    FT d_, tmin_, tmax_;
    if ( vy >= 0 )
    {
      tmin_ = bymin - py;
      tmax_ = bymax - py;
      d_ = vy;
    }
    else
    {
      tmin_ = py - bymax;
      tmax_ = py - bymin;
      d_ = -vy;
    }
    
    
    
    
    if ( d_ == FT(0) ){
      //if py is not in the y-slab
      if( (tmin_ > FT(0) || tmax_ < FT(0)) ) return false;
    }
    else
      if ( (dmin*tmax_) < (d_*tmin) || (dmax*tmin_) > (d_*tmax) )
        return false;

    if( (dmin*tmin_) > (d_*tmin) )
    {
      tmin = tmin_;
      dmin = d_;
    }

    if( (dmax*tmax_) < (d_*tmax) )
    {
      tmax = tmax_;
      dmax = d_;
    }

    // -----------------------------------
    // treat z coord
    // -----------------------------------
    if ( vz >= 0 )
    {
      tmin_ = bzmin - pz;
      tmax_ = bzmax - pz;
      d_ = vz;
    }
    else
    {
      tmin_ = pz - bzmax;
      tmax_ = pz - bzmin;
      d_ = -vz;
    }
    
    //if pz is not in the z-slab
    //if ( d_ == FT(0) && (tmin_ > FT(0) || tmax_ < FT(0)) ) return false;
    //The previous line is not needed as either dmin or d_ are not 0 
    //(otherwise the direction of the line would be null). 
    // The following is equivalent to the in z-slab test if d_=0.

    return ( (dmin*tmax_) >= (d_*tmin) && (dmax*tmin_) <= (d_*tmax) );
  }

  template <class K>
  bool do_intersect(const typename K::Line_3& line,
                    const CGAL::Bbox_3& bbox,
                    const K&)
  {
    typedef typename K::FT FT;
    typedef typename K::Point_3 Point_3;
    typedef typename K::Vector_3 Vector_3;

    const Point_3& point = line.point();
    const Vector_3& v = line.to_vector();

    return bbox_line_do_intersect_aux(
                         point.x(), point.y(), point.z(),
                         v.x(), v.y(), v.z(),
                         FT(bbox.xmin()), FT(bbox.ymin()), FT(bbox.zmin()),
                         FT(bbox.xmax()), FT(bbox.ymax()), FT(bbox.zmax()) );
  }

  template <class K>
  bool do_intersect(const CGAL::Bbox_3& bbox,
                    const typename K::Line_3& line,
                    const K&)
  { return do_intersect(line, bbox, K()); }


} // namespace internal
} // namespace Intersections
} //namespace CGAL

#endif  // CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_LINE_3_DO_INTERSECT_H

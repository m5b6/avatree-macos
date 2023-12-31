// Copyright (c) 2014  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Triangulation_3/include/CGAL/Delaunay_triangulation_cell_base_3.h $
// $Id: Delaunay_triangulation_cell_base_3.h a0427ec 2018-04-26T13:06:21+02:00 Mael Rouxel-Labbé
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//                 Sylvain Pion
//                 Jane Tournois <jane.tournois@geometryfactory.com>

// cell of a Delaunay triangulation of any dimension <=3

#ifndef CGAL_DELAUNAY_TRIANGULATION_CELL_BASE_3_H
#define CGAL_DELAUNAY_TRIANGULATION_CELL_BASE_3_H

#include <CGAL/license/Triangulation_3.h>

#include <CGAL/assertions.h>
#include <CGAL/basic.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_cell_base_3.h>

#include <boost/type_traits/is_same.hpp>

namespace CGAL {

template < typename GT,
           typename Cb = Triangulation_cell_base_3<GT> >
class Delaunay_triangulation_cell_base_3
  : public Cb
{
public:
  typedef typename Cb::Vertex_handle                   Vertex_handle;
  typedef typename Cb::Cell_handle                     Cell_handle;

  typedef GT                                           Geom_traits;
  typedef typename Geom_traits::Point_3                Point_3;
  typedef typename Geom_traits::Point_3                Point;

  template < typename TDS2 >
  struct Rebind_TDS {
    typedef typename Cb::template Rebind_TDS<TDS2>::Other                 Cb2;
    typedef Delaunay_triangulation_cell_base_3<GT, Cb2>                   Other;
  };

  Delaunay_triangulation_cell_base_3()
    : Cb() {}

  Delaunay_triangulation_cell_base_3(Vertex_handle v0, Vertex_handle v1,
                                     Vertex_handle v2, Vertex_handle v3)
    : Cb(v0, v1, v2, v3) {}

  Delaunay_triangulation_cell_base_3(Vertex_handle v0, Vertex_handle v1,
                                     Vertex_handle v2, Vertex_handle v3,
                                     Cell_handle   n0, Cell_handle   n1,
                                     Cell_handle   n2, Cell_handle   n3)
    : Cb(v0, v1, v2, v3, n0, n1, n2, n3) {}

  template <typename GT_>
  Point_3 circumcenter(const GT_& gt) const
  {
    return gt.construct_circumcenter_3_object()(this->vertex(0)->point(),
                                                this->vertex(1)->point(),
                                                this->vertex(2)->point(),
                                                this->vertex(3)->point());
  }

  Point_3 circumcenter() const
  {
    return circumcenter(Geom_traits());
  }
};

} //namespace CGAL

#endif // CGAL_DELAUNAY_TRIANGULATION_CELL_BASE_3_H

// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Triangulation_2/include/CGAL/Triangulation_face_base_2.h $
// $Id: Triangulation_face_base_2.h c5f134c 2018-04-26T13:58:23+02:00 Mael Rouxel-Labbé
// SPDX-License-Identifier: GPL-3.0+
//
//
// Author(s)     : Mariette Yvinec

#ifndef CGAL_TRIANGULATION_FACE_BASE_2_H
#define CGAL_TRIANGULATION_FACE_BASE_2_H

#include <CGAL/license/Triangulation_2.h>


#include <CGAL/config.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_ds_face_base_2.h>

namespace CGAL {

template < typename Gt, typename Fb = Triangulation_ds_face_base_2<> >
class Triangulation_face_base_2
  : public Fb
{
public:
  typedef Gt                                           Geom_traits;
  typedef typename Fb::Vertex_handle                   Vertex_handle;
  typedef typename Fb::Face_handle                     Face_handle;

  template < typename TDS2 >
  struct Rebind_TDS {
    typedef typename Fb::template Rebind_TDS<TDS2>::Other  Fb2;
    typedef Triangulation_face_base_2<Gt, Fb2>             Other;
  };

public:
  Triangulation_face_base_2()
       : Fb() {}

  Triangulation_face_base_2(Vertex_handle v0,
                            Vertex_handle v1,
                            Vertex_handle v2)
    : Fb(v0,v1,v2) {}

  Triangulation_face_base_2(Vertex_handle v0,
                            Vertex_handle v1,
                            Vertex_handle v2,
                            Face_handle n0,
                            Face_handle n1,
                            Face_handle n2)
    : Fb(v0,v1,v2,n0,n1,n2) {}

  static int ccw(int i) {return Triangulation_cw_ccw_2::ccw(i);}
  static int  cw(int i) {return Triangulation_cw_ccw_2::cw(i);}
};

} //namespace CGAL

#endif //CGAL_TRIANGULATION_FACE_BASE_2_H

// Copyright (c) 2003-2008  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Circular_kernel_2/include/CGAL/Circular_kernel_2/internal_functions_on_line_2.h $
// $Id: internal_functions_on_line_2.h ee57fc2 2017-10-21T01:03:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CIRCULAR_KERNEL_FUNCTIONS_ON_LINE_2_H
#define CGAL_CIRCULAR_KERNEL_FUNCTIONS_ON_LINE_2_H

#include <CGAL/license/Circular_kernel_2.h>


namespace CGAL {
namespace LinearFunctors {

  template < class CK >
  typename CK::Polynomial_1_2
  get_equation( const typename CK::Line_2 & L )
  {
    return typename CK::Polynomial_1_2(L.a(),L.b(),L.c());
  }
  
  template < class CK >
  typename CK::Line_2  
  construct_line_2 ( const typename CK::Polynomial_1_2 &eq )
  {
    return typename CK::Line_2(eq[2],eq[1],eq[0]); 
  }
  
  template < class CK >
  bool
  has_on(const typename CK::Line_2 & l,
	 const typename CK::Circular_arc_point_2 &p)
  {
    typedef typename CK::Algebraic_kernel            AK;
    typedef typename CK::Polynomial_1_2 Polynomial_1_2;
    Polynomial_1_2 equation = CGAL::LinearFunctors::get_equation<CK>(l);

    return(AK().sign_at_object()(equation,p.coordinates())== ZERO);
  }

  template < class CK >
  inline bool
  non_oriented_equal(const typename CK::Line_2 & a1,
	             const typename CK::Line_2 & a2) {
    if(identical(a1,a2)) return true;
    const typename CK::RT &a1c = a1.a(); 
    const typename CK::RT &b1c = a1.b();
    const typename CK::RT &c1c = a1.c();
    const typename CK::RT &a2c = a2.a(); 
    const typename CK::RT &b2c = a2.b();
    const typename CK::RT &c2c = a2.c();
    return (a1c*b2c == a2c*b1c) &&
           (a1c*c2c == a2c*c1c) &&
           (b1c*c2c == b2c*c1c);
  }

} // namespace LinearFunctors
} // namespace CGAL
#endif // CGAL_CIRCULAR_KERNEL_FUNCTIONS_ON_LINE_2_H

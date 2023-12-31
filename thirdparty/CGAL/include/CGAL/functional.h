// Copyright (c) 2017  
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/STL_Extension/include/CGAL/functional.h $
// $Id: functional.h 1cfb9e4 2018-06-13T15:36:35+02:00 Mael Rouxel-Labbé
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Andreas Fabri

#ifndef CGAL_FUNCTIONAL_H
#define CGAL_FUNCTIONAL_H

namespace CGAL {

namespace cpp98 {

  /// Replacement for `std::unary_function` that is deprecated since C++11,
  /// and removed from C++17.
  template < typename ArgumentType, typename ResultType>
  struct unary_function {
    typedef ArgumentType argument_type;
    typedef ResultType result_type;
  };

  /// Replacement for `std::binary_function` that is deprecated since C++11,
  /// and removed from C++17.
  template < typename Arg1, typename Arg2, typename Result>
  struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
  };

} // namespace cpp98

} // namespace CGAL

#endif // CGAL_FUNCTIONAL_H

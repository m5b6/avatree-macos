// Copyright (c) 2017 GeometryFactory Sarl (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/STL_Extension/include/CGAL/unordered.h $
// $Id: unordered.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Simon Giraudot

#ifndef CGAL_UNORDERED_H
#define CGAL_UNORDERED_H

#include <CGAL/config.h>
#ifndef CGAL_CFG_NO_CPP0X_UNORDERED
#  include <unordered_set>
#  include <unordered_map>
#else
#  include <boost/unordered_set.hpp>
#  include <boost/unordered_map.hpp>
#endif

namespace CGAL {

namespace cpp11 {

#ifndef CGAL_CFG_NO_CPP0X_UNORDERED
using std::unordered_set;
using std::unordered_map;
#else
using boost::unordered_set;
using boost::unordered_map;
#endif

} // cpp11

} //namespace CGAL

#endif // CGAL_UNORDERED_H

// Copyright (c) 2010   GeometryFactory (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/STL_Extension/include/CGAL/internal/info_check.h $
// $Id: info_check.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_INTERNAL_INFO_CHECK_H
#define CGAL_INTERNAL_INFO_CHECK_H


#include <boost/mpl/has_xxx.hpp>

namespace CGAL {

namespace internal{

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(Has_typedef_Info,Info,false)  
 
template <class T,bool has_info=Has_typedef_Info<T>::value>
 struct Info_check{
 struct type{};
};

template <class T>
struct Info_check<T,true>{
 typedef typename T::Info type;
};

} } //namespace CGAL::internal

#endif //CGAL_INTERNAL_INFO_CHECK_H

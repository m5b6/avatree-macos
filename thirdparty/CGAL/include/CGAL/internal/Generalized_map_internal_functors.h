// Copyright (c) 2016 CNRS and LIRIS' Establishments (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Generalized_map/include/CGAL/internal/Generalized_map_internal_functors.h $
// $Id: Generalized_map_internal_functors.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Guillaume Damiand <guillaume.damiand@liris.cnrs.fr>
//
#ifndef CGAL_GENERALIZED_MAP_INTERNAL_FUNCTORS_H
#define CGAL_GENERALIZED_MAP_INTERNAL_FUNCTORS_H

/* Definition of functors used internally for generalized maps.
 *
 * internal::Alpha_functor<Dart, i...> to call several beta on the given dart.
 *   Indices are given as parameter of the run function.
 *
 * internal::Alpha_functor_static<Dart, i...> to call several beta on the given
 *   dart. Indices are given as template arguments.
 *
 */

#include <CGAL/internal/Combinatorial_map_internal_functors.h>

namespace CGAL
{
// ****************************************************************************
namespace internal
{
// ****************************************************************************
// Alpha functor, used to combine several alpha.
#ifndef CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES
template<typename GMap, typename Dart_handle, typename ... Alphas>
struct Alpha_functor;

template<typename GMap, typename Dart_handle>
struct Alpha_functor<GMap, Dart_handle, int>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart, int B)
  { return AMap.get_alpha(ADart, B); }
};

template<typename GMap, typename Dart_handle>
struct Alpha_functor<GMap, Dart_handle, unsigned int>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart, unsigned int B)
  { return  AMap.get_alpha(ADart, B); }
};

template<typename GMap, typename Dart_handle, typename ... Alphas>
struct Alpha_functor<GMap, Dart_handle, int, Alphas...>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart, int B, Alphas... alphas)
  { return Alpha_functor<GMap, Dart_handle, Alphas...>::
      run(AMap, AMap.get_alpha(ADart, B), alphas...); }
};

template<typename GMap, typename Dart_handle, typename ... Alphas>
struct Alpha_functor<GMap, Dart_handle, unsigned int, Alphas...>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart, unsigned int B,
                         Alphas... alphas)
  { return Alpha_functor<GMap, Dart_handle, Alphas...>::
      run(AMap, AMap.get_alpha(ADart, B), alphas...); }
};
// ****************************************************************************
template<typename GMap, typename Dart_handle, int ... Alphas>
struct Alpha_functor_static;

template<typename GMap, typename Dart_handle, int B>
struct Alpha_functor_static<GMap, Dart_handle, B>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart)
  { return AMap.template get_alpha<B>(ADart); }
};

template<typename GMap, typename Dart_handle, int B, int ... Alphas>
struct Alpha_functor_static<GMap, Dart_handle, B, Alphas...>
{
  static Dart_handle run(GMap& AMap, Dart_handle ADart)
  { return Alpha_functor_static<GMap, Dart_handle, Alphas...>::
        run(AMap, AMap.template get_alpha<B>(ADart)); }
};
#endif //CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES
// ****************************************************************************
} // namespace internal
} // namespace CGAL

#endif // CGAL_GENERALIZED_MAP_INTERNAL_FUNCTORS_H

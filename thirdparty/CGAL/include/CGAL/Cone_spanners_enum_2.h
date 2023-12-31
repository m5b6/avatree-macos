// Copyright (c) 2013-2015  The University of Western Sydney, Australia.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Cone_spanners_2/include/CGAL/Cone_spanners_enum_2.h $
// $Id: Cone_spanners_enum_2.h 2f9408f 2018-09-04T12:01:27+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
//
// Authors: Frédérik Paradis

/*! \file Cone_spanners_enum_2.h
 *
 * This header defines enumerators for the cone spanners functors.
 */

#ifndef CONE_SPANNERS_ENUM_2_H
#define CONE_SPANNERS_ENUM_2_H

#include <CGAL/license/Cone_spanners_2.h>


namespace CGAL {
  /*! \ingroup PkgConeSpanners2Ref

   \brief An enum of the choice of cones in cone spanners.
   */
  enum Cones_selected {
    /*! \brief Select even cones.
     */
    EVEN_CONES = 0,
    /*! \brief Select odd cones.
     */
    ODD_CONES = 1,
    /*! \brief Select all cones.
     */
    ALL_CONES = 2 };

}  // namespace CGAL

#endif

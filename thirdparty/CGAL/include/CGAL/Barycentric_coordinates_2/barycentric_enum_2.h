// Copyright (c) 2014 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is a part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Barycentric_coordinates_2/include/CGAL/Barycentric_coordinates_2/barycentric_enum_2.h $
// $Id: barycentric_enum_2.h 3dd0aa1 2018-09-04T11:26:30+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s) : Dmitry Anisimov, David Bommes, Kai Hormann, and Pierre Alliez.

/*!
  \file barycentric_enum_2.h
*/

#ifndef CGAL_BARYCENTRIC_ENUM_2_H
#define CGAL_BARYCENTRIC_ENUM_2_H

#include <CGAL/license/Barycentric_coordinates_2.h>


// CGAL namespace.
namespace CGAL {

/*!
 * \ingroup PkgBarycentricCoordinates2Ref
 * The namespace Barycentric_coordinates contains implementations of all generalized barycentric coordinates: 2D, 3D, related enumerations, and so on.
 */

// Barycentric_coordinates namespace.
namespace Barycentric_coordinates {

/// \name Locations of a Query Point
/// @{

/// Query_point_location is enumeration with possible locations of a query point provided by the user.
enum Query_point_location
{
    /// Location is not known apriori and is defined automatically by the algorithm.
    UNSPECIFIED_LOCATION,

    /// Query point is located at one of the polygon's vertices.
    ON_VERTEX,

    /// Query point is located on the boundary of the polygon.
    ON_BOUNDARY,

    /// Query point is located inside the polygon, excluding the boundary.
    ON_BOUNDED_SIDE,

    /// Query point is located outside the polygon, excluding the boundary.
    ON_UNBOUNDED_SIDE
};

/// @}

/// \name Types of an Algorithm
/// @{

/// Type_of_algorithm is enumeration with possible algorithms to compute coordinates.
enum Type_of_algorithm
{
    /// A default slow algorithm, which is as precise as possible.
    PRECISE,

    /// A fast algorithm, which is less precise but much faster.
    FAST
};

/// @}

// Types of a Polygon

// Type_of_polygon is enumeration with possible types of the input polygon.
// It is used internally to precondition coordinates.
enum Type_of_polygon
{
    // Concave polygon = non-convex polygon.
    CONCAVE,

    // This is a convex polygon with collinear vertices.
    WEAKLY_CONVEX,

    // This is a convex polygon without collinear vertices.
    STRICTLY_CONVEX
};

} // namespace Barycentric_coordinates

} // namespace CGAL

#endif // CGAL_BARYCENTRIC_ENUM_2_H

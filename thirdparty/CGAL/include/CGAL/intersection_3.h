// Copyright (c) 1997
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Intersections_3/include/CGAL/intersection_3.h $
// $Id: intersection_3.h e1eacea 2018-05-09T12:20:11+01:00 Andreas Fabri
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Geert-Jan Giezeman <geert@cs.uu.nl>


#ifndef CGAL_INTERSECTION_3_H
#define CGAL_INTERSECTION_3_H

#include <CGAL/disable_warnings.h>

#include <CGAL/Intersections_3/Bbox_3_Bbox_3.h>
#include <CGAL/Intersections_3/Bbox_3_Iso_cuboid_3.h>
#include <CGAL/Intersections_3/Bbox_3_Line_3.h>
#include <CGAL/Intersections_3/Bbox_3_Plane_3.h>
#include <CGAL/Intersections_3/Bbox_3_Point_3.h>
#include <CGAL/Intersections_3/Bbox_3_Ray_3.h>
#include <CGAL/Intersections_3/Bbox_3_Segment_3.h>
#include <CGAL/Intersections_3/Bbox_3_Sphere_3.h>
#include <CGAL/Intersections_3/Bbox_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Bbox_3_Triangle_3.h>


#include <CGAL/Intersections_3/Iso_cuboid_3_Iso_cuboid_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Line_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Plane_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Point_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Ray_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Segment_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Sphere_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Iso_cuboid_3_Triangle_3.h>

#include <CGAL/Intersections_3/Line_3_Line_3.h>
#include <CGAL/Intersections_3/Line_3_Plane_3.h>
#include <CGAL/Intersections_3/Line_3_Point_3.h>
#include <CGAL/Intersections_3/Line_3_Ray_3.h>
#include <CGAL/Intersections_3/Line_3_Segment_3.h>
#include <CGAL/Intersections_3/Line_3_Sphere_3.h>
#include <CGAL/Intersections_3/Line_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Line_3_Triangle_3.h>

#include <CGAL/Intersections_3/Plane_3_Plane_3.h>
#include <CGAL/Intersections_3/Plane_3_Point_3.h>
#include <CGAL/Intersections_3/Plane_3_Ray_3.h>
#include <CGAL/Intersections_3/Plane_3_Segment_3.h>
#include <CGAL/Intersections_3/Plane_3_Sphere_3.h>
#include <CGAL/Intersections_3/Plane_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Plane_3_Triangle_3.h>

#include <CGAL/Intersections_3/Point_3_Point_3.h>
#include <CGAL/Intersections_3/Point_3_Ray_3.h>
#include <CGAL/Intersections_3/Point_3_Segment_3.h>
#include <CGAL/Intersections_3/Point_3_Sphere_3.h>
#include <CGAL/Intersections_3/Point_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Point_3_Triangle_3.h>

#include <CGAL/Intersections_3/Ray_3_Ray_3.h>
#include <CGAL/Intersections_3/Ray_3_Segment_3.h>
#include <CGAL/Intersections_3/Ray_3_Sphere_3.h>
#include <CGAL/Intersections_3/Ray_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Ray_3_Triangle_3.h>

#include <CGAL/Intersections_3/Segment_3_Segment_3.h>
#include <CGAL/Intersections_3/Segment_3_Sphere_3.h>
#include <CGAL/Intersections_3/Segment_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Segment_3_Triangle_3.h>

#include <CGAL/Intersections_3/Sphere_3_Sphere_3.h>
#include <CGAL/Intersections_3/Sphere_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Sphere_3_Triangle_3.h>

#include <CGAL/Intersections_3/Tetrahedron_3_Tetrahedron_3.h>
#include <CGAL/Intersections_3/Tetrahedron_3_Triangle_3.h>

#include <CGAL/Intersections_3/Triangle_3_Triangle_3.h>

#include <CGAL/enable_warnings.h>

#endif // CGAL_INTERSECTION_3_H

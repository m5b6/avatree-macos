// Copyright (c) 2014  GeometryFactory (France). All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Surface_mesh_skeletonization/include/CGAL/extract_mean_curvature_flow_skeleton.h $
// $Id: extract_mean_curvature_flow_skeleton.h 2f9408f 2018-09-04T12:01:27+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_EXTRACT_MEAN_CURVATURE_FLOW_SKELETON_H
#define CGAL_EXTRACT_MEAN_CURVATURE_FLOW_SKELETON_H

#include <CGAL/license/Surface_mesh_skeletonization.h>


#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#ifdef CGAL_EIGEN3_ENABLED
#include <CGAL/Eigen_solver_traits.h>  // for sparse linear system solver
#endif

#include <CGAL/Mean_curvature_flow_skeletonization.h>

namespace CGAL{

#if defined(DOXYGEN_RUNNING) || defined(CGAL_EIGEN3_ENABLED)
/// \ingroup PkgSurfaceMeshSkeletonizationRef
/// @brief extracts a medially centered curve skeleton for the triangle mesh `tmesh`.
/// This function uses the class CGAL::Mean_curvature_flow_skeletonization with the default parameters.
/// This function is provided only if \ref thirdpartyEigen "Eigen" 3.2 (or greater) is available and `CGAL_EIGEN3_ENABLED` is defined.
/// @pre `tmesh` is a triangle mesh without borders and having exactly one connected component.
/// @pre The specialization `boost::property_map<TriangleMesh, CGAL::vertex_point_t>::%type` and `get(vertex_point, tmesh)` are defined.
/// @pre The value type of `boost::property_map<TriangleMesh, CGAL::vertex_point_t>::%type` is a point type from a \cgal Kernel.
///
/// @tparam TriangleMesh
///         a model of `FaceListGraph`
///
/// @param tmesh
///        input mesh
/// @param skeleton
///        graph that will contain the skeleton of `tmesh`.
///        For each vertex descriptor `vd` of `skeleton`, the corresponding point
///        and the set of input vertices that contracted to `vd` can be retrieved
///        using `skeleton[vd].point` and `skeleton[vd].vertices` respectively.
///
template <class TriangleMesh>
void extract_mean_curvature_flow_skeleton(const TriangleMesh& tmesh,
                                          typename Mean_curvature_flow_skeletonization<TriangleMesh>::Skeleton& skeleton)
{
  // extract the skeleton
  typedef CGAL::Mean_curvature_flow_skeletonization<TriangleMesh> Mcfskel;
  Mcfskel mcfs(tmesh);
  mcfs(skeleton);
}
#endif

}// end of namespace CGAL

#endif //CGAL_EXTRACT_MEAN_CURVATURE_FLOW_SKELETON_H

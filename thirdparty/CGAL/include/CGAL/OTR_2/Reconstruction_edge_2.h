// Copyright (c) 2014  INRIA Sophia-Antipolis (France), INRIA Lorraine LORIA.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Optimal_transportation_reconstruction_2/include/CGAL/OTR_2/Reconstruction_edge_2.h $
// $Id: Reconstruction_edge_2.h 7843436 2016-08-01T11:24:25+02:00 Simon Giraudot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Fernando de Goes, Pierre Alliez, Ivo Vigan, Clément Jamin

#ifndef CGAL_RECONSTRUCTION_EDGE_2_H_
#define CGAL_RECONSTRUCTION_EDGE_2_H_

#include <CGAL/license/Optimal_transportation_reconstruction_2.h>


namespace CGAL {
namespace OTR_2 {

template<class FT, class Edge, class Vertex_handle, class Face_handle>
class Reconstruction_edge_2 {
protected:
  Edge m_edge;
  Vertex_handle m_source;
  Vertex_handle m_target;

  FT m_before_cost;
  FT m_after_cost;
  FT m_total_weight;

public:
  Reconstruction_edge_2() 
  : m_edge(Face_handle(), 0),
    m_before_cost(0),
    m_after_cost(0),
    m_total_weight(0)
  {}

  Reconstruction_edge_2(const Reconstruction_edge_2& pedge) 
  : m_edge(pedge.edge()),
    m_source(pedge.source()),
    m_target(pedge.target()),
    m_before_cost(pedge.before()),
    m_after_cost(pedge.after()),
    m_total_weight(pedge.total_weight())
  {}

  Reconstruction_edge_2(const Edge& edge, const FT before, const FT after, const FT total_weight)
  : m_edge(edge),
    m_before_cost(before),
    m_after_cost(after),
    m_total_weight (total_weight)
  {
    get_vertices();
  }

  Reconstruction_edge_2(const Edge& edge, const FT priority = FT(0))
  : m_edge(edge),
    m_before_cost(0),
    m_after_cost(priority),
    m_total_weight (0)
  {
    get_vertices(); 
  }

  Reconstruction_edge_2(Vertex_handle source, Vertex_handle target)
  : m_edge(Face_handle(), 0),
    m_source(source),
    m_target(target),
    m_before_cost(0),
    m_after_cost(0),
    m_total_weight(0)
  {}

  Reconstruction_edge_2& operator= (const Reconstruction_edge_2& pedge)
  {
    m_edge = pedge.edge();
    m_source = pedge.source();
    m_target = pedge.target();
    m_before_cost = pedge.before();
    m_after_cost = pedge.after();
    m_total_weight = pedge.total_weight();

    return *this;
  }

  bool operator== (const Reconstruction_edge_2& pedge) const
  {
    return (m_source->id() == pedge.source()->id()
      && m_target->id() == pedge.target()->id());
  }

  bool operator< (const Reconstruction_edge_2& pedge) const 
  {
    if (m_source->id() < pedge.source()->id())
      return true;
    if (m_source->id() > pedge.source()->id())
      return false;
    if (m_target->id() < pedge.target()->id())
      return true;
    return false;
  }

  const Edge& edge() const
  {
    return m_edge;
  }

  const Vertex_handle& source() const
  {
    return m_source;
  }

  const Vertex_handle& target() const
  {
    return m_target;
  }

  const FT before() const
  {
    return m_before_cost;
  }

  const FT after() const
  {
    return m_after_cost;
  }

  const FT priority() const
  {
    return after() - before();
  }

  FT total_weight() const
  {
    return m_total_weight;
  }

protected:
  void get_vertices()
  {
    int index = m_edge.second;
    m_source = m_edge.first->vertex((index + 1) % 3);
    m_target = m_edge.first->vertex((index + 2) % 3);
  }
};

} } // namespace

#endif // CGAL_RECONSTRUCTION_EDGE_2_H_

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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Optimal_transportation_reconstruction_2/include/CGAL/OTR_2/Cost.h $
// $Id: Cost.h d03a49b 2019-01-18T16:05:52+01:00 Andreas Fabri
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Fernando de Goes, Pierre Alliez, Ivo Vigan, Clément Jamin

#ifndef CGAL_OTR2_COST_H_
#define CGAL_OTR2_COST_H_

#include <CGAL/license/Optimal_transportation_reconstruction_2.h>


#include <algorithm>

namespace CGAL {
namespace OTR_2 {

template <class FT>
class Cost
{
private:
  FT m_norm;
  FT m_tang;
  FT m_max_norm;
  FT m_max_tang;
  FT m_total_weight;

public:

  Cost(const FT norm = FT(0), const FT tang = FT(0))
  : m_norm(norm),
    m_tang(tang),
    m_max_norm(norm),
    m_max_tang(tang),
    m_total_weight(0)
  {}

  const FT norm() const { return m_norm; }

  const FT tang() const { return m_tang; }

  const FT max_norm() const { return m_max_norm; }

  const FT max_tang() const { return m_max_tang; }

  const FT total_weight() const { return m_total_weight; }

  template <typename SampleContainer>
  void set_total_weight(const SampleContainer& samples)
  {
    m_total_weight = (FT)0;
    for (typename SampleContainer::const_iterator it = samples.begin();
         it != samples.end(); ++ it)
      m_total_weight += (*it)->mass();
  }

  FT finalize(const FT alpha = FT(0.5)) const
  {
    return FT(2) * (alpha * m_norm + (FT(1) - alpha) * m_tang);
  }

  void divide(const FT ratio)
  {
    CGAL_assertion(ratio != FT(0));
    m_norm /= ratio;
    m_tang /= ratio;
  }

  void add(const Cost& cost, const FT mass = FT(1))
  {
    m_norm += mass * cost.norm();
    m_tang += mass * cost.tang();
  }

  void reset_max()
  {
    m_max_norm = FT(0);
    m_max_tang = FT(0);
  }

  void update_max(const Cost& cost)
  {
    m_max_norm = (std::max)(m_max_norm, cost.max_norm());
    m_max_tang = (std::max)(m_max_tang, cost.max_tang());
  }

  void compute_max(const FT norm, const FT tang)
  {
    m_max_norm = (std::max)(m_max_norm, norm);
    m_max_tang = (std::max)(m_max_tang, tang);
  }
};

} } // namespaces

#endif // CGAL_OTR2_COST_H_

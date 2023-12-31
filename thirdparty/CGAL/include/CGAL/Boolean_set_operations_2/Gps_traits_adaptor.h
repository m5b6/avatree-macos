// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Boolean_set_operations_2/include/CGAL/Boolean_set_operations_2/Gps_traits_adaptor.h $
// $Id: Gps_traits_adaptor.h 07f9ac6 2019-02-23T11:20:56+02:00 Efi Fogel
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s): Baruch Zukerman <baruchzu@post.tau.ac.il>
//            Efi Fogel       <efifogel@gmail.com>

#ifndef CGAL_GPS_TRAITS_ADAPTOR_H
#define CGAL_GPS_TRAITS_ADAPTOR_H

#include <CGAL/license/Boolean_set_operations_2.h>

#include <CGAL/disable_warnings.h>

#include <CGAL/enum.h>
#include <CGAL/assertions.h>

namespace CGAL {

template <typename Traits_>
class Gps_traits_adaptor : public Traits_ {
  typedef Traits_                     Base;
  typedef Gps_traits_adaptor<Base>    Self;

public:
  typedef typename Base::X_monotone_curve_2      X_monotone_curve_2;
  typedef typename Base::Point_2                 Point_2;
  typedef typename Base::Compare_xy_2            Compare_xy_2;
  typedef typename Base::Compare_y_at_x_right_2  Compare_y_at_x_right_2;
  typedef typename Base::Compare_endpoints_xy_2  Compare_endpoints_xy_2;
  typedef typename Base::Construct_min_vertex_2  Construct_min_vertex_2;
  typedef typename Base::Construct_max_vertex_2  Construct_max_vertex_2;

  /*! Default constructor. */
  Gps_traits_adaptor() : Base() {}

  /*! Constructor from a base-traits class. */
  Gps_traits_adaptor(const Base& traits) : Base (traits) {}

  class Construct_vertex_2 {
  protected:
    typedef Gps_traits_adaptor<Base>        Traits_adaptor;

    /*! The traits (in case it has state) */
    const Traits_adaptor& m_traits;

    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Construct_vertex_2(const Traits_adaptor& traits) : m_traits(traits) {}

    friend class Gps_traits_adaptor<Base>;

  public:
    Point_2 operator()(const X_monotone_curve_2& cv, int i) const
    {
      const Base& tr = m_traits;
      Compare_endpoints_xy_2 cmp_endpoints =
        tr.compare_endpoints_xy_2_object();
      Construct_min_vertex_2 ctr_min_v = tr.construct_min_vertex_2_object();
      Construct_max_vertex_2 ctr_max_v = tr.construct_max_vertex_2_object();
      i %= 2;
      if (i == 0) {
        // return the source
        if (cmp_endpoints(cv) == SMALLER) return (ctr_min_v(cv));

        return (ctr_max_v(cv));
      }

      // else i==1 (return the target)
      if (cmp_endpoints(cv) == SMALLER) return (ctr_max_v(cv));

      return (ctr_min_v(cv));
    }
  };

  Construct_vertex_2 construct_vertex_2_object() const
  { return Construct_vertex_2(*this); }

  class Orientation_2 {
  protected:
    typedef Gps_traits_adaptor<Base>        Traits_adaptor;

    /*! The traits (in case it has state) */
    const Traits_adaptor& m_traits;

    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Orientation_2(const Traits_adaptor& traits) : m_traits(traits) {}

    friend class Gps_traits_adaptor<Base>;

  public:
    template <typename CurveInputIteraor>
    Orientation operator()(CurveInputIteraor begin, CurveInputIteraor end) const
    {
      Compare_xy_2 cmp_xy = m_traits.compare_xy_2_object();
      Compare_y_at_x_right_2 cmp_y_at_x_right =
        m_traits.compare_y_at_x_right_2_object();
      Construct_vertex_2 ctr_v = m_traits.construct_vertex_2_object();
      Compare_endpoints_xy_2 cmp_endpoints_xy =
        m_traits.compare_endpoints_xy_2_object();

      CurveInputIteraor into_leftmost = end;
      CurveInputIteraor from_leftmost = end;

      CurveInputIteraor into = end;
      --into;
      for (CurveInputIteraor ci = begin; ci != end; ++ci) {
        CurveInputIteraor from = ci;

        /* We are only concerned with the following case:
         *    o
         *   / <= from or into
         *  /
         * o
         *  \
         *   \ <= into or from, resp.
         *    o
         */
        Comparison_result res_from = cmp_endpoints_xy(*from);
        Comparison_result res_into = cmp_endpoints_xy(*into);
        if ((SMALLER != res_from) || (LARGER != res_into)) {
          into = from;
          continue;
        }

        if (from_leftmost == end) {
          // First occurance
          from_leftmost = from;
          into_leftmost = into;
          into = from;
          continue;
        }

        const Point_2& v = ctr_v(*from, 0);
        const Point_2& v_leftmost = ctr_v(*from_leftmost, 0);
        Comparison_result res_xy = cmp_xy(v, v_leftmost);
        if (res_xy == LARGER) {
          into = from;
          continue;
        }
        if (res_xy == SMALLER) {
          from_leftmost = from;
          into_leftmost = into;
          into = from;
          continue;
        }

        // res_xy == EQUAL
        Comparison_result res_from_leftmost_into =
          cmp_y_at_x_right(*from_leftmost, *into, v_leftmost);

        CGAL_assertion_code
          (Comparison_result res_into_leftmost_from =
           cmp_y_at_x_right(*into_leftmost, *from, v_leftmost));
        CGAL_assertion((res_from_leftmost_into != EQUAL) &&
                       (res_from_leftmost_into != res_into_leftmost_from));
        Comparison_result res_into_from =
          cmp_y_at_x_right(*into_leftmost, *from_leftmost, v_leftmost);
        CGAL_assertion(res_into_from != EQUAL);

        if (res_into_from == res_from_leftmost_into) {
          from_leftmost = from;
          into_leftmost = into;
        }
        into = from;
      }

      const Point_2& v_leftmost = ctr_v(*from_leftmost, 0);
      Comparison_result res =
        cmp_y_at_x_right(*into_leftmost, *from_leftmost, v_leftmost);
      CGAL_assertion(res != EQUAL);
      return (res == SMALLER) ? CLOCKWISE : COUNTERCLOCKWISE;
    }
  };

  Orientation_2 orientation_2_object() const { return Orientation_2(*this); }
};

} //namespace CGAL

#include <CGAL/enable_warnings.h>

#endif

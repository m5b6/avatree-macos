// Copyright (c) 2004  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Box_intersection_d/include/CGAL/box_intersection_d.h $
// $Id: box_intersection_d.h cd6fe20 2018-03-26T11:03:37+02:00 Laurent Rineau
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>
//                 Andreas Meyer <ameyer@mpi-sb.mpg.de>

#ifndef CGAL_BOX_INTERSECTION_D_H
#define CGAL_BOX_INTERSECTION_D_H

#include <CGAL/license/Box_intersection_d.h>

#include <CGAL/disable_warnings.h>

#include <CGAL/Box_intersection_d/segment_tree.h>
#include <CGAL/Box_intersection_d/Box_d.h>
#include <CGAL/Box_intersection_d/Box_with_handle_d.h>
#include <CGAL/Box_intersection_d/Box_with_info_d.h>
#include <CGAL/Box_intersection_d/Box_traits_d.h>
#include <CGAL/Box_intersection_d/box_limits.h>

#include <vector>

namespace CGAL {

// Generic call with custom predicate traits parameter.
template< class RandomAccessIter1, class RandomAccessIter2,
          class Callback, class BoxPredicateTraits >
void box_intersection_custom_predicates_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback,
    BoxPredicateTraits traits,
    std::ptrdiff_t cutoff = 10,
    Box_intersection_d::Setting setting = Box_intersection_d::BIPARTITE)
{
    typedef BoxPredicateTraits Traits;
    typedef typename Traits::NT NT;
    CGAL_assertion( Traits::dimension() > 0 );
    const int dim = Traits::dimension() - 1;
    const NT inf = Box_intersection_d::box_limits<NT>::inf();
    const NT sup = Box_intersection_d::box_limits<NT>::sup();
    Box_intersection_d::segment_tree(begin1, end1, begin2, end2,
                              inf, sup, callback, traits, cutoff, dim, true);
    if(setting == Box_intersection_d::BIPARTITE)
        Box_intersection_d::segment_tree(begin2, end2, begin1, end1,
                              inf, sup, callback, traits, cutoff, dim, false);
}


// Generic call with box traits parameter.
// - make all default parameters explicit overloads (workaround)
template< class RandomAccessIter1, class RandomAccessIter2,
          class Callback, class BoxTraits >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback,
    BoxTraits,
    std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology,
    Box_intersection_d::Setting  setting)
{
    if (topology == Box_intersection_d::CLOSED) {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,true> Traits;
        box_intersection_custom_predicates_d(begin1, end1, begin2, end2,
                                         callback, Traits(), cutoff, setting);
    } else {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,false> Traits;
        box_intersection_custom_predicates_d(begin1, end1, begin2, end2,
                                         callback, Traits(), cutoff, setting);
    }
}

template< class RandomAccessIter1, class RandomAccessIter2,
          class Callback, class BoxTraits >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, BoxTraits box_traits, std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology)
{
    box_intersection_d( begin1, end1, begin2, end2, callback, box_traits, 
                        cutoff, topology, Box_intersection_d::BIPARTITE);
}
template< class RandomAccessIter1, class RandomAccessIter2,
          class Callback, class BoxTraits >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, BoxTraits box_traits, std::ptrdiff_t cutoff)
{
    box_intersection_d( begin1, end1, begin2, end2, callback, box_traits, 
                        cutoff, Box_intersection_d::CLOSED, 
                        Box_intersection_d::BIPARTITE);
}
template< class RandomAccessIter1, class RandomAccessIter2,
          class Callback, class BoxTraits >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, BoxTraits box_traits)
{
    box_intersection_d( begin1, end1, begin2, end2, callback, box_traits, 
                        10, Box_intersection_d::CLOSED, 
                        Box_intersection_d::BIPARTITE);
}

// Specialized call with default box traits.
// - make all default parameters explicit overloads (workaround)
template< class RandomAccessIter1, class RandomAccessIter2, class Callback >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology,
    Box_intersection_d::Setting  setting)
{
    typedef typename std::iterator_traits<RandomAccessIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_d( begin1, end1, begin2, end2, callback, Box_traits(), 
                        cutoff, topology, setting);
}

template< class RandomAccessIter1, class RandomAccessIter2, class Callback >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology)
{
    typedef typename std::iterator_traits<RandomAccessIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_d( begin1, end1, begin2, end2, callback, Box_traits(), 
                        cutoff, topology, Box_intersection_d::BIPARTITE);
}
template< class RandomAccessIter1, class RandomAccessIter2, class Callback >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback, std::ptrdiff_t cutoff)
{
    typedef typename std::iterator_traits<RandomAccessIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_d( begin1, end1, begin2, end2, callback, Box_traits(), 
                        cutoff, Box_intersection_d::CLOSED, 
                        Box_intersection_d::BIPARTITE);
}
template< class RandomAccessIter1, class RandomAccessIter2, class Callback >
void box_intersection_d(
    RandomAccessIter1 begin1, RandomAccessIter1 end1,
    RandomAccessIter2 begin2, RandomAccessIter2 end2,
    Callback callback)
{
    typedef typename std::iterator_traits<RandomAccessIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_d( begin1, end1, begin2, end2, callback, Box_traits(), 
                        10, Box_intersection_d::CLOSED, 
                        Box_intersection_d::BIPARTITE);
}


// Generic call with box traits parameter, specialized for self-intersection.
// - make all default parameters explicit overloads (workaround)
template< class RandomAccessIter, class Callback, class BoxTraits >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback,
    BoxTraits box_traits,
    std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology)
{
    // Copying rather than calling 'box_intersection_d(begin, end, begin, end, ...'
    // is necessary because the 'std::partition' and range splits on the first range
    // would be messed up by sorts on the second range otherwise.
    typedef typename std::iterator_traits<RandomAccessIter>::value_type val_t;
    std::vector< val_t> i( begin, end);
    box_intersection_d( begin, end, i.begin(), i.end(),
                        callback, box_traits, cutoff, topology,
                        Box_intersection_d::COMPLETE);
}

template< class RandomAccessIter, class Callback, class BoxTraits >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback,
    BoxTraits box_traits,
    std::ptrdiff_t cutoff)
{
    return box_self_intersection_d(begin, end, callback, box_traits, cutoff,
                                   Box_intersection_d::CLOSED);
}

template< class RandomAccessIter, class Callback, class BoxTraits >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback,
    BoxTraits box_traits)
{
    return box_self_intersection_d(begin, end, callback, box_traits, 10);
}

// Specialized call with default box traits, specialized for self-intersection.
// - make all default parameters explicit overloads (workaround)
template< class RandomAccessIter, class Callback >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback)
{
    typedef typename std::iterator_traits<RandomAccessIter>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_self_intersection_d(begin, end, callback, Box_traits());
}

template< class RandomAccessIter, class Callback >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback,
    std::ptrdiff_t cutoff)
{
    typedef typename std::iterator_traits<RandomAccessIter>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_self_intersection_d(begin, end, callback, Box_traits(), cutoff);
}

template< class RandomAccessIter, class Callback >
void box_self_intersection_d(
    RandomAccessIter begin, RandomAccessIter end,
    Callback callback,
    std::ptrdiff_t cutoff,
    Box_intersection_d::Topology topology)
{
    typedef typename std::iterator_traits<RandomAccessIter>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_self_intersection_d(begin, end, callback,
                            Box_traits(), cutoff, topology );
}


// Generic call for trivial all-pairs algorithm with box traits parameter.
// - make all default parameters explicit overloads (workaround)
template< class ForwardIter1, class ForwardIter2,
          class Callback, class BoxTraits >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback, BoxTraits)
{
    typedef Box_intersection_d::Predicate_traits_d<BoxTraits,true> Traits;
    Box_intersection_d::all_pairs( begin1, end1, begin2, end2, 
                                   callback, Traits());
}

template< class ForwardIter1, class ForwardIter2,
          class Callback, class BoxTraits >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback, BoxTraits,
    Box_intersection_d::Topology topology,
    Box_intersection_d::Setting setting)
{
    bool complete_case = (setting != Box_intersection_d::BIPARTITE);
    if (topology == Box_intersection_d::CLOSED) {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,true> Traits;
        Box_intersection_d::all_pairs( begin1, end1, begin2, end2, 
                                       callback, Traits(), complete_case);
    } else {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,false> Traits;
        Box_intersection_d::all_pairs( begin1, end1, begin2, end2, 
                                       callback, Traits(), complete_case);
    }
}

template< class ForwardIter1, class ForwardIter2,
          class Callback, class BoxTraits >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback, BoxTraits traits,
    Box_intersection_d::Topology topology)
{
    box_intersection_all_pairs_d( begin1, end1, begin2, end2, callback, traits,
                                  topology, Box_intersection_d::BIPARTITE);
}

// Specialized call for trivial all-pairs algorithm with default box traits.
// - make all default parameters explicit overloads (workaround)
template< class ForwardIter1, class ForwardIter2, class Callback >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback)
{
    typedef typename std::iterator_traits<ForwardIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_all_pairs_d( begin1, end1, begin2, end2, 
                                  callback, Box_traits(), 
                                  Box_intersection_d::CLOSED );   
}

template< class ForwardIter1, class ForwardIter2, class Callback >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback,
    Box_intersection_d::Topology topology)
{
    typedef typename std::iterator_traits<ForwardIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_all_pairs_d( begin1, end1, begin2, end2, 
                                  callback, Box_traits(), topology);
}

template< class ForwardIter1, class ForwardIter2, class Callback >
void box_intersection_all_pairs_d( 
    ForwardIter1 begin1, ForwardIter1 end1,
    ForwardIter2 begin2, ForwardIter2 end2,
    Callback callback,
    Box_intersection_d::Topology topology,
    Box_intersection_d::Setting  setting)
{
    typedef typename std::iterator_traits<ForwardIter1>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_intersection_all_pairs_d( begin1, end1, begin2, end2, 
                                  callback, Box_traits(), topology, setting);
}

// Generic call for trivial all-pairs algorithm with box traits parameter
// specialized for self-intersection test.
// - make all default parameters explicit overloads (workaround)
template< class ForwardIter, class Callback, class BoxTraits >
void box_self_intersection_all_pairs_d( 
  ForwardIter begin1, ForwardIter end1, Callback callback, BoxTraits /* traits */)
{
    typedef Box_intersection_d::Predicate_traits_d<BoxTraits,true> Traits;
    Box_intersection_d::all_pairs( begin1, end1, callback, Traits());
}

template< class ForwardIter, class Callback, class BoxTraits >
void box_self_intersection_all_pairs_d( 
    ForwardIter begin1, ForwardIter end1, Callback callback, BoxTraits,
    Box_intersection_d::Topology topology)
{
    if (topology == Box_intersection_d::CLOSED) {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,true> Traits;
        Box_intersection_d::all_pairs( begin1, end1, callback, Traits());
    } else {
        typedef Box_intersection_d::Predicate_traits_d<BoxTraits,false> Traits;
        Box_intersection_d::all_pairs( begin1, end1, callback, Traits());
    }
}

// Specialized call for trivial all-pairs algorithm with default box traits.
// specialized for self-intersection test.
// - make all default parameters explicit overloads (workaround)
template< class ForwardIter, class Callback >
void box_self_intersection_all_pairs_d( 
    ForwardIter begin1, ForwardIter end1, Callback callback)
{
    typedef typename std::iterator_traits<ForwardIter>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_self_intersection_all_pairs_d( begin1, end1, callback, Box_traits(), 
                                       Box_intersection_d::CLOSED );   
}

template< class ForwardIter, class Callback >
void box_self_intersection_all_pairs_d( 
    ForwardIter begin1, ForwardIter end1, Callback callback,
    Box_intersection_d::Topology topology)
{
    typedef typename std::iterator_traits<ForwardIter>::value_type val_t;
    typedef Box_intersection_d::Box_traits_d< val_t>  Box_traits;
    box_self_intersection_all_pairs_d( begin1, end1, callback, Box_traits(),
                                       topology);
}

} //namespace CGAL

#include <CGAL/enable_warnings.h>

#endif

// Copyright (c) 2006-2013 INRIA Nancy-Grand Est (France). All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.

// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Algebraic_kernel_d/include/CGAL/RS/comparator_1.h $
// $Id: comparator_1.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author: Luis Peñaranda <luis.penaranda@gmx.com>

#ifndef CGAL_RS_COMPARATOR_1_H
#define CGAL_RS_COMPARATOR_1_H

namespace CGAL{
namespace RS_AK1{

template <class Polynomial_,
          class Bound_,
          class Refiner_,
          class Signat_,
          class Ptraits_>
struct Simple_comparator_1{
        typedef Polynomial_                                     Polynomial;
        typedef Bound_                                          Bound;
        typedef Refiner_                                        Refiner;
        typedef Signat_                                         Signat;
        typedef Ptraits_                                        Ptraits;
        typedef typename Ptraits::Gcd_up_to_constant_factor     Gcd;
        typedef typename Ptraits::Degree                        Degree;

        CGAL::Comparison_result
        operator()(const Polynomial &p1,Bound &l1,Bound &r1,
                   const Polynomial &p2,Bound &l2,Bound &r2)const{
                CGAL_precondition(l1<=r1&&l2<=r2);
                if(l1<=l2){
                        if(r1<l2)
                                return SMALLER;
                }else{
                        if(r2<l1)
                                return LARGER;
                }
                Polynomial G=Gcd()(p1,p2);
                if(Degree()(G)==0)
                        return compare_unequal(p1,l1,r1,p2,l2,r2);
                Signat sg(G);
                CGAL::Sign sleft=sg(l1>l2?l1:l2);
                if(sleft==ZERO)
                        return EQUAL;
                CGAL::Sign sright=sg(r1<r2?r1:r2);
                if(sleft!=sright)
                        return EQUAL;
                else
                        return compare_unequal(p1,l1,r1,p2,l2,r2);
        }

        // This function compares two algebraic numbers, assuming that they
        // are not equal.
        CGAL::Comparison_result
        compare_unequal(const Polynomial &p1,Bound &l1,Bound &r1,
                        const Polynomial &p2,Bound &l2,Bound &r2)const{
                CGAL_precondition(l1<=r1&&l2<=r2);
                int prec=CGAL::max(
                                CGAL::max(l1.get_precision(),
                                          r1.get_precision()),
                                CGAL::max(l2.get_precision(),
                                          r2.get_precision()));
                do{
                        prec*=2;
                        Refiner()(p1,l1,r1,prec);
                        Refiner()(p2,l2,r2,prec);
                        CGAL_assertion(l1<=r1&&l2<=r2);
                }while(l1<=l2?r1>=l2:r2>=l1);
                return (r1<l2?SMALLER:LARGER);
        }

}; // struct Simple_comparator_1

} // namespace RS_AK1
} // namespace CGAL

#endif // CGAL_RS_COMPARATOR_1_H

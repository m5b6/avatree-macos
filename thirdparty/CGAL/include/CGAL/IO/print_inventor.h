// Copyright (c) 1997  ETH Zurich (Switzerland).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Polyhedron_IO/include/CGAL/IO/print_inventor.h $
// $Id: print_inventor.h ee57fc2 2017-10-21T01:03:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#ifndef CGAL_IO_PRINT_INVENTOR_H
#define CGAL_IO_PRINT_INVENTOR_H 1

#include <CGAL/license/Polyhedron.h>


#include <CGAL/IO/Polyhedron_inventor_ostream.h>


namespace CGAL {

template <class Polyhedron>
void print_polyhedron_inventor( std::ostream& out, const Polyhedron& P) {
    Inventor_ostream os( out);
    os << P;
}

// Deprecated global functions, replaced with functions above

template < class Traits,
           class Items,
           template < class T, class I, class A>
           class HDS, class Alloc>
void
print_inventor( std::ostream& out,
                const Polyhedron_3<Traits,Items,HDS,Alloc>& P) {
    Inventor_ostream os( out);
    os << P;
}

} //namespace CGAL
#endif // CGAL_IO_PRINT_INVENTOR_H //
// EOF //

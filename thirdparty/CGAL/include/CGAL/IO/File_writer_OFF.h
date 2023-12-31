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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Stream_support/include/CGAL/IO/File_writer_OFF.h $
// $Id: File_writer_OFF.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#ifndef CGAL_IO_FILE_WRITER_OFF_H
#define CGAL_IO_FILE_WRITER_OFF_H 1

#include <CGAL/IO/binary_file_io.h>
#include <CGAL/IO/File_header_OFF.h>
#include <iostream>
#include <cstddef>

namespace CGAL {

class CGAL_EXPORT File_writer_OFF {
    std::ostream*           m_out;
    File_header_OFF         m_header;
public:
    File_writer_OFF( bool verbose = false) : m_header( verbose) {}
    File_writer_OFF( const File_header_OFF& h) : m_header( h) {}

    std::ostream&           out()          { return *m_out;   }
    File_header_OFF&        header()       { return m_header; }
    const File_header_OFF&  header() const { return m_header; }

    void write_header( std::ostream& out,
                       std::size_t   vertices,
                       std::size_t   halfedges,
                       std::size_t   facets,
                       bool          normals = false);
    void write_footer() {
        if ( m_header.ascii() && m_header.comments())
            out() << "\n\n# End of OFF #";
        out() << std::endl;
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            I_Binary_write_big_endian_float32( out(), float(x));
            I_Binary_write_big_endian_float32( out(), float(y));
            I_Binary_write_big_endian_float32( out(), float(z));
        } else {
            out() << '\n' << x << ' ' << y << ' ' << z;
        }
    }
    void write_normal( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            I_Binary_write_big_endian_float32( out(), float(x));
            I_Binary_write_big_endian_float32( out(), float(y));
            I_Binary_write_big_endian_float32( out(), float(z));
        } else {
            out() << ' ' << ' ' << x << ' ' << y << ' ' << z;
        }
    }
    void write_facet_header() {
        if ( m_header.ascii()) {
            if ( m_header.no_comments())
                out() << '\n';
            else {
                out() << "\n\n# " << m_header.size_of_facets()
                       << " facets\n";
                out() << "# ------------------------------------------"
                          "\n\n";
            }
        }
    }
    void write_facet_begin( std::size_t no) {
        if ( m_header.binary())
          I_Binary_write_big_endian_integer32( out(), static_cast<boost::int32_t>(no));
        else
            out() << no << ' ';
    }
    void write_facet_vertex_index( std::size_t index) {
        if ( m_header.binary())
          I_Binary_write_big_endian_integer32( out(), static_cast<boost::int32_t>(index));
        else
            out() << ' ' << index;
    }
    void write_facet_end() {
        if ( m_header.binary())
            I_Binary_write_big_endian_integer32( out(), 0);
        else
            out() << '\n';
    }
};

} //namespace CGAL

#ifdef CGAL_HEADER_ONLY
#include <CGAL/IO/File_writer_OFF_impl.h>
#endif // CGAL_HEADER_ONLY

#endif // CGAL_IO_FILE_WRITER_OFF_H //
// EOF //

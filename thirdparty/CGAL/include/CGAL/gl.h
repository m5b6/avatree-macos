// Copyright (c) 2008 GeometryFactory, Sophia Antipolis (France)
//  All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Installation/include/CGAL/gl.h $
// $Id: gl.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+

#ifndef CGAL_GL_H
#define CGAL_GL_H

#ifdef _MSC_VER
#  include <wtypes.h>
#  include <wingdi.h>
#endif

#ifdef __APPLE__
#  if TARGET_OS_IPHONE
#    include <OpenGLES/ES2/gl.h>
#  else
#    include <OpenGL/gl.h>
#  endif
#else
#  ifdef __arm__
#    include <GLES3/gl3.h>
#  else
#    include <GL/gl.h>
#  endif
#endif

#endif // CGAL_GL_H

// Copyright (c) 2003-2004  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Mesh_2/include/CGAL/Filter_circulator.h $
// $Id: Filter_circulator.h ee57fc2 2017-10-21T01:03:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_FILTRED_CIRCULATOR_H
#define CGAL_FILTRED_CIRCULATOR_H

#include <CGAL/license/Mesh_2.h>


#include <CGAL/config.h>
#include <CGAL/assertions.h>

namespace CGAL {

template <class Circ, class Pred>
class Filter_circulator : public Circ
{
  bool is_null;
  Pred test;

public:
  typedef Filter_circulator<Circ,Pred> Self;


  Filter_circulator(const Pred p=Pred()): is_null(true), test(p) {}

  Filter_circulator(const Self& c): Circ(c), is_null(c.is_null),
    test(c.test) {}

  Self& operator=(const Self& c)
    {
      //this->Circ::operator=(c); // This does not work with bcc
      //*this = c;  // This does not work with VC++6
      static_cast<Circ&>(*this) = static_cast<const Circ&>(c);
      is_null=c.is_null;
      test=c.test;
      return *this;
    }

  Filter_circulator(const Circ& c, const Pred& p=Pred())
    : test(p)
    {
      Circ circ(c);
      if(test(circ))
	is_null=false;
      else
	{
	  Circ end(c);
	  do { 
	    ++circ;
	  } while( !test(circ) && end != circ );
	  is_null = (end == circ);
	}
      static_cast<Circ&>(*this) = circ;
      CGAL_assertion(is_null || test(*this));
    }

  bool operator==( Nullptr_t ) const {
    return is_null;
  }

  bool operator!=( Nullptr_t ) const {
    return !is_null;
  }

  bool operator==(const Self& c) const 
    {
      return is_null==c.is_null && this->Circ::operator==(c);
    }

  bool operator!=( const Self& c) const { return !(*this == c); }

  Self& operator++() {
    CGAL_assertion(!is_null);
    do {
      this->Circ::operator++();
    } while( !test(static_cast<Circ&>(*this)) );
    CGAL_assertion(is_null || test(static_cast<Circ&>(*this)));
    return *this;
  }

  Self  operator++(int) {
    Self tmp= *this;
    ++*this;
    return tmp;
  }
};

}

#endif

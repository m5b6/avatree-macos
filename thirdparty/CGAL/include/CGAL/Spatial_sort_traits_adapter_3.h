// Copyright (c) 2011  GeometryFactory (France).
// All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Spatial_sorting/include/CGAL/Spatial_sort_traits_adapter_3.h $
// $Id: Spatial_sort_traits_adapter_3.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Sebastien Loriot


#ifndef CGAL_SPATIAL_SORT_TRAITS_ADAPTER_3_H
#define CGAL_SPATIAL_SORT_TRAITS_ADAPTER_3_H

#include <boost/call_traits.hpp>

#include <CGAL/property_map.h>


namespace CGAL{

using ::get;
  
template<class Base_traits,class PointPropertyMap>
class Spatial_sort_traits_adapter_3:public Base_traits{
  PointPropertyMap ppmap_;
public:
  Spatial_sort_traits_adapter_3(Base_traits base=Base_traits()):Base_traits(base){}

  Spatial_sort_traits_adapter_3(const PointPropertyMap& ppmap,Base_traits base=Base_traits())
  :Base_traits(base),ppmap_(ppmap){}

  typedef Base_traits Gt;
  typedef typename boost::property_traits<PointPropertyMap>::key_type Point_3;
  typedef typename boost::call_traits<Point_3>::param_type Arg_type;

  struct Less_x_3 : public Base_traits::Less_x_3{
    Less_x_3(const PointPropertyMap& ppmap,const typename Base_traits::Less_x_3& base):
      Base_traits::Less_x_3(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Less_x_3*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };

  struct Less_y_3 : public Base_traits::Less_y_3{
    Less_y_3(const PointPropertyMap& ppmap,const typename Base_traits::Less_y_3& base):
      Base_traits::Less_y_3(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Less_y_3*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };

  struct Less_z_3 : public Base_traits::Less_z_3{
    Less_z_3(const PointPropertyMap& ppmap,const typename Base_traits::Less_z_3& base):
      Base_traits::Less_z_3(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Less_z_3*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };

  Less_x_3 less_x_3_object () const {return Less_x_3(ppmap_,static_cast<const Gt*>(this)->less_x_3_object() );}
  Less_y_3 less_y_3_object () const {return Less_y_3(ppmap_,static_cast<const Gt*>(this)->less_y_3_object() );}
  Less_z_3 less_z_3_object () const {return Less_z_3(ppmap_,static_cast<const Gt*>(this)->less_z_3_object() );}
  
  const PointPropertyMap& point_property_map() const {return ppmap_;}
  
};

} //namespace CGAL

#endif //CGAL_SPATIAL_SORT_TRAITS_ADAPTER_3_H

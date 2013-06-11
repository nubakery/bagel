//
// BAGEL - Parallel electron correlation program.
// Filename: wfn_py.cc
// Copyright (C) 2013 Michael Caldwell
//
// Author: Michael Caldwell <MichaelCaldwell@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//
#include <boost/python.hpp>
#include <src/util/input.h>
#include <src/wfn/geometry.h>

using namespace boost::python;

BOOST_PYTHON_MODULE(bagel){
  using namespace bagel;
  class_<PTree>("PTree", init<const std::string>())
    .def("pr1nt", &PTree::print)
    .def("size", &PTree::size)
    .def("get_child", &PTree::get_child)
    .def("data", &PTree::data);
  class_<Geometry>("Geometry", init<const std::shared_ptr<const PTree>>())
    .def("natom ", &Geometry::natom);
}
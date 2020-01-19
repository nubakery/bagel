//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: test_scf.cc
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Alexander Humeniuk
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <sstream>
#include <src/wfn/reference.h>
#include <src/wfn/dyson.h>

using namespace bagel;

VectorB dyson_norms(std::string filename) {
  auto ofs = std::make_shared<std::ofstream>(filename + ".testout", std::ios::trunc);
  std::streambuf* backup_stream = std::cout.rdbuf(ofs->rdbuf());

  // a bit ugly to hardwire an input file, but anyway...
  std::stringstream ss; ss << location__ << filename << ".json";
  auto idata = std::make_shared<const PTree>(ss.str());
  auto keys = idata->get_child("bagel");
  std::shared_ptr<Geometry> geom;
  std::shared_ptr<const Reference> ref;

  for (auto& itree : *keys) {

    const string title = to_lower(itree->get<string>("title", ""));
    if (title.empty()) throw runtime_error("title is missing in one of the input blocks");

    if (title == "molecule") {
      geom = geom ? make_shared<Geometry>(*geom, itree) : make_shared<Geometry>(itree);
      if (itree->get<bool>("restart", false))
        ref.reset();
      if (ref) ref = ref->project_coeff(geom);
      if (!itree->get<string>("molden_file", "").empty())
        ref = molden_to_ref(geom, itree);
    } else {
      if (!geom) {
        if (title != "continue" && !(title == "relsmith" && itree->get<string>("method", "") == "continue") && title != "load_ref")
          throw runtime_error("molecule block is missing");
      } else {
        if (!itree->get<bool>("df",true)) dodf = false;
        if (dodf && !geom->df() && !geom->do_periodic_df() && !dofmm) throw runtime_error("It seems that DF basis was not specified in molecule block");
      }
    }

    if (title == "dyson") {
      shared_ptr<const DysonOrbitals> dyson = make_shared<DysonOrbitals>(itree);
      dyson->compute();
      return dyson->norms();
      
#ifndef DISABLE_SERIALIZATION
    } else if (title == "load_ref") {
      const string name = itree->get<string>("file", "reference");
      if (name == "") throw runtime_error("Please provide a filename for the Reference object to be read.");
      IArchive archive(name);
      shared_ptr<Reference> ptr;
      archive >> ptr;
      ref = shared_ptr<Reference>(ptr);
      if (itree->get<bool>("continue_geom", true)) {
        cout << endl << "  Using the geometry in the archive file " << endl << endl;
        geom = ref->geom();
      } else {
        cout << endl << "  Using the coefficient projected to the input geometry " << endl << endl;
        ref = ref->project_coeff(geom);
      }
      if (itree->get<bool>("extract_average_rdms", false)) {
        vector<int> rdm_states = itree->get_vector<int>("rdm_state");
        ref = ref->extract_average_rdm(rdm_states);
      }

    } else if (title == "save_ref") {
      const string name = itree->get<string>("file", "reference");
      OArchive archive(name);
      archive << ref;
#endif
    } else {
      // otherwise, they are considered single point energy calculation
      tie(ignore, ref) = get_energy(title, itree, geom, ref);
    }

  }
  assert(false);
  return VectorB(0);
}

VectorB reference_dyson_norms() {
  VectorB norms(6);
  norms[0] = 0.9252774;
  norms[1] = 0.0003564;
  norms[2] = 0.0000284;
  norms[3] = 0.0000017;
  norms[4] = 0.0000059;
  norms[5] = 0.0000523;

  return norms;
}

BOOST_AUTO_TEST_SUITE(TEST_DYSON)

BOOST_AUTO_TEST_CASE(NORMS) {
  BOOST_CHECK(compare(dyson_norms("h2o_svp_cas_dyson.json"), reference_dyson_norms(), 0.000001));
}

BOOST_AUTO_TEST_SUITE_END()

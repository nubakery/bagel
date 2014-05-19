//
// BAGEL - Parallel electron correlation program.
// Filename: zharrison_london.cc
// Copyright (C) 2014 Toru Shiozaki
//
// Author: Ryan D. Reynolds <RyanDReynolds@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
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

#include <src/london/zharrison_london.h>
#include <src/london/relspace_london.h>

//BOOST_CLASS_EXPORT_IMPLEMENT(bagel::ZHarrison_London_London)

using namespace std;
using namespace bagel;

ZHarrison_London::ZHarrison_London(std::shared_ptr<const PTree> idat, shared_ptr<const Geometry_London> g, shared_ptr<const Reference> r, const int ncore, const int norb, const int nstate)
 : Method(idat, g, r), ncore_(ncore), norb_(norb), nstate_(nstate), restarted_(false) {
  if (!ref_) throw runtime_error("ZFCI requires a reference object");

  print_header();

  auto rr = dynamic_pointer_cast<const RelReference>(ref_);
  assert(rr);

  const bool frozen = idata_->get<bool>("frozen", false);
  max_iter_ = idata_->get<int>("maxiter", 100);
  max_iter_ = idata_->get<int>("maxiter_fci", max_iter_);
  thresh_ = idata_->get<double>("thresh", 1.0e-10);
  thresh_ = idata_->get<double>("thresh_fci", thresh_);
  print_thresh_ = idata_->get<double>("print_thresh", 0.05);
  restart_ = idata_->get<bool>("restart", false);

  states_ = idata_->get_vector<int>("state", 0);
  nstate_ = 0;
  for (int i = 0; i != states_.size(); ++i)
    nstate_ += states_[i] * (i+1); // 2S+1 for 0, 1/2, 1, ...

  gaunt_ = rr->gaunt();
  breit_ = rr->breit();

  if (ncore_ < 0)
    ncore_ = idata_->get<int>("ncore", (frozen ? cgeom_->num_count_ncore_only()/2 : 0));
  if (norb_  < 0)
    norb_ = rr->relcoeff()->mdim()/2-ncore_;

  const shared_ptr<const PTree> iactive = idata_->get_child_optional("active");

  // additional charge
  charge_ = idata_->get<int>("charge", 0);

  nele_ = cgeom_->nele() - charge_ - ncore_*2;

  energy_.resize(nstate_);

  space_ = make_shared<RelSpace_London>(norb_, nele_);
  int_space_ = make_shared<RelSpace_London>(norb_, nele_-2, /*mute*/true, /*link up*/true);

  update(rr->relcoeff());
}


void ZHarrison_London::print_header() const {
  cout << "  ----------------------------" << endl;
  cout << "  Relativistic FCI calculation" << endl;
  cout << "  ----------------------------" << endl << endl;
}


// generate initial vectors
void ZHarrison_London::generate_guess(const int nelea, const int neleb, const int nstate, std::shared_ptr<RelZDvec_London> out, const int offset) {
  shared_ptr<const Determinants> cdet = space_->finddet(nelea, neleb);
  int ndet = nstate*10;
  start_over:
  vector<pair<bitset<nbit__>, bitset<nbit__>>> bits = detseeds(ndet, nelea, neleb);

  // Spin adapt detseeds
  int oindex = offset;
  vector<bitset<nbit__>> done;
  for (auto& it : bits) {
    bitset<nbit__> alpha = it.second;
    bitset<nbit__> beta = it.first;
    bitset<nbit__> open_bit = (alpha^beta);

    // make sure that we have enough unpaired alpha
    const int unpairalpha = (alpha ^ (alpha & beta)).count();
    const int unpairbeta  = (beta ^ (alpha & beta)).count();
    if (unpairalpha-unpairbeta < nelea-neleb) continue;

    // check if this orbital configuration is already used
    if (find(done.begin(), done.end(), open_bit) != done.end()) continue;
    done.push_back(open_bit);

    pair<vector<tuple<int, int, int>>, double> adapt = space_->finddet(nelea, neleb)->spin_adapt(nelea-neleb, alpha, beta);
    const double fac = adapt.second;
    for (auto& iter : adapt.first) {
      out->find(nelea, neleb)->data(oindex)->element(get<0>(iter), get<1>(iter)) = get<2>(iter)*fac;
    }
    cout << "     guess " << setw(3) << oindex << ":   closed " <<
          setw(20) << left << print_bit(alpha&beta, norb_) << " open " << setw(20) << print_bit(open_bit, norb_) << right << endl;

    ++oindex;
    if (oindex == offset+nstate) break;
  }
  if (oindex < offset+nstate) {
    for (int i = offset; i != offset+oindex; ++i)
      out->find(nelea, neleb)->data(i)->zero();
    ndet *= 4;
    goto start_over;
  }
  cout << endl;
}


// returns seed determinants for initial guess
vector<pair<bitset<nbit__> , bitset<nbit__>>> ZHarrison_London::detseeds(const int ndet, const int nelea, const int neleb) {
  shared_ptr<const Determinants> cdet = space_->finddet(nelea, neleb);

  multimap<double, pair<bitset<nbit__>,bitset<nbit__>>> tmp;
  for (int i = 0; i != ndet; ++i) tmp.insert(make_pair(-1.0e10*(1+i), make_pair(bitset<nbit__>(0),bitset<nbit__>(0))));

  double* diter = denom_->find(cdet->nelea(), cdet->neleb())->data();
  for (auto& aiter : cdet->string_bits_a()) {
    for (auto& biter : cdet->string_bits_b()) {
      const double din = -(*diter);
      if (tmp.begin()->first < din) {
        tmp.insert(make_pair(din, make_pair(biter, aiter)));
        tmp.erase(tmp.begin());
      }
      ++diter;
    }
  }
  assert(tmp.size() == ndet || ndet > cdet->string_bits_a().size()*cdet->string_bits_b().size());
  vector<pair<bitset<nbit__> , bitset<nbit__>>> out;
  for (auto iter = tmp.rbegin(); iter != tmp.rend(); ++iter)
    out.push_back(iter->second);
  return out;
}


void ZHarrison_London::compute() {
  Timer pdebug(2);

  if (cgeom_->nirrep() > 1) throw runtime_error("ZFCI_London: C1 only at the moment.");

  if (!restarted_) {
    // Creating an initial CI vector
    cc_ = make_shared<RelZDvec_London>(space_, nstate_); // B runs first

    // find determinants that have small diagonal energies
    int offset = 0;
    for (int ispin = 0; ispin != states_.size(); ++ispin) {
      int nstate = 0;
      for (int i = ispin; i != states_.size(); ++i)
        nstate += states_[i];

      if ((cgeom_->nele()+ispin-charge_) % 2 == 1) {
        if (states_[ispin] != 0) throw runtime_error("wrong states specified");
        continue;
      }

      const int nelea = (cgeom_->nele()+ispin-charge_)/2 - ncore_;
      const int neleb = (cgeom_->nele()-ispin-charge_)/2 - ncore_;
      generate_guess(nelea, neleb, nstate, cc_, offset);
      offset += nstate;
      if (nelea != neleb) {
        generate_guess(neleb, nelea, nstate, cc_, offset);
        offset += nstate;
      }
    }
    pdebug.tick_print("guess generation");

    // Davidson utility
    davidson_ = make_shared<DavidsonDiag<RelZDvec_London, ZMatrix>>(nstate_, max_iter_);
  }

  // nuclear energy retrieved from geometry
  const double nuc_core = cgeom_->nuclear_repulsion() + jop_->core_energy();

  // main iteration starts here
  cout << "  === Relativistic FCI iteration ===" << endl << endl;
  // 0 means not converged
  vector<int> conv(nstate_,0);

  for (int iter = 0; iter != max_iter_; ++iter) {
    Timer fcitime;

    if (restart_) {
      stringstream ss; ss << "zfci_" << iter;
      OArchive ar(ss.str());
      ar << static_cast<Method*>(this);
    }

    // form a sigma vector given cc
    shared_ptr<RelZDvec_London> sigma = form_sigma(cc_, jop_, conv);
    pdebug.tick_print("sigma vector");

    // constructing Dvec's for Davidson
    auto ccn = make_shared<RelZDvec_London>(cc_);
    auto sigman = make_shared<RelZDvec_London>(sigma);
    ccn->synchronize();
    sigman->synchronize();

    const vector<double> energies = davidson_->compute(ccn->dvec(conv), sigman->dvec(conv));
    // get residual and new vectors
    vector<shared_ptr<RelZDvec_London>> errvec = davidson_->residual();
    for (auto& i : errvec)
      i->synchronize();
    pdebug.tick_print("davidson");

    // compute errors
    vector<double> errors;
    for (int i = 0; i != nstate_; ++i) {
      errors.push_back(errvec[i]->rms());
      conv[i] = static_cast<int>(errors[i] < thresh_);
    }
    pdebug.tick_print("error");

    if (!*min_element(conv.begin(), conv.end())) {
      // denominator scaling

      auto ctmp = errvec.front()->clone();

      for (int ist = 0; ist != nstate_; ++ist) {
        if (conv[ist]) continue;
        for (auto& ib : space_->detmap()) {
          const int na = ib.second->nelea();
          const int nb = ib.second->neleb();
          const size_t size = ccn->find(na, nb)->data(ist)->size();
          complex<double>* target_array = ctmp->find(na, nb)->data();
          complex<double>* source_array = errvec[ist]->find(na, nb)->data();
          double* denom_array = denom_->find(na, nb)->data();
          const double en = energies[ist];
          for (int i = 0; i != size; ++i) {
            target_array[i] = source_array[i] / min(en - denom_array[i], -0.1);
          }
        }
        ctmp->normalize();
        cc_->set_data(ist, ctmp);
      }
    }
    pdebug.tick_print("denominator");

    // printing out
    if (nstate_ != 1 && iter) cout << endl;
    for (int i = 0; i != nstate_; ++i) {
      cout << setw(7) << iter << setw(3) << i << setw(2) << (conv[i] ? "*" : " ")
                              << setw(17) << fixed << setprecision(8) << energies[i]+nuc_core << "   "
                              << setw(10) << scientific << setprecision(2) << errors[i] << fixed << setw(10) << setprecision(2)
                              << fcitime.tick() << endl;
      energy_[i] = energies[i]+nuc_core;
    }
    if (*min_element(conv.begin(), conv.end())) break;
  }
  // main iteration ends here

  cc_ = make_shared<RelZDvec_London>(davidson_->civec());
  cc_->print(print_thresh_);

#if 0
  for (auto& iprop : properties_) {
    iprop->compute(cc_);
    iprop->print();
  }
#endif
}

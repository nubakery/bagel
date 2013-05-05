//
// BAGEL - Parallel electron correlation program.
// Filename: mp2grad.cc
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki.toru@gmail.com>
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

#include <stddef.h>
#include <src/mp2/mp2grad.h>
#include <src/grad/cphf.h>
#include <iostream>
#include <iomanip>
#include <src/util/f77.h>
#include <src/smith/prim_op.h>
#include <src/prop/dipole.h>
#include <src/grad/gradeval.h>

using namespace std;
using namespace bagel;

MP2Grad::MP2Grad(const boost::property_tree::ptree& input, const shared_ptr<const Geometry> g) : MP2(input, g, shared_ptr<const Reference>()) {

}


// does nothing.
void MP2Grad::compute() { }


template<>
shared_ptr<GradFile> GradEval<MP2Grad>::compute() {
  Timer time;

  const size_t ncore = ref_->ncore();

  // since this is only for closed shell
  const size_t naux = geom_->naux();
  const size_t nocc = ref_->nocc() - ncore;
  const size_t nocca = ref_->nocc();
  if (nocc < 1) throw runtime_error("no correlated electrons");
  const size_t nvirt = geom_->nbasis() - nocca;
  if (nvirt < 1) throw runtime_error("no virtuals orbitals");
  assert(geom_->nbasis() == ref_->coeff()->mdim());

  const size_t nbasis = geom_->nbasis();

  shared_ptr<const Matrix> ccmat = ref_->coeff()->slice(0, ncore);
  shared_ptr<const Matrix> acmat = ref_->coeff()->slice(ncore, nocca);
  shared_ptr<const Matrix> ocmat = ref_->coeff()->slice(0, nocca);
  shared_ptr<const Matrix> vcmat = ref_->coeff()->slice(nocca, nbasis);

  // first compute half transformed integrals
  shared_ptr<const DFHalfDist> half = geom_->df()->compute_half_transform(acmat);
  // TODO this is a waste...
  shared_ptr<const DFHalfDist> halfjj = geom_->df()->compute_half_transform(ocmat)->apply_JJ();
  // second transform for virtual index
  // this is now (naux, nocc, nvirt)
  shared_ptr<const DFFullDist> full = half->compute_second_transform(vcmat)->apply_J();
  shared_ptr<const DFFullDist> bv = full->apply_J();
  shared_ptr<DFFullDist> gia = bv->clone();

  time.tick_print("3-index integral transform");

  // assemble
  unique_ptr<double[]> buf(new double[nocc*nvirt*nocc]); // it is implicitly assumed that o^2v can be kept in core in each node
  unique_ptr<double[]> buf2(new double[nocc*nvirt*nocc]);
  vector<double> eig_tm = ref_->eig();
  vector<double> eig(eig_tm.begin()+ncore, eig_tm.end());

  auto dmp2 = make_shared<Matrix>(nbasis, nbasis);
  double* optr = dmp2->element_ptr(ncore, ncore);
  double* vptr = dmp2->element_ptr(nocca, nocca);

  double ecorr = 0.0;
  for (size_t i = 0; i != nvirt; ++i) {
    // nocc * nvirt * nocc
    unique_ptr<double[]> data = full->form_4index_1fixed(full, 1.0, i);
    copy(data.get(), data.get()+nocc*nvirt*nocc, buf.get());
    copy(data.get(), data.get()+nocc*nvirt*nocc, buf2.get());

    // using SMITH's symmetrizer (src/smith/prim_op.h)
    SMITH::sort_indices<2,1,0,2,1,-1,1>(data, buf, nocc, nvirt, nocc);
    double* tdata = buf.get();
    double* bdata = buf2.get();
    for (size_t j = 0; j != nocc; ++j) {
      for (size_t k = 0; k != nvirt; ++k) {
        for (size_t l = 0; l != nocc; ++l, ++tdata, ++bdata) {
          const double denom = 1.0 / (-eig[i+nocc]+eig[j]-eig[k+nocc]+eig[l]);
          *tdata *= denom;
          *bdata *= denom;
        }
      }
    }
    ecorr += ddot_(nocc*nvirt*nocc, data, 1, buf, 1);

    // form Gia : TODO distribute
    // Gia(D|ic) = BV(D|ja) G_c(ja|i)
    // BV and gia are DFFullDist 
    const size_t offset = i*nocc;
    gia->set_product(bv, buf, nocc, offset);

    // G(ja|ic) -> G_c(a,ij)
    SMITH::sort_indices<1,2,0,0,1,1,1>(buf, data, nocc, nvirt, nocc);
    // T(jb|ic) -> T_c(b,ij)
    SMITH::sort_indices<1,2,0,0,1,1,1>(buf2, buf, nocc, nvirt, nocc);
    // D_ab = G(ja|ic) T(jb|ic)
    dgemm_("N", "T", nvirt, nvirt, nocc*nocc, 2.0, buf.get(), nvirt, data.get(), nvirt, 1.0, vptr, nbasis);
    // D_ij = - G(ja|kc) T(ia|kc)
    dgemm_("T", "N", nocc, nocc, nvirt*nocc, -2.0, buf.get(), nvirt*nocc, data.get(), nvirt*nocc, 1.0, optr, nbasis);
  }

  time.tick_print("assembly (+ unrelaxed rdm)");
  cout << endl;
  cout << "      MP2 correlation energy: " << fixed << setw(15) << setprecision(10) << ecorr << endl << endl;

  // L''aq = 2 Gia(D|ia) (D|iq)
  shared_ptr<const Matrix> laq = gia->form_2index(half, 2.0);
  const Matrix lai = *laq * *ocmat;

  // Gip = Gia(D|ia) C+_ap
  shared_ptr<DFHalfDist> gip = gia->back_transform(vcmat);
  // Liq = 2 Gip(D) * (D|pq)
  Matrix lia(nocca, nvirt);
  Matrix lif(nocc, max(1lu,ncore));
  shared_ptr<const Matrix> lip = gip->form_2index(geom_->df(), 2.0);
  {
    lia.add_block(ncore, 0, nocc, nvirt, *lip * *vcmat);
    if (ncore)
      lif = *lip * *ccmat; 
  }

  // core-occ density matrix elements
  for (int i = 0; i != ncore; ++i)
    for (int j = ncore; j != nocca; ++j)
      dmp2->element(j,i) = dmp2->element(i,j) = lif[(j-ncore)+nocc*i] / (eig_tm[j]-eig_tm[i]);

  // 2*J_al(d_rs)
  auto dmp2ao_part = make_shared<const Matrix>(*ref_->coeff() * *dmp2 ^ *ref_->coeff());
  const Matrix jai = *vcmat % *geom_->df()->compute_Jop(dmp2ao_part) * *ocmat * 2.0;
  // -1*K_al(d_rs)
  const Matrix kia = *halfjj->compute_Kop_1occ(dmp2ao_part->data(), -1.0) * *vcmat;

  auto grad = make_shared<Matrix>(nbasis, nbasis);
  for (int i = 0; i != nocca; ++i)
    for (int a = 0; a != nvirt; ++a)
      // minus sign is due to the convention in the solvers which solve Ax+B=0..
      grad->element(a+nocca, i) = - (lai[a+nvirt*i] - lia[i+nocca*a] - jai[a+nvirt*i] - kia[i+nocca*a]);

  {
    auto d_unrelaxed = make_shared<Matrix>(*dmp2);
    for (int i = 0; i != nocca; ++i) d_unrelaxed->element(i,i) += 2.0;
    auto dao_unrelaxed = make_shared<Matrix>(*ref_->coeff() * *d_unrelaxed ^ *ref_->coeff());
    Dipole dipole(geom_, dao_unrelaxed, "MP2 unrelaxed");
    dipole.compute();
  }
  time.tick_print("Right hand side of CPHF");
  cout << endl;

  // solving CPHF
  auto cphf = make_shared<CPHF>(grad, ref_->eig(), halfjj, ref_);
  shared_ptr<Matrix> dia = cphf->solve();
  *dmp2 += *dia;

  // total density matrix
  auto dtot = make_shared<Matrix>(*dmp2);
  for (int i = 0; i != nocca; ++i) dtot->element(i,i) += 2.0;

  // computes dipole mements
  auto dtotao = make_shared<Matrix>(*ref_->coeff() * *dtot ^ *ref_->coeff());
  {
    Dipole dipole(geom_, dtotao, "MP2 relaxed");
    dipole.compute();
  }

  ////////////////////////////////////////////////////////////////////////////

  time.tick_print("CPHF solved");

  // one electron matrices
  auto dmp2ao = make_shared<Matrix>(*ref_->coeff() * *dmp2 ^ *ref_->coeff());
  auto d0ao = make_shared<Matrix>(*dtotao - *dmp2ao);
  auto dbarao = make_shared<Matrix>(*dtotao - *d0ao*0.5);

  // size of naux
  shared_ptr<const Matrix> cd0 = geom_->df()->compute_cd(d0ao);
  shared_ptr<const Matrix> cdbar = geom_->df()->compute_cd(dbarao);


  // three-index derivatives (seperable part)...
  vector<const double*> cd = {cd0->data(), cdbar->data()};
  vector<const double*> dd = {dbarao->data(), d0ao->data()};

  shared_ptr<DFHalfDist> sepd = halfjj->apply_density(dbarao->data());
  shared_ptr<DFDist> sep3 = sepd->back_transform(ocmat);
  sep3->scale(-2.0);
  /// mp2 two body part ----------------
  {
    shared_ptr<DFDist> sep32 = gip->back_transform(acmat);
    sep3->daxpy(4.0, sep32);
  }
  sep3->add_direct_product(cd, dd, 1.0);

  // two-index derivatives (seperable part)..
  auto sep2 = make_shared<Matrix>(naux, naux);
  dger_(naux, naux, 2.0, cd0->data(), 1, cdbar->data(), 1, sep2->data(), naux);
  *sep2 -= *halfjj->form_aux_2index(sepd, 2.0);
  *sep2 += *gia->form_aux_2index_apply_J(full, 4.0);

  // energy weighted density
  auto wd = make_shared<Matrix>(nbasis, nbasis);
  for (int i = 0; i != nocca; ++i)
    for (int j = 0; j != nocca; ++j)
      wd->element(j,i) += dtot->element(j,i) * eig_tm[j];
  for (int i = 0; i != nvirt; ++i)
    for (int j = 0; j != nvirt; ++j)
      wd->element(j+nocca,i+nocca) += dmp2->element(j+nocca,i+nocca) * eig_tm[j+nocca];
  for (int i = 0; i != nocca; ++i)
    for (int j = 0; j != nvirt; ++j)
      wd->element(j+nocca,i) += 2.0 * dmp2->element(j+nocca,i) * eig_tm[i];
  // Liq + Laq
  wd->add_block(ncore, 0, nocc, nocca, *lip * *ocmat);
  wd->add_block(nocca, 0, nvirt, nocca, *laq * *ocmat * 2.0);
  wd->add_block(nocca, nocca, nvirt, nvirt, *laq * *vcmat);
  wd->add_block(0, 0, nocca, nocca, (*ocmat % *geom_->df()->compute_Jop(dmp2ao) * *ocmat * 2.0));
  wd->add_block(0, 0, nocca, nocca, (*halfjj->compute_Kop_1occ(dmp2ao->data(), -1.0) * *ocmat));

  wd->symmetrize();
  auto wdao = make_shared<Matrix>(*ref_->coeff() * *wd ^ *ref_->coeff());

  time.tick_print("Density matrices computed");
  cout << endl;

  // gradient evaluation
  shared_ptr<GradFile> gradf = contract_gradient(dtotao, wdao, sep3, sep2);

  time.tick_print("Gradient integrals contracted");
  cout << endl;

  // set proper energy_
  energy_ = ref_->energy() + ecorr;

  return gradf;

}



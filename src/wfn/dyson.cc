//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: dyson.cc
// Copyright (C) 2009 Toru Shiozaki
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

#include <algorithm>
#include <string>

#include <src/mat1e/overlap.h>
#include <src/wfn/dyson.h>
#include <src/util/archive.h>
#include <src/util/io/moldenout.h>

using namespace bagel;
using namespace std;

DysonOrbitals::DysonOrbitals(shared_ptr<const PTree> input) :
  input_(input)
{
  cout << indent << "*** Dyson Orbitals ***" << endl << endl;

  // Where are the wavefunctions of the initial states stored?
  shared_ptr<const PTree> initial_keys = input_->get_child("initial");
  const string iname = initial_keys->get<string>("file", "");  
  if (iname == "") {
    throw runtime_error("You need to specify an archive file for loading the wavefunctions of the initial states.");
  }
  // load wavefunctions for initial states from archives  
  IArchive iarchive(iname);
  shared_ptr<Reference> iptr;
  iarchive >> iptr;
  // Find indices of initial states (defaults to [0])
  const shared_ptr<const PTree> istates = initial_keys->get_child_optional("states");
  if (istates) {
    // state indices are 0-based
    for (auto& state : *istates) {
      int i = lexical_cast<int>(state->data());
      if (! (0 <= i < iptr->nstate()) ) {
	throw runtime_error(format("State %1 does not exist in initial wavefunctions.") % i);
      }
      initial_states_.push_back(i);
    }
  } else {
    initial_states_.push_back(0);
  }
  // extract wavefunctions for selected initial states
  refI_ = shared_ptr<Reference>(iptr)->extract_state(initial_states_, false);

  // Where are the wavefunctions of the final states stored?
  shared_ptr<const PTree> final_keys = input_->get_child("final");
  const string fname = final_keys->get<string>("file", "");
  if (fname == "") {
    throw runtime_error("You need to specify an archive file for loading the wavefunctions of the final states.");
  }  
  // load wavefunctions for final states from archives
  IArchive farchive(fname);
  shared_ptr<Reference> fptr;
  farchive >> fptr;
  // Find indices of initial states (defaults to [0])
  const shared_ptr<const PTree> fstates = final_keys->get_child_optional("states");
  if (fstates) {
    // state indices are 0-based
    for (auto& state : *fstates) {
      int j = lexical_cast<int>(state->data());
      if (! (0 <= j < fptr->nstate()) ) {
	throw runtime_error(format("State %1 does not exist in final wavefunctions.") % j);
      }
      final_states_.push_back(j);
    }
  } else {
    final_states_.push_back(0);
  }
  // extract wavefunctions for selected final states
  refF_ = shared_ptr<Reference>(fptr)->extract_state(final_states_, false);

  // read additional options
  thresh_      = input_->get<double>("thresh", 1.0e-10);
  molden_file_ = input_->get<string>("molden_file", "dyson_orbitals.molden");
  
  // initialize member variables
  geom_     = refF_->geom();
  nao_      = !refF_->coeffB() ? refF_->coeff()->ndim() : refF_->coeffB()->ndim();
  nmo_      = !refF_->coeffB() ? refF_->coeff()->mdim() : refF_->coeffB()->mdim();
  nchan_    = refI_->nstate() * refF_->nstate();
  norms_    = VectorB(nchan_);
  energies_ = VectorB(nchan_);
  coeff_    = Matrix(nao_, nchan_);
  
  consistency_checks();
}

bool DysonOrbitals::consistency_checks()
{
  bool out = true;
  
  auto detI = refI_->ciwfn()->det();
  auto detF = refF_->ciwfn()->det();
  // N electrons in initial, N-1 electrons in final (ionized) wavefunctions
  out &= detI->nelea()+detI->neleb()-1 == detF->nelea()+detF->neleb();
  cout << endl;
  cout << indent << "electrons in initial states : " << detI->nelea() << " (alpha)    " << detI->neleb() << " (beta)" << endl;
  cout << indent << "electrons in final states   : " << detF->nelea() << " (alpha)    " << detF->neleb() << " (beta)" << endl;
  cout << endl;
  if (!out) {
    throw runtime_error("Incorrect number of electrons in initial (N) and final (N-1) states.");
  }

  auto molI = refI_->geom();
  auto molF = refF_->geom();
  // compare number of atoms
  out &= molI->atoms().size() == molF->atoms().size();
  if (!out) {
    throw runtime_error("Number of atoms in initial and final wavefunctions differ.");
  }
  // compare geometries
  auto atomsI = molI->atoms();
  auto atomsF = molF->atoms();
  for (auto i = atomsI.begin(), j = atomsF.begin(); i != atomsI.end(), j != atomsF.end(); ++i, ++j) {
    out &= **i == **j;
  }
  if (!out) {
    throw runtime_error("Initial and final geometries differ.");
  }
  // compare basis sets
  out &= molI->nbasis() == molF->nbasis();
  out &= molI->naux() == molF->naux();
  if (!out) {
    throw runtime_error("Initial and final basis sets differ.");
  }
  
  return out;
}
  
void DysonOrbitals::mo_overlaps()
{
  /*
    overlap between molecular orbitals in initial and final wavefunctions
    (assuming that the geometries and basis sets are the same)
  */
  
  // alpha and beta MO coefficients of initial wavefunction
  auto coeffAi = !refI_->coeffB() ? refI_->coeff() : refI_->coeffA();
  auto coeffBi = !refI_->coeffB() ? refI_->coeff() : refI_->coeffB();

  // alpha and beta MO coefficients of final wavefunction
  auto coeffAf = !refF_->coeffB() ? refF_->coeff() : refF_->coeffA();
  auto coeffBf = !refF_->coeffB() ? refF_->coeff() : refF_->coeffB();

  // overlap between AOs
  Sao_ = Overlap(refI_->geom());
  // overlap between  MOs of initial and MOs of final wavefunction
  SmoA_ = *coeffAi % Sao_  * *coeffAf;
  SmoB_ = *coeffBi % Sao_  * *coeffBf;

  //SmoA_.print("overlap between initial and final MOs (alpha)", 0);
  //SmoB_.print("overlap between initial and final MOs (beta)", 0);
}

VectorB DysonOrbitals::slater_dyson(bitset<nbit__> bita1, bitset<nbit__> bitb1, shared_ptr<const Determinants> det1, int nclosed1,
				    bitset<nbit__> bita2, bitset<nbit__> bitb2, shared_ptr<const Determinants> det2, int nclosed2)
{
  /*
    computes overlap between two Slater determinants composed of different sets of molecular orbitals.
    The occupation numbers in the bra <1| and ket |2> Slater determinants are passed as bit strings.
    The bra wavefunction contains N-1 electron, the ket wavefunction N electrons, so that the overlap
    <1|2> is a wavefunction with 1 electron (called the Dyson orbital).

    This is explained in J. Chem. Phys. **139**, 134104 (2013), see eqns. (21)-(23).
  */
  
  // overlap between occupied alpha MOs
  auto SmoAocc = make_shared<Matrix>(nclosed1+det1->nelea(), nclosed2+det2->nelea());
  // overlap between occupied beta MOs
  auto SmoBocc = make_shared<Matrix>(nclosed1+det1->neleb(), nclosed2+det2->neleb());
  
  // select occupied orbitals in bra and ket and compose overlap matrices
  
  // The closed orbitals are doubly occupied in all determinants.
  for (int i1 = 0; i1 < nclosed1; i1++) {
    for (int i2 = 0; i2 < nclosed2; i2++) {
      SmoAocc->element(i1,i2) = SmoA_.element(i1,i2);
      SmoBocc->element(i1,i2) = SmoB_.element(i1,i2);
    }
  }
  // In the active space we have to check the occupation numbers.
  int a1 = nclosed1;
  int b1 = nclosed1;
  for (int i1 = 0; i1 != det1->norb(); i1++) {
    int a2 = nclosed2;
    int b2 = nclosed2;
    for (int i2 = 0; i2 != det2->norb(); i2++) {
      if (bita1[i1] && bita2[i2]) {
	// SmoAocc[a1,a2] = SmoA_[i1,i2]
	SmoAocc->element(a1,a2) = SmoA_.element(nclosed1+i1,nclosed2+i2);
      }
      if (bitb1[i1] && bitb2[i2]) {
	// SmoBocc[b1,b2] = SmoB_[i1,i2]
	SmoBocc->element(b1,b2) = SmoB_.element(nclosed1+i1,nclosed2+i2);
      }
      if (bita2[i2]) a2++;
      if (bitb2[i2]) b2++;
    }
    assert(a2 == nclosed2+det2->nelea());
    assert(b2 == nclosed2+det2->neleb());
    if (bita1[i1]) a1++;
    if (bitb1[i1]) b1++;
  }
  assert(a1 == nclosed1+det1->nelea());
  assert(b1 == nclosed1+det1->neleb());

  // coefficients of Dyson orbital <bra(N-1 electrons)|ket(N electron)> in the
  // basis of the final MOs
  auto coeff = VectorB(det2->norb());

  assert(det1->nelea()+det1->neleb() == det2->nelea()+det2->neleb()-1);
  //SmoAocc->print("overlap between occupied alpha orbitals", 0);
  //SmoBocc->print("overlap between occupied beta orbitals", 0);
  
  if (det1->nelea() < det2->nelea()) {
    assert(det1->neleb() == det2->neleb());
    // ket contains 1 alpha electron more
    coeff = SmoBocc->det() * minors(SmoAocc);
  } else {
    assert(det1->nelea() == det2->nelea());
    // ket contains 1 beta electron more
    coeff = SmoAocc->det() * minors(SmoBocc);
  }

  return coeff;
}

VectorB DysonOrbitals::minors(shared_ptr<const Matrix> mat)
{
  /*
    `mat` should be an (N-1)xN matrix. This function computes a vector
    of length N containing the determinants of the minors obtained by
    deleting the j-th column, with the appropriate sign from Laplace's expansion rule:

    v[j] = (-1)^j * det(mat[:,column j deleted])
  */

  int n = mat->ndim();
  int m = mat->mdim();
  assert(n == m-1);

  auto v = VectorB(n);
  
  for (int j=0; j<m; j++) {
    // Deleting the j-th column would require to shift the m-j-1 columns to the
    // right by one position to the left. To avoid this, we replace the j-th
    // column with the last column (m-1) and take the submatrix [0:n,0:n],
    // which contains the same columns as mat[0:n,column j deleted] but in
    // different order. The different ordering leads to an additional sign
    // in the determinant.

    auto minor = mat->get_submatrix(0,0,n,n);
    // sign from Laplace's expansion
    int sgn = pow(-1,j);    
    // swap column j with column m-1, unless j==m-1
    if (j != m-1) {
      for (int i=0; i<n; i++) {
        minor->element(i,j) = mat->element(i,m-1);
      }
      // Moving column m-1 to position j envolves m-1-j exchanges
      // of neighbouring columns and thus introduces an additional
      // factor of (-1)^(m-1-j) in the determinant
      sgn *= pow(-1,m-1-j);
    }
    v[j] = sgn * minor->det();
  }

  return v;
}

void DysonOrbitals::ci_dyson()
{
  /*
    Dyson orbitals between CI wavefunctions
  */
  // coefficients of CI vectors for initial and final states
  auto civecI = refI_->ciwfn()->civectors();
  auto civecF = refF_->ciwfn()->civectors();
  // determinant spaces
  auto detI = refI_->ciwfn()->det();
  auto detF = refF_->ciwfn()->det();
  // number of closed orbitals (doubly occupied in all determinants)
  int nclosedI = refI_->nclosed();
  int nclosedF = refF_->nclosed();
  
  // coefficients of Dyson orbital in MO basis
  Matrix coeffMO(nmo_, nchan_);
  
  auto ciI = civecI->begin();
  // loop over initial states
  for (int stI=0; stI<refI_->nstate(); stI++) {
    // loop over determinants definig initial Hilbert space
    for (auto& bitaI : detI->string_bits_a()) {
      for (auto& bitbI : detI->string_bits_b()) {
	// loop over final states
	auto ciF = civecF->begin();
	for (int stF=0; stF<refF_->nstate(); stF++) {
	  // ij enumerates ionization channels I->F
	  int ij = stI * refF_->nstate() + stF;
	  assert(0 <= ij <= nchan_);
	  // loop over determinants definig final Hilbert space
	  for (auto& bitaF : detF->string_bits_a()) {
	    for (auto& bitbF : detF->string_bits_b()) {

	      double cc = *ciI * *ciF;
	      if (cc > thresh_) {

		// Print occupations of Slater determinants between which
		// the Dyson orbital is computed, i.e. <222a|2222>.
		//cout << "<" << print_bit(bitaF, bitbF, detF->norb())
		//     << "|" << print_bit(bitaI, bitbI, detI->norb())
		//     << ">" << endl;

		VectorB incr = cc * slater_dyson(bitaF, bitbF, detF, nclosedF,
						 bitaI, bitbI, detI, nclosedI);

		// add contribution from this determinant pair to Dyson MO
		// for ionization channel ij.
		for (int k=0; k < incr.size(); k++) {
		  coeffMO.element(k,ij) += incr[k];
		}
	      }
	      ++ciF;
	    }
          }
	}
	++ciI;
      }
    }
  }
  //coeffMO.print("Dyson orbitals in MO basis", 0);
  
  // convert coefficients of Dyson orbitals from MO to AO basis
  if (detF->nelea() == detI->nelea()-1) {
    assert(detF->neleb() == detI->neleb());
    // Dyson orbital has alpha spin
    auto coeffAf = !refF_->coeffB() ? refF_->coeff() : refF_->coeffA();
    coeff_ = *coeffAf * coeffMO;
  } else {
    assert(detF->neleb() == detI->neleb()-1);
    assert(detF->nelea() == detI->nelea());
    // Dyson orbital has beta spin
    auto coeffBf = !refF_->coeffB() ? refF_->coeff() : refF_->coeffB();
    coeff_ = *coeffBf * coeffMO;
  }
  //coeff_.print("Dyson orbitals in AO basis", 0);
  
  // compute ionization energies IE(ij) = E[final(j)] - E[initial(i)]
  int ij = 0;
  for(int i=0; i < refI_->nstate(); i++) {
    for(int j=0; j < refF_->nstate(); j++) {
      energies_[ij] = refF_->energy(j) - refI_->energy(i);
      ij++;
    }
  }

  // Dyson orbitals should be orthogonal to each other
  auto Sdyson = coeff_ % Sao_ * coeff_;
  // diagonal elements are the Dyson norms,
  // which are ~1 for Koopmans allowed transitions and
  // ~0 for Koopmans forbitten transitions
  for(int ij = 0; ij < nchan_; ij++) {
    norms_[ij] = Sdyson.element(ij,ij);
  }
}

  
void DysonOrbitals::compute()
{
  mo_overlaps();
  ci_dyson();
}

void DysonOrbitals::print_results()
{
  cout << endl;
  cout << indent << "initial states : ";
  for (int i : initial_states_) cout << setw(3) << i << " ";
  cout << endl;
  cout << indent << "final states   : ";
  for (int f : final_states_) cout << setw(3) << f << " "; 
  cout << endl << endl;   

  // Table with ionization energies and Dyson norms for each ionization channel I -> F
  //     I->F     energy     norm
  cout << indent 
       << "I -> F"
       << "     " << "energy" << "        "
       << "norm" << endl << endl;
  
  int ij = 0;
  for(int i=0; i < refI_->nstate(); i++) {
    for(int j=0; j < refF_->nstate(); j++) {
      cout << indent 
	   << initial_states_[i] << " -> " << final_states_[j]
	   << "     " << setprecision(7) << energies_[ij] << "     "
	   << norms_[ij] << endl;
      ij++;
    }
  }

}

void DysonOrbitals::write_molden()
{
  /*
    save Dyson orbitals to molden file
  */
  MoldenOut mfs(molden_file_);

  // write geometry and AOs
  mfs << geom_;

  // write MO coefficients of Dyson orbitals for all transitions
  stringstream ss;
  if (geom_->spherical())
    ss << "[5D]" << endl << "[7F]" << endl << "[9G]" << endl;
  ss << "[MO]" << endl;

  // ij enumerates ionization channels I->F.
  int ij = 0;
  for(int i=0; i < refI_->nstate(); i++) {
    for(int j=0; j < refF_->nstate(); j++) {
      // ionization energy (in Hartree)
      ss << " Ene=" << setw(12) << setprecision(6) << fixed << energies_[ij] << endl;
      // Spin doesn't matter.
      ss << " Spin= Alpha" << endl;
      // We abuse the symmetry keyword for storing information about the transition, I->F.
      ss << " Sym= " << i << "->" << j << endl;
      // The occupation keyword is abused for storing the dyson norm.
      ss << " Occup= " << setw(12) << norms_[ij] << endl;
      mfs.write_mo_single(ss, coeff_.element_ptr(0, ij));
      
      ij++;
    }
  }
  mfs.ofs() << ss.str();
}

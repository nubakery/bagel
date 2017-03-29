//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: zharrison_io.cc
// Copyright (C) 2016 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
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

#include <map>
#include <src/ci/fci/fci.h>

using namespace std;
using namespace bagel;

// The following code is due to George Booth

// Write integrals to an file in chemists notation suitable for reading into NECI
void FCI::dump_ints() const {

  cout << "" << endl;
  cout << "Writing integrals to FCIDUMP file" << endl;
  cout << setprecision(10) << endl;
  cout << "Number of AO basis functions: " << jop_->coeff()->ndim() << endl;
  cout << "Number of MO basis functions to dump: " << jop_->coeff()->mdim() << endl;

  ofstream fs("FCIDUMP");

  if (fs.is_open()) {

    fs << " &FCI NORB= " << norb_ << ",NELEC= " << det_->nelea() + det_->neleb() << ",ORBSYM= ";
    for (int i = 0; i != norb_; ++i)
      fs << "1, ";
    fs << endl;
    fs << " ISYM= 0 ," << endl;
    fs << " TREL=.FALSE." << endl;
    fs << " &END" << endl;

    fs << setw(20) << setprecision(15);

    cout << "Writing 2e integral block " << endl;

    for (int j = 0; j != norb_; ++j)
      for (int j2 = 0; j2 != norb_; ++j2)
        for (int k = 0; k != norb_; ++k)
          for (int k2 = 0; k2 != norb_; ++k2) {
            const double val = jop_->mo2e(k2, k, j2, j);
            if (abs(val) > 1.0e-9) {
              fs << setw(20) << val << setw(4) << k2+1 << setw(4)
                 << k+1 << setw(4) << j2+1 << setw(4) << j+1 << endl;   // electron 1, electron 2
            }
          }

    cout << "Writing 1e integral block " << endl;

    for (int j = 0; j != norb_; ++j)
      for (int k = 0; k != norb_; ++k) {
        const double val = jop_->mo1e(min(k,j), max(k,j));
        if (abs(val) > 1.0e-9)
          fs << val << setw(4) << k+1 << setw(4) << j+1 << "   0   0" << endl;
      }
    fs << jop_->core_energy()  + geom_->nuclear_repulsion() << "   0   0   0   0" << endl;
    fs.close();
  }
  else throw runtime_error("Unable to open file: ZHarrison::dump_ints");
}


#if 0
std::shared_ptr<Kramers<8,ZRDM<4>>> ZHarrison::read_external_rdm4(const int ist, const int jst, const string& file) const {
  auto out = make_shared<Kramers<8,ZRDM<4>>>();

  map<array<int,4>,double> elem;
  elem.emplace(array<int,4>{{0,1,2,3}},  1.0); elem.emplace(array<int,4>{{0,1,3,2}}, -1.0); elem.emplace(array<int,4>{{0,2,1,3}}, -1.0);
  elem.emplace(array<int,4>{{0,2,3,1}},  1.0); elem.emplace(array<int,4>{{0,3,1,2}},  1.0); elem.emplace(array<int,4>{{0,3,2,1}}, -1.0);
  elem.emplace(array<int,4>{{1,0,2,3}}, -1.0); elem.emplace(array<int,4>{{1,0,3,2}},  1.0); elem.emplace(array<int,4>{{1,2,0,3}},  1.0);
  elem.emplace(array<int,4>{{1,2,3,0}}, -1.0); elem.emplace(array<int,4>{{1,3,0,2}}, -1.0); elem.emplace(array<int,4>{{1,3,2,0}},  1.0);
  elem.emplace(array<int,4>{{2,0,1,3}},  1.0); elem.emplace(array<int,4>{{2,0,3,1}}, -1.0); elem.emplace(array<int,4>{{2,1,0,3}}, -1.0);
  elem.emplace(array<int,4>{{2,1,3,0}},  1.0); elem.emplace(array<int,4>{{2,3,0,1}},  1.0); elem.emplace(array<int,4>{{2,3,1,0}}, -1.0);
  elem.emplace(array<int,4>{{3,0,1,2}}, -1.0); elem.emplace(array<int,4>{{3,0,2,1}},  1.0); elem.emplace(array<int,4>{{3,1,0,2}},  1.0);
  elem.emplace(array<int,4>{{3,1,2,0}}, -1.0); elem.emplace(array<int,4>{{3,2,0,1}}, -1.0); elem.emplace(array<int,4>{{3,2,1,0}},  1.0);

  stringstream ss; ss << file << "_" << ist << "_" << jst << ".rdm4";
  ifstream fs(ss.str()); 
  if (!fs.is_open()) throw runtime_error(ss.str() + " cannot be opened");
  string line;
  while (getline(fs, line)) {
    stringstream ss(line);
    int i, j, k, l, m, n, o, p;
    double re, im;
    // assuming that the 2RDM is dumped as i+ j+ k+ l m n -> i l j m k n
    ss >> i >> j >> k >> o >> l >> m >> n >> p >> re >> im;
    map<int,pair<int,int>> mij{{0,{(i-1)/2,(i-1)%2}}, {1,{(j-1)/2,(j-1)%2}}, {2,{(k-1)/2,(k-1)%2}}, {2,{(o-1)/2,(o-1)%2}}};
    map<int,pair<int,int>> mkl{{0,{(l-1)/2,(l-1)%2}}, {1,{(m-1)/2,(m-1)%2}}, {2,{(n-1)/2,(n-1)%2}}, {2,{(p-1)/2,(p-1)%2}}};
    const complex<double> dat(re, im);
    for (auto& eij : elem) {
      for (auto& ekl : elem) {
        if (mij[eij.first[0]].second > mij[eij.first[1]].second || mij[eij.first[1]].second > mij[eij.first[2]].second || mij[eij.first[2]].second > mij[eij.first[3]].second || 
            mkl[ekl.first[0]].second > mkl[ekl.first[1]].second || mkl[ekl.first[1]].second > mkl[ekl.first[2]].second || mkl[ekl.first[2]].second > mkl[ekl.first[3]].second) continue;

        const KTag<8> t{mij[eij.first[0]].second, mkl[ekl.first[0]].second, mij[eij.first[1]].second, mkl[ekl.first[1]].second,
                        mij[eij.first[2]].second, mkl[ekl.first[2]].second, mij[eij.first[3]].second, mkl[ekl.first[3]].second};
        if (!out->exist(t))
          out->add(t, make_shared<ZRDM<4>>(norb_));
        out->at(t)->element(mij[eij.first[0]].first, mkl[ekl.first[0]].first, mij[eij.first[1]].first, mkl[ekl.first[1]].first,
                            mij[eij.first[2]].first, mkl[ekl.first[2]].first, mij[eij.first[3]].first, mkl[ekl.first[3]].first)
          = eij.second * ekl.second * dat; 

        const KTag<8> t2{mkl[ekl.first[0]].second, mij[eij.first[0]].second, mkl[ekl.first[1]].second, mij[eij.first[1]].second,
                         mkl[ekl.first[2]].second, mij[eij.first[2]].second, mkl[ekl.first[3]].second, mij[eij.first[3]].second};
        if (!out->exist(t2))
          out->add(t2, make_shared<ZRDM<4>>(norb_));
        out->at(t2)->element(mkl[ekl.first[0]].first, mij[eij.first[0]].first, mkl[ekl.first[1]].first, mij[eij.first[1]].first,
                             mkl[ekl.first[2]].first, mij[eij.first[2]].first, mkl[ekl.first[3]].first, mij[eij.first[3]].first)
          = eij.second * ekl.second * conj(dat);
      }
    }
  }
  for (auto& i : elem) {
    for (auto& j : elem) {
      vector<int> perm(8);
      for (int k = 0; k != 4; ++k) {
        perm[k*2]   = j.first[k]*2;
        perm[k*2+1] = i.first[k]*2+1;
      }
      out->emplace_perm(perm, j.second*i.second);
    }
  }
  return out;
}


std::shared_ptr<Kramers<6,ZRDM<3>>> ZHarrison::read_external_rdm3(const int ist, const int jst, const string& file) const {
  auto out = make_shared<Kramers<6,ZRDM<3>>>();

  map<array<int,3>,double> elem;
  elem.emplace(array<int,3>{{0,1,2}},  1.0); elem.emplace(array<int,3>{{0,2,1}}, -1.0); elem.emplace(array<int,3>{{1,0,2}}, -1.0);
  elem.emplace(array<int,3>{{1,2,0}},  1.0); elem.emplace(array<int,3>{{2,0,1}},  1.0); elem.emplace(array<int,3>{{2,1,0}}, -1.0);

  stringstream ss; ss << file << "_" << ist << "_" << jst << ".rdm3";
  ifstream fs(ss.str()); 
  if (!fs.is_open()) throw runtime_error(ss.str() + " cannot be opened");
  string line;
  while (getline(fs, line)) {
    stringstream ss(line);
    int i, j, k, l, m, n;
    double re, im;
    // assuming that the 2RDM is dumped as i+ j+ k+ l m n -> i l j m k n
    ss >> i >> j >> k >> l >> m >> n >> re >> im;
    map<int,pair<int,int>> mij{{0,{(i-1)/2,(i-1)%2}}, {1,{(j-1)/2,(j-1)%2}}, {2,{(k-1)/2,(k-1)%2}}};
    map<int,pair<int,int>> mkl{{0,{(l-1)/2,(l-1)%2}}, {1,{(m-1)/2,(m-1)%2}}, {2,{(n-1)/2,(n-1)%2}}};
    const complex<double> dat(re, im);
    for (auto& eij : elem) {
      for (auto& ekl : elem) {
        if (mij[eij.first[0]].second > mij[eij.first[1]].second || mij[eij.first[1]].second > mij[eij.first[2]].second || 
            mkl[ekl.first[0]].second > mkl[ekl.first[1]].second || mkl[ekl.first[1]].second > mkl[ekl.first[2]].second) continue;

        const KTag<6> t{mij[eij.first[0]].second, mkl[ekl.first[0]].second, mij[eij.first[1]].second, mkl[ekl.first[1]].second,
                        mij[eij.first[2]].second, mkl[ekl.first[2]].second};
        if (!out->exist(t))
          out->add(t, make_shared<ZRDM<3>>(norb_));
        out->at(t)->element(mij[eij.first[0]].first, mkl[ekl.first[0]].first, mij[eij.first[1]].first, mkl[ekl.first[1]].first,
                            mij[eij.first[2]].first, mkl[ekl.first[2]].first)
          = eij.second * ekl.second * dat; 

        const KTag<6> t2{mkl[ekl.first[0]].second, mij[eij.first[0]].second, mkl[ekl.first[1]].second, mij[eij.first[1]].second,
                         mkl[ekl.first[2]].second, mij[eij.first[2]].second};
        if (!out->exist(t2))
          out->add(t2, make_shared<ZRDM<3>>(norb_));
        out->at(t2)->element(mkl[ekl.first[0]].first, mij[eij.first[0]].first, mkl[ekl.first[1]].first, mij[eij.first[1]].first,
                             mkl[ekl.first[2]].first, mij[eij.first[2]].first)
          = eij.second * ekl.second * conj(dat);
      }
    }
  }
  for (auto& i : elem) {
    for (auto& j : elem) {
      vector<int> perm(6);
      for (int k = 0; k != 3; ++k) {
        perm[k*2]   = j.first[k]*2;
        perm[k*2+1] = i.first[k]*2+1;
      }
      out->emplace_perm(perm, j.second*i.second);
    }
  }
  return out;
}
#endif


std::shared_ptr<RDM<2>> FCI::read_external_rdm2(const int ist, const int jst, const string& file) const {
  auto out = make_shared<RDM<2>>(norb_);

  map<array<int,2>,double> elem;
  elem.emplace(array<int,2>{{0,1}},  1.0); elem.emplace(array<int,2>{{1,0}}, -1.0);

  stringstream ss; ss << file << "_" << ist << "_" << jst << ".rdm2";
  ifstream fs(ss.str()); 
  if (!fs.is_open()) throw runtime_error(ss.str() + " cannot be opened");
  string line;
  while (getline(fs, line)) {
    stringstream ss(line);
    int i, j, k, l;
    double dat;
    // assuming that the 2RDM is dumped as i+ j+ k l -> i k j l
    ss >> i >> j >> k >> l >> dat;
    map<int,int> mij{{0,i-1}, {1,j-1}};
    map<int,int> mkl{{0,k-1}, {1,l-1}};
    for (auto& eij : elem) {
      for (auto& ekl : elem) {
        out->element(mij[eij.first[0]], mkl[ekl.first[0]], mij[eij.first[1]], mkl[ekl.first[1]])
          = eij.second * ekl.second * dat; 
        out->element(mkl[ekl.first[0]], mij[eij.first[0]], mkl[ekl.first[1]], mij[eij.first[1]])
          = eij.second * ekl.second * dat;
      }
    }
  }
  return out;
}


std::shared_ptr<RDM<1>> FCI::read_external_rdm1(const int ist, const int jst, const string& file) const {
  auto out = make_shared<RDM<1>>(norb_);

  stringstream ss; ss << file << "_" << ist << "_" << jst << ".rdm1";
  ifstream fs(ss.str()); 
  if (!fs.is_open()) throw runtime_error(ss.str() + " cannot be opened");
  string line;
  while (getline(fs, line)) {
    stringstream ss(line);
    int i, j;
    double dat;
    ss >> i >> j >> dat; 
    out->element(i-1, j-1) = dat; 
    out->element(j-1, i-1) = dat;
  }
  return out;
}


void FCI::read_external_rdm12_av(const string& file) {
  // feed RDM1
  rdm1_av_ = read_external_rdm1(/*TODO*/0, 0, file);
  rdm2_av_ = read_external_rdm2(/*TODO*/0, 0, file);
}

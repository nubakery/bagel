//
// BAGEL - Parallel electron correlation program.
// Filename: reldvec_london.h
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

#ifndef __SRC_LONDON_RELDVEC_LONDON_H
#define __SRC_LONDON_RELDVEC_LONDON_H

#include <numeric>
#include <src/fci/dvec.h>
#include <src/london/relspace_london.h>

namespace bagel {

template <typename DataType>
class RelDvector_London {
  protected:
    using MapType = std::pair<std::pair<int,int>, std::shared_ptr<Dvector<DataType>>>;

    std::map<std::pair<int, int>, std::shared_ptr<Dvector<DataType>>> dvecs_;
    std::shared_ptr<const Space_base> space_;

  private:
    /*
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
      ar & dvecs_ & space_;
    }
    */

  public:
    RelDvector_London() { }

    // make an empty Dvec
    RelDvector_London(std::shared_ptr<const Space_base> space, const size_t ij) : space_(space) {
      for (auto& isp : space->detmap())
        dvecs_.insert(std::make_pair(std::make_pair(isp.second->nelea(), isp.second->neleb()),
                                     std::make_shared<Dvector<DataType>>(isp.second, ij)));
    }

    RelDvector_London(const std::map<std::pair<int,int>, std::shared_ptr<Dvector<DataType>>>& o, std::shared_ptr<const Space_base> space) : dvecs_(o), space_(space) { }

    RelDvector_London(const RelDvector_London<DataType>& o) : space_(o.space_) {
      for (auto& i : o.dvecs_)
        dvecs_.insert(std::make_pair(i.first, i.second->copy()));
    }

    RelDvector_London(RelDvector_London<DataType>&& o) : dvecs_(o.dvecs_), space_(o.space_) { }

    RelDvector_London(std::shared_ptr<const RelDvector_London<DataType>> o) : space_(o->space_) {
      for (auto& i : o->dvecs_)
        dvecs_.insert(std::make_pair(i.first, std::make_shared<Dvector<DataType>>(i.second)));
    }

    // combines (opposite of split())
    RelDvector_London(const std::vector<std::shared_ptr<RelDvector_London<DataType>>>& o) : space_(o.front()->space_) {
      for (auto& isp : space_->detmap())
        dvecs_.insert(std::make_pair(std::make_pair(isp.second->nelea(), isp.second->neleb()), std::make_shared<Dvector<DataType>>(isp.second, o.size())));
      int j = 0;
      for (auto& i : o)
        set_data(j++, i);
    }

    std::shared_ptr<RelDvector_London<DataType>> clone() const { return std::make_shared<RelDvector_London<DataType>>(space_, dvecs_.begin()->second->ij()); }
    std::shared_ptr<RelDvector_London<DataType>> copy() const { return std::make_shared<RelDvector_London<DataType>>(*this); }

    std::shared_ptr<Dvector<DataType>> find(int a, int b) { return dvecs_.at(std::make_pair(a, b)); }
    std::shared_ptr<const Dvector<DataType>> find(int a, int b) const { return dvecs_.at(std::make_pair(a, b)); }

    std::shared_ptr<const Space_base> space() const { return space_; }

    void set_data(const int istate, std::shared_ptr<const RelDvector_London<DataType>> o) {
      assert(space_ == o->space_ || o->dvecs_.begin()->second->ij() == 1);
      auto j = o->dvecs_.begin();
      for (auto& i : dvecs_) {
        *i.second->data(istate) = *j->second->data(0);
        ++j;
      }
    }

    void zero() { std::for_each(dvecs_.begin(), dvecs_.end(), [](MapType i) { i.second->zero(); }); }

    size_t size() const { return std::accumulate(dvecs_.begin(), dvecs_.end(), 0ull, [](size_t i, MapType o) { return i+o.second->size(); }); }
    double norm() const { return std::sqrt(detail::real(dot_product(*this))); }
    double variance() const { return detail::real(dot_product(*this)) / size(); }
    double rms() const { return std::sqrt(variance()); }

    DataType dot_product(const RelDvector_London<DataType>& o) const {
      return std::inner_product(dvecs_.begin(), dvecs_.end(), o.dvecs_.begin(), DataType(0.0), std::plus<DataType>(),
                                [](MapType i, MapType j) { return i.second->dot_product(*j.second); });
    }

    void ax_plus_y(const DataType a, const RelDvector_London<DataType>& o) {
      auto iter = o.dvecs_.begin();
      for (auto& i : dvecs_) {
        assert(i.first == iter->first);
        i.second->ax_plus_y(a, *iter->second);
        ++iter;
      }
    }

    std::vector<std::shared_ptr<const RelDvector_London<DataType>>> split() const {
      const int nstate = dvecs_.begin()->second->ij();
      return split(0, nstate);
    }

    std::vector<std::shared_ptr<const RelDvector_London<DataType>>> split(const int nstart, const int nend) const {
      std::vector<std::shared_ptr<const RelDvector_London<DataType>>> out;
      for (int i = nstart; i != nend; ++i) {
        std::map<std::pair<int, int>, std::shared_ptr<Dvector<DataType>>> tmp;
        // copy construct each of them
        for (auto& j : dvecs_) {
          std::vector<std::shared_ptr<Civector<DataType>>> tmp1 { std::make_shared<Civector<DataType>>(*j.second->data(i)) };
          tmp.insert(std::make_pair(j.first, std::make_shared<Dvector<DataType>>(tmp1)));
        }
        out.push_back(std::make_shared<RelDvector_London<DataType>>(tmp, space_));
      }
      return out;
    }

    std::vector<std::shared_ptr<const RelDvector_London<DataType>>> dvec(const std::vector<int>& conv) const {
      std::vector<std::shared_ptr<const RelDvector_London<DataType>>> sp = split();
      std::vector<std::shared_ptr<const RelDvector_London<DataType>>> out;
      auto c = conv.begin();
      for (auto& i : sp)
        if (*c++ == 0) out.push_back(i);
      return out;
    }


    void project_out(std::shared_ptr<const RelDvector_London<DataType>> o) { ax_plus_y(-dot_product(*o), *o); }
    void scale(const DataType& a) { std::for_each(dvecs_.begin(), dvecs_.end(), [&a](MapType i) { i.second->scale(a); }); }

    double orthog(std::list<std::shared_ptr<const RelDvector_London<DataType>>> c) {
      for (auto& iter : c)
        project_out(iter);
      return normalize();
    }

    double orthog(std::shared_ptr<const RelDvector_London<DataType>> o) {
      return orthog(std::list<std::shared_ptr<const RelDvector_London<DataType>>>{o});
    }

    double normalize() {
      const double norm = this->norm();
      const double scal = (norm*norm<1.0e-60 ? 0.0 : 1.0/norm);
      scale(DataType(scal));
      return norm;
    }

    void print(double thresh) const {
      for (auto& i : dvecs_)
        i.second->print(thresh);
    }

    void synchronize() {
#ifdef HAVE_MPI_H
      for (auto& i : dvecs_)
        i.second->synchronize();
#endif
    }

};

using RelDvec_London = RelDvector_London<double>;
using RelZDvec_London = RelDvector_London<std::complex<double>>;

}

extern template class bagel::RelDvector_London<double>;
extern template class bagel::RelDvector_London<std::complex<double>>;

//#include <src/util/archive.h>
//BOOST_CLASS_EXPORT_KEY(bagel::RelDvector_London<double>)
//BOOST_CLASS_EXPORT_KEY(bagel::RelDvector_London<std::complex<double>>)

#endif

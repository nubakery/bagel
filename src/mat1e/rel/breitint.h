//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: breitint.h
// Copyright (C) 2012 Quantum Simulation Technologies, Inc.
//
// Author: Toru Shiozaki <shiozaki@qsimulate.com>
// Maintainer: QSimulate
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


#ifndef __SRC_REL_BREITINT_H
#define __SRC_REL_BREITINT_H

#include <src/molecule/molecule.h>
#include <src/mat1e/matrix1earray.h>

namespace bagel {

class BreitInt : public Matrix1eArray<6> {
  protected:
    std::vector<std::pair<const int, const int>> index_;

    void init(std::shared_ptr<const Molecule>) override;
    void computebatch(const std::array<std::shared_ptr<const Shell>,2>&, const int, const int, std::shared_ptr<const Molecule>) override;

  public:
    BreitInt(const std::shared_ptr<const Molecule>);

    void print(const std::string name, const int len = 10) const override { Matrix1eArray<6>::print(name.empty() ? "Breit" : name, len); }

    std::pair<const int, const int> index(const int i) const { return index_[i]; }
    std::vector<std::pair<const int, const int>> index() const { return index_; }

    /// returns if block k is not diagonal
    bool not_diagonal(const int k) const { assert(k >= 0); assert(k <= index_.size()); return index_[k].first != index_[k].second; }

};

}

#endif


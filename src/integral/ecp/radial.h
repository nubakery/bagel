//
// BAGEL - Parallel electron correlation program.
// Filename: radial.h
// Copyright (C) 2014 Toru Shiozaki
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
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


#ifndef __SRC_INTEGRAL_ECP_RADIAL_H
#define __SRC_INTEGRAL_ECP_RADIAL_H

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <src/util/constants.h>

namespace bagel {

template<typename T, typename... Value>
class RadialInt {

  protected:
    int ngrid_;
    bool print_intermediate_;
    int max_iter_;
    double thresh_int_;
    std::vector<double> x_, w_, r_;
    double integral_;

  public:
    RadialInt(Value... tail, const bool print = false, const int max_iter = 100, const double thresh_int = 1e-10) :
      print_intermediate_(print),
      max_iter_(max_iter),
      thresh_int_(thresh_int)
    {
      T function(tail...);
      integrate(function);
    }

    ~RadialInt() {}

    void integrate(T function) {
      double previous = 0.0;
      int ngrid = 31;
      for (int iter = 0; iter != max_iter_; ++iter) {
//      transform_Becke(ngrid);
//      transform_Log(ngrid, 3); //TODO: to be checked
        transform_Ahlrichs(ngrid);
        double ans = 0.0;
        int cnt = 0;
        for (auto& it : r_) {
          ans += function.compute(it) * w_[cnt++];
        }
        const double error = ans - previous;
        if (print_intermediate_)
           std::cout << "Iter = " << std::setw(5) << iter << std::setw(10) << "npts = " << std::setw(10) << ngrid
                     << std::setw(10) << "ans = " << std::setw(20) << std::setprecision(10) << ans
                     << std::setw(10) << "err = " << std::setw(20) << std::setprecision(10) << error << std::endl;
        if (fabs(error) < thresh_int_ && iter != 0) {
          if (print_intermediate_) {
            std::cout << "Integration converged..." << std::endl;
            std::cout << "Radial integral = " << ans << std::endl;
          }
          integral_ = ans;
          break;
        } else if (iter == max_iter_-1) {
          std::cout << "Max iteration exceeded..." << std::endl;
        }
        previous = ans;
        x_.clear();
        w_.clear();
        r_.clear();
        ngrid *= 2;
      }
    }

    double integral() { return integral_; }

    void transform_Log(const int ngrid, const int m = 3) { // Mura and Knowles JCP, 104, 9848.
      w_.resize(ngrid);
      r_.resize(ngrid);
      const double alpha = 5.0;
      for (int i = 1; i <= ngrid; ++i) {
        const double x = i / (ngrid + 1.0);
        const double xm = 1.0 - std::pow(x, m);
        r_[i-1] = - alpha * std::log(xm);
        w_[i-1] = std::pow(r_[i-1], 2) * alpha * m * std::pow(x, m-1) / (xm * (ngrid + 1.0));
      }
    }

    void transform_Ahlrichs(const int ngrid) { // Treutler and Ahlrichs JCP, 102, 346.
      GaussChebyshev2nd(ngrid);
      r_.resize(ngrid);
      const double alpha = 1.0;
      for (int i = 0; i != ngrid; ++i) {
        const double exp = 0.6;
        const double prefactor = alpha / std::log(2.0);
        r_[i]  = prefactor * std::pow(1.0 + x_[i], exp) * std::log(2.0 / (1 - x_[i]));
        w_[i] *= prefactor * (exp * std::pow(1.0 + x_[i], exp - 1.0) * std::log(2.0 / (1.0 - x_[i]))
                          + std::pow(1.0 + x_[i], exp) / (1.0 - x_[i]));
      }
    }

    void transform_Becke(const int ngrid) { // Becke JCP, 88, 2547.
      GaussChebyshev2nd(ngrid);
      r_.resize(ngrid);
      const double alpha = 1.0;
      for (int i = 0; i != ngrid; ++i) {
        r_[i] = alpha * (1.0 + x_[i]) / (1.0 - x_[i]);
        w_[i] *= 2.0 * alpha / std::pow(1.0 - x_[i], 2);
      }
    }

    void GaussChebyshev2nd(const int ngrid) {
      x_.resize(ngrid);
      w_.resize(ngrid);
      for (int i = 1; i <= ngrid; ++i) {
        x_[i-1] = std::cos(i * pi__ / (ngrid + 1));
        w_[i-1] = pi__ * std::sin(i * pi__ / (ngrid + 1)) / (ngrid + 1);
      }
    }

};

}

#endif

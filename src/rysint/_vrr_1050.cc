//
// Newint - Parallel electron correlation program.
// Filename: _vrr_1050.cc
// Copyright (C) 2009 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the Newint package (to be renamed).
//
// The Newint package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// The Newint package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the Newint package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//


#include <src/rysint/vrrlist.h>

// returns double array of length 48
void VRRList::_vrr_1050(double* data_, const double* C00, const double* D00, const double* B00, const double* B01, const double* B10) {
#ifdef __GNUC__
  const double C00_[4]__attribute__((aligned(32))) = {C00[0], C00[1], C00[2], C00[3]};
  const double D00_[4]__attribute__((aligned(32))) = {D00[0], D00[1], D00[2], D00[3]};
  const double B00_[4]__attribute__((aligned(32))) = {B00[0], B00[1], B00[2], B00[3]};
  const double B01_[4]__attribute__((aligned(32))) = {B01[0], B01[1], B01[2], B01[3]};
  const double B10_[4]__attribute__((aligned(32))) = {B10[0], B10[1], B10[2], B10[3]};
#else
  const double* C00_ = C00;
  const double* D00_ = D00;
  const double* B00_ = B00;
  const double* B01_ = B01;
  const double* B10_ = B10;
#endif

  for (int t = 0; t != 4; ++t)
    data_[0+t] = 1.0;

  for (int t = 0; t != 4; ++t)
    data_[4+t] = C00_[t];

  for (int t = 0; t != 4; ++t)
    data_[8+t] = D00_[t];

  double cB00_current[4];
  for (int t = 0; t != 4; ++t)
    cB00_current[t] = B00_[t];

  for (int t = 0; t != 4; ++t)
    data_[12+t] = C00_[t] * data_[8+t] + cB00_current[t];

  double B01_current[4];
  for (int t = 0; t != 4; ++t)
    B01_current[t] = B01_[t];

  for (int t = 0; t != 4; ++t)
    data_[16+t] = D00_[t] * data_[8+t] + B01_current[t];

  for (int t = 0; t != 4; ++t)
    cB00_current[t] += B00_[t];

  for (int t = 0; t != 4; ++t)
    data_[20+t] = C00_[t] * data_[16+t] + cB00_current[t] * data_[8+t];

  for (int t = 0; t != 4; ++t)
    B01_current[t] += B01_[t];

  for (int t = 0; t != 4; ++t)
    data_[24+t] = D00_[t] * data_[16+t] + B01_current[t] * data_[8+t];

  for (int t = 0; t != 4; ++t)
    cB00_current[t] += B00_[t];

  for (int t = 0; t != 4; ++t)
    data_[28+t] = C00_[t] * data_[24+t] + cB00_current[t] * data_[16+t];

  for (int t = 0; t != 4; ++t)
    B01_current[t] += B01_[t];

  for (int t = 0; t != 4; ++t)
    data_[32+t] = D00_[t] * data_[24+t] + B01_current[t] * data_[16+t];

  for (int t = 0; t != 4; ++t)
    cB00_current[t] += B00_[t];

  for (int t = 0; t != 4; ++t)
    data_[36+t] = C00_[t] * data_[32+t] + cB00_current[t] * data_[24+t];

  for (int t = 0; t != 4; ++t)
    B01_current[t] += B01_[t];

  for (int t = 0; t != 4; ++t)
    data_[40+t] = D00_[t] * data_[32+t] + B01_current[t] * data_[24+t];

  for (int t = 0; t != 4; ++t)
    cB00_current[t] += B00_[t];

  for (int t = 0; t != 4; ++t)
    data_[44+t] = C00_[t] * data_[40+t] + cB00_current[t] * data_[32+t];
}


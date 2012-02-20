//
// Newint - Parallel electron correlation program.
// Filename: _vrr_1070.cc
// Copyright (C) 2009 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki.toru@gmail.com>
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


#include "vrrlist.h"

// returns double array of length 80
void VRRList::_vrr_1070(double* data_, const double* C00_, const double* D00_, const double* B00_, const double* B01_, const double* B10_) {
  data_[0] = 1.0;
  data_[1] = 1.0;
  data_[2] = 1.0;
  data_[3] = 1.0;
  data_[4] = 1.0;

  data_[5] = C00_[0];
  data_[6] = C00_[1];
  data_[7] = C00_[2];
  data_[8] = C00_[3];
  data_[9] = C00_[4];

  data_[10] = D00_[0];
  data_[11] = D00_[1];
  data_[12] = D00_[2];
  data_[13] = D00_[3];
  data_[14] = D00_[4];

  double cB00_current[5];
  cB00_current[0] = B00_[0];
  cB00_current[1] = B00_[1];
  cB00_current[2] = B00_[2];
  cB00_current[3] = B00_[3];
  cB00_current[4] = B00_[4];

  data_[15] = C00_[0] * data_[10] + cB00_current[0];
  data_[16] = C00_[1] * data_[11] + cB00_current[1];
  data_[17] = C00_[2] * data_[12] + cB00_current[2];
  data_[18] = C00_[3] * data_[13] + cB00_current[3];
  data_[19] = C00_[4] * data_[14] + cB00_current[4];

  double B01_current[5];
  B01_current[0] = B01_[0];
  B01_current[1] = B01_[1];
  B01_current[2] = B01_[2];
  B01_current[3] = B01_[3];
  B01_current[4] = B01_[4];

  data_[20] = D00_[0] * data_[10] + B01_current[0];
  data_[21] = D00_[1] * data_[11] + B01_current[1];
  data_[22] = D00_[2] * data_[12] + B01_current[2];
  data_[23] = D00_[3] * data_[13] + B01_current[3];
  data_[24] = D00_[4] * data_[14] + B01_current[4];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[25] = C00_[0] * data_[20] + cB00_current[0] * data_[10];
  data_[26] = C00_[1] * data_[21] + cB00_current[1] * data_[11];
  data_[27] = C00_[2] * data_[22] + cB00_current[2] * data_[12];
  data_[28] = C00_[3] * data_[23] + cB00_current[3] * data_[13];
  data_[29] = C00_[4] * data_[24] + cB00_current[4] * data_[14];

  B01_current[0] += B01_[0];
  B01_current[1] += B01_[1];
  B01_current[2] += B01_[2];
  B01_current[3] += B01_[3];
  B01_current[4] += B01_[4];

  data_[30] = D00_[0] * data_[20] + B01_current[0] * data_[10];
  data_[31] = D00_[1] * data_[21] + B01_current[1] * data_[11];
  data_[32] = D00_[2] * data_[22] + B01_current[2] * data_[12];
  data_[33] = D00_[3] * data_[23] + B01_current[3] * data_[13];
  data_[34] = D00_[4] * data_[24] + B01_current[4] * data_[14];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[35] = C00_[0] * data_[30] + cB00_current[0] * data_[20];
  data_[36] = C00_[1] * data_[31] + cB00_current[1] * data_[21];
  data_[37] = C00_[2] * data_[32] + cB00_current[2] * data_[22];
  data_[38] = C00_[3] * data_[33] + cB00_current[3] * data_[23];
  data_[39] = C00_[4] * data_[34] + cB00_current[4] * data_[24];

  B01_current[0] += B01_[0];
  B01_current[1] += B01_[1];
  B01_current[2] += B01_[2];
  B01_current[3] += B01_[3];
  B01_current[4] += B01_[4];

  data_[40] = D00_[0] * data_[30] + B01_current[0] * data_[20];
  data_[41] = D00_[1] * data_[31] + B01_current[1] * data_[21];
  data_[42] = D00_[2] * data_[32] + B01_current[2] * data_[22];
  data_[43] = D00_[3] * data_[33] + B01_current[3] * data_[23];
  data_[44] = D00_[4] * data_[34] + B01_current[4] * data_[24];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[45] = C00_[0] * data_[40] + cB00_current[0] * data_[30];
  data_[46] = C00_[1] * data_[41] + cB00_current[1] * data_[31];
  data_[47] = C00_[2] * data_[42] + cB00_current[2] * data_[32];
  data_[48] = C00_[3] * data_[43] + cB00_current[3] * data_[33];
  data_[49] = C00_[4] * data_[44] + cB00_current[4] * data_[34];

  B01_current[0] += B01_[0];
  B01_current[1] += B01_[1];
  B01_current[2] += B01_[2];
  B01_current[3] += B01_[3];
  B01_current[4] += B01_[4];

  data_[50] = D00_[0] * data_[40] + B01_current[0] * data_[30];
  data_[51] = D00_[1] * data_[41] + B01_current[1] * data_[31];
  data_[52] = D00_[2] * data_[42] + B01_current[2] * data_[32];
  data_[53] = D00_[3] * data_[43] + B01_current[3] * data_[33];
  data_[54] = D00_[4] * data_[44] + B01_current[4] * data_[34];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[55] = C00_[0] * data_[50] + cB00_current[0] * data_[40];
  data_[56] = C00_[1] * data_[51] + cB00_current[1] * data_[41];
  data_[57] = C00_[2] * data_[52] + cB00_current[2] * data_[42];
  data_[58] = C00_[3] * data_[53] + cB00_current[3] * data_[43];
  data_[59] = C00_[4] * data_[54] + cB00_current[4] * data_[44];

  B01_current[0] += B01_[0];
  B01_current[1] += B01_[1];
  B01_current[2] += B01_[2];
  B01_current[3] += B01_[3];
  B01_current[4] += B01_[4];

  data_[60] = D00_[0] * data_[50] + B01_current[0] * data_[40];
  data_[61] = D00_[1] * data_[51] + B01_current[1] * data_[41];
  data_[62] = D00_[2] * data_[52] + B01_current[2] * data_[42];
  data_[63] = D00_[3] * data_[53] + B01_current[3] * data_[43];
  data_[64] = D00_[4] * data_[54] + B01_current[4] * data_[44];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[65] = C00_[0] * data_[60] + cB00_current[0] * data_[50];
  data_[66] = C00_[1] * data_[61] + cB00_current[1] * data_[51];
  data_[67] = C00_[2] * data_[62] + cB00_current[2] * data_[52];
  data_[68] = C00_[3] * data_[63] + cB00_current[3] * data_[53];
  data_[69] = C00_[4] * data_[64] + cB00_current[4] * data_[54];

  B01_current[0] += B01_[0];
  B01_current[1] += B01_[1];
  B01_current[2] += B01_[2];
  B01_current[3] += B01_[3];
  B01_current[4] += B01_[4];

  data_[70] = D00_[0] * data_[60] + B01_current[0] * data_[50];
  data_[71] = D00_[1] * data_[61] + B01_current[1] * data_[51];
  data_[72] = D00_[2] * data_[62] + B01_current[2] * data_[52];
  data_[73] = D00_[3] * data_[63] + B01_current[3] * data_[53];
  data_[74] = D00_[4] * data_[64] + B01_current[4] * data_[54];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[75] = C00_[0] * data_[70] + cB00_current[0] * data_[60];
  data_[76] = C00_[1] * data_[71] + cB00_current[1] * data_[61];
  data_[77] = C00_[2] * data_[72] + cB00_current[2] * data_[62];
  data_[78] = C00_[3] * data_[73] + cB00_current[3] * data_[63];
  data_[79] = C00_[4] * data_[74] + cB00_current[4] * data_[64];
}


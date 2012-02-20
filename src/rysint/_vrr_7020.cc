//
// Newint - Parallel electron correlation program.
// Filename: _vrr_7020.cc
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

// returns double array of length 120
void VRRList::_vrr_7020(double* data_, const double* C00_, const double* D00_, const double* B00_, const double* B01_, const double* B10_) {
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

  double B10_current[5];
  B10_current[0] = B10_[0];
  B10_current[1] = B10_[1];
  B10_current[2] = B10_[2];
  B10_current[3] = B10_[3];
  B10_current[4] = B10_[4];

  data_[10] = C00_[0] * data_[5] + B10_current[0];
  data_[11] = C00_[1] * data_[6] + B10_current[1];
  data_[12] = C00_[2] * data_[7] + B10_current[2];
  data_[13] = C00_[3] * data_[8] + B10_current[3];
  data_[14] = C00_[4] * data_[9] + B10_current[4];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[15] = C00_[0] * data_[10] + B10_current[0] * data_[5];
  data_[16] = C00_[1] * data_[11] + B10_current[1] * data_[6];
  data_[17] = C00_[2] * data_[12] + B10_current[2] * data_[7];
  data_[18] = C00_[3] * data_[13] + B10_current[3] * data_[8];
  data_[19] = C00_[4] * data_[14] + B10_current[4] * data_[9];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[20] = C00_[0] * data_[15] + B10_current[0] * data_[10];
  data_[21] = C00_[1] * data_[16] + B10_current[1] * data_[11];
  data_[22] = C00_[2] * data_[17] + B10_current[2] * data_[12];
  data_[23] = C00_[3] * data_[18] + B10_current[3] * data_[13];
  data_[24] = C00_[4] * data_[19] + B10_current[4] * data_[14];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[25] = C00_[0] * data_[20] + B10_current[0] * data_[15];
  data_[26] = C00_[1] * data_[21] + B10_current[1] * data_[16];
  data_[27] = C00_[2] * data_[22] + B10_current[2] * data_[17];
  data_[28] = C00_[3] * data_[23] + B10_current[3] * data_[18];
  data_[29] = C00_[4] * data_[24] + B10_current[4] * data_[19];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[30] = C00_[0] * data_[25] + B10_current[0] * data_[20];
  data_[31] = C00_[1] * data_[26] + B10_current[1] * data_[21];
  data_[32] = C00_[2] * data_[27] + B10_current[2] * data_[22];
  data_[33] = C00_[3] * data_[28] + B10_current[3] * data_[23];
  data_[34] = C00_[4] * data_[29] + B10_current[4] * data_[24];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[35] = C00_[0] * data_[30] + B10_current[0] * data_[25];
  data_[36] = C00_[1] * data_[31] + B10_current[1] * data_[26];
  data_[37] = C00_[2] * data_[32] + B10_current[2] * data_[27];
  data_[38] = C00_[3] * data_[33] + B10_current[3] * data_[28];
  data_[39] = C00_[4] * data_[34] + B10_current[4] * data_[29];

  data_[40] = D00_[0];
  data_[41] = D00_[1];
  data_[42] = D00_[2];
  data_[43] = D00_[3];
  data_[44] = D00_[4];

  double cB00_current[5];
  cB00_current[0] = B00_[0];
  cB00_current[1] = B00_[1];
  cB00_current[2] = B00_[2];
  cB00_current[3] = B00_[3];
  cB00_current[4] = B00_[4];

  data_[45] = C00_[0] * data_[40] + cB00_current[0];
  data_[46] = C00_[1] * data_[41] + cB00_current[1];
  data_[47] = C00_[2] * data_[42] + cB00_current[2];
  data_[48] = C00_[3] * data_[43] + cB00_current[3];
  data_[49] = C00_[4] * data_[44] + cB00_current[4];

  B10_current[0] = B10_[0];
  B10_current[1] = B10_[1];
  B10_current[2] = B10_[2];
  B10_current[3] = B10_[3];
  B10_current[4] = B10_[4];

  data_[50] = C00_[0] * data_[45] + B10_current[0] * data_[40] + cB00_current[0] * data_[5];
  data_[51] = C00_[1] * data_[46] + B10_current[1] * data_[41] + cB00_current[1] * data_[6];
  data_[52] = C00_[2] * data_[47] + B10_current[2] * data_[42] + cB00_current[2] * data_[7];
  data_[53] = C00_[3] * data_[48] + B10_current[3] * data_[43] + cB00_current[3] * data_[8];
  data_[54] = C00_[4] * data_[49] + B10_current[4] * data_[44] + cB00_current[4] * data_[9];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[55] = C00_[0] * data_[50] + B10_current[0] * data_[45] + cB00_current[0] * data_[10];
  data_[56] = C00_[1] * data_[51] + B10_current[1] * data_[46] + cB00_current[1] * data_[11];
  data_[57] = C00_[2] * data_[52] + B10_current[2] * data_[47] + cB00_current[2] * data_[12];
  data_[58] = C00_[3] * data_[53] + B10_current[3] * data_[48] + cB00_current[3] * data_[13];
  data_[59] = C00_[4] * data_[54] + B10_current[4] * data_[49] + cB00_current[4] * data_[14];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[60] = C00_[0] * data_[55] + B10_current[0] * data_[50] + cB00_current[0] * data_[15];
  data_[61] = C00_[1] * data_[56] + B10_current[1] * data_[51] + cB00_current[1] * data_[16];
  data_[62] = C00_[2] * data_[57] + B10_current[2] * data_[52] + cB00_current[2] * data_[17];
  data_[63] = C00_[3] * data_[58] + B10_current[3] * data_[53] + cB00_current[3] * data_[18];
  data_[64] = C00_[4] * data_[59] + B10_current[4] * data_[54] + cB00_current[4] * data_[19];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[65] = C00_[0] * data_[60] + B10_current[0] * data_[55] + cB00_current[0] * data_[20];
  data_[66] = C00_[1] * data_[61] + B10_current[1] * data_[56] + cB00_current[1] * data_[21];
  data_[67] = C00_[2] * data_[62] + B10_current[2] * data_[57] + cB00_current[2] * data_[22];
  data_[68] = C00_[3] * data_[63] + B10_current[3] * data_[58] + cB00_current[3] * data_[23];
  data_[69] = C00_[4] * data_[64] + B10_current[4] * data_[59] + cB00_current[4] * data_[24];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[70] = C00_[0] * data_[65] + B10_current[0] * data_[60] + cB00_current[0] * data_[25];
  data_[71] = C00_[1] * data_[66] + B10_current[1] * data_[61] + cB00_current[1] * data_[26];
  data_[72] = C00_[2] * data_[67] + B10_current[2] * data_[62] + cB00_current[2] * data_[27];
  data_[73] = C00_[3] * data_[68] + B10_current[3] * data_[63] + cB00_current[3] * data_[28];
  data_[74] = C00_[4] * data_[69] + B10_current[4] * data_[64] + cB00_current[4] * data_[29];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[75] = C00_[0] * data_[70] + B10_current[0] * data_[65] + cB00_current[0] * data_[30];
  data_[76] = C00_[1] * data_[71] + B10_current[1] * data_[66] + cB00_current[1] * data_[31];
  data_[77] = C00_[2] * data_[72] + B10_current[2] * data_[67] + cB00_current[2] * data_[32];
  data_[78] = C00_[3] * data_[73] + B10_current[3] * data_[68] + cB00_current[3] * data_[33];
  data_[79] = C00_[4] * data_[74] + B10_current[4] * data_[69] + cB00_current[4] * data_[34];


  data_[80] = D00_[0] * data_[40] + B01_[0];
  data_[81] = D00_[1] * data_[41] + B01_[1];
  data_[82] = D00_[2] * data_[42] + B01_[2];
  data_[83] = D00_[3] * data_[43] + B01_[3];
  data_[84] = D00_[4] * data_[44] + B01_[4];

  cB00_current[0] += B00_[0];
  cB00_current[1] += B00_[1];
  cB00_current[2] += B00_[2];
  cB00_current[3] += B00_[3];
  cB00_current[4] += B00_[4];

  data_[85] = C00_[0] * data_[80] + cB00_current[0] * data_[40];
  data_[86] = C00_[1] * data_[81] + cB00_current[1] * data_[41];
  data_[87] = C00_[2] * data_[82] + cB00_current[2] * data_[42];
  data_[88] = C00_[3] * data_[83] + cB00_current[3] * data_[43];
  data_[89] = C00_[4] * data_[84] + cB00_current[4] * data_[44];

  B10_current[0] = B10_[0];
  B10_current[1] = B10_[1];
  B10_current[2] = B10_[2];
  B10_current[3] = B10_[3];
  B10_current[4] = B10_[4];

  data_[90] = C00_[0] * data_[85] + B10_current[0] * data_[80] + cB00_current[0] * data_[45];
  data_[91] = C00_[1] * data_[86] + B10_current[1] * data_[81] + cB00_current[1] * data_[46];
  data_[92] = C00_[2] * data_[87] + B10_current[2] * data_[82] + cB00_current[2] * data_[47];
  data_[93] = C00_[3] * data_[88] + B10_current[3] * data_[83] + cB00_current[3] * data_[48];
  data_[94] = C00_[4] * data_[89] + B10_current[4] * data_[84] + cB00_current[4] * data_[49];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[95] = C00_[0] * data_[90] + B10_current[0] * data_[85] + cB00_current[0] * data_[50];
  data_[96] = C00_[1] * data_[91] + B10_current[1] * data_[86] + cB00_current[1] * data_[51];
  data_[97] = C00_[2] * data_[92] + B10_current[2] * data_[87] + cB00_current[2] * data_[52];
  data_[98] = C00_[3] * data_[93] + B10_current[3] * data_[88] + cB00_current[3] * data_[53];
  data_[99] = C00_[4] * data_[94] + B10_current[4] * data_[89] + cB00_current[4] * data_[54];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[100] = C00_[0] * data_[95] + B10_current[0] * data_[90] + cB00_current[0] * data_[55];
  data_[101] = C00_[1] * data_[96] + B10_current[1] * data_[91] + cB00_current[1] * data_[56];
  data_[102] = C00_[2] * data_[97] + B10_current[2] * data_[92] + cB00_current[2] * data_[57];
  data_[103] = C00_[3] * data_[98] + B10_current[3] * data_[93] + cB00_current[3] * data_[58];
  data_[104] = C00_[4] * data_[99] + B10_current[4] * data_[94] + cB00_current[4] * data_[59];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[105] = C00_[0] * data_[100] + B10_current[0] * data_[95] + cB00_current[0] * data_[60];
  data_[106] = C00_[1] * data_[101] + B10_current[1] * data_[96] + cB00_current[1] * data_[61];
  data_[107] = C00_[2] * data_[102] + B10_current[2] * data_[97] + cB00_current[2] * data_[62];
  data_[108] = C00_[3] * data_[103] + B10_current[3] * data_[98] + cB00_current[3] * data_[63];
  data_[109] = C00_[4] * data_[104] + B10_current[4] * data_[99] + cB00_current[4] * data_[64];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[110] = C00_[0] * data_[105] + B10_current[0] * data_[100] + cB00_current[0] * data_[65];
  data_[111] = C00_[1] * data_[106] + B10_current[1] * data_[101] + cB00_current[1] * data_[66];
  data_[112] = C00_[2] * data_[107] + B10_current[2] * data_[102] + cB00_current[2] * data_[67];
  data_[113] = C00_[3] * data_[108] + B10_current[3] * data_[103] + cB00_current[3] * data_[68];
  data_[114] = C00_[4] * data_[109] + B10_current[4] * data_[104] + cB00_current[4] * data_[69];

  B10_current[0] += B10_[0];
  B10_current[1] += B10_[1];
  B10_current[2] += B10_[2];
  B10_current[3] += B10_[3];
  B10_current[4] += B10_[4];

  data_[115] = C00_[0] * data_[110] + B10_current[0] * data_[105] + cB00_current[0] * data_[70];
  data_[116] = C00_[1] * data_[111] + B10_current[1] * data_[106] + cB00_current[1] * data_[71];
  data_[117] = C00_[2] * data_[112] + B10_current[2] * data_[107] + cB00_current[2] * data_[72];
  data_[118] = C00_[3] * data_[113] + B10_current[3] * data_[108] + cB00_current[3] * data_[73];
  data_[119] = C00_[4] * data_[114] + B10_current[4] * data_[109] + cB00_current[4] * data_[74];
}


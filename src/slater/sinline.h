//
// Newint - Parallel electron correlation program.
// Filename: sinline.h
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


// input  : x (kappa or lambda)
// return : exp(x^2)erfc(x)

// for t > 0 
// inline static double experfc(const double t)

// else  
// inline static double experfcm(const double t)

inline static double experfc(const double t) {
 static const double x[140] = {
  1.32735090960991231e+00,  -2.78469065276597649e-01,
  4.90341793971706408e-02,  -7.59975102038317526e-03,
  1.06541074275299879e-03,  -1.37503478565861853e-04,
  1.65405454398546059e-05,  -1.87148312206852366e-06,
  2.00570752388497620e-07,  -2.04743547337025683e-08,
  1.99975318559098815e-09,  -1.87582593283834443e-10,
  1.69515203283570203e-11,  -1.46972641527303837e-12,

  6.62854563278903908e-01,  -8.50021377067431971e-02,
  9.95112734146611812e-03,  -1.08108881022082578e-03,
  1.10232436311956763e-04,  -1.06368305182241049e-05,
  9.77501268047226645e-07,  -8.59792286780304571e-08,
  7.26770841603311590e-09,  -5.92354385692786116e-10,
  4.66839410061035340e-11,  -3.56611462647336244e-12,
  2.64588580532857356e-13,  -1.90113345574082215e-14,

  4.27964965112464457e-01,  -3.79384040999995661e-02,
  3.19591781133803663e-03,  -2.57366670789000059e-04,
  1.99058389502245308e-05,  -1.48427718543485026e-06,
  1.07028895479495731e-07,  -7.48282422459248670e-09,
  5.08354848420498209e-10,  -3.36225672578901429e-11,
  2.16857825966003273e-12,  -1.36593333925698789e-13,
  8.40893366749511585e-15,  -5.03549956488522918e-16,

  3.13283546490962572e-01,  -2.09154617343656098e-02,
  1.35330627411546587e-03,  -8.50732056314609726e-05,
  5.20670283713497351e-06,  -3.10801313832967597e-07,
  1.81228802799104260e-08,  -1.03368219353142442e-09,
  5.77410947885029628e-11,  -3.16218554899356205e-12,
  1.69941142526418635e-13,  -8.96855996220606761e-15,
  4.59505854701976242e-16,  -2.09878028663407440e-17,

  2.46333344736393067e-01,  -1.31123758418642926e-02,
  6.83617512355154042e-04,  -3.49474563176521987e-05,
  1.75359887101991021e-06,  -8.64475262290614213e-08,
  4.19023683146868683e-09,  -1.99853037292722755e-10,
  9.38561218739519694e-12,  -4.34272697372586972e-13,
  1.98097584894625275e-14,  -8.91194777334275430e-16,
  3.60415292148607475e-17,  -1.36582393753095995e-18,

  2.02701408503468766e-01,  -8.94731286031756959e-03,
  3.89190966913722353e-04,  -1.66925556162625175e-05,
  7.06329420400032286e-07,  -2.95006741921674294e-08,
  1.21673534854949562e-09,  -4.95775002228964850e-11,
  1.99650159394286004e-12,  -7.94878609276331799e-14,
  3.13030249379456172e-15,  -1.21868402341759322e-16,
  5.14714846846320796e-18,  -1.72244887134647450e-18,

  1.72093332246209429e-01,  -6.47935109295749885e-03,
  2.41320060688580409e-04,  -8.89390780562753275e-06,
  3.24461243544726191e-07,  -1.17200514396100183e-08,
  4.19286313067663935e-10,  -1.48599550286013860e-11,
  5.21859419226803715e-13,  -1.81617755916058296e-14,
  6.28162355005276893e-16,  -2.01530584748016939e-17,
  2.63520429071728278e-18,  -1.30296963119297846e-18,

  1.49465973957517151e-01,  -4.90229398563081595e-03,
  1.59458436179692534e-04,  -5.14484251034294723e-06,
  1.64685027956619755e-07,  -5.23083051583442520e-09,
  1.64890279171026362e-10,  -5.15937568836075181e-12,
  1.60269209806412586e-13,  -4.94301058519324777e-15,
  1.53204137019669324e-16,  -1.75413916748371245e-18,
 -1.28540210382723247e-19,   6.50896948667254211e-19,

  1.32071386891592757e-01,  -3.83554627135039312e-03,
  1.10661237693892336e-04,  -3.17225003601984822e-06,
  9.03638017182006460e-08,  -2.55815192914807016e-09,
  7.19797871491994263e-11,  -2.01322722338673680e-12,
  5.59783584510264175e-14,  -1.54768332955339165e-15,
  4.72146591380715374e-17,  -9.01754066574418887e-19,
 -7.46663216619042236e-19,  -1.07554531770019083e-18,

  1.18288931196140368e-01,  -3.08130634276606750e-03,
  7.98399849349575329e-05,  -2.05795688207633006e-06,
  5.27735893691278839e-08,  -1.34646384617988690e-09,
  3.41823999987884723e-11,  -8.63517908371809292e-13,
  2.17089941802865090e-14,  -5.42996030508804706e-16,
  1.44292061925869674e-17,   8.90701213693067486e-20,
  5.76408611162558504e-19,   2.74350527740376455e-20 };

  const double sqrtpi = 1.772453850905516;

  double rr;
  double tt = t;
  if (tt > 10.0) {
    // see Eq. (52) of Ten-no J. Chem. Phys. 126, 014108 (2007) 
    const double denom1 = 0.5 / (tt * tt);
    const double denom2 = denom1 * denom1;
    const double denom3 = denom2 * denom1;
    const double denom4 = denom2 * denom2;
    const double denom5 = denom3 * denom2;
    const double denom6 = denom3 * denom3;
    const double denom7 = denom4 * denom3;
    const double denom8 = denom4 * denom4;
    const double denom9 = denom5 * denom4;
    rr = 1.0 / (tt * sqrtpi) * (1.0 - 1.0 * denom1
                                    + 3.0 * denom2
                                   - 15.0 * denom3
                                  + 105.0 * denom4
                                  - 945.0 * denom5
                                + 10395.0 * denom6
                               - 135135.0 * denom7
                              + 2027025.0 * denom8
                             - 34459425.0 * denom9); 
  } else  {
    const int it = tt;
    tt = tt - it;
    tt = 2.0 * tt - 1.0 ;
    const double t2 = tt + tt ;
 
    const int j = 14 * it - 1;
    double g = x[j + 14];
    double d = t2 * g + x[j + 13];
    g = t2 * d - g + x[j + 12];
    d = t2 * g - d + x[j + 11];
    g = t2 * d - g + x[j + 10];
    d = t2 * g - d + x[j + 9];
    g = t2 * d - g + x[j + 8];
    d = t2 * g - d + x[j + 7];
    g = t2 * d - g + x[j + 6];
    d = t2 * g - d + x[j + 5];
    g = t2 * d - g + x[j + 4];
    d = t2 * g - d + x[j + 3];
    g = t2 * d - g + x[j + 2];
    rr = tt * g - d + x[j + 1] * 0.5;
  }

  return rr;
}

// input: x < 0 (kappa)
// output: exp(x^2)erfc(x)
inline static double experfcm(const double t) {
 static const double x[84] = {
  2.93926583578230005e+00,   4.25824458043810417e-01,
 -4.95526267962043687e-02,  -4.49293488768379243e-03,
  1.29194104658500171e-03,   1.83638929215046704e-05,
 -2.21111470409748946e-05,   5.23337485225582617e-07,
  2.78184788837837052e-07,  -1.41158092843532278e-08,
 -2.72571297349201315e-09,   2.06344043341805734e-10,
  2.14267149008798270e-11,  -2.24940086579804845e-12,

  3.88570451147277840e+00,   7.21641118603761761e-02,
 -2.35556624125410723e-02,   4.17971927155726727e-03,
 -2.93844713348674267e-04,  -3.26386351389361837e-05,
  8.85374239436867520e-06,  -4.68100847123979754e-07,
 -7.33010934815385173e-08,   1.17524071066379994e-08,
 -7.52477830979747016e-11,  -1.14282754795680042e-10,
  7.87389623256051203e-12,   5.46235673674301230e-13,

  3.99739375866624247e+00,   1.99352065722625859e-03,
 -9.70184077040146093e-04,   3.21911064703697290e-04,
 -7.53210576026188344e-05,   1.23431885233389756e-05,
 -1.29641407899809473e-06,   4.91995219064453734e-08,
  9.34789744808105178e-09,  -1.87221490169452829e-09,
  1.30327583363565665e-10,   4.14304106957651670e-12,
 -1.65011216930129706e-12,   1.23356449450200489e-13,

  3.99998978044626963e+00,   8.53219732676929317e-06,
 -5.10821007543958795e-06,   2.28271062903516679e-06,
 -7.87120654369614487e-07,   2.14347869782272894e-07,
 -4.67111463088835947e-08,   8.16536739393715685e-09,
 -1.13029271944430539e-09,   1.18592042721716148e-10,
 -8.15685873925416626e-12,   9.44501944531836080e-14,
  6.20745218935514132e-14,  -9.06901135436050988e-15,

  3.99999999379367921e+00,   5.42588027652835553e-09,
 -3.66658881181244632e-09,   1.95767942765662002e-09,
 -8.44942713624937319e-10,   3.00701237704745955e-10,
 -8.96563848983259489e-11,   2.26681201526779357e-11,
 -4.90154772392090144e-12,   9.10893262546741798e-13,
 -1.45682470122664603e-13,   1.99423178877656578e-14,
 -2.31332115802038006e-15,   2.57087487985075709e-16,

  3.99999999999944578e+00,   4.98232351075774773e-13,
 -3.63680438524402626e-13,   2.18368293150082724e-13,
 -1.09406793215582497e-13,   4.64416881076737338e-14,
 -1.69262370456413392e-14,   5.33831435952483493e-15,
 -1.52987009908514926e-15,   3.73456814093590329e-16,
 -4.88896504685174825e-17,   1.84738264778802582e-17,
  1.08261097017773357e-17,  -9.41429238002382805e-18 };

  double rr;
  if (t < -6.0) {
    rr = 2.0;
  } else {    
    double tt = -t;
    const int it = tt;
    tt = tt - it;
    tt = 2.0 * tt - 1.0 ;
    const double t2 = tt + tt ;
   
    const int j = 14 * it - 1;
    double g = x[j + 14];
    double d = t2 * g + x[j + 13];
    g = t2 * d - g + x[j + 12];
    d = t2 * g - d + x[j + 11];
    g = t2 * d - g + x[j + 10];
    d = t2 * g - d + x[j + 9];
    g = t2 * d - g + x[j + 8];
    d = t2 * g - d + x[j + 7];
    g = t2 * d - g + x[j + 6];
    d = t2 * g - d + x[j + 5];
    g = t2 * d - g + x[j + 4];
    d = t2 * g - d + x[j + 3];
    g = t2 * d - g + x[j + 2];
    rr = tt * g - d + x[j + 1] * 0.5;
  }
  
  return rr;
}

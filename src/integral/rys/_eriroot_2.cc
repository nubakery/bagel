//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: _eriroot_2.cc
// Copyright (C) 2013 Toru Shiozaki
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

#include <algorithm>
#include <cassert>
#include <src/integral/rys/erirootlist.h>

using namespace std;
using namespace bagel;

void ERIRootList::eriroot2(const double* ta, double* rr, double* ww, const int n) {

  constexpr double ax[2] = {2.752551286084111e-01,2.724744871391588e+00};
  constexpr double aw[2] = {8.049140900055123e-01,8.131283544724531e-02};
  constexpr double x[768] = {  1.932488560368105e-01, -1.780410264696489e-02,  1.104952643536104e-03, -5.209086926321668e-05,  1.557077571175864e-06,
  1.602449123030568e-08, -4.927153298770279e-09,  2.975911263113046e-10, -9.559437574356920e-12, -6.920509303563687e-14,  3.122108790148673e-14, -1.930986828735923e-15,
  1.388011268456905e+00, -4.914458058909676e-02, -1.550226343010855e-03,  5.058551001364932e-05,  6.415273721174869e-06,  5.167111238522261e-08, -2.032819531271784e-08,
 -8.692662249696952e-10,  4.214069230765610e-11,  4.555527177584852e-12,  4.066648720865206e-15, -1.625766004015951e-14,  1.363444667880911e-01, -1.104708305829675e-02,
  6.254041740924089e-04, -2.879941244655954e-05,  1.202153545609479e-06, -3.376605092818612e-08, -2.753574494484826e-10,  7.083422674087998e-11, -3.496096403196590e-12,
  1.698497279397509e-13, -6.166639612185181e-15, -1.270340230655902e-16,  1.172794021789875e+00, -5.749101131746336e-02, -3.914159625521947e-04,  1.311094262638111e-04,
  1.912507248836593e-06, -4.603880499271945e-07, -9.464340504885015e-09,  1.706122273711224e-09,  4.588017590569331e-11, -6.350291253415793e-12, -2.150544744683258e-13,
  2.355947656994740e-14,  1.003680828150822e-01, -7.150270230616452e-03,  3.731874204579854e-04, -1.482452125823011e-05,  5.736938812051325e-07, -2.529301375734063e-08,
  7.225679884318967e-10,  1.098986088926664e-11, -1.313120363923837e-12,  2.487816544821913e-16,  2.831774287832985e-16,  2.066389199685661e-16,  9.463435052338093e-01,
 -5.450607656421128e-02,  1.066975012954916e-03,  9.208063003217851e-05, -5.775803396859316e-06, -1.645204022205787e-07,  2.522098767468352e-08, -3.491682857668640e-11,
 -9.330729376570850e-11,  2.441625837025802e-12,  2.906931624244455e-13, -1.634840955349520e-14,  7.678889115351413e-02, -4.752444733640928e-03,  2.368132458953042e-04,
 -8.727563820441887e-06,  2.429103600918387e-07, -8.640297519365998e-09,  5.190823541878842e-10, -1.967210543378963e-11, -2.374933106584747e-13,  5.060058340221483e-14,
 -5.079129677537847e-16, -1.252498937162531e-16,  7.500851831251477e-01, -4.317893100471359e-02,  1.603183731726211e-03,  1.356919902844394e-06, -4.321300172824227e-06,
  2.154211291117139e-07,  2.938368175460105e-09, -8.414822310152234e-10,  3.113054361352919e-11,  1.264262301099439e-12, -1.620691036484422e-13,  3.550721896467841e-15,
  6.098520039069188e-02, -3.220452249704640e-03,  1.513841239058399e-04, -5.730730632034734e-06,  1.516212610453335e-07, -2.298602854937782e-09,  6.588663666143851e-11,
 -8.588458746131065e-12,  5.411258236389796e-13, -8.712480809592735e-15, -9.312244119793709e-16,  6.244614179269458e-17,  6.018893891329907e-01, -3.114218839994169e-02,
  1.342639919577796e-03, -3.528998586854332e-05, -5.855388582166639e-07,  1.235421619740781e-07, -6.282880760130387e-09,  6.237233918271527e-11,  1.298465523069419e-11,
 -9.523218068860578e-13,  2.240866289814564e-14,  1.199179189592848e-15,  5.014397542779008e-02, -2.246429930399083e-03,  9.578220394692094e-05, -3.638484440655241e-06,
  1.103159257416035e-07, -2.075419855590297e-09, -3.733940802905933e-12,  9.677792848280196e-13,  6.819747415906643e-14, -8.854239394294053e-15,  3.922178010900495e-16,
 -2.450429732234431e-18,  4.960827934111384e-01, -2.211451564863305e-02,  9.208594543883010e-04, -3.198156622384870e-05,  6.532783044508768e-07,  1.618826081494686e-08,
 -2.437619055986126e-09,  1.289071446843064e-10, -3.290312992733884e-12, -6.108138504630751e-14,  1.090488511430627e-14, -5.663268011280682e-16,  4.245247385349755e-02,
 -1.627946228175633e-03,  6.135476585541975e-05, -2.199517527739336e-06,  7.048654514916928e-08, -1.791971626049823e-09,  2.454264415021261e-11,  5.244215562279688e-13,
 -4.048183145679534e-14,  4.813166759523827e-16,  6.844431488850495e-17, -5.308912538355569e-18,  4.201915359206115e-01, -1.609590815746254e-02,  6.030082936822323e-04,
 -2.110910226271790e-05,  6.219685582184542e-07, -1.091240923353079e-08, -2.576334111076833e-10,  3.546869671311549e-11, -1.901704529719196e-12,  6.322077649159639e-14,
 -8.388885025673699e-16, -5.234816124509177e-17,  3.677895825512028e-02, -1.226013304219771e-03,  4.065621690068790e-05, -1.323766781436941e-06,  4.107839242285563e-08,
 -1.146855459159686e-09,  2.551962018365887e-11, -2.822003951181400e-13, -9.546689025746235e-15,  6.945301589685760e-16, -1.962519251635093e-17, -3.433604007309778e-20,
  3.640675079130911e-01, -1.213341374360658e-02,  4.017955934901223e-04, -1.300145360628228e-05,  3.946740422492114e-07, -1.024100754937341e-08,  1.672752998949794e-10,
  2.741989751744423e-12, -4.016902262387328e-13,  2.149337158989020e-14, -7.831920939404686e-16,  1.884682712951901e-17,  3.243852813733616e-02, -9.546730602990390e-04,
  2.805711756191650e-05, -8.197948290940905e-07,  2.352668754597770e-08, -6.457587136225203e-10,  1.609261732393821e-11, -3.248833121738280e-13,  3.354916753432138e-15,
  1.069330043118368e-16, -8.011817290449547e-18,  2.769525276585535e-19,  3.211073513223666e-01, -9.449866996456207e-03,  2.776390503428650e-04, -8.099797878081762e-06,
  2.310798942654462e-07, -6.221523107949931e-09,  1.459157303321663e-10, -2.322644167205828e-12, -1.848513655783906e-14,  3.681654523673125e-15, -1.966725284189541e-16,
  7.358981053895432e-18,  2.901433971180480e-02, -7.640265947056110e-04,  2.011205412431809e-05, -5.285510928314432e-07,  1.380831193383610e-08, -3.547093015347988e-10,
  8.753486423305161e-12, -1.982423177701051e-13,  3.725385411579490e-15, -3.967782712438706e-17, -8.502767935300521e-19,  7.067725689350918e-20,  2.872122126214008e-01,
 -7.563022228290439e-03,  1.990745250493971e-04, -5.229862652833758e-06,  1.364202138725747e-07, -3.485749938760658e-09,  8.462988168485815e-11, -1.825617844219553e-12,
  2.881335235729798e-14,  2.716521701181570e-17, -2.792513970118205e-17,  1.512267802786610e-18,  2.624453096066973e-02, -6.252182004272730e-04,  1.489329258484382e-05,
 -3.546202011138503e-07,  8.428896396371914e-09, -1.992026610312427e-10,  4.636307784330627e-12, -1.041604084650993e-13,  2.171823606887670e-15, -3.859687222691931e-17,
  4.375850057742988e-19,  4.686706434982235e-21,  2.597940533341057e-01, -6.189013299357572e-03,  1.474263318019566e-04, -3.510050753353239e-06,  8.339835342100744e-08,
 -1.968157179821678e-09,  4.559592430148337e-11, -1.010686569651130e-12,  2.028389861490300e-14, -3.179690445153633e-16,  1.302275424564876e-18,  1.755619479015991e-19,
  2.395788129559429e-02, -5.210688814128648e-04,  1.133273152179690e-05, -2.464500750449562e-07,  5.356914154898945e-09, -1.162350286605106e-10,  2.508762381413679e-12,
 -5.341842103196087e-14,  1.103169125849307e-15, -2.137586945140925e-17,  3.623661233206462e-19, -4.349865151744274e-21,  2.371585725712533e-01, -5.158048902708464e-03,
  1.121821803833993e-04, -2.439557105709370e-06,  5.302232934081483e-08, -1.150064401843175e-09,  2.479059690498065e-11, -5.257951736214924e-13,  1.074076257632378e-14,
 -2.020527204740283e-16,  3.131427551759964e-18, -2.339262940588833e-20,  2.203804739683256e-02, -4.409372373225182e-04,  8.822241488593153e-06, -1.765105999408515e-07,
  3.531096818599279e-09, -7.060448951330055e-11,  1.409381429735365e-12, -2.799979190073591e-14,  5.497395670798863e-16, -1.051546985590645e-17,  1.906321563760560e-19,
 -3.095273803723796e-21,  2.181541786725070e-01, -4.364828486681654e-03,  8.733114522802171e-05, -1.747268067514574e-06,  3.495344394794237e-08, -6.988341303497628e-10,
  1.394514000269093e-11, -2.767351199276546e-13,  5.415688294432772e-15, -1.026924352477615e-16,  1.819803816944772e-18, -2.771414579131637e-20,  2.040326753920829e-02,
 -3.779679266675517e-04,  7.001802785332982e-06, -1.297067413344606e-07,  2.402716331790524e-09, -4.450259061566757e-11,  8.238647817477579e-13, -1.522854734506250e-14,
  2.803098287745054e-16, -5.107719255229465e-18,  9.104571097683391e-20, -1.551607337097957e-21,  2.019715267510623e-01, -3.741496726787889e-03,  6.931069613285915e-05,
 -1.283963412900829e-06,  2.378432403948086e-08, -4.405190421840918e-10,  8.154517436157432e-12, -1.506845950297443e-13,  2.771001084690562e-15, -5.035813895253663e-17,
  8.914560070087259e-19, -1.493048262619812e-20,  1.899440841942344e-02, -3.275872058515602e-04,  5.649734429818838e-06, -9.743806784280429e-08,  1.680453043954991e-09,
 -2.898076318128077e-11,  4.997298192335721e-13, -8.613121646532226e-15,  1.482474401898286e-16, -2.542355875626627e-18,  4.322826035078326e-20, -7.214578162010585e-22,
  1.880252592761560e-01, -3.242779026860744e-03,  5.592660437145669e-05, -9.645372989338657e-07,  1.663475380070718e-08, -2.868783890145560e-10,  4.946686482056897e-12,
 -8.525218307410435e-14,  1.466956399108345e-15, -2.513751655690478e-17,  4.265000869221746e-19, -7.079512444880638e-21,  1.776764214960578e-02, -2.866494628462603e-04,
  4.624581686889708e-06, -7.460942308452064e-08,  1.203688935921940e-09, -1.941920530032866e-11,  3.132807033415369e-13, -5.053352460711381e-15,  8.147837461098251e-17,
 -1.312137770880062e-18,  2.106542199406817e-20, -3.356921287884904e-22,  1.758815251446816e-01, -2.837537151757669e-03,  4.577863912837049e-05, -7.385571293919661e-07,
  1.191528976501304e-08, -1.922300896151283e-10,  3.101140990685637e-12, -5.002176244444168e-14,  8.064755109069341e-16, -1.298464998123448e-17,  2.083232658445982e-19,
 -3.314066281539949e-21,  1.668979366516901e-02, -2.529337404416901e-04,  3.833209567751741e-06, -5.809226923679938e-08,  8.803877348870566e-10, -1.334224304041943e-11,
  2.021994706966187e-13, -3.064193654767003e-15,  4.643010767092904e-17, -7.032656966763111e-19,  1.064106441186423e-20, -1.605529748206894e-22,  1.652119251096822e-01,
 -2.503785907768866e-03,  3.794486285827166e-05, -5.750541787518017e-07,  8.714939800443767e-09, -1.320745583717008e-10,  2.001565831630553e-12, -3.033221036034766e-14,
  4.595997258285236e-16, -6.961019184384459e-18,  1.053067608612627e-19, -1.588032689965708e-21,  1.573528836982337e-02, -2.248357280524574e-04,  3.212594734784093e-06,
 -4.590358006060919e-08,  6.558992653379728e-10, -9.371898127896431e-12,  1.339112606938580e-13, -1.913387067130137e-15,  2.733846841888577e-17, -3.905687073360711e-19,
  5.577981751117823e-21, -7.957601017958750e-23,  1.557632967723299e-01, -2.225644259603717e-03,  3.180140937271567e-05, -4.543985969563002e-07,  6.492733326323948e-09,
 -9.277222284062392e-11,  1.325584459071266e-12, -1.894055397069972e-14,  2.706213899313889e-16, -3.866147611223281e-18,  5.521222548401509e-20, -7.875396427248659e-22,
  1.488409271212456e-02, -2.011731319520630e-04,  2.719052467371795e-06, -3.675066464816873e-08,  4.967213214068378e-10, -6.713675863818113e-12,  9.074187256350306e-14,
 -1.226462225057195e-15,  1.657665364485705e-17, -2.240402943456814e-19,  3.027697463244718e-21, -4.089741344817811e-23,  1.473373284185855e-01, -1.991408706239219e-03,
  2.691584459436343e-05, -3.637940753803014e-07,  4.917034164226878e-09, -6.645853902207958e-11,  8.982518839593728e-13, -1.214072084074111e-14,  1.640917363839286e-16,
 -2.217758429705428e-18,  2.997053566397960e-20, -4.048169475948582e-22,  1.412029016263157e-02, -1.810591258348239e-04,  2.321652506404731e-06, -2.976966962621094e-08,
  3.817251827963959e-10, -4.894717154589538e-12,  6.276309412895413e-14, -8.047868502743689e-16,  1.031944777491695e-17, -1.323209052996592e-19,  1.696634338163106e-21,
 -2.174899159774342e-23,  1.397764626501339e-01, -1.792300572313306e-03,  2.298199053346831e-05, -2.946893489145708e-07,  3.778689752727930e-09, -4.845270461326742e-11,
  6.212905740861656e-13, -7.966568021231036e-15,  1.021519712207420e-16, -1.309840261344179e-18,  1.679486692820300e-20, -2.152891962023077e-22,  1.343107500442021e-02,
 -1.638179644106205e-04,  1.998077254031401e-06, -2.437042071196474e-08,  2.972444654924506e-10, -3.625471754972562e-12,  4.421964639557121e-14, -5.393441281115384e-16,
  6.578341526251842e-18, -8.023538861585583e-20,  9.786156815174742e-22, -1.193391476378367e-23,  1.329539359378586e-01, -1.621630669067945e-03,  1.977892574822721e-05,
 -2.412422946813319e-07,  2.942416865982690e-09, -3.588847051573421e-11,  4.377293715299424e-13, -5.338956389903875e-15,  6.511886353107228e-17, -7.942482323624653e-19,
  9.687285102346171e-21, -1.181330677531320e-22,  1.280602755006633e-02, -1.489274360307397e-04,  1.731948577805353e-06, -2.014166063742707e-08,  2.342370312805693e-10,
 -2.724054772417597e-12,  3.167933920719568e-14, -3.684142173526208e-16,  4.284464962784043e-18, -4.982606406800940e-20,  5.794496297895562e-22, -6.737721612313732e-24,
  1.267666040097041e-01, -1.474229634106284e-03,  1.714452344175013e-05, -1.993818854549869e-07,  2.318707567388884e-09, -2.696536230801519e-11,  3.135931287890099e-13,
 -3.646924770001198e-15,  4.241183017422726e-17, -4.932271533826078e-19,  5.735958394241826e-21, -6.669649655878112e-23,  1.223658302311098e-02, -1.359788231721986e-04,
  1.511062386972867e-06, -1.679165537731399e-08,  1.865969881432109e-10, -2.073555894094784e-12,  2.304235499528148e-14, -2.560577808913849e-16,  2.845437687785582e-18,
 -3.161987340368601e-20,  3.513750715575882e-22, -3.904157626006708e-24,  1.211296843192051e-01, -1.346051581053048e-03,  1.495797557005522e-05, -1.662202521087114e-07,
  1.847119757695689e-09, -2.052608725758214e-11,  2.280957993780295e-13, -2.534710718802859e-15,  2.816692921529966e-17, -3.130044735979580e-19,  3.478254400949428e-21,
 -3.864716625201218e-23,  1.171563629263745e-02, -1.246485371384278e-04,  1.326198374774906e-06, -1.411009041607808e-08,  1.501243368534994e-10, -1.597248199729142e-12,
  1.699392559874134e-14, -1.808069071336980e-16,  1.923695456576969e-18, -2.046716112505319e-20,  2.177603661207003e-22, -2.316598157874376e-24,  1.159728433211748e-01,
 -1.233893312039153e-03,  1.312801050568822e-05, -1.396754955682406e-07,  1.486077730796708e-09, -1.581112716244360e-11,  1.682225208784844e-13, -1.789803864375873e-15,
  1.904262184949950e-17, -2.026040074690462e-19,  2.155605365736960e-21, -2.293195624562682e-23,  1.123724356957945e-02, -1.146776925712685e-04,  1.170302404859458e-06,
 -1.194310495887066e-08,  1.218811099304280e-10, -1.243814318718180e-12,  1.269330464969279e-14, -1.295370060194199e-16,  1.321943841171113e-18, -1.349062759132930e-20,
  1.376737950193577e-22, -1.404834421369081e-24,  1.112372435695795e-01, -1.135192126215072e-03,  1.158479949761275e-05, -1.182245509818261e-07,  1.206498606879318e-09,
 -1.231249242484038e-11,  1.256507623309785e-13, -1.282284165181623e-15,  1.308589496320630e-17, -1.335434456855486e-19,  1.362830068243994e-21, -1.390642692329292e-23,
  1.079639439992907e-02, -1.058571795606443e-04,  1.037915256653472e-06, -1.017661800989965e-08,  9.978035630126591e-11, -9.783328306037407e-13,  9.592420421311967e-15,
 -9.405237834845660e-17,  9.221707850502693e-19, -9.041759182112546e-21,  8.865321815718216e-23, -8.691491646520789e-25,  1.068732866829813e-01, -1.047878048870732e-03,
  1.027430183336906e-05, -1.007381329124417e-07,  9.877237000887266e-10, -9.684496620201859e-12,  9.495517296744301e-14, -9.310225638364479e-16,  9.128549683176692e-18,
 -8.950418864487708e-20,  8.775763872622534e-22, -8.603689723734170e-24,  1.038883535512736e-02, -9.801660492821507e-05,  9.247672634365293e-07, -8.724996057047774e-09,
  8.231861053624187e-11, -7.766597940342410e-13,  7.327631403628786e-15, -6.913475166264224e-17,  6.522726954853049e-19, -6.154063750937263e-21,  5.806237261342894e-23,
 -5.477582273257973e-25,  1.028388680593322e-01, -9.702643614292631e-04,  9.154252169681542e-06, -8.636855698036325e-08,  8.148702369785840e-10, -7.688139368409055e-12,
  7.253607294230596e-14, -6.843634884477143e-16,  6.456834031572967e-18, -6.091895082169080e-20,  5.747582352996296e-22, -5.422247451589788e-24,  1.001093224026070e-02,
 -9.101599751648099e-05,  8.274865522118798e-07, -7.523226825784265e-09,  6.839862438961731e-11, -6.218570736638799e-13,  5.653713411879685e-15, -5.140164307414971e-17,
  4.673262895034574e-19, -4.248771980512927e-21,  3.862839223513786e-23, -3.511672014197887e-25,  9.909801287773549e-02, -9.009654922740038e-04,  8.191272404927432e-06,
 -7.447226801370094e-08,  6.770765796737803e-10, -6.155750415153062e-12,  5.596599308146737e-14, -5.088238103153419e-16,  4.626053352856257e-18, -4.205850667371036e-20,
  3.823816622843908e-22, -3.476196922336765e-24,  9.659561346175771e-03, -8.473951519703517e-05,  7.433862862387053e-07, -6.521434177229151e-09,  5.720996541800088e-11,
 -5.018804229531414e-13,  4.402798657598161e-15, -3.862401307721601e-17,  3.388332063767496e-19, -2.972449846480237e-21,  2.607612793126584e-23, -2.287379642041367e-25,
  9.561979960536370e-02, -8.388347225522896e-04,  7.358765597328303e-06, -6.455554313686268e-08,  5.663202740427514e-10, -4.968104011020511e-12,  4.358321359064315e-14,
 -3.823383131015982e-16,  3.354102958951519e-18, -2.942422005215002e-20,  2.581270554529908e-22, -2.264272415154694e-24,  9.332022844690794e-03, -7.909061993496337e-05,
  6.703076348827871e-07, -5.680981205503606e-09,  4.814736663849681e-11, -4.080578390183801e-13,  3.458365672094985e-15, -2.931028883232753e-17,  2.484101199494101e-19,
 -2.105321719825959e-21,  1.784299094552023e-23, -1.512117876585392e-25,  9.237750269843076e-02, -7.829164242369279e-04,  6.635361526723212e-06, -5.623591641116822e-08,
  4.766097946385220e-10, -4.039356177367483e-12,  3.423429084165514e-14, -2.901419478672335e-16,  2.459006681386206e-18, -2.084053651506993e-20,  1.766274013306277e-22,
 -1.496842383997692e-24,  9.025971238671529e-03, -7.398834214134200e-05,  6.065025721963198e-07, -4.971666609018578e-09,  4.075410394670091e-11, -3.340724789320433e-13,
  2.738483008380186e-15, -2.244809034003782e-17,  1.840131044714853e-19, -1.508405485913848e-21,  1.236481013778915e-23, -1.013509027665288e-25,  8.934790412892142e-02,
 -7.324090810282093e-04,  6.003756520114598e-06, -4.921442577175016e-08,  4.034240389210311e-10, -3.306976615640595e-12,  2.710818712152750e-14, -2.222131857661745e-16,
  1.821541946238600e-18, -1.493167496097630e-20,  1.223990018968668e-22, -1.003270507328115e-24,  8.739359072680490e-03, -6.936436204897169e-05,  5.505454899434740e-07,
 -4.369683906025244e-09,  3.468221570671022e-11, -2.752730202448261e-13,  2.184844137857305e-15, -1.734112519448458e-17,  1.376366477590917e-19, -1.092423161351629e-21,
  8.670571233397532e-24, -6.881405740759285e-26,  8.651073617746238e-02, -6.866363969521683e-04,  5.449838510821527e-06, -4.325541134415335e-08,  3.433185417947118e-10,
 -2.724921980333425e-12,  2.162772729980937e-14, -1.716594425568408e-16,  1.362462352629370e-18, -1.081387446377723e-20,  8.582980676753968e-23, -6.811889425961560e-25,
  };
  constexpr double w[768] = {  1.114730883302197e+00, -8.666854230455823e-02,  7.463109340274397e-03, -6.009650759222781e-04,  4.397003731169806e-05,
 -2.933649212339785e-06,  1.817049815028525e-07, -1.050127540210960e-08,  5.675970686803894e-10, -2.887272331169160e-11,  1.378170808509073e-12, -6.118239130607376e-14,
  4.306311079182445e-01, -1.113534030291854e-01,  1.865937449751453e-02, -2.283884895051518e-03,  2.230976393329356e-04, -1.817936711010214e-05,  1.269705826576588e-06,
 -7.761172866006901e-08,  4.217060695276920e-09, -2.059981296551100e-10,  9.137294442437935e-12, -3.708593522630232e-13,  8.542716376142342e-01, -4.714985036665221e-02,
  3.098816322858472e-03, -2.023190089284534e-04,  1.267773131546505e-05, -7.283287918948486e-07,  3.904995012386475e-08, -2.023522032656099e-09,  9.890277542388500e-11,
 -4.493380193350613e-12,  2.004850082811989e-13, -8.724261486577012e-15,  1.695487216672346e-01, -3.069533851487885e-02,  4.525306041702311e-03, -4.999206367962720e-04,
  4.509742169497154e-05, -3.482881169110718e-06,  2.339786558872332e-07, -1.383945465085859e-08,  7.336979449228628e-10, -3.528927949296989e-11,  1.542046843438215e-12,
 -6.158820169734835e-14,  7.036107222127798e-01, -2.947334532610372e-02,  1.531845358289263e-03, -7.940606063394858e-05,  4.261884768182252e-06, -2.219255114928610e-07,
  1.016063325770815e-08, -4.343054116487171e-10,  2.034982453756598e-11, -9.302479325421991e-13,  3.174128061236276e-14, -9.767859575897795e-16,  9.339718749245124e-02,
 -1.003634773174497e-02,  1.274154577294331e-03, -1.262345559490468e-04,  1.014859857210265e-05, -7.153508012234219e-07,  4.578194400730766e-08, -2.621667714834087e-09,
  1.326680656544901e-10, -6.116558772453417e-12,  2.679618673315817e-13, -1.083067635229739e-14,  6.054722909095990e-01, -2.013838461658663e-02,  8.757363583445695e-04,
 -3.660770972460663e-05,  1.552948494252827e-06, -7.406527687440257e-08,  3.497794129201062e-09, -1.283732360813108e-10,  3.434390183322821e-12, -1.373660224254089e-13,
  1.037893447568148e-14, -4.594005042940592e-16,  6.687866186536441e-02, -3.937526794682184e-03,  4.029304146427927e-04, -3.697066405514273e-05,  2.708390831619308e-06,
 -1.655210690666312e-07,  9.309626187982828e-09, -5.150824459830753e-10,  2.677900673251189e-11, -1.186044159808531e-12,  4.371649445299281e-14, -1.604937136753898e-15,
  5.366271023512934e-01, -1.455550532960970e-02,  5.485321673062493e-04, -2.008628586328820e-05,  6.722219977122438e-07, -2.344697100462722e-08,  1.061069818126129e-09,
 -5.240228661237809e-11,  1.887012094512723e-12, -2.527444421553817e-14, -9.899380859068534e-16, -2.680050083249383e-18,  5.555037637013399e-02, -1.943435453877605e-03,
  1.392592264676000e-04, -1.154946371763860e-05,  8.325776583894936e-07, -4.827557744203338e-08,  2.292213213810652e-09, -9.904489451627941e-11,  4.650859249857770e-12,
 -2.427021215290931e-13,  1.138043153348308e-14, -3.774034879685623e-16,  4.858750287385987e-01, -1.097721801749982e-02,  3.599413154248221e-04, -1.208773995024652e-05,
  3.699778279502276e-07, -9.817620777466638e-09,  2.634237426847439e-10, -1.130085824331746e-11,  6.567379168134950e-13, -2.995637202279618e-14,  7.088373648554538e-16,
  1.298944115088250e-17,  4.936987646289186e-02, -1.214967128561374e-03,  5.639125064749796e-05, -3.681882427346172e-06,  2.543547837013943e-07, -1.536193643123718e-08,
  7.535770916448059e-10, -2.927333031097327e-11,  9.239175178854579e-13, -2.962484161101365e-14,  1.449565478008243e-15, -8.771518407086902e-17,  4.469312681814895e-01,
 -8.590354935025336e-03,  2.448244426955246e-04, -7.471039573484325e-06,  2.199984647884219e-07, -5.712634458534110e-09,  1.189740185781591e-10, -2.042653384432902e-12,
  7.078551453989074e-14, -5.531381152749725e-15,  3.382202007787695e-16, -1.321026021469445e-17,  4.520593652178299e-02, -8.895232481266243e-04,  2.903242517081573e-05,
 -1.315837275064763e-06,  7.567930022743268e-08, -4.490240727167696e-09,  2.373520019861317e-10, -1.042305138398225e-11,  3.619843694547323e-13, -9.249411088596437e-15,
  1.546246850315560e-16, -2.717153521373780e-18,  4.159934390857044e-01, -6.938288734876401e-03,  1.729783130888321e-04, -4.726420570083928e-06,  1.304699819911434e-07,
 -3.402348509102556e-09,  7.667415193477292e-11, -1.267832674266192e-12,  8.753094036516512e-15,  3.418728980340030e-17,  2.231011942662416e-17, -2.329501114470113e-18,
  4.203445266204390e-02, -7.050630690852207e-04,  1.832436153600776e-05, -5.931288925957885e-07,  2.480239367517664e-08, -1.255494156737016e-09,  6.534793367897532e-11,
 -3.100283191443342e-12,  1.258654740199164e-13, -4.164048653269488e-15,  1.029852693187269e-16, -1.403171315115697e-18,  3.906927594937402e-01, -5.750422024496354e-03,
  1.268331964652683e-04, -3.094747628822849e-06,  7.812876448263473e-08, -1.952640530807278e-09,  4.574692947921067e-11, -9.180604750405756e-13,  1.262139246787860e-14,
  1.547664108767978e-17, -6.582016313780994e-18,  1.073879789952587e-19,  3.946987249177323e-02, -5.816654882538401e-04,  1.297096034788360e-05, -3.348018291664808e-07,
  1.020244578662818e-08, -3.869181884413207e-10,  1.732945532794058e-11, -8.022077924779116e-13,  3.461052293816711e-14, -1.315143120655895e-15,  4.225581051632526e-17,
 -1.078622242356907e-18,  3.695117293172931e-01, -4.865673842518420e-03,  9.607915730782977e-05, -2.105383680439089e-06,  4.820543033080183e-08, -1.118551317361930e-09,
  2.548677728721044e-11, -5.438845463568846e-13,  9.957993124192317e-15, -1.219121277522678e-16, -6.016867230027041e-19,  9.057652106712613e-20,  3.732859099019602e-02,
 -4.916649407110612e-04,  9.734137304534393e-06, -2.167195042398927e-07,  5.300784962518608e-09, -1.495069998959149e-10,  5.117038545486775e-12, -2.040012452932553e-13,
  8.476538252601022e-15, -3.349439881243243e-16,  1.194968557824092e-17, -3.719720997945145e-19,  3.514428041828184e-01, -4.186494654658350e-03,  7.479898449394046e-05,
 -1.484412502951798e-06,  3.088648797344428e-08, -6.576735253235227e-10,  1.406106599998854e-11, -2.943734165999235e-13,  5.789149066669541e-15, -9.861392133494914e-17,
  1.145519420674032e-18,  5.088366377096937e-21,  3.550298766706304e-02, -4.229442779409774e-04,  7.561083040505693e-06, -1.506617852277930e-07,  3.197035045427778e-09,
 -7.309581812441992e-11,  1.896556714139952e-12, -5.857442312432043e-14,  2.090034069091771e-15, -7.846469302604814e-17,  2.852150370809248e-18, -9.549833116743613e-20,
  3.357914711555576e-01, -3.651846512581338e-03,  5.956963072741935e-05, -1.079585533523075e-06,  2.053545876540684e-08, -4.011471350535057e-10,  7.941440884837305e-12,
 -1.571495948770523e-13,  3.044544536011295e-15, -5.569486947320719e-17,  8.951528385906306e-19, -1.027754874505573e-20,  3.392183617459151e-02, -3.689151362875956e-04,
  6.018568531456471e-06, -1.091801601669331e-07,  2.087750210052922e-09, -4.169077815227478e-11,  8.873263849220280e-13, -2.114839500628227e-14,  5.905257169410325e-16,
 -1.894895655749329e-17,  6.459048887872045e-19, -2.164649505201158e-20,  3.220623089773352e-01, -3.222073089918405e-03,  4.835113771768051e-05, -8.061655669954866e-07,
  1.411191118263486e-08, -2.539729886241632e-10,  4.648004156391076e-12, -8.576091586197224e-14,  1.578351238054503e-15, -2.847291357027399e-17,  4.880210420907242e-19,
 -7.468881297062592e-21,  3.253490159043085e-02, -3.254960872913211e-04,  4.884590483005057e-06, -8.145915100164254e-08,  1.427815988361375e-09, -2.585485872505962e-11,
  4.842264751274728e-13, -9.589374916071670e-15,  2.101294802283969e-16, -5.319991349593597e-18,  1.541485427742780e-19, -4.784186485805917e-21,  3.098913213626154e-01,
 -2.870471831394250e-03,  3.988189772839027e-05, -6.156743559267747e-07,  9.979386871581180e-09, -1.663562673028727e-10,  2.823190150287408e-12, -4.845894898169092e-14,
  8.361139021391574e-16, -1.437686633451326e-17,  2.427672454266508e-19, -3.919527100033873e-21,  3.130538093488904e-02, -2.899766382415437e-04,  4.028911408358261e-06,
 -6.219897835994075e-08,  1.008488149488059e-09, -1.683833345765178e-11,  2.876667148522871e-13, -5.052949391256202e-15,  9.322508992572141e-17, -1.882213631139092e-18,
  4.335129209814397e-20, -1.137395218977203e-21,  2.990042794328627e-01, -2.578485657761212e-03,  3.335281488979094e-05, -4.793521911092248e-07,  7.233737718982326e-09,
 -1.122772769758538e-10,  1.774736640952139e-12, -2.840385993028881e-14,  4.582968670210512e-16, -7.420113532841541e-18,  1.197003625839537e-19, -1.899965951206736e-21,
  3.020556616273437e-02, -2.604799629762891e-04,  3.369321952929698e-06, -4.842492387444112e-08,  7.308149066537240e-10, -1.134767293258441e-11,  1.796903765666523e-13,
 -2.895562299272294e-15,  4.777064721009187e-17, -8.228588785541082e-19,  1.535166341540983e-20, -3.226208759818323e-22,  2.891901212605841e-01, -2.332861324508444e-03,
  2.822774753439203e-05, -3.795059510534727e-07,  5.357334761735716e-09, -7.778751540380403e-11,  1.150337375479742e-12, -1.723007281564069e-14,  2.604417730192533e-16,
 -3.960618017441114e-18,  6.037367451152184e-20, -9.169269094478593e-22,  2.921413482456649e-02, -2.356668535079081e-04,  2.851582117258357e-06, -3.833796847114918e-08,
  5.412101047090558e-10, -7.858994801722961e-12,  1.162731995133211e-13, -1.744859034411473e-15,  2.655238775830810e-17, -4.122917509714871e-19,  6.647757796592045e-21,
 -1.149357315557861e-22,  2.802833901602156e-01, -2.123907677142670e-03,  2.414108874341667e-05, -3.048831821875577e-07,  4.042950651535083e-09, -5.514380769968190e-11,
  7.660554069962335e-13, -1.077983367996411e-14,  1.531311541618932e-16, -2.190478839931539e-18,  3.148074851731312e-20, -4.531208589412036e-22,  2.831437226206935e-02,
 -2.145582465267867e-04,  2.438745287863413e-06, -3.079946873855360e-08,  4.084224311821698e-10, -5.570791851573801e-12,  7.739774462303827e-14, -1.089668872435381e-15,
  1.550857801931087e-17, -2.232709889702641e-19,  3.270577562346907e-21, -4.948848515515782e-23,  2.721522953333084e-01, -1.944391477967617e-03,  2.083719642350300e-05,
 -2.481135615306796e-07,  3.102060451985983e-09, -3.989182846193282e-11,  5.224990436057949e-13, -6.932452541451057e-15,  9.286001442839711e-17, -1.252916455005850e-18,
  1.699799509185516e-20, -2.314250001635822e-22,  2.749296487900226e-02, -1.964234274218454e-04,  2.104984315009179e-06, -2.506456161066263e-08,  3.133719723831192e-10,
 -4.029914306312210e-12,  5.278476301386512e-14, -7.004282372995554e-16,  9.387009114375580e-18, -1.268892119903597e-19,  1.731765206609406e-21, -2.398479011626417e-23,
  2.646903843853113e-01, -1.788816110900864e-03,  1.813334305463270e-05, -2.042423952348974e-07,  2.415474991270072e-09, -2.938280739311448e-11,  3.640429105584519e-13,
 -4.568931775012639e-15,  5.789333997117299e-17, -7.389798374157849e-19,  9.487112264390710e-21, -1.223174410141328e-22,  2.673915879626350e-02, -1.807071237591073e-04,
  1.831839645761560e-06, -2.063267214082090e-08,  2.440125616342246e-10, -2.968269612727820e-12,  3.677605743417450e-14, -4.615727820715233e-16,  5.849397094631615e-18,
 -7.470261155763160e-20,  9.607227541892243e-22, -1.245388044720719e-23,  2.578106033065695e-01, -1.652937771602913e-03,  1.589635455607361e-05, -1.698613535345674e-07,
  1.905813166902333e-09, -2.199379727381007e-11,  2.585168341469372e-13, -3.078087674929078e-15,  3.700223991408830e-17, -4.481011939912180e-19,  5.458296320598307e-21,
 -6.678829166331156e-23,  2.604415977248081e-02, -1.669806240154460e-04,  1.605857915174959e-06, -1.715948136293628e-08,  1.925262319509870e-10, -2.221825220760679e-12,
  2.611554294488158e-14, -3.109526248400933e-16,  3.738138179145458e-18, -4.527531347729305e-20,  5.517665629359347e-22, -6.762397614331675e-24,  2.514409747792871e-01,
 -1.533433275686674e-03,  1.402747778547586e-05, -1.425773178022687e-07,  1.521633467094015e-09, -1.670336028129216e-11,  1.867524948176315e-13, -2.115108768219861e-15,
  2.418547647117507e-17, -2.785997006554957e-19,  3.228121677802649e-21, -3.757677496429109e-23,  2.540069662190091e-02, -1.549082183597338e-04,  1.417063022140675e-06,
 -1.440323399798954e-08,  1.537161964477536e-10, -1.687382125464843e-12,  1.886583911996575e-14, -2.136697788695156e-16,  2.443252850413888e-18, -2.814550908497101e-20,
  3.261636008793521e-22, -3.798437251889568e-24,  2.455213981569562e-01, -1.427667181260237e-03,  1.245233993638674e-05, -1.206788676736964e-07,  1.228005451157736e-09,
 -1.285297237610320e-11,  1.370173745295136e-13, -1.479624410089842e-15,  1.613181291997327e-17, -1.771820437124431e-19,  1.957502671441180e-21, -2.172702360235077e-23,
  2.480269794628327e-02, -1.442236730909690e-04,  1.257941786283207e-06, -1.219104129472500e-08,  1.240537425273856e-10, -1.298413893102733e-12,  1.384156657584378e-14,
 -1.494724804987550e-16,  1.629647646490675e-18, -1.789920920526276e-20,  1.977567331755450e-22, -2.195248906610356e-24,  2.400012424554552e-01, -1.333525471559152e-03,
  1.111414173094275e-05, -1.029216924506791e-07,  1.000752675137876e-09, -1.000877285278909e-11,  1.019538682628820e-13, -1.052035459774500e-15,  1.096006025665259e-17,
 -1.150271992932356e-19,  1.214325303770147e-21, -1.287929646868168e-23,  2.424504897756377e-02, -1.347134291472774e-04,  1.122756315149282e-06, -1.039720231790730e-08,
  1.010965500818969e-10, -1.011091384193835e-12,  1.029943235843123e-14, -1.062771726475139e-16,  1.107191473160261e-18, -1.162013550374170e-20,  1.226731143196119e-22,
 -1.301130581314143e-24,  2.348375100504165e-01, -1.249294770791443e-03,  9.968952791603609e-06, -8.838745373577489e-08,  8.228498529107271e-10, -7.879248909957029e-12,
  7.684539677024003e-14, -7.591973755483545e-16,  7.572642368437041e-18, -7.609310166923919e-20,  7.691131239147392e-22, -7.810207967886848e-24,  2.372340607360907e-02,
 -1.262044004246133e-04,  1.007068739372657e-06, -8.928946045891467e-09,  8.312471544547013e-11, -7.959657784973385e-13,  7.762961534298016e-15, -7.669451083386664e-17,
  7.649923103633526e-19, -7.686968614425550e-21,  7.769640813398352e-23, -7.889999818372861e-25,  2.299934177283603e-01, -1.173573290490526e-03,  8.982402594250001e-06,
 -7.638909488625210e-08,  6.821174097143596e-10, -6.265001396091395e-12,  5.860734288719538e-14, -5.553754804558802e-16,  5.313458417418224e-18, -5.121214606982423e-20,
  4.964960659435032e-22, -4.836040210443209e-24,  2.323405337527089e-02, -1.185549775309371e-04,  9.074069309212540e-07, -7.716865662533116e-09,  6.890785163390236e-11,
 -6.328936639997845e-13,  5.920543931145564e-15, -5.610431694892845e-17,  5.367683151580185e-19, -5.173477994241501e-21,  5.015631889546355e-23, -4.885405956586138e-25,
  2.254372874097561e-01, -1.105204261553571e-03,  8.127315724102592e-06, -6.640615462931125e-08,  5.697160894004896e-10, -5.027393962520822e-12,  4.518519742772459e-14,
 -4.113895583384398e-16,  3.781518792406301e-18, -3.501743826083052e-20,  3.261742265163561e-22, -3.052456056013837e-24,  2.277379074665877e-02, -1.116483030563971e-04,
  8.210256154134893e-07, -6.708383902213637e-09,  5.755301243242240e-11, -5.078699243602518e-13,  4.564631889394025e-15, -4.155878484717580e-17,  3.820109756021343e-19,
 -3.537479725008666e-21,  3.295029279551304e-23, -3.083608806191768e-25,  2.211416697030966e-01, -1.043225545730489e-03,  7.381997255678409e-06, -5.803984323587076e-08,
  4.791456602574219e-10, -4.068583022765254e-12,  3.518743773849988e-14, -3.082733095390006e-16,  2.726717387187715e-18, -2.429682037014118e-20,  2.177739477972687e-22,
 -1.961100166815934e-24,  2.233984523612176e-02, -1.053871813000128e-04,  7.457331603163801e-07, -5.863214821335781e-09,  4.840354108786169e-11, -4.110103499765926e-13,
  3.554653062013075e-15, -3.114192832041820e-17,  2.754543934442253e-19, -2.454477307454968e-21,  2.199963692927427e-23, -1.981113775822593e-25,  2.170826446452450e-01,
 -9.868310525630313e-04,  6.728972873937722e-06, -5.098136870086325e-08,  4.055675544489599e-10, -3.318556560320893e-12,  2.765693749622587e-14, -2.334870383903892e-16,
  1.990111406666920e-18, -1.708823139686653e-20,  1.475924057679656e-22, -1.280769055696466e-24,  2.192980043667855e-02, -9.969018058901160e-05,  6.797643013352234e-07,
 -5.150164092692484e-09,  4.097064298803009e-11, -3.352422909008862e-13,  2.793918053537895e-15, -2.358698073246840e-17,  2.010420781225077e-19, -1.726261928632182e-21,
  1.490986086011546e-23, -1.293839533277818e-25,  2.132392587868051e-01, -9.353408813245848e-04,  6.154051733412410e-06, -4.498929246092619e-08,  3.453394587806035e-10,
 -2.726575714135871e-12,  2.192591722536403e-14, -1.786083696199890e-16,  1.468932259891424e-18, -1.217045592355439e-20,  1.014282884270068e-22, -8.492851823378929e-25,
  2.154153962009195e-02, -9.448861700222734e-05,  6.216854719605791e-07, -4.544841468408418e-09,  3.488636978025289e-11, -2.754400812843039e-13,  2.214967437537240e-15,
 -1.804310938126625e-17,  1.483922925684148e-19, -1.229465718608448e-21,  1.024633789025566e-23, -8.579522668075644e-26,  2.095930682734510e-01, -8.881779878721694e-04,
  5.645621460326827e-06, -3.987313155086076e-08,  2.956909107553391e-10, -2.255433001638976e-12,  1.752228508571032e-14, -1.378971797940899e-16,  1.095660374795691e-18,
 -8.770041425174965e-21,  7.061134848883125e-23, -5.712045003986451e-25,  2.117319957870985e-02, -8.972419724348520e-05,  5.703235842198355e-07, -4.028004261348309e-09,
  2.987084791785704e-11, -2.278450020961895e-13,  1.770110253411636e-15, -1.393044404176238e-17,  1.106841747073023e-19, -8.859540964224878e-22,  7.133194751441321e-24,
 -5.770337257459599e-26,  2.061277651121327e-01, -8.448497846261297e-04,  5.194112214323083e-06, -3.548134225503946e-08,  2.544941533535744e-10, -1.877543090263090e-12,
  1.410817625453413e-14, -1.073879803095882e-16,  8.252706557301733e-19, -6.389137745549611e-21,  4.975483291716404e-23, -3.892910346743309e-25,  2.082313287068494e-02,
 -8.534715986208480e-05,  5.247118879169906e-07, -3.584343447400271e-09,  2.570913029213273e-11, -1.896703688497110e-13,  1.425215222953588e-15, -1.084838901486677e-17,
  8.336926618898192e-20, -6.454339818497185e-22,  5.026258817181927e-24, -3.932638060155788e-26,  2.028288692948272e-01, -8.049335081376955e-04,  4.791585290669536e-06,
 -3.169241687197211e-08,  2.201002661760019e-10, -1.572244622794477e-12,  1.143901245670935e-14, -8.430644656102465e-17,  6.273197617625510e-19, -4.702429291952939e-21,
  3.545706249945471e-23, -2.686154705947692e-25,  2.048987671815775e-02, -8.131479707694760e-05,  4.840484110161172e-07, -3.201584256052115e-09,  2.223464211608164e-11,
 -1.588289606102284e-13,  1.155574922989642e-15, -8.516680601667526e-18,  6.337216504766265e-20, -4.750418261619280e-22,  3.581890694049104e-24, -2.713567302642395e-26,
  };
  int offset = -2;
  for (int i = 1; i <= n; ++i) {
    double t = ta[i-1];
    offset += 2;
    if (std::isnan(t)) {
      fill_n(rr+offset, 2, 0.5);
      fill_n(ww+offset, 2, 0.0);
    } else if (t >= 64.0) {
      t = 1.0/sqrt(t);
      for (int r = 0; r != 2; ++r) {
        rr[offset+r] = ax[r]*t*t;
        ww[offset+r] = aw[r]*t;
      }
    } else {
      assert(t >= 0);
      int it = static_cast<int>(t*   0.500000000000000);
      t = (t-it*2.000000000000000-   1.000000000000000) *   1.000000000000000;

      const double t2 = t * 2.0;
      for (int j=1; j <=2; ++j) {
        const int boxof = it*24+12*(j-1);
        double d = x[boxof+11];
        double e = w[boxof+11];
        double f = t2*d + x[boxof+10];
        double g = t2*e + w[boxof+10];
        d = t2*f - d + x[boxof+9];
        e = t2*g - e + w[boxof+9];
        f = t2*d - f + x[boxof+8];
        g = t2*e - g + w[boxof+8];
        d = t2*f - d + x[boxof+7];
        e = t2*g - e + w[boxof+7];
        f = t2*d - f + x[boxof+6];
        g = t2*e - g + w[boxof+6];
        d = t2*f - d + x[boxof+5];
        e = t2*g - e + w[boxof+5];
        f = t2*d - f + x[boxof+4];
        g = t2*e - g + w[boxof+4];
        d = t2*f - d + x[boxof+3];
        e = t2*g - e + w[boxof+3];
        f = t2*d - f + x[boxof+2];
        g = t2*e - g + w[boxof+2];
        d = t2*f - d + x[boxof+1];
        e = t2*g - e + w[boxof+1];
        rr[offset+j-1] = t*d - f + x[boxof+0]*0.5;
        ww[offset+j-1] = t*e - g + w[boxof+0]*0.5;
      }
    }
  }
}

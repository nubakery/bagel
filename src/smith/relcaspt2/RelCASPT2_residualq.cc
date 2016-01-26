//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: RelCASPT2_residualqq.cc
// Copyright (C) 2014 Toru Shiozaki
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH


#include <src/smith/relcaspt2/RelCASPT2.h>
#include <src/smith/relcaspt2/RelCASPT2_tasks.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;

shared_ptr<Queue> RelCASPT2::RelCASPT2::make_residualq(const bool reset, const bool diagonal) {

  array<shared_ptr<const IndexRange>,3> pindex = {{rclosed_, ractive_, rvirt_}};
  auto residualq = make_shared<Queue>();
  auto tensor30 = vector<shared_ptr<Tensor>>{r};
  auto task30 = make_shared<Task30>(tensor30, reset);
  residualq->add_task(task30);

  vector<IndexRange> I0_index = {closed_, closed_, active_, active_};
  auto I0 = make_shared<Tensor>(I0_index);
  auto tensor31 = vector<shared_ptr<Tensor>>{r, I0};
  auto task31 = make_shared<Task31>(tensor31, pindex);
  task31->add_dep(task30);
  residualq->add_task(task31);

  auto tensor32 = vector<shared_ptr<Tensor>>{I0, Gamma0_(), t2};
  auto task32 = make_shared<Task32>(tensor32, pindex);
  task31->add_dep(task32);
  task32->add_dep(task30);
  residualq->add_task(task32);

  auto tensor33 = vector<shared_ptr<Tensor>>{I0, Gamma92_(), t2};
  auto task33 = make_shared<Task33>(tensor33, pindex, this->e0_);
  task31->add_dep(task33);
  task33->add_dep(task30);
  residualq->add_task(task33);

  vector<IndexRange> I2_index = {closed_, closed_, active_, active_};
  auto I2 = make_shared<Tensor>(I2_index);
  auto tensor34 = vector<shared_ptr<Tensor>>{r, I2};
  auto task34 = make_shared<Task34>(tensor34, pindex);
  task34->add_dep(task30);
  residualq->add_task(task34);

  vector<IndexRange> I3_index = {closed_, closed_, active_, active_};
  auto I3 = make_shared<Tensor>(I3_index);
  auto tensor35 = vector<shared_ptr<Tensor>>{I2, Gamma92_(), I3};
  auto task35 = make_shared<Task35>(tensor35, pindex);
  task34->add_dep(task35);
  task35->add_dep(task30);
  residualq->add_task(task35);

  auto tensor36 = vector<shared_ptr<Tensor>>{I3, t2, f1_};
  auto task36 = make_shared<Task36>(tensor36, pindex);
  task35->add_dep(task36);
  task36->add_dep(task30);
  residualq->add_task(task36);

  vector<IndexRange> I6_index = {closed_, active_, active_, active_};
  auto I6 = make_shared<Tensor>(I6_index);
  auto tensor37 = vector<shared_ptr<Tensor>>{I2, f1_, I6};
  auto task37 = make_shared<Task37>(tensor37, pindex);
  task34->add_dep(task37);
  task37->add_dep(task30);
  residualq->add_task(task37);

  auto tensor38 = vector<shared_ptr<Tensor>>{I6, Gamma2_(), t2};
  auto task38 = make_shared<Task38>(tensor38, pindex);
  task37->add_dep(task38);
  task38->add_dep(task30);
  residualq->add_task(task38);

  vector<IndexRange> I9_index = {active_, closed_, closed_, active_};
  auto I9 = make_shared<Tensor>(I9_index);
  auto tensor39 = vector<shared_ptr<Tensor>>{I2, Gamma3_(), I9};
  auto task39 = make_shared<Task39>(tensor39, pindex);
  task34->add_dep(task39);
  task39->add_dep(task30);
  residualq->add_task(task39);

  auto tensor40 = vector<shared_ptr<Tensor>>{I9, t2, f1_};
  auto task40 = make_shared<Task40>(tensor40, pindex);
  task39->add_dep(task40);
  task40->add_dep(task30);
  residualq->add_task(task40);

  vector<IndexRange> I11_index = {closed_, active_, active_, active_};
  auto I11 = make_shared<Tensor>(I11_index);
  auto tensor41 = vector<shared_ptr<Tensor>>{r, I11};
  auto task41 = make_shared<Task41>(tensor41, pindex);
  task41->add_dep(task30);
  residualq->add_task(task41);

  vector<IndexRange> I12_index = {active_, closed_, active_, active_};
  auto I12 = make_shared<Tensor>(I12_index);
  auto tensor42 = vector<shared_ptr<Tensor>>{I11, Gamma4_(), I12};
  auto task42 = make_shared<Task42>(tensor42, pindex);
  task41->add_dep(task42);
  task42->add_dep(task30);
  residualq->add_task(task42);

  auto tensor43 = vector<shared_ptr<Tensor>>{I12, t2, f1_};
  auto task43 = make_shared<Task43>(tensor43, pindex);
  task42->add_dep(task43);
  task43->add_dep(task30);
  residualq->add_task(task43);

  auto tensor44 = vector<shared_ptr<Tensor>>{I11, Gamma5_(), t2};
  auto task44 = make_shared<Task44>(tensor44, pindex);
  task41->add_dep(task44);
  task44->add_dep(task30);
  residualq->add_task(task44);

  vector<IndexRange> I17_index = {closed_, active_, active_, active_};
  auto I17 = make_shared<Tensor>(I17_index);
  auto tensor45 = vector<shared_ptr<Tensor>>{I11, Gamma6_(), I17};
  auto task45 = make_shared<Task45>(tensor45, pindex);
  task41->add_dep(task45);
  task45->add_dep(task30);
  residualq->add_task(task45);

  auto tensor46 = vector<shared_ptr<Tensor>>{I17, t2};
  auto task46 = make_shared<Task46>(tensor46, pindex, this->e0_);
  task45->add_dep(task46);
  task46->add_dep(task30);
  residualq->add_task(task46);

  auto tensor47 = vector<shared_ptr<Tensor>>{I17, t2, f1_};
  auto task47 = make_shared<Task47>(tensor47, pindex);
  task45->add_dep(task47);
  task47->add_dep(task30);
  residualq->add_task(task47);

  auto tensor48 = vector<shared_ptr<Tensor>>{I17, t2, f1_};
  auto task48 = make_shared<Task48>(tensor48, pindex);
  task45->add_dep(task48);
  task48->add_dep(task30);
  residualq->add_task(task48);

  vector<IndexRange> I20_index = {closed_, active_};
  auto I20 = make_shared<Tensor>(I20_index);
  auto tensor49 = vector<shared_ptr<Tensor>>{I11, Gamma7_(), I20};
  auto task49 = make_shared<Task49>(tensor49, pindex);
  task41->add_dep(task49);
  task49->add_dep(task30);
  residualq->add_task(task49);

  auto tensor50 = vector<shared_ptr<Tensor>>{I20, t2, f1_};
  auto task50 = make_shared<Task50>(tensor50, pindex);
  task49->add_dep(task50);
  task50->add_dep(task30);
  residualq->add_task(task50);

  auto tensor51 = vector<shared_ptr<Tensor>>{I20, t2, f1_};
  auto task51 = make_shared<Task51>(tensor51, pindex);
  task49->add_dep(task51);
  task51->add_dep(task30);
  residualq->add_task(task51);

  vector<IndexRange> I26_index = {active_, active_, closed_, active_};
  auto I26 = make_shared<Tensor>(I26_index);
  auto tensor52 = vector<shared_ptr<Tensor>>{I11, Gamma9_(), I26};
  auto task52 = make_shared<Task52>(tensor52, pindex);
  task41->add_dep(task52);
  task52->add_dep(task30);
  residualq->add_task(task52);

  auto tensor53 = vector<shared_ptr<Tensor>>{I26, t2, f1_};
  auto task53 = make_shared<Task53>(tensor53, pindex);
  task52->add_dep(task53);
  task53->add_dep(task30);
  residualq->add_task(task53);

  vector<IndexRange> I31_index = {closed_, closed_, active_, virt_};
  auto I31 = make_shared<Tensor>(I31_index);
  auto tensor54 = vector<shared_ptr<Tensor>>{r, I31};
  auto task54 = make_shared<Task54>(tensor54, pindex);
  task54->add_dep(task30);
  residualq->add_task(task54);

  vector<IndexRange> I32_index = {closed_, closed_, active_, active_};
  auto I32 = make_shared<Tensor>(I32_index);
  auto tensor55 = vector<shared_ptr<Tensor>>{I31, f1_, I32};
  auto task55 = make_shared<Task55>(tensor55, pindex);
  task54->add_dep(task55);
  task55->add_dep(task30);
  residualq->add_task(task55);

  auto tensor56 = vector<shared_ptr<Tensor>>{I32, Gamma3_(), t2};
  auto task56 = make_shared<Task56>(tensor56, pindex);
  task55->add_dep(task56);
  task56->add_dep(task30);
  residualq->add_task(task56);

  vector<IndexRange> I35_index = {closed_, active_};
  auto I35 = make_shared<Tensor>(I35_index);
  auto tensor57 = vector<shared_ptr<Tensor>>{I31, f1_, I35};
  auto task57 = make_shared<Task57>(tensor57, pindex);
  task54->add_dep(task57);
  task57->add_dep(task30);
  residualq->add_task(task57);

  auto tensor58 = vector<shared_ptr<Tensor>>{I35, Gamma12_(), t2};
  auto task58 = make_shared<Task58>(tensor58, pindex);
  task57->add_dep(task58);
  task58->add_dep(task30);
  residualq->add_task(task58);

  vector<IndexRange> I38_index = {closed_, active_};
  auto I38 = make_shared<Tensor>(I38_index);
  auto tensor59 = vector<shared_ptr<Tensor>>{I31, f1_, I38};
  auto task59 = make_shared<Task59>(tensor59, pindex);
  task54->add_dep(task59);
  task59->add_dep(task30);
  residualq->add_task(task59);

  auto tensor60 = vector<shared_ptr<Tensor>>{I38, Gamma12_(), t2};
  auto task60 = make_shared<Task60>(tensor60, pindex);
  task59->add_dep(task60);
  task60->add_dep(task30);
  residualq->add_task(task60);

  vector<IndexRange> I41_index = {closed_, virt_, closed_, active_};
  auto I41 = make_shared<Tensor>(I41_index);
  auto tensor61 = vector<shared_ptr<Tensor>>{I31, Gamma14_(), I41};
  auto task61 = make_shared<Task61>(tensor61, pindex);
  task54->add_dep(task61);
  task61->add_dep(task30);
  residualq->add_task(task61);

  auto tensor62 = vector<shared_ptr<Tensor>>{I41, t2};
  auto task62 = make_shared<Task62>(tensor62, pindex);
  task61->add_dep(task62);
  task62->add_dep(task30);
  residualq->add_task(task62);

  vector<IndexRange> I45_index = {closed_, virt_, closed_, active_};
  auto I45 = make_shared<Tensor>(I45_index);
  auto tensor63 = vector<shared_ptr<Tensor>>{I31, Gamma16_(), I45};
  auto task63 = make_shared<Task63>(tensor63, pindex);
  task54->add_dep(task63);
  task63->add_dep(task30);
  residualq->add_task(task63);

  auto tensor64 = vector<shared_ptr<Tensor>>{I45, t2};
  auto task64 = make_shared<Task64>(tensor64, pindex, this->e0_);
  task63->add_dep(task64);
  task64->add_dep(task30);
  residualq->add_task(task64);

  auto tensor65 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task65 = make_shared<Task65>(tensor65, pindex);
  task63->add_dep(task65);
  task65->add_dep(task30);
  residualq->add_task(task65);

  auto tensor66 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task66 = make_shared<Task66>(tensor66, pindex);
  task63->add_dep(task66);
  task66->add_dep(task30);
  residualq->add_task(task66);

  auto tensor67 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task67 = make_shared<Task67>(tensor67, pindex);
  task63->add_dep(task67);
  task67->add_dep(task30);
  residualq->add_task(task67);

  auto tensor68 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task68 = make_shared<Task68>(tensor68, pindex);
  task63->add_dep(task68);
  task68->add_dep(task30);
  residualq->add_task(task68);

  auto tensor69 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task69 = make_shared<Task69>(tensor69, pindex);
  task63->add_dep(task69);
  task69->add_dep(task30);
  residualq->add_task(task69);

  auto tensor70 = vector<shared_ptr<Tensor>>{I45, t2, f1_};
  auto task70 = make_shared<Task70>(tensor70, pindex);
  task63->add_dep(task70);
  task70->add_dep(task30);
  residualq->add_task(task70);

  vector<IndexRange> I63_index = {virt_, closed_, active_, active_};
  auto I63 = make_shared<Tensor>(I63_index);
  auto tensor71 = vector<shared_ptr<Tensor>>{I31, f1_, I63};
  auto task71 = make_shared<Task71>(tensor71, pindex);
  task54->add_dep(task71);
  task71->add_dep(task30);
  residualq->add_task(task71);

  auto tensor72 = vector<shared_ptr<Tensor>>{I63, Gamma22_(), t2};
  auto task72 = make_shared<Task72>(tensor72, pindex);
  task71->add_dep(task72);
  task72->add_dep(task30);
  residualq->add_task(task72);

  auto tensor73 = vector<shared_ptr<Tensor>>{I63, Gamma12_(), t2};
  auto task73 = make_shared<Task73>(tensor73, pindex);
  task71->add_dep(task73);
  task73->add_dep(task30);
  residualq->add_task(task73);

  vector<IndexRange> I66_index = {virt_, closed_, active_, active_};
  auto I66 = make_shared<Tensor>(I66_index);
  auto tensor74 = vector<shared_ptr<Tensor>>{I31, f1_, I66};
  auto task74 = make_shared<Task74>(tensor74, pindex);
  task54->add_dep(task74);
  task74->add_dep(task30);
  residualq->add_task(task74);

  vector<IndexRange> I67_index = {active_, virt_, closed_, active_};
  auto I67 = make_shared<Tensor>(I67_index);
  auto tensor75 = vector<shared_ptr<Tensor>>{I66, Gamma12_(), I67};
  auto task75 = make_shared<Task75>(tensor75, pindex);
  task74->add_dep(task75);
  task75->add_dep(task30);
  residualq->add_task(task75);

  auto tensor76 = vector<shared_ptr<Tensor>>{I67, t2};
  auto task76 = make_shared<Task76>(tensor76, pindex);
  task75->add_dep(task76);
  task76->add_dep(task30);
  residualq->add_task(task76);

  vector<IndexRange> I75_index = {virt_, active_};
  auto I75 = make_shared<Tensor>(I75_index);
  auto tensor77 = vector<shared_ptr<Tensor>>{I31, t2, I75};
  auto task77 = make_shared<Task77>(tensor77, pindex);
  task54->add_dep(task77);
  task77->add_dep(task30);
  residualq->add_task(task77);

  auto tensor78 = vector<shared_ptr<Tensor>>{I75, Gamma16_(), f1_};
  auto task78 = make_shared<Task78>(tensor78, pindex);
  task77->add_dep(task78);
  task78->add_dep(task30);
  residualq->add_task(task78);

  vector<IndexRange> I78_index = {virt_, active_};
  auto I78 = make_shared<Tensor>(I78_index);
  auto tensor79 = vector<shared_ptr<Tensor>>{I31, t2, I78};
  auto task79 = make_shared<Task79>(tensor79, pindex);
  task54->add_dep(task79);
  task79->add_dep(task30);
  residualq->add_task(task79);

  auto tensor80 = vector<shared_ptr<Tensor>>{I78, Gamma16_(), f1_};
  auto task80 = make_shared<Task80>(tensor80, pindex);
  task79->add_dep(task80);
  task80->add_dep(task30);
  residualq->add_task(task80);

  vector<IndexRange> I80_index = {closed_, active_, active_, virt_};
  auto I80 = make_shared<Tensor>(I80_index);
  auto tensor81 = vector<shared_ptr<Tensor>>{r, I80};
  auto task81 = make_shared<Task81>(tensor81, pindex);
  task81->add_dep(task30);
  residualq->add_task(task81);

  vector<IndexRange> I81_index = {closed_, active_, active_, active_};
  auto I81 = make_shared<Tensor>(I81_index);
  auto tensor82 = vector<shared_ptr<Tensor>>{I80, f1_, I81};
  auto task82 = make_shared<Task82>(tensor82, pindex);
  task81->add_dep(task82);
  task82->add_dep(task30);
  residualq->add_task(task82);

  auto tensor83 = vector<shared_ptr<Tensor>>{I81, Gamma28_(), t2};
  auto task83 = make_shared<Task83>(tensor83, pindex);
  task82->add_dep(task83);
  task83->add_dep(task30);
  residualq->add_task(task83);

  vector<IndexRange> I84_index = {active_, virt_, closed_, active_};
  auto I84 = make_shared<Tensor>(I84_index);
  auto tensor84 = vector<shared_ptr<Tensor>>{I80, Gamma29_(), I84};
  auto task84 = make_shared<Task84>(tensor84, pindex);
  task81->add_dep(task84);
  task84->add_dep(task30);
  residualq->add_task(task84);

  auto tensor85 = vector<shared_ptr<Tensor>>{I84, t2, f1_};
  auto task85 = make_shared<Task85>(tensor85, pindex);
  task84->add_dep(task85);
  task85->add_dep(task30);
  residualq->add_task(task85);

  vector<IndexRange> I87_index = {active_, closed_, virt_, active_};
  auto I87 = make_shared<Tensor>(I87_index);
  auto tensor86 = vector<shared_ptr<Tensor>>{I80, Gamma7_(), I87};
  auto task86 = make_shared<Task86>(tensor86, pindex);
  task81->add_dep(task86);
  task86->add_dep(task30);
  residualq->add_task(task86);

  auto tensor87 = vector<shared_ptr<Tensor>>{I87, t2, f1_};
  auto task87 = make_shared<Task87>(tensor87, pindex);
  task86->add_dep(task87);
  task87->add_dep(task30);
  residualq->add_task(task87);

  auto tensor88 = vector<shared_ptr<Tensor>>{I80, Gamma31_(), t2};
  auto task88 = make_shared<Task88>(tensor88, pindex);
  task81->add_dep(task88);
  task88->add_dep(task30);
  residualq->add_task(task88);

  vector<IndexRange> I92_index = {closed_, active_, virt_, active_};
  auto I92 = make_shared<Tensor>(I92_index);
  auto tensor89 = vector<shared_ptr<Tensor>>{I80, Gamma32_(), I92};
  auto task89 = make_shared<Task89>(tensor89, pindex);
  task81->add_dep(task89);
  task89->add_dep(task30);
  residualq->add_task(task89);

  auto tensor90 = vector<shared_ptr<Tensor>>{I92, t2};
  auto task90 = make_shared<Task90>(tensor90, pindex, this->e0_);
  task89->add_dep(task90);
  task90->add_dep(task30);
  residualq->add_task(task90);

  auto tensor91 = vector<shared_ptr<Tensor>>{I92, t2, f1_};
  auto task91 = make_shared<Task91>(tensor91, pindex);
  task89->add_dep(task91);
  task91->add_dep(task30);
  residualq->add_task(task91);

  auto tensor92 = vector<shared_ptr<Tensor>>{I92, t2, f1_};
  auto task92 = make_shared<Task92>(tensor92, pindex);
  task89->add_dep(task92);
  task92->add_dep(task30);
  residualq->add_task(task92);

  auto tensor93 = vector<shared_ptr<Tensor>>{I92, t2, f1_};
  auto task93 = make_shared<Task93>(tensor93, pindex);
  task89->add_dep(task93);
  task93->add_dep(task30);
  residualq->add_task(task93);

  auto tensor94 = vector<shared_ptr<Tensor>>{I80, Gamma34_(), t2};
  auto task94 = make_shared<Task94>(tensor94, pindex);
  task81->add_dep(task94);
  task94->add_dep(task30);
  residualq->add_task(task94);

  vector<IndexRange> I100_index = {closed_, virt_, active_, active_};
  auto I100 = make_shared<Tensor>(I100_index);
  auto tensor95 = vector<shared_ptr<Tensor>>{I80, Gamma35_(), I100};
  auto task95 = make_shared<Task95>(tensor95, pindex);
  task81->add_dep(task95);
  task95->add_dep(task30);
  residualq->add_task(task95);

  auto tensor96 = vector<shared_ptr<Tensor>>{I100, t2};
  auto task96 = make_shared<Task96>(tensor96, pindex, this->e0_);
  task95->add_dep(task96);
  task96->add_dep(task30);
  residualq->add_task(task96);

  auto tensor97 = vector<shared_ptr<Tensor>>{I100, t2, f1_};
  auto task97 = make_shared<Task97>(tensor97, pindex);
  task95->add_dep(task97);
  task97->add_dep(task30);
  residualq->add_task(task97);

  auto tensor98 = vector<shared_ptr<Tensor>>{I100, t2, f1_};
  auto task98 = make_shared<Task98>(tensor98, pindex);
  task95->add_dep(task98);
  task98->add_dep(task30);
  residualq->add_task(task98);

  auto tensor99 = vector<shared_ptr<Tensor>>{I100, t2, f1_};
  auto task99 = make_shared<Task99>(tensor99, pindex);
  task95->add_dep(task99);
  task99->add_dep(task30);
  residualq->add_task(task99);

  vector<IndexRange> I106_index = {virt_, active_, active_, active_};
  auto I106 = make_shared<Tensor>(I106_index);
  auto tensor100 = vector<shared_ptr<Tensor>>{I80, f1_, I106};
  auto task100 = make_shared<Task100>(tensor100, pindex);
  task81->add_dep(task100);
  task100->add_dep(task30);
  residualq->add_task(task100);

  auto tensor101 = vector<shared_ptr<Tensor>>{I106, Gamma37_(), t2};
  auto task101 = make_shared<Task101>(tensor101, pindex);
  task100->add_dep(task101);
  task101->add_dep(task30);
  residualq->add_task(task101);

  vector<IndexRange> I109_index = {closed_, virt_};
  auto I109 = make_shared<Tensor>(I109_index);
  auto tensor102 = vector<shared_ptr<Tensor>>{I80, Gamma38_(), I109};
  auto task102 = make_shared<Task102>(tensor102, pindex);
  task81->add_dep(task102);
  task102->add_dep(task30);
  residualq->add_task(task102);

  auto tensor103 = vector<shared_ptr<Tensor>>{I109, t2, f1_};
  auto task103 = make_shared<Task103>(tensor103, pindex);
  task102->add_dep(task103);
  task103->add_dep(task30);
  residualq->add_task(task103);

  auto tensor104 = vector<shared_ptr<Tensor>>{I109, t2, f1_};
  auto task104 = make_shared<Task104>(tensor104, pindex);
  task102->add_dep(task104);
  task104->add_dep(task30);
  residualq->add_task(task104);

  vector<IndexRange> I120_index = {closed_, active_, active_, virt_};
  auto I120 = make_shared<Tensor>(I120_index);
  auto tensor105 = vector<shared_ptr<Tensor>>{r, I120};
  auto task105 = make_shared<Task105>(tensor105, pindex);
  task105->add_dep(task30);
  residualq->add_task(task105);

  vector<IndexRange> I121_index = {closed_, active_, active_, active_};
  auto I121 = make_shared<Tensor>(I121_index);
  auto tensor106 = vector<shared_ptr<Tensor>>{I120, f1_, I121};
  auto task106 = make_shared<Task106>(tensor106, pindex);
  task105->add_dep(task106);
  task106->add_dep(task30);
  residualq->add_task(task106);

  auto tensor107 = vector<shared_ptr<Tensor>>{I121, Gamma6_(), t2};
  auto task107 = make_shared<Task107>(tensor107, pindex);
  task106->add_dep(task107);
  task107->add_dep(task30);
  residualq->add_task(task107);

  vector<IndexRange> I124_index = {active_, virt_, closed_, active_};
  auto I124 = make_shared<Tensor>(I124_index);
  auto tensor108 = vector<shared_ptr<Tensor>>{I120, Gamma7_(), I124};
  auto task108 = make_shared<Task108>(tensor108, pindex);
  task105->add_dep(task108);
  task108->add_dep(task30);
  residualq->add_task(task108);

  auto tensor109 = vector<shared_ptr<Tensor>>{I124, t2, f1_};
  auto task109 = make_shared<Task109>(tensor109, pindex);
  task108->add_dep(task109);
  task109->add_dep(task30);
  residualq->add_task(task109);

  auto tensor110 = vector<shared_ptr<Tensor>>{I124, t2, f1_};
  auto task110 = make_shared<Task110>(tensor110, pindex);
  task108->add_dep(task110);
  task110->add_dep(task30);
  residualq->add_task(task110);

  vector<IndexRange> I130_index = {active_, virt_, closed_, active_};
  auto I130 = make_shared<Tensor>(I130_index);
  auto tensor111 = vector<shared_ptr<Tensor>>{I120, Gamma34_(), I130};
  auto task111 = make_shared<Task111>(tensor111, pindex);
  task105->add_dep(task111);
  task111->add_dep(task30);
  residualq->add_task(task111);

  auto tensor112 = vector<shared_ptr<Tensor>>{I130, t2};
  auto task112 = make_shared<Task112>(tensor112, pindex);
  task111->add_dep(task112);
  task112->add_dep(task30);
  residualq->add_task(task112);

  vector<IndexRange> I132_index = {closed_, active_, virt_, active_};
  auto I132 = make_shared<Tensor>(I132_index);
  auto tensor113 = vector<shared_ptr<Tensor>>{I120, Gamma35_(), I132};
  auto task113 = make_shared<Task113>(tensor113, pindex);
  task105->add_dep(task113);
  task113->add_dep(task30);
  residualq->add_task(task113);

  auto tensor114 = vector<shared_ptr<Tensor>>{I132, t2};
  auto task114 = make_shared<Task114>(tensor114, pindex, this->e0_);
  task113->add_dep(task114);
  task114->add_dep(task30);
  residualq->add_task(task114);

  auto tensor115 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task115 = make_shared<Task115>(tensor115, pindex);
  task113->add_dep(task115);
  task115->add_dep(task30);
  residualq->add_task(task115);

  auto tensor116 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task116 = make_shared<Task116>(tensor116, pindex);
  task113->add_dep(task116);
  task116->add_dep(task30);
  residualq->add_task(task116);

  auto tensor117 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task117 = make_shared<Task117>(tensor117, pindex);
  task113->add_dep(task117);
  task117->add_dep(task30);
  residualq->add_task(task117);

  auto tensor118 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task118 = make_shared<Task118>(tensor118, pindex);
  task113->add_dep(task118);
  task118->add_dep(task30);
  residualq->add_task(task118);

  auto tensor119 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task119 = make_shared<Task119>(tensor119, pindex);
  task113->add_dep(task119);
  task119->add_dep(task30);
  residualq->add_task(task119);

  auto tensor120 = vector<shared_ptr<Tensor>>{I132, t2, f1_};
  auto task120 = make_shared<Task120>(tensor120, pindex);
  task113->add_dep(task120);
  task120->add_dep(task30);
  residualq->add_task(task120);

  vector<IndexRange> I146_index = {virt_, active_, active_, active_};
  auto I146 = make_shared<Tensor>(I146_index);
  auto tensor121 = vector<shared_ptr<Tensor>>{I120, f1_, I146};
  auto task121 = make_shared<Task121>(tensor121, pindex);
  task105->add_dep(task121);
  task121->add_dep(task30);
  residualq->add_task(task121);

  auto tensor122 = vector<shared_ptr<Tensor>>{I146, Gamma51_(), t2};
  auto task122 = make_shared<Task122>(tensor122, pindex);
  task121->add_dep(task122);
  task122->add_dep(task30);
  residualq->add_task(task122);

  vector<IndexRange> I149_index = {closed_, virt_};
  auto I149 = make_shared<Tensor>(I149_index);
  auto tensor123 = vector<shared_ptr<Tensor>>{I120, Gamma38_(), I149};
  auto task123 = make_shared<Task123>(tensor123, pindex);
  task105->add_dep(task123);
  task123->add_dep(task30);
  residualq->add_task(task123);

  auto tensor124 = vector<shared_ptr<Tensor>>{I149, t2, f1_};
  auto task124 = make_shared<Task124>(tensor124, pindex);
  task123->add_dep(task124);
  task124->add_dep(task30);
  residualq->add_task(task124);

  auto tensor125 = vector<shared_ptr<Tensor>>{I149, t2, f1_};
  auto task125 = make_shared<Task125>(tensor125, pindex);
  task123->add_dep(task125);
  task125->add_dep(task30);
  residualq->add_task(task125);

  vector<IndexRange> I160_index = {virt_, active_, active_, active_};
  auto I160 = make_shared<Tensor>(I160_index);
  auto tensor126 = vector<shared_ptr<Tensor>>{r, I160};
  auto task126 = make_shared<Task126>(tensor126, pindex);
  task126->add_dep(task30);
  residualq->add_task(task126);

  vector<IndexRange> I161_index = {active_, active_, virt_, active_};
  auto I161 = make_shared<Tensor>(I161_index);
  auto tensor127 = vector<shared_ptr<Tensor>>{I160, Gamma56_(), I161};
  auto task127 = make_shared<Task127>(tensor127, pindex);
  task126->add_dep(task127);
  task127->add_dep(task30);
  residualq->add_task(task127);

  auto tensor128 = vector<shared_ptr<Tensor>>{I161, t2, f1_};
  auto task128 = make_shared<Task128>(tensor128, pindex);
  task127->add_dep(task128);
  task128->add_dep(task30);
  residualq->add_task(task128);

  vector<IndexRange> I164_index = {active_, virt_, active_, active_};
  auto I164 = make_shared<Tensor>(I164_index);
  auto tensor129 = vector<shared_ptr<Tensor>>{I160, Gamma57_(), I164};
  auto task129 = make_shared<Task129>(tensor129, pindex);
  task126->add_dep(task129);
  task129->add_dep(task30);
  residualq->add_task(task129);

  auto tensor130 = vector<shared_ptr<Tensor>>{I164, t2, f1_};
  auto task130 = make_shared<Task130>(tensor130, pindex);
  task129->add_dep(task130);
  task130->add_dep(task30);
  residualq->add_task(task130);

  auto tensor131 = vector<shared_ptr<Tensor>>{I160, Gamma58_(), t2};
  auto task131 = make_shared<Task131>(tensor131, pindex);
  task126->add_dep(task131);
  task131->add_dep(task30);
  residualq->add_task(task131);

  vector<IndexRange> I169_index = {virt_, active_, active_, active_};
  auto I169 = make_shared<Tensor>(I169_index);
  auto tensor132 = vector<shared_ptr<Tensor>>{I160, Gamma59_(), I169};
  auto task132 = make_shared<Task132>(tensor132, pindex);
  task126->add_dep(task132);
  task132->add_dep(task30);
  residualq->add_task(task132);

  auto tensor133 = vector<shared_ptr<Tensor>>{I169, t2};
  auto task133 = make_shared<Task133>(tensor133, pindex, this->e0_);
  task132->add_dep(task133);
  task133->add_dep(task30);
  residualq->add_task(task133);

  auto tensor134 = vector<shared_ptr<Tensor>>{I169, t2, f1_};
  auto task134 = make_shared<Task134>(tensor134, pindex);
  task132->add_dep(task134);
  task134->add_dep(task30);
  residualq->add_task(task134);

  auto tensor135 = vector<shared_ptr<Tensor>>{I169, t2, f1_};
  auto task135 = make_shared<Task135>(tensor135, pindex);
  task132->add_dep(task135);
  task135->add_dep(task30);
  residualq->add_task(task135);

  vector<IndexRange> I172_index = {active_, virt_};
  auto I172 = make_shared<Tensor>(I172_index);
  auto tensor136 = vector<shared_ptr<Tensor>>{I160, Gamma60_(), I172};
  auto task136 = make_shared<Task136>(tensor136, pindex);
  task126->add_dep(task136);
  task136->add_dep(task30);
  residualq->add_task(task136);

  auto tensor137 = vector<shared_ptr<Tensor>>{I172, t2, f1_};
  auto task137 = make_shared<Task137>(tensor137, pindex);
  task136->add_dep(task137);
  task137->add_dep(task30);
  residualq->add_task(task137);

  auto tensor138 = vector<shared_ptr<Tensor>>{I172, t2, f1_};
  auto task138 = make_shared<Task138>(tensor138, pindex);
  task136->add_dep(task138);
  task138->add_dep(task30);
  residualq->add_task(task138);

  vector<IndexRange> I180_index = {virt_, closed_, virt_, closed_};
  auto I180 = make_shared<Tensor>(I180_index);
  auto tensor139 = vector<shared_ptr<Tensor>>{r, I180};
  auto task139 = make_shared<Task139>(tensor139, pindex);
  task139->add_dep(task30);
  residualq->add_task(task139);

  vector<IndexRange> I181_index = {virt_, active_};
  auto I181 = make_shared<Tensor>(I181_index);
  auto tensor140 = vector<shared_ptr<Tensor>>{I180, t2, I181};
  auto task140 = make_shared<Task140>(tensor140, pindex);
  task139->add_dep(task140);
  task140->add_dep(task30);
  residualq->add_task(task140);

  auto tensor141 = vector<shared_ptr<Tensor>>{I181, Gamma16_(), f1_};
  auto task141 = make_shared<Task141>(tensor141, pindex);
  task140->add_dep(task141);
  task141->add_dep(task30);
  residualq->add_task(task141);

  vector<IndexRange> I184_index = {virt_, active_};
  auto I184 = make_shared<Tensor>(I184_index);
  auto tensor142 = vector<shared_ptr<Tensor>>{I180, t2, I184};
  auto task142 = make_shared<Task142>(tensor142, pindex);
  task139->add_dep(task142);
  task142->add_dep(task30);
  residualq->add_task(task142);

  auto tensor143 = vector<shared_ptr<Tensor>>{I184, Gamma16_(), f1_};
  auto task143 = make_shared<Task143>(tensor143, pindex);
  task142->add_dep(task143);
  task143->add_dep(task30);
  residualq->add_task(task143);

  vector<IndexRange> I187_index = {virt_, closed_};
  auto I187 = make_shared<Tensor>(I187_index);
  auto tensor144 = vector<shared_ptr<Tensor>>{I180, f1_, I187};
  auto task144 = make_shared<Task144>(tensor144, pindex);
  task139->add_dep(task144);
  task144->add_dep(task30);
  residualq->add_task(task144);

  vector<IndexRange> I188_index = {active_, virt_, closed_, active_};
  auto I188 = make_shared<Tensor>(I188_index);
  auto tensor145 = vector<shared_ptr<Tensor>>{I187, Gamma38_(), I188};
  auto task145 = make_shared<Task145>(tensor145, pindex);
  task144->add_dep(task145);
  task145->add_dep(task30);
  residualq->add_task(task145);

  auto tensor146 = vector<shared_ptr<Tensor>>{I188, t2};
  auto task146 = make_shared<Task146>(tensor146, pindex);
  task145->add_dep(task146);
  task146->add_dep(task30);
  residualq->add_task(task146);

  vector<IndexRange> I190_index = {virt_, closed_};
  auto I190 = make_shared<Tensor>(I190_index);
  auto tensor147 = vector<shared_ptr<Tensor>>{I180, f1_, I190};
  auto task147 = make_shared<Task147>(tensor147, pindex);
  task139->add_dep(task147);
  task147->add_dep(task30);
  residualq->add_task(task147);

  vector<IndexRange> I191_index = {active_, virt_, closed_, active_};
  auto I191 = make_shared<Tensor>(I191_index);
  auto tensor148 = vector<shared_ptr<Tensor>>{I190, Gamma38_(), I191};
  auto task148 = make_shared<Task148>(tensor148, pindex);
  task147->add_dep(task148);
  task148->add_dep(task30);
  residualq->add_task(task148);

  auto tensor149 = vector<shared_ptr<Tensor>>{I191, t2};
  auto task149 = make_shared<Task149>(tensor149, pindex);
  task148->add_dep(task149);
  task149->add_dep(task30);
  residualq->add_task(task149);

  vector<IndexRange> I199_index = {closed_, active_};
  auto I199 = make_shared<Tensor>(I199_index);
  auto tensor150 = vector<shared_ptr<Tensor>>{I180, t2, I199};
  auto task150 = make_shared<Task150>(tensor150, pindex);
  task139->add_dep(task150);
  task150->add_dep(task30);
  residualq->add_task(task150);

  auto tensor151 = vector<shared_ptr<Tensor>>{I199, Gamma38_(), f1_};
  auto task151 = make_shared<Task151>(tensor151, pindex);
  task150->add_dep(task151);
  task151->add_dep(task30);
  residualq->add_task(task151);

  vector<IndexRange> I202_index = {closed_, active_};
  auto I202 = make_shared<Tensor>(I202_index);
  auto tensor152 = vector<shared_ptr<Tensor>>{I180, t2, I202};
  auto task152 = make_shared<Task152>(tensor152, pindex);
  task139->add_dep(task152);
  task152->add_dep(task30);
  residualq->add_task(task152);

  auto tensor153 = vector<shared_ptr<Tensor>>{I202, Gamma38_(), f1_};
  auto task153 = make_shared<Task153>(tensor153, pindex);
  task152->add_dep(task153);
  task153->add_dep(task30);
  residualq->add_task(task153);

  vector<IndexRange> I204_index = {virt_, closed_, active_, virt_};
  auto I204 = make_shared<Tensor>(I204_index);
  auto tensor154 = vector<shared_ptr<Tensor>>{r, I204};
  auto task154 = make_shared<Task154>(tensor154, pindex);
  task154->add_dep(task30);
  residualq->add_task(task154);

  vector<IndexRange> I205_index = {virt_, closed_, active_, active_};
  auto I205 = make_shared<Tensor>(I205_index);
  auto tensor155 = vector<shared_ptr<Tensor>>{I204, f1_, I205};
  auto task155 = make_shared<Task155>(tensor155, pindex);
  task154->add_dep(task155);
  task155->add_dep(task30);
  residualq->add_task(task155);

  vector<IndexRange> I206_index = {active_, virt_, closed_, active_};
  auto I206 = make_shared<Tensor>(I206_index);
  auto tensor156 = vector<shared_ptr<Tensor>>{I205, Gamma35_(), I206};
  auto task156 = make_shared<Task156>(tensor156, pindex);
  task155->add_dep(task156);
  task156->add_dep(task30);
  residualq->add_task(task156);

  auto tensor157 = vector<shared_ptr<Tensor>>{I206, t2};
  auto task157 = make_shared<Task157>(tensor157, pindex);
  task156->add_dep(task157);
  task157->add_dep(task30);
  residualq->add_task(task157);

  vector<IndexRange> I208_index = {virt_, closed_, active_, active_};
  auto I208 = make_shared<Tensor>(I208_index);
  auto tensor158 = vector<shared_ptr<Tensor>>{I204, f1_, I208};
  auto task158 = make_shared<Task158>(tensor158, pindex);
  task154->add_dep(task158);
  task158->add_dep(task30);
  residualq->add_task(task158);

  auto tensor159 = vector<shared_ptr<Tensor>>{I208, Gamma32_(), t2};
  auto task159 = make_shared<Task159>(tensor159, pindex);
  task158->add_dep(task159);
  task159->add_dep(task30);
  residualq->add_task(task159);

  auto tensor160 = vector<shared_ptr<Tensor>>{I208, Gamma35_(), t2};
  auto task160 = make_shared<Task160>(tensor160, pindex);
  task158->add_dep(task160);
  task160->add_dep(task30);
  residualq->add_task(task160);

  vector<IndexRange> I217_index = {virt_, active_};
  auto I217 = make_shared<Tensor>(I217_index);
  auto tensor161 = vector<shared_ptr<Tensor>>{I204, f1_, I217};
  auto task161 = make_shared<Task161>(tensor161, pindex);
  task154->add_dep(task161);
  task161->add_dep(task30);
  residualq->add_task(task161);

  auto tensor162 = vector<shared_ptr<Tensor>>{I217, Gamma60_(), t2};
  auto task162 = make_shared<Task162>(tensor162, pindex);
  task161->add_dep(task162);
  task162->add_dep(task30);
  residualq->add_task(task162);

  vector<IndexRange> I220_index = {virt_, active_};
  auto I220 = make_shared<Tensor>(I220_index);
  auto tensor163 = vector<shared_ptr<Tensor>>{I204, f1_, I220};
  auto task163 = make_shared<Task163>(tensor163, pindex);
  task154->add_dep(task163);
  task163->add_dep(task30);
  residualq->add_task(task163);

  auto tensor164 = vector<shared_ptr<Tensor>>{I220, Gamma60_(), t2};
  auto task164 = make_shared<Task164>(tensor164, pindex);
  task163->add_dep(task164);
  task164->add_dep(task30);
  residualq->add_task(task164);

  vector<IndexRange> I223_index = {closed_, active_};
  auto I223 = make_shared<Tensor>(I223_index);
  auto tensor165 = vector<shared_ptr<Tensor>>{I204, t2, I223};
  auto task165 = make_shared<Task165>(tensor165, pindex);
  task154->add_dep(task165);
  task165->add_dep(task30);
  residualq->add_task(task165);

  auto tensor166 = vector<shared_ptr<Tensor>>{I223, Gamma38_(), f1_};
  auto task166 = make_shared<Task166>(tensor166, pindex);
  task165->add_dep(task166);
  task166->add_dep(task30);
  residualq->add_task(task166);

  vector<IndexRange> I226_index = {closed_, active_};
  auto I226 = make_shared<Tensor>(I226_index);
  auto tensor167 = vector<shared_ptr<Tensor>>{I204, t2, I226};
  auto task167 = make_shared<Task167>(tensor167, pindex);
  task154->add_dep(task167);
  task167->add_dep(task30);
  residualq->add_task(task167);

  auto tensor168 = vector<shared_ptr<Tensor>>{I226, Gamma38_(), f1_};
  auto task168 = make_shared<Task168>(tensor168, pindex);
  task167->add_dep(task168);
  task168->add_dep(task30);
  residualq->add_task(task168);

  vector<IndexRange> I229_index = {active_, virt_, closed_, virt_};
  auto I229 = make_shared<Tensor>(I229_index);
  auto tensor169 = vector<shared_ptr<Tensor>>{I204, Gamma79_(), I229};
  auto task169 = make_shared<Task169>(tensor169, pindex);
  task154->add_dep(task169);
  task169->add_dep(task30);
  residualq->add_task(task169);

  auto tensor170 = vector<shared_ptr<Tensor>>{I229, t2};
  auto task170 = make_shared<Task170>(tensor170, pindex);
  task169->add_dep(task170);
  task170->add_dep(task30);
  residualq->add_task(task170);

  vector<IndexRange> I233_index = {closed_, active_, virt_, virt_};
  auto I233 = make_shared<Tensor>(I233_index);
  auto tensor171 = vector<shared_ptr<Tensor>>{I204, Gamma38_(), I233};
  auto task171 = make_shared<Task171>(tensor171, pindex);
  task154->add_dep(task171);
  task171->add_dep(task30);
  residualq->add_task(task171);

  auto tensor172 = vector<shared_ptr<Tensor>>{I233, t2};
  auto task172 = make_shared<Task172>(tensor172, pindex, this->e0_);
  task171->add_dep(task172);
  task172->add_dep(task30);
  residualq->add_task(task172);

  auto tensor173 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task173 = make_shared<Task173>(tensor173, pindex);
  task171->add_dep(task173);
  task173->add_dep(task30);
  residualq->add_task(task173);

  auto tensor174 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task174 = make_shared<Task174>(tensor174, pindex);
  task171->add_dep(task174);
  task174->add_dep(task30);
  residualq->add_task(task174);

  auto tensor175 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task175 = make_shared<Task175>(tensor175, pindex);
  task171->add_dep(task175);
  task175->add_dep(task30);
  residualq->add_task(task175);

  auto tensor176 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task176 = make_shared<Task176>(tensor176, pindex);
  task171->add_dep(task176);
  task176->add_dep(task30);
  residualq->add_task(task176);

  auto tensor177 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task177 = make_shared<Task177>(tensor177, pindex);
  task171->add_dep(task177);
  task177->add_dep(task30);
  residualq->add_task(task177);

  auto tensor178 = vector<shared_ptr<Tensor>>{I233, t2, f1_};
  auto task178 = make_shared<Task178>(tensor178, pindex);
  task171->add_dep(task178);
  task178->add_dep(task30);
  residualq->add_task(task178);

  vector<IndexRange> I251_index = {virt_, virt_, active_, active_};
  auto I251 = make_shared<Tensor>(I251_index);
  auto tensor179 = vector<shared_ptr<Tensor>>{I204, f1_, I251};
  auto task179 = make_shared<Task179>(tensor179, pindex);
  task154->add_dep(task179);
  task179->add_dep(task30);
  residualq->add_task(task179);

  auto tensor180 = vector<shared_ptr<Tensor>>{I251, Gamma60_(), t2};
  auto task180 = make_shared<Task180>(tensor180, pindex);
  task179->add_dep(task180);
  task180->add_dep(task30);
  residualq->add_task(task180);

  vector<IndexRange> I253_index = {virt_, active_, active_, virt_};
  auto I253 = make_shared<Tensor>(I253_index);
  auto tensor181 = vector<shared_ptr<Tensor>>{r, I253};
  auto task181 = make_shared<Task181>(tensor181, pindex);
  task181->add_dep(task30);
  residualq->add_task(task181);

  vector<IndexRange> I254_index = {virt_, active_, active_, active_};
  auto I254 = make_shared<Tensor>(I254_index);
  auto tensor182 = vector<shared_ptr<Tensor>>{I253, f1_, I254};
  auto task182 = make_shared<Task182>(tensor182, pindex);
  task181->add_dep(task182);
  task182->add_dep(task30);
  residualq->add_task(task182);

  auto tensor183 = vector<shared_ptr<Tensor>>{I254, Gamma59_(), t2};
  auto task183 = make_shared<Task183>(tensor183, pindex);
  task182->add_dep(task183);
  task183->add_dep(task30);
  residualq->add_task(task183);

  vector<IndexRange> I257_index = {active_, active_, virt_, virt_};
  auto I257 = make_shared<Tensor>(I257_index);
  auto tensor184 = vector<shared_ptr<Tensor>>{I253, Gamma60_(), I257};
  auto task184 = make_shared<Task184>(tensor184, pindex);
  task181->add_dep(task184);
  task184->add_dep(task30);
  residualq->add_task(task184);

  auto tensor185 = vector<shared_ptr<Tensor>>{I257, t2, f1_};
  auto task185 = make_shared<Task185>(tensor185, pindex);
  task184->add_dep(task185);
  task185->add_dep(task30);
  residualq->add_task(task185);

  auto tensor186 = vector<shared_ptr<Tensor>>{I257, t2, f1_};
  auto task186 = make_shared<Task186>(tensor186, pindex);
  task184->add_dep(task186);
  task186->add_dep(task30);
  residualq->add_task(task186);

  vector<IndexRange> I259_index = {virt_, virt_, active_, active_};
  auto I259 = make_shared<Tensor>(I259_index);
  auto tensor187 = vector<shared_ptr<Tensor>>{r, I259};
  auto task187 = make_shared<Task187>(tensor187, pindex);
  task187->add_dep(task30);
  residualq->add_task(task187);

  auto tensor188 = vector<shared_ptr<Tensor>>{I259, Gamma90_(), t2};
  auto task188 = make_shared<Task188>(tensor188, pindex);
  task187->add_dep(task188);
  task188->add_dep(task30);
  residualq->add_task(task188);

  auto tensor189 = vector<shared_ptr<Tensor>>{I259, Gamma60_(), t2};
  auto task189 = make_shared<Task189>(tensor189, pindex, this->e0_);
  task187->add_dep(task189);
  task189->add_dep(task30);
  residualq->add_task(task189);

  return residualq;
}


#endif
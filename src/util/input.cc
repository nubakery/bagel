//
// Newint - Parallel electron correlation program.
// Filename: input.cc
// Copyright (C) 2011 Toru Shiozaki
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


#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <src/util/input.h>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

InputData::InputData(const string filename) : inputfile_(filename) {
  ifstream ifs;
  ifs.open(inputfile_);
  if (!ifs.is_open())
    throw runtime_error("Your input file cannot be opened.");

  string content = "";
  while(1) {
    string sline;
    if (!getline(ifs, sline)) break;
    // get rid of comments
    const regex comm("^(.*)//(.*)$");
    const string ss = sline;
    auto start = ss.begin();  
    auto end = ss.end();  
    smatch what;
    while (regex_search(start, end, what, comm)) {
      sline = what[1];
      const string sk = sline;
      start = sk.begin();
      end   = sk.end();
    }
    content += sline;
  }
  // true false to 1 and 0 to be friendly to lexical_cast which does not accept true/false
  {
    const regex reg_true("^(.*)=(\\s*)(true)(\\s*);(.*)$");
    const regex reg_false("^(.*)=(\\s*)(false)(\\s*);(.*)$");
    const string ss = content;
    auto start = ss.begin();
    auto end = ss.end();
    smatch what;
    while (regex_search(start, end, what, reg_true)) {
      const string sk = what[1] + "=1;" + what[5];  
      start = sk.begin();
      end = sk.end();
      content = sk;
    }
    while (regex_search(start, end, what, reg_false)) {
      const string sk = what[1] + "=0;" + what[5];  
      start = sk.begin();
      end = sk.end();
      content = sk;
    }
  }

  // first split with { and }
  vector<string> blocks;
  vector<string> pairs;
  vector<string> lines;
  if (content.find("}") == string::npos) throw runtime_error("Check your input format");
  split(blocks, content, boost::is_any_of("}"));
  for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
    if (iter->size() == 0) continue;
    split(pairs, *iter, boost::is_any_of("{"));
    if (pairs[1].size() > 0) {
      trim(pairs[0]);
      string tag = pairs[0];
      transform(tag.begin(), tag.end(), tag.begin(), ::tolower);

      split(lines, pairs[1], boost::is_any_of(";"));
      multimap<string, string> tmp;
      for (auto i = lines.begin(); i != lines.end(); ++i) {
        if (i->size() > 0) {
          vector<string> ll;
          split(ll, *i, boost::is_any_of("="));
          if (ll.size() != 2) {
            stringstream ss;
            ss << "There seem " << ll.size()-1 << " '=' in a single directive. Check your input.";
            throw runtime_error(ss.str());
          }
          trim(ll[0]); trim(ll[1]);
          transform(ll[0].begin(), ll[0].end(), ll[0].begin(), ::tolower);
          transform(ll[1].begin(), ll[1].end(), ll[1].begin(), ::tolower);
          tmp.insert(make_pair(ll[0],ll[1]));
        }
      }
      data_.push_back(make_pair(tag, tmp));
    }
  }
}

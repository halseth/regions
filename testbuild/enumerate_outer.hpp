//
//  enumerate_outer.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef enumerate_outer_hpp
#define enumerate_outer_hpp

#include <vector>
#include <iostream>
using namespace std;

#include "BaseRegion.h"

void enumerate_non_dominator_outer_3regions(vector<BaseRegion> &outer_non_dom_3regions, bool removeEdge);
void enumerate_non_dominator_outer_4regions(vector<BaseRegion> &outer_non_dom_4regions, bool removeEdge);
void generate_outer_6regions(map<vector<int>,BaseRegion> &signature_minimal_000,
                             map<vector<int>,BaseRegion> &signature_minimal_001,
                             map<vector<int>,BaseRegion> &signature_minimal_010,
                             map<vector<int>,BaseRegion> &signature_minimal_011,
                             map<vector<int>,BaseRegion> &signature_minimal_100,
                             map<vector<int>,BaseRegion> &signature_minimal_101,
                             map<vector<int>,BaseRegion> &signature_minimal_110,
                             map<vector<int>,BaseRegion> &signature_minimal_111,
                             const vector<BaseRegion> &outer_3regions_with_edge,
                             const vector<BaseRegion> &outer_4regions_with_edge,
                             const vector<BaseRegion> &outer_3regions_without_edge,
                             const vector<BaseRegion> &outer_4regions_without_edge
                             );

#endif /* enumerate_outer_hpp */

//
//  generate_4starregions_from_inner.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_4starregions_from_inner_hpp
#define generate_4starregions_from_inner_hpp
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"

void generate_4starregions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                      const vector<BaseRegion> &inner_2regions,
                                      const vector<BaseRegion> &inner_3regions,
                                      const vector<BaseRegion> &inner_4starregions,
                                      const vector<BaseRegion> &regions_3hat_with_edges,
                                      const vector<BaseRegion> &regions_3hat_without_ac_edge,
                                      const vector<BaseRegion> &regions_4hat_with_edges,
                                      const vector<BaseRegion> &regions_4hat_without_ad_edge,
                                      const vector<BaseRegion> &regions_3_with_edges
                                      );

#endif /* generate_4starregions_from_inner_hpp */

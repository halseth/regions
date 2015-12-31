//
//  generate_3regions_from_inner.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_3regions_from_inner_hpp
#define generate_3regions_from_inner_hpp

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"
#include "store_sign.h"

void generate_3regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &inner_2regions,
                                  const vector<BaseRegion> &inner_3regions,
                                  const vector<BaseRegion> &inner_4starregions,
                                  const vector<BaseRegion> &outer_general_3regions_with_edge,
                                  const vector<BaseRegion> &outer_general_3regions_without_edge,
                                  bool with_edge);

#endif /* generate_3regions_from_inner_hpp */

//
//  generate_from_inner.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_from_inner_hpp
#define generate_from_inner_hpp

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"
#include "store_sign.h"

void generate_from_nonempty_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &inner_2regions,
                                  const vector<BaseRegion> &inner_3regions,
                                  const vector<BaseRegion> &inner_4regions,
                                  const vector<BaseRegion> &inner_4starregions,
                                  const vector<BaseRegion> &inner_5regions,
                                  const vector<BaseRegion> &inner_6regions,
                                  const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                                  const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                                  const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                                  const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                                  );

#endif /* generate_from_inner_hpp */

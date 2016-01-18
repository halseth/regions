//
//  generate_5regions_from_inner.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_5regions_from_inner_hpp
#define generate_5regions_from_inner_hpp

#include <vector>
#include <map>
using namespace std;

#include "BaseRegion.h"

void generate_5regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &inner_2regions,
                                  const vector<BaseRegion> &inner_3regions,
                                  const vector<BaseRegion> &inner_4regions,
                                  const vector<BaseRegion> &inner_4starregions,
                                  const vector<BaseRegion> &inner_5regions,
                                  const vector<BaseRegion> &inner_6regions,
                                  const vector<BaseRegion> &empty_inner_6regions,
                                  const vector<BaseRegion> &regions_3hat_with_edges,
                                  const vector<BaseRegion> &regions_3hat_without_ac_edge,
                                  const vector<BaseRegion> &regions_4hat_with_edges,
                                  const vector<BaseRegion> &regions_4hat_without_ad_edge,
                                  const vector<BaseRegion> &regions_5hat_with_edges,
                                  const vector<BaseRegion> &non_dom_regions_3hat_with_edges,
                                  const vector<BaseRegion> &non_dom_regions_3hat_without_ac_edge,
                                  const vector<BaseRegion> &non_dom_regions_4hat_with_edges,
                                  const vector<BaseRegion> &non_dom_regions_4hat_without_ad_edge,
                                  const vector<BaseRegion> &regions_3,
                                  const vector<BaseRegion> &regions_4
                                  );

#endif /* generate_5regions_from_inner_hpp */

//
//  generate_hat_regions.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 22/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_hat_regions_hpp
#define generate_hat_regions_hpp

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"
#include "HatRegion.h"
#include "store_sign.h"

void generate_3hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                                      bool with_edge
                                      );

void generate_4hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edge,
                           const vector<BaseRegion> &regions_3hat_without_edge,
                           const vector<BaseRegion> &inner_2regions,
                           const vector<BaseRegion> &inner_3regions,
                           const vector<BaseRegion> &inner_4regions,
                           bool with_bc_edge,
                           bool with_ad_edge
                           );
void generate_5hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edge,
                           const vector<BaseRegion> &regions_3hat_without_ac_edge,
                           const vector<BaseRegion> &regions_4hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_without_bc_edge,
                           const vector<BaseRegion> &regions_4hat_without_ad_edge,
                           const vector<BaseRegion> &regions_4hat_without_bc_ad_edges,
                           bool with_de_edge
                           );
void generate_6hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_without_ad_edge,
                           const vector<BaseRegion> &regions_5hat_with_edges,
                           const vector<BaseRegion> &regions_5hat_without_de_edge
                           );

#endif /* generate_hat_regions_hpp */

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

void generate_6regions_from_empty_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                        const vector<BaseRegion> &empty_inner_2regions,
                                        const vector<BaseRegion> &empty_inner_3regions,
                                        const vector<BaseRegion> &empty_inner_4regions,
                                        const vector<BaseRegion> &empty_inner_4starregions,
                                        const vector<BaseRegion> &empty_inner_5regions,
                                        const vector<BaseRegion> &empty_inner_6regions,
                                        const vector<BaseRegion> &outer_general_3regions_with_edge,
                                        const vector<BaseRegion> &outer_general_4regions_with_edge,
                                        const vector<BaseRegion> &outer_general_3regions_without_edge,
                                        const vector<BaseRegion> &outer_general_4regions_without_edge
                                        );
void generate_6regions_from_nonempty_inner(map<vector<int>,BaseRegion> &signature_minimal,
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

void generate_6regions_with_no_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                     const vector<BaseRegion> &regions_3hat_with_edges,
                                     const vector<BaseRegion> &regions_4hat_with_edges,
                                     const vector<BaseRegion> &regions_5hat_with_edges,
                                     const vector<BaseRegion> &regions_6hat_with_edges
                                     );

vector<BaseRegion> choose_outer_regions(bool edge,
                                        const vector<BaseRegion> &regions_with_edge,
                                        const vector<BaseRegion> &regions_without_edge
                                        );
vector<BaseRegion> choose_outer_regions(int size, bool edge,
                                        const vector<BaseRegion> &outer_3regions_with_edge,
                                        const vector<BaseRegion> &outer_3regions_without_edge,
                                        const vector<BaseRegion> &outer_4regions_with_edge,
                                        const vector<BaseRegion> &outer_4regions_without_edge
                                        );

void generate_6regions(map<vector<int>,BaseRegion> &signature_minimal,
                       const vector<BaseRegion> &inner_2regions,
                       const vector<BaseRegion> &inner_3regions,
                       const vector<BaseRegion> &inner_4regions,
                       const vector<BaseRegion> &inner_4starregions,
                       const vector<BaseRegion> &inner_5regions,
                       const vector<BaseRegion> &inner_6regions,
                       const vector<BaseRegion> &empty_inner_2regions,
                       const vector<BaseRegion> &empty_inner_3regions,
                       const vector<BaseRegion> &empty_inner_4regions,
                       const vector<BaseRegion> &empty_inner_4starregions,
                       const vector<BaseRegion> &empty_inner_5regions,
                       const vector<BaseRegion> &empty_inner_6regions,
                       const vector<BaseRegion> &regions_3hat_with_edges,
                       const vector<BaseRegion> &regions_4hat_with_edges,
                       const vector<BaseRegion> &regions_5hat_with_edges,
                       const vector<BaseRegion> &regions_6hat_with_edges,
                       const vector<BaseRegion> &regions_3hat_without_ac_edge,
                       const vector<BaseRegion> &regions_4hat_without_ad_edge,
                       const vector<BaseRegion> &non_dom_regions_3hat_with_edges,
                       const vector<BaseRegion> &non_dom_regions_4hat_with_edges,
                       const vector<BaseRegion> &non_dom_regions_3hat_without_ac_edge,
                       const vector<BaseRegion> &non_dom_regions_4hat_without_ad_edge
                       );

#endif /* generate_from_inner_hpp */

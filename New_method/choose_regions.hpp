//
//  choose_regions.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#ifndef choose_regions_hpp
#define choose_regions_hpp

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"
#include "store_sign.h"

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

#endif /* choose_regions_hpp */

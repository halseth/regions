//
//  generate_basic_regions.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#ifndef generate_basic_regions_hpp
#define generate_basic_regions_hpp

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "BaseRegion.h"
#include "Region.h"
#include "store_sign.h"

void generate_basic_regions(map<vector<int>, BaseRegion> &sign_minimal);
void build_from_basic_regions(map<vector<int>, BaseRegion> &sign_minimal, const map<vector<int>, BaseRegion> &basic_regions);

#endif /* generate_basic_regions_hpp */

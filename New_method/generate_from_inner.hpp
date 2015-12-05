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

void generate_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                         vector<BaseRegion> &inner_2regions,
                         vector<BaseRegion> &inner_3regions,
                         vector<BaseRegion> &inner_4regions,
                         vector<BaseRegion> &inner_4starregions,
                         vector<BaseRegion> &inner_5regions,
                         vector<BaseRegion> &inner_6regions,
                         map<vector<int>, BaseRegion> &regions_3hat,
                         map<vector<int>, BaseRegion> &regions_4hat
                         );

#endif /* generate_from_inner_hpp */

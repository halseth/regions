//
//  store_sign.h
//  New_method
//
//  Created by Johan Torås Halseth on 20/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef New_method_store_sign_h
#define New_method_store_sign_h

#include <vector>
#include <map>
#include "BaseRegion.h"

void print_map(const std::map<std::vector<int>,BaseRegion > &map);
void store_sign(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal);
bool contains_sign(std::map<std::vector<int>,BaseRegion> &regions, BaseRegion &region);

#endif

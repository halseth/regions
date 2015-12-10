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
#include "InnerRegion.hpp"

void store_sign(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal);
void store_sign_if_valid(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal);
void store_sign_if_valid3(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal);
bool contains_sign(std::map<std::vector<int>,BaseRegion> &regions, BaseRegion &region);
//void inner_region_store_sign(InnerRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal);

#endif

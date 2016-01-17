//
//  store_region_map.h
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__store_region_map__
#define __New_method__store_region_map__

#include "BaseRegion.h"

void store_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename);
void store_region_vector(std::vector<BaseRegion> vec, std::string filename);
void load_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename);
void load_region_vector(std::vector<BaseRegion> &vec, std::string filename);
std::vector<BaseRegion> toVector(std::map<std::vector<int>,BaseRegion> &map);

#endif /* defined(__New_method__store_region_map__) */

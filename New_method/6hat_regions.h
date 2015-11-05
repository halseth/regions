//
//  6hat_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__6hat_regions__
#define __New_method__6hat_regions__

#include <vector>
#include <map>

#include "BaseRegion.h"
using namespace std;

void generate_6hat_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_4hat_b, std::map<std::vector<int>,BaseRegion> &regions_5hat_b, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_6hat_b);
void old_generate_6hat_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_4hat_a,std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_3hat_a, std::map<std::vector<int>,BaseRegion> &regions_6hat_a, std::map<std::vector<int>,BaseRegion> &regions_5hat_a);

#endif /* defined(__New_method__6hat_regions__) */

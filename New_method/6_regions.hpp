//
//  6_regions.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 07/10/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef New_method_6_regions_hpp
#define New_method_6_regions_hpp

#include <vector>
#include <map>

#include "BaseRegion.h"
using namespace std;

void generate_6_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal,std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_4star, std::map<std::vector<int>,BaseRegion> &regions_5, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_6hat);

#endif /* __regions_hpp */

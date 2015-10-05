//
//  3hat_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 27/08/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef New_method_3hat_regions_h
#define New_method_3hat_regions_h

#include <map>
#include "BaseRegion.h"

void generate_3hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_ab);

#endif /* defined(__New_method___hat_regions__) */

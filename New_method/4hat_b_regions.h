//
//  generate_4b_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 20/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef New_method_4hat_b_regions_h
#define New_method_4hat_b_regions_h

#include <vector>
#include "BaseRegion.h"

// Generates 4hat regions where all internal are dominated by b
void generate_4hat_b_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_b);

#endif

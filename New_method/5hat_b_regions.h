//
//  5hat_a_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 21/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method_5hat_b_regions__
#define __New_method_5hat_b_regions__

#include "HatABCRegion.h"

// Generates 5hat regions where all internal are dominated by a
void generate_5hat_b_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_b, std::map<std::vector<int>,BaseRegion> &regions_4hat_b);

#endif /* defined(__New_method___hat_a_regions__) */

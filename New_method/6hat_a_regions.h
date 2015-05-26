//
//  6hat_a_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__6hat_a_regions__
#define __New_method__6hat_a_regions__

#include "HatABCRegion.h"

// Generates 6hat regions where all internal are dominated by a
void generate_6hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal);

#endif /* defined(__New_method__6hat_a_regions__) */

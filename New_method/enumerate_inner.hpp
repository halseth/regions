//
//  enumerate_inner.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 03/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef enumerate_inner_hpp
#define enumerate_inner_hpp

#include <stdio.h>
#include "Region.h"

void generate_inner(std::map<std::vector<int>, BaseRegion> &sign_minimal, int size, int endpoint1, int endpoint2);
void enumerate_inner_hat_regions(vector<BaseRegion> &hat_regions, int size, int endpoint1, int endpoint2);
    

#endif /* enumerate_inner_hpp */

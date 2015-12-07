//
//  enumerate_outer.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef enumerate_outer_hpp
#define enumerate_outer_hpp

#include <vector>
#include <iostream>
using namespace std;

#include "BaseRegion.h"

void enumerate_non_dominator_outer_3regions(vector<BaseRegion> &outer_non_dom_3regions);
void enumerate_non_dominator_outer_4regions(vector<BaseRegion> &outer_non_dom_4regions);

#endif /* enumerate_outer_hpp */

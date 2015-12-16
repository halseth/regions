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

void enumerate_inner_2regions(std::vector<BaseRegion> &inner_2regions);
void enumerate_inner_3regions(std::vector<BaseRegion> &inner_3regions);
void enumerate_inner_4regions(std::vector<BaseRegion> &inner_4regions);
void enumerate_inner_4starregions(std::vector<BaseRegion> &inner_4regions);
void enumerate_inner_5regions(std::vector<BaseRegion> &inner_5regions);
void enumerate_inner_6regions(std::map<std::vector<int>, BaseRegion> &sign_minimal);
void filter_on_red_rules(std::vector<BaseRegion> &regions);

#endif /* enumerate_inner_hpp */

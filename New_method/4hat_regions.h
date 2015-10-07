//
//  4hat_regions.h
//  New_method
//
//  Created by Johan Torås Halseth on 21/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef New_method_4hat_regions_h
#define New_method_4hat_regions_h

void generate_4hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<vector<int>,BaseRegion> &regions_3hat, std::map<vector<int>,BaseRegion> &regions_4hat_b);
void generate_4hat_regions_new(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_4hat_a);

#endif

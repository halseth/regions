//
//  main.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 07/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "BaseRegion.h"

#include "enumerate_inner.hpp"
#include "enumerate_outer.hpp"
#include "generate_from_inner.hpp"

#include "store_region_map.h"
#include "store_sign.h"
#include "signature_benchmark.hpp"


#define FILENAME_6 "regions_6.txt"
map<vector<int>, BaseRegion> regions_6;


int main(){
    
//    benchmark();
//    return 0;
    vector<BaseRegion> outer_non_dom_3regions_with_edge;
    vector<BaseRegion> outer_non_dom_3regions_without_edge;
    vector<BaseRegion> outer_non_dom_4regions_with_edge;
    vector<BaseRegion> outer_non_dom_4regions_without_edge;
    
    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_without_edge, true);
    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_without_edge, true);
    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_with_edge, false);
    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_with_edge, false);

    std::vector<BaseRegion> inner_2regions;
    load_region_vector(inner_2regions, "inner_2regions.txt");
    std::vector<BaseRegion> inner_3regions;
    load_region_vector(inner_3regions, "inner_3regions.txt");
    std::vector<BaseRegion> inner_4regions;
    load_region_vector(inner_4regions, "inner_4regions.txt");
    std::vector<BaseRegion> inner_4starregions;
    load_region_vector(inner_4starregions, "inner_4starregions.txt");
    std::vector<BaseRegion> inner_5regions;
    load_region_vector(inner_5regions, "inner_5regions.txt");
    std::vector<BaseRegion> inner_6regions;
    load_region_vector(inner_6regions, "inner_6regions.txt");
    
    generate_from_nonempty_inner(regions_6, inner_2regions, inner_3regions, inner_4regions, inner_4starregions, inner_5regions, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    
//    map<vector<int>, BaseRegion> inner_regions_6;
//    enumerate_inner_6regions(inner_regions_6);
//    store_region_map(inner_regions_6, "sign_minimal_inner6.txt");

    cout << "main done" << endl;
    return 0;
}

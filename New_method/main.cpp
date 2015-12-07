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


#define FILENAME_6 "regions_6.txt"
map<vector<int>, BaseRegion> regions_6;


int main(){
    
    vector<BaseRegion> outer_non_dom_3regions;
    vector<BaseRegion> outer_non_dom_4regions;
    
    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions);
    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions);    
    
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
    
    generate_from_inner(regions_6, inner_2regions, inner_3regions, inner_4regions, inner_4starregions, inner_5regions, inner_6regions, outer_non_dom_3regions, outer_non_dom_4regions);
    
    
//    enumerate_inner_2regions(inner_2regions);
//    store_region_vector(inner_2regions, "inner_2regions.txt");
//
////    return 0;
//    
//    std::vector<BaseRegion> inner_3regions;
//    enumerate_inner_3regions(inner_3regions);
//    store_region_vector(inner_3regions, "inner_3regions.txt");
//    
////    return 0;
//    
//    std::vector<BaseRegion> inner_4regions;
//    enumerate_inner_4regions(inner_4regions);
//    store_region_vector(inner_4regions, "inner_4regions.txt");
//    
////    return 0;
//    
//    std::vector<BaseRegion> inner_4starregions;
//    enumerate_inner_4starregions(inner_4starregions);
//    store_region_vector(inner_4starregions, "inner_4starregions.txt");
//    
//    return 0;
//
//    std::vector<BaseRegion> inner_5regions;
//    enumerate_inner_5regions(inner_5regions);
//    store_region_vector(inner_5regions, "inner_5regions.txt");
//    
////    return 0;
//    
//    std::vector<BaseRegion> inner_6regions;
//    enumerate_inner_6regions(inner_6regions);
//    store_region_vector(inner_6regions, "inner_6regions.txt");
//    
//    return 0;
    

    cout << "main done" << endl;
    return 0;
}

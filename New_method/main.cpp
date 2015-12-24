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
#include "generate_empty_inner.hpp"
#include "generate_3regions_from_inner.hpp"
#include "generate_hat_regions.hpp"


#define FILENAME_6 "regions_6.txt"
//vector<BaseRegion> regions_6;
//
//vector<BaseRegion> regions_3_with_edge;
//vector<BaseRegion> regions_3_without_edge;
//
//vector<BaseRegion> regions_3hat_with_edge;
//vector<BaseRegion> regions_3hat_without_edge;
//vector<BaseRegion> regions_4hat_with_edge;
//vector<BaseRegion> regions_4hat_without_edge;


int main(){
    
    
    std::vector<BaseRegion> inner_2regions;
    load_region_vector(inner_2regions, "inner_2regions.txt");
    std::vector<BaseRegion> inner_3regions;
    load_region_vector(inner_3regions, "inner_3regions.txt");
    std::vector<BaseRegion> inner_4regions;
    load_region_vector(inner_4regions, "inner_4regions.txt");
//    std::vector<BaseRegion> inner_4starregions;
//    load_region_vector(inner_4starregions, "inner_4starregions.txt");
//    std::vector<BaseRegion> inner_5regions;
//    load_region_vector(inner_5regions, "inner_5regions.txt");
//    std::vector<BaseRegion> inner_6regions;
//    load_region_vector(inner_6regions, "inner_6regions.txt");
    
    vector<BaseRegion> regions_3hat_without_edge;
    load_region_vector(regions_3hat_without_edge, "3hat_without_edge.txt");
    
    vector<BaseRegion> regions_3hat_with_edge;
    load_region_vector(regions_3hat_with_edge, "3hat_with_edge.txt");
    
    vector<BaseRegion> regions_4hat_with_edges;
    load_region_vector(regions_4hat_with_edges, "4hat_with_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_ad_edge;
    load_region_vector(regions_4hat_without_ad_edge, "4hat_without_ad_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_bc_edge;
    load_region_vector(regions_4hat_without_bc_edge, "4hat_without_bc_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_ad_bc_edges;
    load_region_vector(regions_4hat_without_bc_edge, "4hat_without_ad_bc_edges.txt");
    
    
    
    vector<BaseRegion> regions_5hat_with_edges;
    load_region_vector(regions_5hat_with_edges, "5hat_with_edges.txt");
    
    vector<BaseRegion> regions_5hat_without_de_edge;
    load_region_vector(regions_5hat_without_de_edge, "5hat_without_de_edge.txt");
    
    vector<BaseRegion> regions_6hat_with_edges;
    load_region_vector(regions_6hat_with_edges, "6hat_with_edges.txt");
    
    map<vector<int>, BaseRegion> signature_minimal;
    generate_6regions_with_no_inner(signature_minimal, regions_3hat_with_edge, regions_4hat_with_edges, regions_5hat_with_edges, regions_6hat_with_edges);
    
    return 0;
    
    
    

//    generate_empty_inner(regions_6, 6, 0, 3);
//    cout << "DOOONONOONONNONO"<< endl;
//    generate_empty_inner6(regions_6);
    return 0;
    
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
    
    

//    generate_4hat_regions(regions_4hat_with_edge, regions_3hat_with_edge, regions_3hat_without_edge, inner_2regions, inner_3regions, inner_4regions, true);
    
//    generate_3regions_from_inner(regions_3_with_edge, inner_2regions, inner_3regions, inner_4starregions, out, <#const vector<BaseRegion> &outer_general_3regions_without_edge#>, <#bool with_edge#>)

    
//    generate_6regions_from_nonempty_inner(regions_6, inner_2regions, inner_3regions, inner_4regions, inner_4starregions, inner_5regions, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    
//    map<vector<int>, BaseRegion> inner_regions_6;
//    enumerate_inner_6regions(inner_regions_6);
//    store_region_map(inner_regions_6, "sign_minimal_inner6.txt");

    cout << "main done" << endl;
    return 0;
}

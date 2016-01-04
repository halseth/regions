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
#include "generate_4regions_from_inner.hpp"
#include "generate_4starregions_from_inner.hpp"
#include "generate_5regions_from_inner.hpp"


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

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;


int main(){
//    
//    vector<BaseRegion> outer_non_dom_3regions_with_edge;
//    vector<BaseRegion> outer_non_dom_3regions_without_edge;
//    vector<BaseRegion> outer_non_dom_4regions_with_edge;
//    vector<BaseRegion> outer_non_dom_4regions_without_edge;
//    
//    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_without_edge, true);
//    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_without_edge, true);
//    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_with_edge, false);
//    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_with_edge, false);
//    
//    map<std::vector<int>, BaseRegion> outer6_000;
//    map<std::vector<int>, BaseRegion> outer6_001;
//    map<std::vector<int>, BaseRegion> outer6_010;
//    map<std::vector<int>, BaseRegion> outer6_011;
//    map<std::vector<int>, BaseRegion> outer6_100;
//    map<std::vector<int>, BaseRegion> outer6_101;
//    map<std::vector<int>, BaseRegion> outer6_110;
//    map<std::vector<int>, BaseRegion> outer6_111;
//    generate_outer_6regions(outer6_000, outer6_001, outer6_010, outer6_011, outer6_100, outer6_101, outer6_110, outer6_111, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
//    
//    print_map(outer6_000);
//    print_map(outer6_001);
//    print_map(outer6_010);
//    print_map(outer6_011);
//    print_map(outer6_100);
//    print_map(outer6_101);
//    print_map(outer6_110);
//    print_map(outer6_111);
//    
//    
//    return 0;
    
    
    
    
    // Generate sign minimal inner regions
//    std::map<std::vector<int>, BaseRegion> inner_2regions_map;
////    enumerate_inner_2regions(inner_2regions_map);
//    generate_inner(inner_2regions_map, 2, a, b);
//    store_region_map(inner_2regions_map, "inner_2regions.txt");
////
//    std::map<std::vector<int>, BaseRegion> inner_3regions_map;
////    enumerate_inner_3regions(inner_3regions_map);
//    generate_inner(inner_3regions_map, 3, a, c);
//    store_region_map(inner_3regions_map, "inner_3regions.txt");
////
//    std::map<std::vector<int>, BaseRegion> inner_4regions_map;
////    enumerate_inner_4regions(inner_4regions_map);
//    generate_inner(inner_4regions_map, 4, a, c);
//    store_region_map(inner_4regions_map, "inner_4regions.txt");
//
//    std::map<std::vector<int>, BaseRegion> inner_4starregions_map;
////    enumerate_inner_4starregions(inner_4starregions_map);
//    generate_inner(inner_4starregions_map, 4, a, d);
//    store_region_map(inner_4starregions_map, "inner_4starregions.txt");
////
//    std::map<std::vector<int>, BaseRegion> inner_5regions_map;
////    enumerate_inner_5regions(inner_5regions_map);
//    generate_inner(inner_5regions_map, 5, a, d);
//    store_region_map(inner_5regions_map, "inner_5regions.txt");
//
//    std::map<std::vector<int>, BaseRegion> inner_6regions_map;
////    enumerate_inner_6regions(inner_6regions_map);
//    generate_inner(inner_6regions_map, 6, a, d);
//    store_region_map(inner_6regions_map, "inner_6regions.txt");
    
    
    // Load inner region vectors
    std::vector<BaseRegion> inner_2regions_vec;
    load_region_vector(inner_2regions_vec, "inner_2regions.txt");
    
    std::vector<BaseRegion> inner_3regions_vec;
    load_region_vector(inner_3regions_vec, "inner_3regions.txt");
    
    std::vector<BaseRegion> inner_4regions_vec;
    load_region_vector(inner_4regions_vec, "inner_4regions.txt");

    std::vector<BaseRegion> inner_4starregions_vec;
    load_region_vector(inner_4starregions_vec, "inner_4starregions.txt");
    
    std::vector<BaseRegion> inner_5regions_vec;
    load_region_vector(inner_5regions_vec, "inner_5regions.txt");
    
    std::vector<BaseRegion> inner_6regions_vec;
    load_region_vector(inner_6regions_vec, "inner_6regions.txt");
    
    
    // Generate hat regions
//    std::map<std::vector<int>, BaseRegion> regions_3hat_with_edges_map;
//    generate_3hat_regions(regions_3hat_with_edges_map, true);
//    store_region_map(regions_3hat_with_edges_map, "3hat_with_edges.txt");
    
    vector<BaseRegion> regions_3hat_with_edges_vec;
    load_region_vector(regions_3hat_with_edges_vec, "3hat_with_edges.txt");
//
//    std::map<std::vector<int>, BaseRegion> regions_3hat_without_ac_edge_map;
//    generate_3hat_regions(regions_3hat_without_ac_edge_map, false);
//    store_region_map(regions_3hat_without_ac_edge_map, "3hat_without_ac_edge.txt");
//
    vector<BaseRegion> regions_3hat_without_ac_edge_vec;
    load_region_vector(regions_3hat_without_ac_edge_vec, "3hat_without_ac_edge.txt");

//    std::map<std::vector<int>, BaseRegion> regions_4hat_with_edges_map;
//    generate_4hat_regions(regions_4hat_with_edges_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, true, true);
//    store_region_map(regions_4hat_with_edges_map, "4hat_with_edges.txt");
    
    vector<BaseRegion> regions_4hat_with_edges_vec;
    load_region_vector(regions_4hat_with_edges_vec, "4hat_with_edges.txt");
    
//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_ad_edge_map;
//    generate_4hat_regions(regions_4hat_without_ad_edge_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, true, false);
//    store_region_map(regions_4hat_without_ad_edge_map, "4hat_without_ad_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_ad_edge_vec;
    load_region_vector(regions_4hat_without_ad_edge_vec, "4hat_without_ad_edge.txt");
    

//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_bc_edge_map;
//    generate_4hat_regions(regions_4hat_without_bc_edge_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, false, true);
//    store_region_map(regions_4hat_without_bc_edge_map, "4hat_without_bc_edge.txt");
    vector<BaseRegion> regions_4hat_without_bc_edge_vec;
    load_region_vector(regions_4hat_without_bc_edge_vec, "4hat_without_bc_edge.txt");
    
//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_ad_bc_edges_map;
//    generate_4hat_regions(regions_4hat_without_ad_bc_edges_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, false, false);
//    store_region_map(regions_4hat_without_ad_bc_edges_map, "4hat_without_ad_bc_edges.txt");
    vector<BaseRegion> regions_4hat_without_ad_bc_edges_vec;
    load_region_vector(regions_4hat_without_ad_bc_edges_vec, "4hat_without_ad_bc_edges.txt");
//
//    map<vector<int>, BaseRegion> regions_5hat_with_edges_map;
//    generate_5hat_regions(regions_5hat_with_edges_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_with_edges_vec, regions_4hat_without_bc_edge_vec, regions_4hat_without_ad_edge_vec, regions_4hat_without_ad_bc_edges_vec, true);
//    store_region_map(regions_5hat_with_edges_map, "5hat_with_edges.txt");
    vector<BaseRegion> regions_5hat_with_edges_vec;
    load_region_vector(regions_5hat_with_edges_vec, "5hat_with_edges.txt");
//
//    map<vector<int>, BaseRegion> regions_5hat_without_de_edge_map;
//    generate_5hat_regions(regions_5hat_without_de_edge_map, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_with_edges_vec, regions_4hat_without_bc_edge_vec, regions_4hat_without_ad_edge_vec, regions_4hat_without_ad_bc_edges_vec, false);
//    store_region_map(regions_5hat_without_de_edge_map, "5hat_without_de_edge.txt");
    vector<BaseRegion> regions_5hat_without_de_edge_vec;
    load_region_vector(regions_5hat_without_de_edge_vec, "5hat_without_de_edge.txt");
//
//    map<vector<int>, BaseRegion> regions_6hat_with_edges_map;
//    generate_6hat_regions(regions_6hat_with_edges_map, regions_3hat_with_edges_vec, regions_4hat_with_edges_vec, regions_4hat_without_ad_edge_vec, regions_5hat_with_edges_vec, regions_5hat_without_de_edge_vec);
//    store_region_map(regions_6hat_with_edges_map, "6hat_with_edges.txt");
    vector<BaseRegion> regions_6hat_with_edges_vec;
    load_region_vector(regions_6hat_with_edges_vec, "6hat_with_edges.txt");
    
    
    // Generate non-dominator hat regions
    vector<BaseRegion> outer_non_dom_3regions_with_edge;
    vector<BaseRegion> outer_non_dom_3regions_without_edge;
    vector<BaseRegion> outer_non_dom_4regions_with_edge;
    vector<BaseRegion> outer_non_dom_4regions_without_edge;
    
    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_without_edge, true);
    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_without_edge, true);
    enumerate_non_dominator_outer_3regions(outer_non_dom_3regions_with_edge, false);
    enumerate_non_dominator_outer_4regions(outer_non_dom_4regions_with_edge, false);
    
    // Generate empty inner regions
    map<vector<int>, BaseRegion> empty_inner2_map;
    map<vector<int>, BaseRegion> empty_inner3_map;
    map<vector<int>, BaseRegion> empty_inner4_map;
    map<vector<int>, BaseRegion> empty_inner4star_map;
    map<vector<int>, BaseRegion> empty_inner5_map;
    map<vector<int>, BaseRegion> empty_inner6_map;
    generate_empty_inner(empty_inner2_map, 2, a, b);
    generate_empty_inner(empty_inner3_map, 3, a, c);
    generate_empty_inner(empty_inner4_map, 4, a, c);
    generate_empty_inner(empty_inner4star_map, 4, a, d);
    generate_empty_inner(empty_inner5_map, 5, a, d);
    generate_empty_inner(empty_inner6_map, 6, a, d);
    
    vector<BaseRegion> empty_inner2_vec = toVector(empty_inner2_map);
    vector<BaseRegion> empty_inner3_vec = toVector(empty_inner3_map);
    vector<BaseRegion> empty_inner4_vec = toVector(empty_inner4_map);
    vector<BaseRegion> empty_inner4star_vec = toVector(empty_inner4star_map);
    vector<BaseRegion> empty_inner5_vec = toVector(empty_inner5_map);
    vector<BaseRegion> empty_inner6_vec = toVector(empty_inner6_map);
    
    // Generate 3-regions
//    map<vector<int>, BaseRegion> regions_3_with_edges_map;
//    generate_3regions_from_inner(regions_3_with_edges_map, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, true);
//    store_region_map(regions_3_with_edges_map, "3regions.txt");
    vector<BaseRegion> regions_3_with_edges_vec;
    load_region_vector(regions_3_with_edges_vec, "3regions.txt");
    
//    map<vector<int>, BaseRegion> regions_3_without_ac_edge_map;
//    generate_3regions_from_inner(regions_3_without_ac_edge_map, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, false);
//    store_region_map(regions_3_without_ac_edge_map, "3regions_without_ac_edge.txt");
    vector<BaseRegion> regions_3_without_ac_edge_vec;
    load_region_vector(regions_3_without_ac_edge_vec, "3regions_without_ac_edge.txt");
//
//    // Generate 4-regions
//    map<vector<int>, BaseRegion> regions_4_map;
//    generate_4regions_from_inner(regions_4_map, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, inner_4starregions_vec, inner_5regions_vec, inner_6regions_vec, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_with_edges_vec);
//    store_region_map(regions_4_map, "4regions.txt");
    vector<BaseRegion> regions_4_vec;
    load_region_vector(regions_4_vec, "4regions.txt");
//
//    // Generate 4*-regions
//    map<vector<int>, BaseRegion> regions_4star_with_edges_map;
//    generate_4starregions_from_inner(regions_4star_with_edges_map, inner_2regions_vec, inner_3regions_vec, inner_4starregions_vec, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_with_edges_vec, regions_4hat_without_ad_edge_vec, regions_3_with_edges_vec, regions_3_without_ac_edge_vec, false);
//    store_region_map(regions_4star_with_edges_map, "4star_regions_with_edges.txt");
    vector<BaseRegion> regions_4star_with_edges_vec;
    load_region_vector(regions_4star_with_edges_vec, "4star_regions_with_edges.txt");
    
    // Generate 5-regions
    map<vector<int>, BaseRegion> regions_5_with_edges_map;
    generate_5regions_from_inner(regions_5_with_edges_map, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, inner_4starregions_vec, inner_5regions_vec, inner_6regions_vec, regions_3hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_with_edges_vec, regions_4hat_without_ad_edge_vec, regions_3_with_edges_vec, regions_4_vec);
    store_region_map(regions_5_with_edges_map, "5regions.txt");
    vector<BaseRegion> regions_5_with_edges_vec;
    load_region_vector(regions_5_with_edges_vec, "5regions.txt");
    
    // Generate 6-regions
    map<vector<int>, BaseRegion> regions_6_with_edges_map;
    generate_6regions(regions_6_with_edges_map, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, inner_4starregions_vec, inner_5regions_vec, inner_6regions_vec, empty_inner2_vec, empty_inner3_vec, empty_inner4_vec, empty_inner4star_vec, empty_inner5_vec, empty_inner6_vec, regions_3hat_with_edges_vec, regions_4hat_with_edges_vec, regions_5hat_with_edges_vec, regions_6hat_with_edges_vec, regions_3hat_without_ac_edge_vec, regions_4hat_without_ad_edge_vec, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    store_region_map(regions_6_with_edges_map, "6regions.txt");
    vector<BaseRegion> regions_6_with_edges_vec;
    load_region_vector(regions_6_with_edges_vec, "6regions.txt");
    
//    map<vector<int>, BaseRegion> signature_minimal_6_regions;
//    generate_6regions_with_no_inner(signature_minimal_6_regions, regions_3hat_with_edges_vec, regions_4hat_with_edges_vec, regions_5hat_with_edges_vec, regions_6hat_with_edges_vec);
    
//    generate_6regions_from_nonempty_inner(signature_minimal_6_regions, inner_2regions_vec, inner_3regions_vec, inner_4regions_vec, inner_4starregions_vec, inner_5regions_vec, inner_6regions_vec, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, star, <#const vector<BaseRegion> &outer_non_dom_4starregions_with_edge#>)
    cout << "main done" << endl;
    return 0;
    
    
    

//    generate_empty_inner(regions_6, 6, 0, 3);
//    cout << "DOOONONOONONNONO"<< endl;
//    generate_empty_inner6(regions_6);
    return 0;
    
//    benchmark();
//    return 0;
    
    

//    generate_4hat_regions(regions_4hat_with_edge, regions_3hat_with_edge, regions_3hat_without_edge, inner_2regions, inner_3regions, inner_4regions, true);
    
//    generate_3regions_from_inner(regions_3_with_edge, inner_2regions, inner_3regions, inner_4starregions, out, <#const vector<BaseRegion> &outer_general_3regions_without_edge#>, <#bool with_edge#>)

    
//    generate_6regions_from_nonempty_inner(regions_6, inner_2regions, inner_3regions, inner_4regions, inner_4starregions, inner_5regions, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    
//    map<vector<int>, BaseRegion> inner_regions_6;
//    enumerate_inner_6regions(inner_regions_6);
//    store_region_map(inner_regions_6, "sign_minimal_inner6.txt");

    cout << "main done" << endl;
    return 0;
}

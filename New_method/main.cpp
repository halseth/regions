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
#include "Region.h"

#include "enumerate_inner.hpp"
#include "enumerate_outer.hpp"

#include "store_region_map.h"
#include "store_sign.h"
#include "signature_benchmark.hpp"
#include "generate_empty_inner.hpp"
#include "generate_3regions_from_inner.hpp"
#include "generate_hat_regions.hpp"
#include "generate_4regions_from_inner.hpp"
#include "generate_4starregions_from_inner.hpp"
#include "generate_5regions_from_inner.hpp"
#include "generate_6regions_from_inner.hpp"

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;


int main(){
//    Region R1(6,a,d);
//    int node6 = R1.addNode();
//    int node7 = R1.addNode();
//    int node8 = R1.addNode();
//    int node9 = R1.addNode();
//    int node10 = R1.addNode();
//    int node11 = R1.addNode();
//    int node12 = R1.addNode();
//    int node13 = R1.addNode();
//    
//    R1.addEdge(node6, 0);
//    R1.addEdge(node6, 1);
//    R1.addEdge(node6, 2);
//    R1.addEdge(node6, node8);
//    
//    R1.addEdge(node7, 2);
//    R1.addEdge(node7, 3);
//    R1.addEdge(node7, node8);
//    R1.addEdge(node7, node9);
//    
//    R1.addEdge(node8, 0);
//    R1.addEdge(node8, 2);
//    R1.addEdge(node8, node9);
//    R1.addEdge(node8, node10);
//    
//    R1.addEdge(node9, 3);
//    R1.addEdge(node9, node10);
//    R1.addEdge(node9, node11);
//    
//    R1.addEdge(node10, 0);
//    R1.addEdge(node10, node11);
//    R1.addEdge(node10, node12);
//    
//    R1.addEdge(node11, 3);
//    R1.addEdge(node11, 5);
//    R1.addEdge(node11, node12);
//    R1.addEdge(node11, node13);
//    
//    R1.addEdge(node12, 0);
//    R1.addEdge(node12, 5);
//    
//    R1.addEdge(node13, 3);
//    R1.addEdge(node13, 4);
//    R1.addEdge(node13, 5);
//    
//    if (!R1.isValid()) {
//        cout << "BAD" << endl;
//        exit(1);
//    }
//    
//    std::ofstream regfile;
//    regfile.open("region1.txt");
//    
//    if (!regfile.is_open()) {
//        std::cerr << "ERROR opening file " << std::endl;
//        exit(0);
//    } else {
//        regfile << R1.getFormattedSignature() << std::endl;
//        regfile.close();
//        std::cout << "Done storing to file " << std::endl;
//    }
//    
//    Region R2(6,a,d);
//    node6 = R2.addNode();
//    node7 = R2.addNode();
//    node8 = R2.addNode();
//    node9 = R2.addNode();
//    node10 = R2.addNode();
//    node11 = R2.addNode();
//    node12 = R2.addNode();
//    node13 = R2.addNode();
//    
//    R2.addEdge(node6, 0);
//    R2.addEdge(node6, 1);
//    R2.addEdge(node6, 2);
//    R2.addEdge(node6, node8);
//    
//    R2.addEdge(node7, 2);
//    R2.addEdge(node7, 3);
//    R2.addEdge(node7, node8);
//    R2.addEdge(node7, node9);
//    
//    R2.addEdge(node8, 0);
//    R2.addEdge(node8, 2);
//    R2.addEdge(node8, node9);
//    R2.addEdge(node8, node10);
//    
//    R2.addEdge(node9, 3);
//    R2.addEdge(node9, node10);
//    R2.addEdge(node9, node11);
//    
//    R2.addEdge(node10, 0);
//    R2.addEdge(node10, node11);
//    R2.addEdge(node10, node12);
//    
//    R2.addEdge(node11, 3);
//    R2.addEdge(node11, 5);
//    R2.addEdge(node11, node12);
//    R2.addEdge(node11, node13);
//    
//    R2.addEdge(node12, 0);
//    R2.addEdge(node12, 5);
//    
//    R2.addEdge(node13, 3);
//    R2.addEdge(node13, 4);
//    R2.addEdge(node13, 5);
//    
//    vector<int> X;
//    X.push_back(4);
//    
//    if (!R2.isValid()) {
//        cout << "BAD" << endl;
//        exit(1);
//    }
//    
//    std::ofstream regfile2;
//    regfile2.open("region2.txt");
//    
//    if (!regfile2.is_open()) {
//        std::cerr << "ERROR opening file " << std::endl;
//        exit(0);
//    } else {
//        regfile2 << R2.getFormattedSignature() << std::endl;
//        regfile2.close();
//        std::cout << "Done storing to file " << std::endl;
//    }
//    
//    return 0;
    
    Region check(6,a,d);
    int node6 = check.addNode();
    int node7 = check.addNode();
    int node8 = check.addNode();
    
    check.addEdge(0, node6);
    check.addEdge(0, node7);
    check.addEdge(0, node8);
    
    check.addEdge(3, node6);
    
    check.addEdge(4, node7);
    
    check.addEdge(5, node7);
    check.addEdge(5, node8);
    
    check.addEdge(node6, node7);
    check.addEdge(node8, node7);
    
    vector<int> checkSign;
    check.getSignature(checkSign);
    
    vector<BaseRegion> testvec;
    load_region_vector(testvec, "6regions.txt");
    
    int num = 0;
    for (int i = 0; i < testvec.size(); i++) {
        if((++num)%100 == 0) cout << "num: " << num << endl;
        BaseRegion reg = testvec[i];
        vector<int> sign;
        reg.getSignature(sign);
        if (sign == checkSign) {
            cout << "found sign" << endl;
            reg.printRegion();
            exit(1);
        }
    }
    
//    std::ofstream file;
//    file.open("signatures.txt");
    
//    int cnt = 0;
//    if (!file.is_open()) {
//        std::cerr << "ERROR opening file " << std::endl;
//        exit(0);
//    } else {
//        for (int i = 0; i < testvec.size(); i++) {
//            BaseRegion R = testvec[i];
//            
//            
//            file << R.getFormattedSignature() << std::endl;
//            cnt++;
//            if (cnt == 11) {
//                R.printRegion();
//                cout << R.getFormattedSignature();
//                exit(0);
////                break;
//            }
//        }
//        file.close();
//        std::cout << "Done storing to file " << std::endl;
//    }
    
    
    
    
    return 0;
    
    // Generate sign minimal inner regions
//    std::map<std::vector<int>, BaseRegion> inner_2regions_map;
//    generate_inner(inner_2regions_map, 2, a, b);
//    store_region_map(inner_2regions_map, "inner_2regions.txt");
//    
//    std::map<std::vector<int>, BaseRegion> inner_3regions_map;
//    generate_inner(inner_3regions_map, 3, a, c);
//    store_region_map(inner_3regions_map, "inner_3regions.txt");
//    
//    std::map<std::vector<int>, BaseRegion> inner_4regions_map;
//    generate_inner(inner_4regions_map, 4, a, c);
//    store_region_map(inner_4regions_map, "inner_4regions.txt");
//
//    std::map<std::vector<int>, BaseRegion> inner_4starregions_map;
//    generate_inner(inner_4starregions_map, 4, a, d);
//    store_region_map(inner_4starregions_map, "inner_4starregions.txt");
//    
//    std::map<std::vector<int>, BaseRegion> inner_5regions_map;
//    generate_inner(inner_5regions_map, 5, a, d);
//    store_region_map(inner_5regions_map, "inner_5regions.txt");
//
//    std::map<std::vector<int>, BaseRegion> inner_6regions_map;
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
//    map<vector<int>, BaseRegion> regions_3hat_with_edges_map;
//    generate_3hat_regions(regions_3hat_with_edges_map, true);
//    store_region_map(regions_3hat_with_edges_map, "3hat_with_edges.txt");
    
    vector<BaseRegion> regions_3hat_with_edges_vec;
    load_region_vector(regions_3hat_with_edges_vec, "3hat_with_edges.txt");

//    std::map<std::vector<int>, BaseRegion> regions_3hat_without_ac_edge_map;
//    generate_3hat_regions(regions_3hat_without_ac_edge_map, false);
//    store_region_map(regions_3hat_without_ac_edge_map, "3hat_without_ac_edge.txt");
    
    vector<BaseRegion> regions_3hat_without_ac_edge_vec;
    load_region_vector(regions_3hat_without_ac_edge_vec, "3hat_without_ac_edge.txt");
    
    
    
    vector<BaseRegion> inner_2hat_regions;
//    enumerate_inner_hat_regions(inner_2hat_regions, 2, a, b);
//    store_region_vector(inner_2hat_regions, "inner_2hat_regions.txt");
    load_region_vector(inner_2hat_regions, "inner_2hat_regions.txt");
    
    vector<BaseRegion> inner_3hat_regions;
//    enumerate_inner_hat_regions(inner_3hat_regions, 3, a, c);
//    store_region_vector(inner_3hat_regions, "inner_3hat_regions.txt");
    load_region_vector(inner_3hat_regions, "inner_3hat_regions.txt");
    
    vector<BaseRegion> inner_4hat_regions;
//    enumerate_inner_hat_regions(inner_4hat_regions, 4, a, c);
//    store_region_vector(inner_4hat_regions, "inner_4hat_regions.txt");
    load_region_vector(inner_4hat_regions, "inner_4hat_regions.txt");

//    std::map<std::vector<int>, BaseRegion> regions_4hat_with_edges_map;
//    generate_4hat_regions(regions_4hat_with_edges_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          inner_2hat_regions,
//                          inner_3hat_regions,
//                          inner_4hat_regions,
//                          true, true);
//    store_region_map(regions_4hat_with_edges_map, "4hat_with_edges.txt");
    
    vector<BaseRegion> regions_4hat_with_edges_vec;
    load_region_vector(regions_4hat_with_edges_vec, "4hat_with_edges.txt");
    
//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_ad_edge_map;
//    generate_4hat_regions(regions_4hat_without_ad_edge_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          inner_2hat_regions,
//                          inner_3hat_regions,
//                          inner_4hat_regions,
//                          true, false);
//    store_region_map(regions_4hat_without_ad_edge_map, "4hat_without_ad_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_ad_edge_vec;
    load_region_vector(regions_4hat_without_ad_edge_vec, "4hat_without_ad_edge.txt");
    

//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_bc_edge_map;
//    generate_4hat_regions(regions_4hat_without_bc_edge_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          inner_2hat_regions,
//                          inner_3hat_regions,
//                          inner_4hat_regions,
//                          false, true);
//    store_region_map(regions_4hat_without_bc_edge_map, "4hat_without_bc_edge.txt");
    
    vector<BaseRegion> regions_4hat_without_bc_edge_vec;
    load_region_vector(regions_4hat_without_bc_edge_vec, "4hat_without_bc_edge.txt");
    
//    std::map<std::vector<int>, BaseRegion> regions_4hat_without_ad_bc_edges_map;
//    generate_4hat_regions(regions_4hat_without_ad_bc_edges_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          inner_2hat_regions,
//                          inner_3hat_regions,
//                          inner_4hat_regions,
//                          false, false);
//    store_region_map(regions_4hat_without_ad_bc_edges_map, "4hat_without_ad_bc_edges.txt");
    
    vector<BaseRegion> regions_4hat_without_ad_bc_edges_vec;
    load_region_vector(regions_4hat_without_ad_bc_edges_vec, "4hat_without_ad_bc_edges.txt");

//    map<vector<int>, BaseRegion> regions_5hat_with_edges_map;
//    generate_5hat_regions(regions_5hat_with_edges_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          regions_4hat_with_edges_vec,
//                          regions_4hat_without_bc_edge_vec,
//                          regions_4hat_without_ad_edge_vec,
//                          regions_4hat_without_ad_bc_edges_vec,
//                          true);
//    store_region_map(regions_5hat_with_edges_map, "5hat_with_edges.txt");
    
    vector<BaseRegion> regions_5hat_with_edges_vec;
    load_region_vector(regions_5hat_with_edges_vec, "5hat_with_edges.txt");

//    map<vector<int>, BaseRegion> regions_5hat_without_de_edge_map;
//    generate_5hat_regions(regions_5hat_without_de_edge_map,
//                          regions_3hat_with_edges_vec,
//                          regions_3hat_without_ac_edge_vec,
//                          regions_4hat_with_edges_vec,
//                          regions_4hat_without_bc_edge_vec,
//                          regions_4hat_without_ad_edge_vec,
//                          regions_4hat_without_ad_bc_edges_vec,
//                          false);
//    store_region_map(regions_5hat_without_de_edge_map, "5hat_without_de_edge.txt");
    
    vector<BaseRegion> regions_5hat_without_de_edge_vec;
    load_region_vector(regions_5hat_without_de_edge_vec, "5hat_without_de_edge.txt");

//    map<vector<int>, BaseRegion> regions_6hat_with_edges_map;
//    generate_6hat_regions(regions_6hat_with_edges_map,
//                          regions_3hat_with_edges_vec,
//                          regions_4hat_with_edges_vec,
//                          regions_4hat_without_ad_edge_vec,
//                          regions_5hat_with_edges_vec,
//                          regions_5hat_without_de_edge_vec);
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
    map<vector<int>, BaseRegion> regions_3_map;
    generate_3regions_from_inner(regions_3_map,
                                 inner_2regions_vec,
                                 inner_3regions_vec,
                                 inner_4starregions_vec,
                                 regions_3hat_with_edges_vec,
                                 regions_3hat_without_ac_edge_vec);
    store_region_map(regions_3_map, "3regions.txt");
    vector<BaseRegion> regions_3_vec;
    load_region_vector(regions_3_vec, "3regions.txt");

    // Generate 4-regions
    map<vector<int>, BaseRegion> regions_4_map;
    generate_4regions_from_inner(regions_4_map,
                                 inner_2regions_vec,
                                 inner_3regions_vec,
                                 inner_4regions_vec, 
                                 inner_4starregions_vec, 
                                 inner_5regions_vec, 
                                 inner_6regions_vec, 
                                 regions_3hat_with_edges_vec, 
                                 regions_3hat_without_ac_edge_vec, 
                                 regions_4hat_with_edges_vec);
    store_region_map(regions_4_map, "4regions.txt");
    vector<BaseRegion> regions_4_vec;
    load_region_vector(regions_4_vec, "4regions.txt");

    // Generate 4*-regions
    map<vector<int>, BaseRegion> regions_4star_map;
    generate_4starregions_from_inner(regions_4star_map,
                                     inner_2regions_vec, 
                                     inner_3regions_vec, 
                                     inner_4starregions_vec, 
                                     regions_3hat_with_edges_vec, 
                                     regions_3hat_without_ac_edge_vec, 
                                     regions_4hat_with_edges_vec, 
                                     regions_4hat_without_ad_edge_vec,
                                     regions_3_vec);
    store_region_map(regions_4star_map, "4star_regions.txt");
    vector<BaseRegion> regions_4star_vec;
    load_region_vector(regions_4star_vec, "4star_regions.txt");

    // Generate 5-regions
    map<vector<int>, BaseRegion> regions_5_map;
    generate_5regions_from_inner(regions_5_map,
                                 inner_2regions_vec, 
                                 inner_3regions_vec, 
                                 inner_4regions_vec, 
                                 inner_4starregions_vec, 
                                 inner_5regions_vec, 
                                 inner_6regions_vec, 
                                 empty_inner6_vec, 
                                 regions_3hat_with_edges_vec, 
                                 regions_3hat_without_ac_edge_vec, 
                                 regions_4hat_with_edges_vec, 
                                 regions_4hat_without_ad_edge_vec,
                                 regions_5hat_with_edges_vec,
                                 outer_non_dom_3regions_with_edge,
                                 outer_non_dom_3regions_without_edge,
                                 outer_non_dom_4regions_with_edge,
                                 outer_non_dom_4regions_without_edge, 
                                 regions_3_vec,
                                 regions_4_vec);
    store_region_map(regions_5_map, "5regions.txt");
    vector<BaseRegion> regions_5_vec;
    load_region_vector(regions_5_vec, "5regions.txt");

    // Generate 6-regions
    map<vector<int>, BaseRegion> regions_6_map;
    generate_6regions(regions_6_map,
                      inner_2regions_vec,
                      inner_3regions_vec,
                      inner_4regions_vec,
                      inner_4starregions_vec,
                      inner_5regions_vec,
                      inner_6regions_vec,
                      empty_inner2_vec,
                      empty_inner3_vec,
                      empty_inner4_vec,
                      empty_inner4star_vec,
                      empty_inner5_vec,
                      empty_inner6_vec,
                      regions_3hat_with_edges_vec,
                      regions_3hat_without_ac_edge_vec,
                      regions_4hat_with_edges_vec,
                      regions_4hat_without_ad_edge_vec,
                      regions_5hat_with_edges_vec,
                      regions_6hat_with_edges_vec,
                      outer_non_dom_3regions_with_edge,
                      outer_non_dom_3regions_without_edge,
                      outer_non_dom_4regions_with_edge,
                      outer_non_dom_4regions_without_edge,
                      regions_5_vec);
    store_region_map(regions_6_map, "6regions.txt");
    vector<BaseRegion> regions_6_vec;
//    load_region_vector(regions_6_with_edges_vec, "6regions.txt");
    
    cout << "main done" << endl;
    return 0;
}

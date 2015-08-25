//
//  testSignatureMethod.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 24/08/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "BaseRegion.h"
#include "4hat_a_regions.h"
#include "store_region_map.h"

TEST_CASE( "Testing signature method1", "[Signature1]" ) {
    
    int v = 0;
    int a = 1;
    int b = 3;
    int c = 2; // TODO
    int deg2_v_a = 0;
    int deg2_v_b = 0;
    int deg3_v_a_c = 0;
    int deg3_v_b_c = 0;
    int deg2_v_c = 0;
    int deg3_v_a_b = 0;
    int deg4 = 1;
    int v_c_edge = 0;
    int a_b_edge = 0;
    
    HatRegion R(4, v);
    for (int i = 0; i < deg2_v_a; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
    }
    for (int i = 0; i < deg2_v_b; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, b);
    }
    for (int i = 0; i < deg3_v_a_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, c);
    }
    for (int i = 0; i < deg3_v_b_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, b);
        R.addEdge(node, c);
    }
    
    for (int i = 0; i < deg2_v_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, c);
    }
    
    for(int i = 0; i < deg3_v_a_b; i++){
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, b);
    }
    for (int i = 0; i < deg4; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, b);
        R.addEdge(node, c);
    }
    
    if(v_c_edge){
        R.addEdge(v, c);
    }
    if(a_b_edge){
        R.addEdge(a, b);
    }
    
    REQUIRE(R.isValid());
    std::stringstream ss;
    std::vector<int> sign;
    R.getSignature(sign);
    
    for(int i = 0; i < sign.size(); i++){
        ss << sign[i] << " ";
    }
    REQUIRE(ss.str() == "1 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 1 1 1 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 0 1 1 1 0 1 0 0 0 1 0 1 1 0 0 1 0 0 0 1 0 0 0 1 1 1 0 1 0 1 0 0 0 1 0 1 0 1 ");
    
    REQUIRE(R.isValid());
    std::stringstream ss2;
    std::vector<int> sign2;
    R.getSignature2(sign2);
    
    for(int i = 0; i < sign2.size(); i++){
        ss2 << sign2[i] << " ";
    }
    REQUIRE(ss2.str() == "1 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 1 1 1 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 0 1 1 1 0 1 0 0 0 1 0 1 1 0 0 1 0 0 0 1 0 0 0 1 1 1 0 1 0 1 0 0 0 1 0 1 0 1 ");
}

TEST_CASE( "Testing signature method2", "[Signature2]" ) {
    
    int v = 0;
    int a = 1;
    int b = 3;
    int c = 2; // TODO
    int deg2_v_a = 0;
    int deg2_v_b = 0;
    int deg3_v_a_c = 0;
    int deg3_v_b_c = 0;
    int deg2_v_c = 1;
    int deg3_v_a_b = 0;
    int deg4 = 0;
    int v_c_edge = 0;
    int a_b_edge = 0;
    
    HatRegion R(4, v);
    for (int i = 0; i < deg2_v_a; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
    }
    for (int i = 0; i < deg2_v_b; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, b);
    }
    for (int i = 0; i < deg3_v_a_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, c);
    }
    for (int i = 0; i < deg3_v_b_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, b);
        R.addEdge(node, c);
    }
    
    for (int i = 0; i < deg2_v_c; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, c);
    }
    
    for(int i = 0; i < deg3_v_a_b; i++){
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, b);
    }
    for (int i = 0; i < deg4; i++) {
        int node = R.addNode();
        R.addEdge(node, v);
        R.addEdge(node, a);
        R.addEdge(node, b);
        R.addEdge(node, c);
    }
    
    if(v_c_edge){
        R.addEdge(v, c);
    }
    if(a_b_edge){
        R.addEdge(a, b);
    }
    
    REQUIRE(R.isValid());
    std::stringstream ss;
    std::vector<int> sign;
    R.getSignature(sign);
    
    for(int i = 0; i < sign.size(); i++){
        ss << sign[i] << " ";
    }
    REQUIRE(R.isValid());
    std::stringstream ss2;
    std::vector<int> sign2;
    R.getSignature2(sign2);
    
    for(int i = 0; i < sign2.size(); i++){
        ss2 << sign2[i] << " ";
    }
    
    REQUIRE(sign == sign2);
}

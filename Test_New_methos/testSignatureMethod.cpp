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
#include "HatRegion.h"
#include "4hat_b_regions.h"
#include "store_region_map.h"
#include "enumerate_inner.hpp"

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
    
    std::stringstream ss3;
    std::vector<int> sign3;
    R.getSignature3(sign3);
    
    for(int i = 0; i < sign3.size(); i++){
        ss3 << sign3[i] << " ";
    }
    REQUIRE(ss3.str() == "1 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 1 1 1 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 0 1 1 1 0 1 0 0 0 1 0 1 1 0 0 1 0 0 0 1 0 0 0 1 1 1 0 1 0 1 0 0 0 1 0 1 0 1 ");
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
    
    std::stringstream ss3;
    std::vector<int> sign3;
    R.getSignature3(sign3);
    
    for(int i = 0; i < sign3.size(); i++){
        ss3 << sign3[i] << " ";
    }
    
    REQUIRE(sign == sign3);
}

TEST_CASE( "Testing signature equivalence", "[Signature3]" ) {
    
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;

    HatRegion R(4, v);
    
    // NB: not really s nodes, should change name
    int s1 = R.addNode();
    int s2 = R.addNode();
    R.addEdge(s1, v);
    R.addEdge(s1, b);
    R.addEdge(s2, v);
    R.addEdge(s2, b);
    R.addEdge(s2, s1);
    
    int node = R.addNode();
    R.addEdge(node, v);
    R.addEdge(node, a);
    
    int s3 = R.addNode();
    R.addEdge(s3, v);
    R.addEdge(s3, s1);
    R.addEdge(s3, s2);
    
    REQUIRE(R.isValid());
    std::stringstream ss;
    std::vector<int> sign;
    R.getSignature2(sign);
    
    for(int i = 0; i < sign.size(); i++){
        ss << sign[i] << " ";
    }
    
    HatRegion R2(4, v);
    s1 = R2.addNode();
    s2 = R2.addNode();
    R2.addEdge(s1, v);
    R2.addEdge(s1, b);
    R2.addEdge(s2, v);
    R2.addEdge(s2, b);
    
    node = R2.addNode();
    R2.addEdge(node, v);
    R2.addEdge(node, a);
    
    s3 = R2.addNode();
    R2.addEdge(s3, v);
    
    REQUIRE(R2.isValid());
    std::stringstream ss2;
    std::vector<int> sign2;
    R2.getSignature2(sign2);
    
    for(int i = 0; i < sign2.size(); i++){
        ss2 << sign2[i] << " ";
    }
    
    REQUIRE(sign == sign2);
    
    std::stringstream ss3;
    std::vector<int> sign3;
    R2.getSignature3(sign3);
    
    for(int i = 0; i < sign3.size(); i++){
        ss3 << sign3[i] << " ";
    }
    
    REQUIRE(sign == sign3);
}

TEST_CASE( "Testing signatures on dataset", "[Signature4]" ) {
    
    std::vector<BaseRegion> inner_regions;
    
    // Uncomment the one to test
    enumerate_inner_2regions(inner_regions);
    //enumerate_inner_3regions(inner_regions);
    //enumerate_inner_4regions(inner_regions);
    //enumerate_inner_5regions(inner_regions);
    //enumerate_inner_6regions(inner_regions); // NB: Very slow!
    
    
    for (std::vector<BaseRegion>::iterator it = inner_regions.begin(); it != inner_regions.end(); it++) {
        std::stringstream ss;
        std::vector<int> sign;
        it->getSignature2(sign);
        
        for(int i = 0; i < sign.size(); i++){
            ss << sign[i] << " ";
        }
        
        std::stringstream ss2;
        std::vector<int> sign2;
        it->getSignature2(sign2);
        
        for(int i = 0; i < sign2.size(); i++){
            ss2 << sign2[i] << " ";
        }
        
        REQUIRE(sign == sign2);
        
        std::stringstream ss3;
        std::vector<int> sign3;
        it->getSignature3(sign3);
        
        for(int i = 0; i < sign3.size(); i++){
            ss3 << sign3[i] << " ";
        }
        
        REQUIRE(sign == sign3);
    }
}

//
//  testBaseRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 15/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "BaseRegion.h"

TEST_CASE( "Testin BaseRegion", "[BaseRegion]" ) {
    BaseRegion b(3);
    REQUIRE( b.getSize() == 3 );
    
    REQUIRE( b.isValid());
    
    // must be connected
    int node = b.addNode();
    REQUIRE( !b.isValid());
    
    b.addEdge(0, node);
    REQUIRE( b.isValid());
    
    // Check two regions having the same signature
    BaseRegion b1(6);
    
    int node1 = b1.addNode();
    int node2 = b1.addNode();
    b1.addEdge(0, node1);
    b1.addEdge(node1, 1);
    b1.addEdge(0, node2);
    b1.addEdge(node2, node1);
    
    BaseRegion b2(6);
    int node3 = b2.addNode();
    b2.addEdge(0, node3);
    b2.addEdge(node3, 1);
    int node4 = b2.addNode();
    b2.addEdge(0, node4);
    
    
    std::vector<int> sig1, sig2;
    b1.getSignature(sig1);
    b2.getSignature(sig2);
    
    REQUIRE(sig1 == sig2);
    
}

TEST_CASE( "Testing Reduction Rules", "[BaseRegion]" ) {
    BaseRegion b1(6);
    
    int node1 = b1.addNode();
    int node2 = b1.addNode();
    b1.addEdge(0, node1);
    b1.addEdge(node1, 3);
    b1.addEdge(0, node2);
    b1.addEdge(node2, 3);
    
    BaseRegion b2(6);
    for(int i = 0; i < 6; i++){
        int node = b2.addNode();
        b2.addEdge(0, node);
        b2.addEdge(node, 3);
    }
    
    std::vector<int> sig1, sig2;
    b1.getSignature(sig1);
    b2.getSignature(sig2);
    
    REQUIRE(sig1 == sig2);
    
}

TEST_CASE( "Testing equality", "[BaseRegion]" ) {
    BaseRegion b1(6);
    int node1 = b1.addNode();
    b1.addEdge(0, node1);
    
    BaseRegion b2(6);
    int node2 = b2.addNode();
    b2.addEdge(0, node2);
    
    REQUIRE( b1.isEqual(b2));
}

TEST_CASE( "Testing gluing", "[BaseRegion]" ) {
    BaseRegion r1(5);
    r1.addLabelToNode(1, 0);
    r1.addLabelToNode(2, 1);
    r1.addLabelToNode(3, 2);
    
    BaseRegion b1(4);
    b1.addLabelToNode(1, 0);
    b1.addLabelToNode(2, 1);
    b1.addLabelToNode(3, 2);
    
    std::vector<BaseRegion> regions;
    regions.push_back(b1);
    
    r1.glue(b1);
   // std::cout << "r is:" << std::endl;
  //  r.printRegion();
    
    BaseRegion shouldEqual(5);
    int node = shouldEqual.addNode();
    shouldEqual.addEdge(0, node);
    shouldEqual.addEdge(2, node);
    
   // std::cout << "Should be:" << std::endl;
   // shouldEqual.printRegion();
    
    REQUIRE( r1.isEqual(shouldEqual));
    
    BaseRegion r2(3);
    r2.addLabelToNode(1, 0);
    r2.addLabelToNode(2, 0);
    
    BaseRegion b2(3);
    b2.addLabelToNode(1, 0);
    b2.addLabelToNode(2, 2);
    
    r2.glue(b2);
    
    BaseRegion shouldEqual2(3);
    node = shouldEqual2.addNode();
    shouldEqual2.addEdge(node, 0);
    
    REQUIRE( r2.isEqual(shouldEqual2));
    
}

//
//  testHatABCRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//


#include "catch.hpp"
#include <iostream>
#include "HatABCRegion.h"

TEST_CASE( "Testing HatABCRegion with 1 boundary dominator", "[HatABCRegion]" ) {
    int v = 0;
    int a = 1;
    int b = 2;
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(b);
    
    HatABCRegion h(6, 0, boundaryDominators);
    for (int i = 0; i < 4; i++) {
        int node = h.addNode();
        h.addEdge(node, 0);
        h.addEdge(node, i+1);
    }
    
    REQUIRE(!h.isValid()); // Not dominated by 2
    
    int node = h.addNode();
    h.addEdge(node, 2);
    REQUIRE(!h.isValid());
    
    HatABCRegion h1(6, 0, boundaryDominators);
    for (int i = 0; i < 7; i++) {
        node = h1.addNode();
        h1.addEdge(node, 0);
        h1.addEdge(node, 2); // edge to 2
    }
    REQUIRE(h1.isValid());
    
    node = h1.addNode();
    h1.addEdge(node, 0);
    h1.addEdge(node, 3);
    REQUIRE(!h1.isValid()); // Not dominated by 2
    
    
}

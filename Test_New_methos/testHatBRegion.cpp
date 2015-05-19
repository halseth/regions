//
//  testHatBRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//


#include "catch.hpp"
#include <iostream>
#include "HatBRegion.h"

TEST_CASE( "Testining HatBRegion", "[HatBRegion]" ) {
    
    HatBRegion h(6, 0, 2);
    for (int i = 0; i < 4; i++) {
        int node = h.addNode();
        h.addEdge(node, 0);
        h.addEdge(node, i+1);
    }
    
    REQUIRE(!h.isValid()); // Not dominated by 2
    
    int node = h.addNode();
    h.addEdge(node, 2);
    REQUIRE(!h.isValid());
    
    HatBRegion h1(6, 0, 2);
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

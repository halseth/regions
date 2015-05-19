//
//  testHatARegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "HatARegion.h"

TEST_CASE( "Testining HatARegion", "[HatARegion]" ) {
    
    HatARegion h(6, 0, 1, 2);
    for (int i = 0; i < 4; i++) {
        int node = h.addNode();
        h.addEdge(node, 0);
        h.addEdge(node, i+1);
    }
    
    REQUIRE(!h.isValid()); // Not dominated by 1 and 2
    
    int node = h.addNode();
    h.addEdge(node, 2);
    REQUIRE(!h.isValid());
    
    HatARegion h1(6, 0, 1, 2);
    for (int i = 0; i < 7; i++) {
        node = h1.addNode();
        h1.addEdge(node, 0);
        h1.addEdge(node, (i%2) + 1); // edge to 1 or 2
    }
    REQUIRE(h1.isValid());
    
    node = h1.addNode();
    h1.addEdge(node, 0);
    h1.addEdge(node, 3);
    REQUIRE(!h1.isValid());
    
    // Check not planar
    HatARegion h3(6, 0, 1, 2);
    node = h3.addNode();
    h3.addEdge(node, 0);
    h3.addEdge(node, 1);
    h3.addEdge(node, 2);
    
    node = h3.addNode();
    h3.addEdge(node, 0);
    h3.addEdge(node, 1);
    
    REQUIRE(h3.isValid());
    
    h3.addEdge(node, 2);
    REQUIRE(!h3.isValid());
    
    
}
//
//  testHatRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "HatRegion.h"

TEST_CASE( "Testining HatRegion", "[HatRegion]" ) {
   
    HatRegion h(6, 0);
    for (int i = 0; i < 4; i++) {
        int node = h.addNode();
        h.addEdge(node, 0);
        h.addEdge(node, i+1);
    }
    
    REQUIRE(h.isValid());
    
    int node = h.addNode();
    h.addEdge(node, 2);
    REQUIRE(!h.isValid());
    
}
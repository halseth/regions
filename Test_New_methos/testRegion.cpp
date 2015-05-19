//
//  testRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "Region.h"

TEST_CASE( "Testining Region", "[Region]" ) {
    
    Region h(6, 0, 3);
    for (int i = 0; i < 4; i++) {
        int node = h.addNode();
        h.addEdge(node, 0);
    }
    
    REQUIRE(h.isValid());
    
    int node = h.addNode();
    h.addEdge(node, 2);
    REQUIRE(!h.isValid());
    
    Region r(6, 0, 3);
    for (int i = 0; i < 0; i++) {
        node = r.addNode();
        r.addEdge(node, (i%2) == 0 ? 0 : 3);
    }
    
    REQUIRE(r.isValid());
    
    node = r.addNode();
    r.addEdge(node, 2);
    
    REQUIRE(!r.isValid());
    
}
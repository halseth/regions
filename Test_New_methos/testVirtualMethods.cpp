//
//  testVirtualMethods.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 20/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "HatARegion.h"
#include "store_sign.h"

TEST_CASE( "Testining virtual methods", "[Virtual methods]" ) {
    
    int v = 0;
    int a = 1;
    int b = 2;
    
    HatARegion ha(3, v, a, b);
    int node = ha.addNode();
    ha.addEdge(v, node);
    
    // Should be valid Base- and HatRegion, but not HatARegion
    REQUIRE(ha.BaseRegion::isValid());
    REQUIRE(ha.HatRegion::isValid());
    REQUIRE(!ha.isValid());
    
    // Check virtual methods
    BaseRegion *br = &ha;
    REQUIRE(!br->isValid());
    HatRegion *hr = &ha;
    REQUIRE(!hr->isValid());
    
}

TEST_CASE( "Testing polymorphism for store_sign method", "[Virtual methods, Store_sign]" ) {
    
    int v = 0;
    int a = 1;
    int b = 2;
    
    std::map<std::vector<int>, BaseRegion> sign;
    {
        HatARegion ha(3, v, a, b);
        int node = ha.addNode();
        ha.addEdge(v, node);
    
        store_sign(ha, sign);
        REQUIRE( sign.size() == 0);
    
        ha.addEdge(node, a);
        store_sign(ha, sign);
        REQUIRE( sign.size() == 1);
    }

    for (std::map<std::vector<int>, BaseRegion>::iterator it = sign.begin(); it != sign.end(); it++) {
        REQUIRE(it->second.getSize() == 4);
    }
    
    HatRegion h(3, v);
    int node = h.addNode();
    h.addEdge(v, node);
    
    store_sign(h, sign);
    REQUIRE( sign.size() == 2);
}
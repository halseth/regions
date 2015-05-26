//
//  testRegionFromAndToFile.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "BaseRegion.h"

TEST_CASE( "Testining string reading an saving", "[Region string]" ) {
    
    BaseRegion R(6);
    for(int i = 0; i < 7; i++){
        int node = R.addNode();
        R.addEdge(0, node);
    }
    
    REQUIRE(R.isValid());
    
    std::string str = R.toString();
    //std::cout << "string rep: " << str << std::endl;
    
    BaseRegion Rcopy(str);
    
    REQUIRE(R.isEqual(Rcopy));
    
}
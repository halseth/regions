//
//  InnerRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#include "InnerRegion.hpp"
#include <iostream>

InnerRegion::InnerRegion(int boundarySize, int endpoint1, int endpoint2) : BaseRegion(boundarySize){
    this->endpoint1 = endpoint1;
    this->endpoint2 = endpoint2;
    
    // Start without boundary
    for (int i = 0; i < getBoundarySize(); i++) {
        removeEdge(i, (i+1)%getBoundarySize());
    }
}

bool InnerRegion::isValid(){
    
    // Is planar
    bool valid = isPlanar();
    
    // All vertices (internal and boundary) must be dominated by the two endpoints
    for (int i = 0; i < getSize(); i++) {
        if (i == endpoint1 || i == endpoint2) {
            continue;
        }
        valid &= isAdjacent(i, endpoint1) || isAdjacent(i, endpoint2);
    }
    return valid;
}
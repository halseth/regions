//
//  Region.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "Region.h"

Region::Region(int boundarySize, int endpoint1, int endpoint2) : BaseRegion(boundarySize){
    this->endpoint1 = endpoint1;
    this->endpoint2 = endpoint2;
}

bool Region::isValid(){
    bool valid = BaseRegion::isValid();
    
    // All internal vertices must be dominated by the two endpoints
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, endpoint1) || isAdjacent(i, endpoint2);
    }
    return valid;
}
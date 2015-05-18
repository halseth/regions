//
//  HatBRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "HatBRegion.h"

HatBRegion::HatBRegion(int boundarySize, int endpoint, int boundaryDominator) : HatRegion(boundarySize, endpoint){
    this->boundaryDominator = boundaryDominator;
}

bool HatBRegion::isValid(){
    bool valid = HatRegion::isValid();
    
    // The two boundary nodes must dominate all internal
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, boundaryDominator);
    }
    return valid;
}
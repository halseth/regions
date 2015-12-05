//
//  InnerHatABCRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 10/11/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "InnerHatABCRegion.hpp"
#include <iostream>

InnerHatABCRegion::InnerHatABCRegion(int boundarySize, int endpoint, std::vector<int> boundaryDominators) : InnerHatRegion(boundarySize, endpoint){
    this->boundaryDominators = boundaryDominators;
}

bool InnerHatABCRegion::isValid(){
    bool valid = InnerHatRegion::isValid();
    
    // The boundary nodes must dominate all internal
    for (int i = getBoundarySize(); i < getSize(); i++) {
        bool dominated = false;
        for (int j = 0; j < boundaryDominators.size(); j++) {
            dominated |= isAdjacent(boundaryDominators[j], i);
        }
        valid &= dominated;
    }
    return valid;
}

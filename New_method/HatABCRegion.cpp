//
//  HatABCRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "HatABCRegion.h"
#include <iostream>

HatABCRegion::HatABCRegion(int boundarySize, int endpoint, std::vector<int> boundaryDominators) : HatRegion(boundarySize, endpoint){
    this->boundaryDominators = boundaryDominators;
}

bool HatABCRegion::isValid(){
    bool valid = HatRegion::isValid();
    
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

void HatABCRegion::test(){
    std::cout << "I am HatABCRegion" << std::endl;
}
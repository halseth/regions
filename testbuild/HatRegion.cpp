//
//  HatRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "HatRegion.h"
#include <iostream>

HatRegion::HatRegion(int boundarySize, int endpoint) : BaseRegion(boundarySize){
    this->endpoint = endpoint;
}

bool HatRegion::isValid(){
    bool valid = BaseRegion::isValid();
    if (!valid) {
        return false;
    }
    // All internal vertices must be dominated by the endpoint
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, endpoint);
    }
//    if (!valid) {
//        std::cout << "not dominating all" << std::endl;
//    }
    return valid;
}

void HatRegion::test(){
    std::cout << "I am hatRegion" << std::endl;
}
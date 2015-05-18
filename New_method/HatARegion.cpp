//
//  HatARegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "HatARegion.h"

HatARegion::HatARegion(int boundarySize, int endpoint, int boundaryDominator1, int boundaryDominator2) : HatRegion(boundarySize, endpoint){
    this->boundaryDominator1 = boundaryDominator1;
    this->boundaryDominator2 = boundaryDominator2;
}

bool HatARegion::isValid(){
    bool valid = HatRegion::isValid();
    
    // The two boundary nodes must dominate all internal
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, boundaryDominator1) || isAdjacent(i, boundaryDominator2);
    }
    return valid;
}
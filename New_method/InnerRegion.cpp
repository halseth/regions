//
//  InnerRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 10/11/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "InnerRegion.hpp"
#include <iostream>

InnerRegion::InnerRegion(int boundarySize, int endpoint1, int endpoint2) : BaseRegion(boundarySize){
    
    // Remove boundary edges
    for(int i = 0; i < Boundary.size(); i++){
        this->removeEdge(Boundary[i], Boundary[(i+1)%Boundary.size()] );
    }
    
    this->endpoint1 = endpoint1;
    this->endpoint2 = endpoint2;
}

bool InnerRegion::isValid(){
    bool valid = BaseRegion::isPlanar();
    std::cout << "BaseRegion::isPlanar():" << valid << std::endl;
    
    // All internal vertices must be dominated by the two endpoints
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, endpoint1) || isAdjacent(i, endpoint2);
    }
    std::cout << "Inernal vertices dominated:" << valid << std::endl;
    return valid;
}
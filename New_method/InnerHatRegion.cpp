//
//  InnerHatRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 10/11/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "InnerHatRegion.hpp"
#include <iostream>

InnerHatRegion::InnerHatRegion(int boundarySize, int endpoint) : InnerRegion(boundarySize, endpoint, endpoint){
    // Remove boundary edges
    for(int i = 0; i < Boundary.size(); i++){
        this->removeEdge(Boundary[i], Boundary[(i+1)%Boundary.size()] );
    }
    this->endpoint = endpoint;
}

bool InnerHatRegion::isValid(){
    bool valid = InnerRegion::isValid();
    std::cout << "InnerRegion::isValid():" << valid << std::endl;
    
    // All internal vertices must be dominated by the endpoint
    for (int i = getBoundarySize(); i < getSize(); i++) {
        valid &= isAdjacent(i, endpoint);
    }
    std::cout << "Dominated by endpoint:" << valid << std::endl;
    
    return valid;
}

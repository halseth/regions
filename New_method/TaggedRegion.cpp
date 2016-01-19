//
//  TaggedRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#include "TaggedRegion.hpp"

TaggedRegion::TaggedRegion(int boundarySize, int endpoint1, int endpoint2, int tag) : Region(boundarySize, endpoint1, endpoint2){
    this->tag = tag;
}

bool TaggedRegion::isValid(){
    bool valid = Region::isValid();
    
    return valid;
}

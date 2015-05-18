//
//  BoundariedRegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 08/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__BoundariedRegion__
#define __New_method__BoundariedRegion__

#include <map>
#include <vector>
#include "Region.h"


class BoundariedRegion : public Region {
    std::map<int, int> labels;
    
    
public:
    
    BoundariedRegion(int boundary_size, int endpoint2_num, int id): Region(boundary_size, endpoint2_num, id){
        
    }
    
    void addLabel(int node, int label);
    
    
    void glue(std::vector<BoundariedRegion> regions);
};


#endif /* defined(__New_method__BoundariedRegion__) */

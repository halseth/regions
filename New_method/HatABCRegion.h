//
//  HatABCRegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__HatABCRegion__
#define __New_method__HatABCRegion__

#include <vector>
#include "HatRegion.h"

class HatABCRegion : public HatRegion {
private:
    std::vector<int> boundaryDominators;
    
public:
    HatABCRegion(int boundarySize, int endpoint, std::vector<int> boundaryDominators);
    virtual bool isValid();
    virtual void test();
};

#endif /* defined(__New_method__HatABCRegion__) */

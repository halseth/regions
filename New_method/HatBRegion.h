//
//  HatBRegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__HatBRegion__
#define __New_method__HatBRegion__

#include "HatRegion.h"

class HatBRegion : HatRegion {
private:
    int boundaryDominator;
    
public:
    HatBRegion(int boundarySize, int endpoint, int boundaryDominator);
    virtual bool isValid();
};

#endif /* defined(__New_method__HatBRegion__) */

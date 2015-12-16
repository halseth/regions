//
//  HatRegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__HatRegion__
#define __New_method__HatRegion__

#include "BaseRegion.h"

class HatRegion : public BaseRegion {
private:
    int endpoint;
    
public:
    HatRegion(int boundarySize, int endpoint);
    virtual bool isValid();
    virtual void test();
};

#endif /* defined(__New_method__HatRegion__) */

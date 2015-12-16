//
//  Region.h
//  New_method
//
//  Created by Johan Torås Halseth on 19/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__Region__
#define __New_method__Region__

#include "BaseRegion.h"

class Region : public BaseRegion {
private:
    int endpoint1;
    int endpoint2;
    
public:
    Region(int boundarySize, int endpoint1, int endpoint2);
    virtual bool isValid();
};

#endif /* defined(__New_method__Region__) */

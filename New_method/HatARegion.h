//
//  HatARegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__HatARegion__
#define __New_method__HatARegion__

#include "HatRegion.h"

class HatARegion : public HatRegion {
private:
    int boundaryDominator1;
    int boundaryDominator2;
    
public:
    HatARegion(int boundarySize, int endpoint, int boundaryDominator1, int boundaryDominator2);
    virtual bool isValid();
};

#endif /* defined(__New_method__HatARegion__) */

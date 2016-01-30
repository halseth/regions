//
//  InnerRegion.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#ifndef InnerRegion_hpp
#define InnerRegion_hpp

#include "BaseRegion.h"

class InnerRegion : public BaseRegion {
private:
    int endpoint1;
    int endpoint2;
    
public:
    InnerRegion(int boundarySize, int endpoint1, int endpoint2);
    virtual bool isValid();
};

#endif /* InnerRegion_hpp */

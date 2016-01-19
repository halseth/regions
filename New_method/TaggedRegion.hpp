//
//  TaggedRegion.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#ifndef TaggedRegion_hpp
#define TaggedRegion_hpp

#include "Region.h"

class TaggedRegion : public Region {
private:
    int endpoint1;
    int endpoint2;
    int tag;
    
public:
    TaggedRegion(int boundarySize, int endpoint1, int endpoint2, int tag);
    virtual bool isValid();
};

#endif /* TaggedRegion_hpp */

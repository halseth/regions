//
//  InnerHatRegion.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 10/11/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef InnerHatRegion_hpp
#define InnerHatRegion_hpp

#include "InnerRegion.hpp"

class InnerHatRegion : public InnerRegion {
private:
    int endpoint;
    
public:
    InnerHatRegion(int boundarySize, int endpoint);
    virtual bool isValid();
};

#endif /* InnerHatRegion_hpp */

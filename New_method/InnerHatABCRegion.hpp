//
//  InnerHatABCRegion.hpp
//  New_method
//
//  Created by Johan Torås Halseth on 10/11/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef InnerHatABCRegion_hpp
#define InnerHatABCRegion_hpp

#include <vector>
#include "InnerHatRegion.hpp"

class InnerHatABCRegion : public InnerHatRegion {
private:
    std::vector<int> boundaryDominators;
    
public:
    InnerHatABCRegion(int boundarySize, int endpoint, std::vector<int> boundaryDominators);
    virtual bool isValid();
};

#endif /* InnerHatABCRegion_hpp */

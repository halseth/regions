//
//  3hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 27/08/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//


#include <vector>
#include <iostream>
using namespace std;

#include "3hat_regions.h"
#include "store_sign.h"
#include "HatRegion.h"

void generate_3hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_ab){
    int v = 0;
    int a = 1;
    int b = 2;
    
    for (int deg1 = 0; deg1 <= 1; deg1++) {
        for (std::map<std::vector<int>,BaseRegion>::const_iterator it = regions_3hat_ab.begin(); it != regions_3hat_ab.end(); it++) {
            BaseRegion R2 = it->second;
            R2.addLabelToNode(0, v);
            R2.addLabelToNode(1, a);
            R2.addLabelToNode(2, b);
            
            HatRegion R(3, v);
            R.addLabelToNode(0, v);
            R.addLabelToNode(1, a);
            R.addLabelToNode(2, b);
            
            R.glue(R2);
            
            if(deg1){
                int c = R.addNode();
                R.addEdge(c, v);
            }
            store_sign(R, signature_minimal);
        }
        
        
    }
    
    cout << "done with 3hat_regions" << endl;
}
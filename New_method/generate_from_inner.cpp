//
//  generate_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//



#include "generate_from_inner.hpp"

void generate_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                         vector<BaseRegion> &inner_2regions,
                         vector<BaseRegion> &inner_3regions,
                         vector<BaseRegion> &inner_4regions,
                         vector<BaseRegion> &inner_4starregions,
                         vector<BaseRegion> &inner_5regions,
                         vector<BaseRegion> &inner_6regions,
                         map<vector<int>, BaseRegion> &regions_3hat,
                         map<vector<int>, BaseRegion> &regions_4hat
                         ) {
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat.empty()|| inner_4starregions.empty() || inner_4regions.empty() || inner_5regions.empty() || inner_6regions.empty() || inner_2regions.empty() || inner_3regions.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    // Inner 2-regions. Outer regions will be empty
    for (int i = 0; i < inner_2regions.size(); i++) {
        for (int edge_over = 0; edge_over <= 1; edge_over++) {
                
            BaseRegion inner = inner_2regions[i];                
            inner.removeEdge(a, b);
            if (edge_over) {
                inner.addEdge(a, b);
            }
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            
            Region R(6,a,d);
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, d);
            
            R.glue(&inner);
            
            store_sign(R, signature_minimal);
        }
    }
    
}

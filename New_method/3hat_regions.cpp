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

void generate_3hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int a = 0;
    int b = 1;
    int c = 2;
    
    for (int dangling_n3 = 0; dangling_n3 <= 1; dangling_n3++) {
        
        // Can always assume |S| = 0, since picking a is at least as good
        for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
            for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                for (int deg3 = 0; deg3 <= 1; deg3++) {
                    HatRegion R(3,a);
                    
                    for (int i = 0; i < dangling_n3; i++) {
                        int node = R.addNode();
                        R.addEdge(a, node);
                    }
                    
                    for (int i = 0; i < deg2_a_b; i++) {
                        int node = R.addNode();
                        R.addEdge(a, node);
                        R.addEdge(node, b);
                    }
                    
                    for (int i = 0; i < deg2_a_c; i++) {
                        int node = R.addNode();
                        R.addEdge(a, node);
                        R.addEdge(node, c);
                    }
                    
                    for (int i = 0; i < deg3; i++) {
                        int node = R.addNode();
                        R.addEdge(a, node);
                        R.addEdge(b, node);
                        R.addEdge(c, node);
                    }
                    
                    store_sign(R, signature_minimal);
                }
            }
        }
    }
    
    cout << "done with 3hat_regions" << endl;
}
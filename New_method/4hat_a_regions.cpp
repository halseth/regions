//
//  4hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 21/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//
#include <iostream>

#include "4hat_a_regions.h"
#include "store_sign.h"


void generate_4hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    
    for (int num_internal = 0; num_internal <= 2; num_internal++) {
        int max_internal_edge = num_internal > 1 ? 1 : 0;
        for (int internal_edge = 0; internal_edge <= max_internal_edge; internal_edge++) {
            int max_edges = num_internal > 0 ? 0b11 : 0b00;
            for (int edges = 0b00; edges <= max_edges; edges++) {
                int max_ac_edge = (edges & 0b01) == 0 ? 1 : 0;
                for (int ac_edge = 0; ac_edge <= max_ac_edge; ac_edge++) {
                    int max_vb_edge = (edges & 0b10) == 0 && !ac_edge ? 1 : 0;
                    for (int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++) {
                        std::vector<int> boundaryDominator;
                        boundaryDominator.push_back(a);
                        HatABCRegion R(4, v, boundaryDominator);
                        
                        int node = -1;
                        for (int i = 0; i < num_internal; i++) {
                            node = R.addNode();
                            R.addEdge(v, node);
                            R.addEdge(node, a);
                        }
                        
                        if (internal_edge) {
                            R.addEdge(node, node-1);
                        }
                        
                        if ( (edges & 0b01) != 0 ) {
                            R.addEdge(node, b);
                        }
                        
                        if ( (edges & 0b10) != 0 ) {
                            R.addEdge(node, c);
                        }
                        
                        if (ac_edge) {
                            R.addEdge(a, c);
                        }
                        
                        if (vb_edge) {
                            R.addEdge(v, b);
                        }
                        
                        counter++;
                        store_sign(R, signature_minimal);
                    }
                    
                }
            }
        }
    }
    
    std::cout << "done with 4hat_a_regions. Total regions checked: " << counter << std::endl;
}
//
//  5hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 21/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <iostream>

#include "5hat_a_regions.h"
#include "store_sign.h"

void generate_5hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    
    for (int num_internal = 0; num_internal <= 3; num_internal++) {
        int max_internal_edges = num_internal > 0 ? (1 << (num_internal - 1 )) - 1 : 0;
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            int max_edges = num_internal > 0 ? 0b111 : 0b000;
            for (int edges = 0b000; edges <= max_edges; edges++) {
                int max_ac_edge = (edges & 0b001) == 0 ? 1 : 0;
                for (int ac_edge = 0; ac_edge <= max_ac_edge; ac_edge++) {
                    int max_bd_edge = (edges & 0b010) == 0 && !ac_edge ? 1 : 0;
                    for (int bd_edge = 0; bd_edge <= max_bd_edge; bd_edge++) {
                        int max_ad_edge = (edges & 0b011) == 0 ? 1 : 0;
                        for (int ad_edge = 0; ad_edge <= max_ad_edge; ad_edge++) {
                            int max_vb_edge = (edges & 0b110) == 0 && !ac_edge && !ad_edge ? 1 : 0;
                            for (int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++) {
                                int max_vc_edge = (edges & 0b100) == 0 && !ad_edge && !bd_edge ? 1 : 0;
                                for (int vc_edge = 0; vc_edge <= max_vc_edge; vc_edge++) {
                                    std::vector<int> boundaryDominator;
                                    boundaryDominator.push_back(a);
                                    HatABCRegion R(5, v, boundaryDominator);
                                    
                                    int node = -1;
                                    for (int i = 0; i < num_internal; i++) {
                                        node = R.addNode();
                                        R.addEdge(v, node);
                                        R.addEdge(node, a);
                                        if ( i > 0 && ( internal_edges & ( 1 << (i-1) ) ) != 0 ){
                                            R.addEdge(i, i-1);
                                        }
                                    }
                                    
                                    if ( (edges & 0b001) != 0 ) {
                                        R.addEdge(node, b);
                                    }
                                    
                                    if ( (edges & 0b010) != 0 ) {
                                        R.addEdge(node, c);
                                    }
                                    
                                    if ( (edges & 0b100) != 0 ) {
                                        R.addEdge(node, d);
                                    }
                                    
                                    if (ac_edge) {
                                        R.addEdge(a, c);
                                    }
                                    
                                    if (ad_edge) {
                                        R.addEdge(a, d);
                                    }
                                    
                                    if (bd_edge) {
                                        R.addEdge(b, d);
                                    }
                                    
                                    if (vb_edge) {
                                        R.addEdge(v, b);
                                    }
                                    if (vc_edge) {
                                        R.addEdge(v, c);
                                    }
                                    counter++;
                                    store_sign(R, signature_minimal);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    std::cout << "done with 5hat_a_regions. Total regions checked: " << counter << std::endl;
}
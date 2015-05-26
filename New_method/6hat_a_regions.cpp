//
//  6hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "6hat_a_regions.h"
#include "store_sign.h"
#include <iostream>

void generate_6hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    
    for (int num_internal = 0; num_internal <= 3; num_internal++) {
        int max_internal_edges = num_internal > 0 ? (1 << (num_internal - 1 )) - 1 : 0;
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            int max_edges = num_internal > 0 ? 0b1111 : 0b0000;
            for (int edges = 0b0000; edges <= max_edges; edges++) {
                
                int max_ac_edge = (edges & 0b001) == 0 ? 1 : 0;
                for (int ac_edge = 0; ac_edge <= max_ac_edge; ac_edge++) {
                    int max_ad_edge = (edges & 0b0011) == 0 ? 1 : 0;
                    for (int ad_edge = 0; ad_edge <= max_ad_edge; ad_edge++) {
                        int max_ae_edge = (edges & 0b0111) == 0 ? 1 : 0;
                        for (int ae_edge = 0; ae_edge <= max_ae_edge; ae_edge++) {
                            int max_bd_edge = (edges & 0b0010) == 0 && !ac_edge ? 1 : 0;
                            for (int bd_edge = 0; bd_edge <= max_bd_edge; bd_edge++) {
                                int max_be_edge = (edges & 0b0110) == 0 && !ac_edge && !ad_edge ? 1 : 0;
                                for (int be_edge = 0; be_edge <= max_be_edge; be_edge++) {
                                    
                                    int max_ce_edge = (edges & 0b0100) == 0 && !ad_edge && !bd_edge ? 1 : 0;
                                    for (int ce_edge = 0; ce_edge <= max_ce_edge; ce_edge++) {
                                        int max_vb_edge = (edges & 0b1110) == 0 && !ac_edge && !ad_edge && !ae_edge ? 1 : 0;
                                        for (int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++) {
                                            int max_vc_edge = (edges & 0b1100) == 0 && !ad_edge && !ae_edge && !bd_edge && !be_edge ? 1 : 0;
                                            for (int vc_edge = 0; vc_edge <= max_vc_edge; vc_edge++) {
                                                int max_vd_edge = (edges & 0b1000) == 0 && !ae_edge && !be_edge && !ce_edge ? 1 : 0;
                                                for (int vd_edge = 0; vd_edge <= max_vd_edge; vd_edge++) {
                                                    std::vector<int> boundaryDominator;
                                                    boundaryDominator.push_back(a);
                                                    HatABCRegion R(6, v, boundaryDominator);
                                                    
                                                    int node = -1;
                                                    for (int i = 0; i < num_internal; i++) {
                                                        node = R.addNode();
                                                        R.addEdge(v, node);
                                                        R.addEdge(node, a);
                                                        if ( i > 0 && ( internal_edges & ( 1 << (i-1) ) ) != 0 ){
                                                            R.addEdge(i, i-1);
                                                        }
                                                    }
                                                    
                                                    if ( (edges & 0b0001) != 0 ) {
                                                        R.addEdge(node, b);
                                                    }
                                                    
                                                    if ( (edges & 0b0010) != 0 ) {
                                                        R.addEdge(node, c);
                                                    }
                                                    
                                                    if ( (edges & 0b0100) != 0 ) {
                                                        R.addEdge(node, d);
                                                    }
                                                    
                                                    if ( (edges & 0b1000) != 0 ) {
                                                        R.addEdge(node, e);
                                                    }
                                                    
                                                    if (ac_edge) {
                                                        R.addEdge(a, c);
                                                    }
                                                    
                                                    if (ad_edge) {
                                                        R.addEdge(a, d);
                                                    }
                                                    
                                                    if (ae_edge) {
                                                        R.addEdge(a, e);
                                                    }
                                                    
                                                    if (bd_edge) {
                                                        R.addEdge(b, d);
                                                    }
                                                    
                                                    if (be_edge) {
                                                        R.addEdge(b, e);
                                                    }
                                                    
                                                    if (ce_edge) {
                                                        R.addEdge(c, e);
                                                    }
                                                    
                                                    if (vb_edge) {
                                                        R.addEdge(v, b);
                                                    }
                                                    if (vc_edge) {
                                                        R.addEdge(v, c);
                                                    }
                                                    
                                                    if (vd_edge) {
                                                        R.addEdge(v, d);
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
                }
            }
        }
    }
    
    std::cout << "done with 6hat_a_regions. Total regions checked: " << counter << std::endl;
}
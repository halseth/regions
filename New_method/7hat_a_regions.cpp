//
//  7hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 27/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "7hat_a_regions.h"
#include "store_sign.h"
#include <iostream>

void generate_7hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    
    
    for (int num_internal = 0; num_internal <= 3; num_internal++) {
        int max_internal_edges = num_internal > 0 ? (1 << (num_internal - 1 )) - 1 : 0;
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            int max_edges = num_internal > 0 ? 0b11111 : 0b00000;
            for (int edges = 0b00000; edges <= max_edges; edges++) {
                
                int max_ac_edge = (edges & 0b0001) == 0 ? 1 : 0;
                for (int ac_edge = 0; ac_edge <= max_ac_edge; ac_edge++) {
                    int max_ad_edge = (edges & 0b00011) == 0 ? 1 : 0;
                    for (int ad_edge = 0; ad_edge <= max_ad_edge; ad_edge++) {
                        int max_ae_edge = (edges & 0b00111) == 0 ? 1 : 0;
                        for (int ae_edge = 0; ae_edge <= max_ae_edge; ae_edge++) {
                            int max_af_edge = (edges & 0b01111) == 0 ? 1 : 0;
                            for (int af_edge = 0; af_edge <= max_af_edge; af_edge++) {
                                
                                int max_bd_edge = (edges & 0b00010) == 0 && !ac_edge ? 1 : 0;
                                for (int bd_edge = 0; bd_edge <= max_bd_edge; bd_edge++) {
                                    int max_be_edge = (edges & 0b00110) == 0 && !ac_edge && !ad_edge ? 1 : 0;
                                    for (int be_edge = 0; be_edge <= max_be_edge; be_edge++) {
                                        int max_bf_edge = (edges & 0b01110) == 0 && !ac_edge && !ad_edge && !ae_edge ? 1 : 0;
                                        for (int bf_edge = 0; bf_edge <= max_bf_edge; bf_edge++) {
                                            
                                            int max_ce_edge = (edges & 0b00100) == 0 && !ad_edge && !bd_edge ? 1 : 0;
                                            for (int ce_edge = 0; ce_edge <= max_ce_edge; ce_edge++) {
                                                int max_cf_edge = (edges & 0b01100) == 0 && !ad_edge && !ae_edge && !bd_edge && !be_edge ? 1 : 0;
                                                for (int cf_edge = 0; cf_edge <= max_cf_edge; cf_edge++) {
                                                    
                                                    int max_df_edge = (edges & 0b01000) == 0 && !ae_edge && !be_edge && !ce_edge ? 1 : 0;
                                                    for (int df_edge = 0; df_edge <= max_df_edge; df_edge++) {
                                                        
                                                        int max_vb_edge = (edges & 0b11110) == 0 && !ac_edge && !ad_edge && !ae_edge && !af_edge ? 1 : 0;
                                                        for (int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++) {
                                                            int max_vc_edge = (edges & 0b11100) == 0 && !ad_edge && !ae_edge && !af_edge && !bd_edge && !be_edge && !bf_edge ? 1 : 0;
                                                            for (int vc_edge = 0; vc_edge <= max_vc_edge; vc_edge++) {
                                                                int max_vd_edge = (edges & 0b11000) == 0 && !ae_edge && !af_edge && !be_edge && !bf_edge && !ce_edge && !cf_edge ? 1 : 0;
                                                                for (int vd_edge = 0; vd_edge <= max_vd_edge; vd_edge++) {
                                                                    int max_ve_edge = (edges & 0b10000) == 0 && !af_edge && !bf_edge && !cf_edge && ! df_edge ? 1 : 0;
                                                                    for (int ve_edge = 0; ve_edge <= max_ve_edge; ve_edge++) {
                                                                        std::vector<int> boundaryDominator;
                                                                        boundaryDominator.push_back(a);
                                                                        HatABCRegion R(7, v, boundaryDominator);
                                                                        
                                                                        int node = -1;
                                                                        for (int i = 0; i < num_internal; i++) {
                                                                            node = R.addNode();
                                                                            R.addEdge(v, node);
                                                                            R.addEdge(node, a);
                                                                            if ( i > 0 && ( internal_edges & ( 1 << (i-1) ) ) != 0 ){
                                                                                R.addEdge(i, i-1);
                                                                            }
                                                                        }
                                                                        
                                                                        if ( (edges & 0b00001) != 0 ) {
                                                                            R.addEdge(node, b);
                                                                        }
                                                                        
                                                                        if ( (edges & 0b00010) != 0 ) {
                                                                            R.addEdge(node, c);
                                                                        }
                                                                        
                                                                        if ( (edges & 0b00100) != 0 ) {
                                                                            R.addEdge(node, d);
                                                                        }
                                                                        
                                                                        if ( (edges & 0b01000) != 0 ) {
                                                                            R.addEdge(node, e);
                                                                        }
                                                                        
                                                                        if ( (edges & 0b10000) != 0 ) {
                                                                            R.addEdge(node, f);
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
                                                                        
                                                                        if (af_edge) {
                                                                            R.addEdge(a, f);
                                                                        }
                                                                        
                                                                        if (bd_edge) {
                                                                            R.addEdge(b, d);
                                                                        }
                                                                        
                                                                        if (be_edge) {
                                                                            R.addEdge(b, e);
                                                                        }
                                                                        
                                                                        if (bf_edge) {
                                                                            R.addEdge(b, f);
                                                                        }
                                                                        
                                                                        if (ce_edge) {
                                                                            R.addEdge(c, e);
                                                                        }
                                                                        
                                                                        if (cf_edge) {
                                                                            R.addEdge(c, f);
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
                                                                        
                                                                        if (ve_edge) {
                                                                            R.addEdge(v, e);
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
                    }
                }
            }
        }
    }
    
    std::cout << "done with 7hat_a_regions. Total regions checked: " << counter << std::endl;
}
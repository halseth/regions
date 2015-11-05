//
//  6hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "6hat_b_regions.h"
#include "store_sign.h"
#include "HatABCRegion.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void generate_6hat_b_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_b, std::map<std::vector<int>,BaseRegion> &regions_4hat_b, std::map<std::vector<int>,BaseRegion> &regions_5hat_b){
    cout << "in generate_6hat_b_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat_b.empty() || regions_4hat_b.empty() || regions_5hat_b.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    // Edge a-c
    cout << "edge a-c" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_b = regions_3hat_b.begin(); it_3hat_b != regions_3hat_b.end(); ++it_3hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(a, c);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat_b = it_3hat_b->second;
        R_3hat_b.addLabelToNode(a, 0);
        R_3hat_b.addLabelToNode(b, 1);
        R_3hat_b.addLabelToNode(c, 2);
        toGlue.push_back(&R_3hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge a-d
    cout << "edge a-d" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(a, d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat_b = it_4hat_b->second;
        R_4hat_b.addLabelToNode(a, 0);
        R_4hat_b.addLabelToNode(b, 1);
        R_4hat_b.addLabelToNode(c, 2);
        R_4hat_b.addLabelToNode(d, 3);
        toGlue.push_back(&R_4hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge a-e
    cout << "edge a-e" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(a, e);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_5hat_b = it_5hat_b->second;
        R_5hat_b.addLabelToNode(a, 0);
        R_5hat_b.addLabelToNode(b, 1);
        R_5hat_b.addLabelToNode(c, 2);
        R_5hat_b.addLabelToNode(d, 3);
        R_5hat_b.addLabelToNode(e, 4);
        toGlue.push_back(&R_5hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge b-d
    cout << "edge b-d" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(b, d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_5hat_b = it_5hat_b->second;
        R_5hat_b.addLabelToNode(a, 0);
        R_5hat_b.addLabelToNode(b, 1);
        R_5hat_b.addLabelToNode(d, 2);
        R_5hat_b.addLabelToNode(e, 3);
        R_5hat_b.addLabelToNode(f, 4);
        toGlue.push_back(&R_5hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // Edge b-e
    cout << "edge b-e" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(b, e);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat_b = it_4hat_b->second;
        R_4hat_b.addLabelToNode(a, 0);
        R_4hat_b.addLabelToNode(b, 1);
        R_4hat_b.addLabelToNode(e, 2);
        R_4hat_b.addLabelToNode(f, 3);
        toGlue.push_back(&R_4hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // Edge b-f
    cout << "edge b-f" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_b = regions_3hat_b.begin(); it_3hat_b != regions_3hat_b.end(); ++it_3hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(b, f);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat_b = it_3hat_b->second;
        R_3hat_b.addLabelToNode(a, 0);
        R_3hat_b.addLabelToNode(b, 1);
        R_3hat_b.addLabelToNode(f, 2);
        toGlue.push_back(&R_3hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    
    // edge c-e
    cout << "edge c-e" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(c, e);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_5hat_b = it_5hat_b->second;
        R_5hat_b.addLabelToNode(a, 0);
        R_5hat_b.addLabelToNode(b, 1);
        R_5hat_b.addLabelToNode(c, 2);
        R_5hat_b.addLabelToNode(e, 3);
        R_5hat_b.addLabelToNode(f, 4);
        toGlue.push_back(&R_5hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge c-f
    cout << "edge c-e" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(c, f);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat_b = it_4hat_b->second;
        R_4hat_b.addLabelToNode(a, 0);
        R_4hat_b.addLabelToNode(b, 1);
        R_4hat_b.addLabelToNode(c, 2);
        R_4hat_b.addLabelToNode(f, 3);
        toGlue.push_back(&R_4hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge d-f
    cout << "edge d-f" << endl;
    for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(6, a, boundaryDominator);
        R.addEdge(d, f);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_5hat_b = it_5hat_b->second;
        R_5hat_b.addLabelToNode(a, 0);
        R_5hat_b.addLabelToNode(b, 1);
        R_5hat_b.addLabelToNode(c, 2);
        R_5hat_b.addLabelToNode(d, 3);
        R_5hat_b.addLabelToNode(f, 4);
        toGlue.push_back(&R_5hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // no edges between boundary nodes
    for (int num_internal = 0; num_internal <= 3; num_internal++) {
        int max_internal_edges = num_internal > 0 ? (1 << (num_internal - 1 )) - 1 : 0;
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            int max_edges = num_internal > 0 ? 0b1111 : 0b0000;
            for (int edges = 0b0000; edges <= max_edges; edges++) {
                
                std::vector<int> boundaryDominator;
                boundaryDominator.push_back(b);
                HatABCRegion R(6, a, boundaryDominator);
                
                // To keep last node added
                int node = -1;
                
                for (int i = 0; i < num_internal; i++) {
                    node = R.addNode();
                    R.addEdge(a, node);
                    R.addEdge(node, b);
                    // Add internal edge
                    if ( i > 0 && ( internal_edges & ( 1 << (i-1) ) ) != 0 ){
                        R.addEdge(node, node-1);
                    }
                }
                
                if ( (edges & 0b0001) != 0 ) {
                    R.addEdge(node, c);
                }
                
                if ( (edges & 0b0010) != 0 ) {
                    R.addEdge(node, d);
                }
                
                if ( (edges & 0b0100) != 0 ) {
                    R.addEdge(node, e);
                }
                
                if ( (edges & 0b1000) != 0 ) {
                    R.addEdge(node, f);
                }
                
                store_sign(R, signature_minimal);
            }
        }
    }
    
    
    cout << "done with 6hat_b_regions." << endl;
    
}

void old_generate_6hat_a_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal){
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
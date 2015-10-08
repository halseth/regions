//
//  5hat_a_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 21/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <iostream>
using namespace std;

#include "5hat_b_regions.h"
#include "store_sign.h"

void generate_5hat_b_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat_b, std::map<std::vector<int>,BaseRegion> &regions_4hat_b){
    cout << "in generate_5hat_b_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat_b.empty() || regions_4hat_b.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    
    // Edge a-c
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_b = regions_3hat_b.begin(); it_3hat_b != regions_3hat_b.end(); ++it_3hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(5, a, boundaryDominator);
        R.addEdge(a, c);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat_b = it_3hat_b->second;
        R_3hat_b.addLabelToNode(a, 0);
        R_3hat_b.addLabelToNode(b, 1);
        R_3hat_b.addLabelToNode(c, 2);
        toGlue.push_back(&R_3hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // Edge b-e
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_b = regions_3hat_b.begin(); it_3hat_b != regions_3hat_b.end(); ++it_3hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(5, a, boundaryDominator);
        R.addEdge(b, e);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat_b = it_3hat_b->second;
        R_3hat_b.addLabelToNode(a, 0);
        R_3hat_b.addLabelToNode(b, 1);
        R_3hat_b.addLabelToNode(e, 2);
        toGlue.push_back(&R_3hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge b-d
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(5, a, boundaryDominator);
        R.addEdge(b, d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat_b = it_4hat_b->second;
        R_4hat_b.addLabelToNode(a, 0);
        R_4hat_b.addLabelToNode(b, 1);
        R_4hat_b.addLabelToNode(d, 2);
        R_4hat_b.addLabelToNode(e, 3);
        toGlue.push_back(&R_4hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // edge a-d
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(5, a, boundaryDominator);
        R.addEdge(a, d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
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
    
    // edge c-e
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        std::vector<int> boundaryDominator;
        boundaryDominator.push_back(b);
        HatABCRegion R(5, a, boundaryDominator);
        R.addEdge(c, e);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat_b = it_4hat_b->second;
        R_4hat_b.addLabelToNode(a, 0);
        R_4hat_b.addLabelToNode(b, 1);
        R_4hat_b.addLabelToNode(c, 2);
        R_4hat_b.addLabelToNode(e, 3);
        toGlue.push_back(&R_4hat_b);
        
        R.glue(toGlue);
        store_sign(R, signature_minimal);
        
    }
    
    // no edges between boundary nodes
    for (int num_internal = 0; num_internal <= 3; num_internal++) {
        int max_internal_edges = num_internal > 0 ? (1 << (num_internal - 1 )) - 1 : 0;
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            int max_edges = num_internal > 0 ? 0b111 : 0b000;
            for (int edges = 0b000; edges <= max_edges; edges++) {
                
                std::vector<int> boundaryDominator;
                boundaryDominator.push_back(b);
                HatABCRegion R(5, a, boundaryDominator);
                
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
                
                if ( (edges & 0b001) != 0 ) {
                    R.addEdge(node, c);
                }
                
                if ( (edges & 0b010) != 0 ) {
                    R.addEdge(node, d);
                }
                
                if ( (edges & 0b100) != 0 ) {
                    R.addEdge(node, e);
                }
                
                store_sign(R, signature_minimal);
            }
        }
    }
    
    
    cout << "done with 5hat_b_regions." << endl;
    
}
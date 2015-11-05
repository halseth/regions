//
//  5hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 25/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "5hat_regions.h"
#include "store_sign.h"
#include "HatRegion.h"

void generate_5hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<vector<int>,BaseRegion> &regions_3hat, std::map<vector<int>,BaseRegion> &regions_4hat, std::map<vector<int>,BaseRegion> &regions_4hat_b, std::map<vector<int>,BaseRegion> &regions_5hat_b){
    cout << "in generate_5hat_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat.empty() || regions_4hat_b.empty() || regions_5hat_b.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    
    // S any size
    
    // a-c edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
            HatRegion R(5, a);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(c, 2);
            toGlue.push_back(&R_3hat);
            
            BaseRegion R_4hat = it_4hat->second;
            R_4hat.addLabelToNode(a, 0);
            R_4hat.addLabelToNode(c, 1);
            R_4hat.addLabelToNode(d, 2);
            R_4hat.addLabelToNode(e, 3);
            toGlue.push_back(&R_4hat);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    // b-d edge
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
        HatRegion R(5, a);
        R.addEdge(b, d);
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat = it_4hat->second;
        R_4hat.addLabelToNode(a, 0);
        R_4hat.addLabelToNode(b, 1);
        R_4hat.addLabelToNode(d, 2);
        R_4hat.addLabelToNode(e, 3);
        toGlue.push_back(&R_4hat);
        
        R.glue(toGlue);
        
        store_sign(R, signature_minimal);
        
    }
    
    // b-e edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        HatRegion R(5, a);
        R.addEdge(b, e);
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat = it_3hat->second;
        R_3hat.addLabelToNode(a, 0);
        R_3hat.addLabelToNode(b, 1);
        R_3hat.addLabelToNode(e, 2);
        toGlue.push_back(&R_3hat);
        
        R.glue(toGlue);
        
        store_sign(R, signature_minimal);
        
    }
    
    // c-e node
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
            for (int edge_node_d = 0; edge_node_d <= 1; edge_node_d++) {
                HatRegion R(5, a);
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(c, node);
                R.addEdge(e, node);
                
                if(edge_node_d){
                    R.addEdge(node, d);
                }
                
                R.addLabelToNode(a, a);
                R.addLabelToNode(b, b);
                R.addLabelToNode(c, c);
                R.addLabelToNode(d, d);
                R.addLabelToNode(e, e);
                R.addLabelToNode(node, node);
                
                std::vector<BaseRegion*> toGlue;
                
                BaseRegion R_3hat = it_3hat->second;
                R_3hat.addLabelToNode(a, 0);
                R_3hat.addLabelToNode(node, 1);
                R_3hat.addLabelToNode(e, 2);
                toGlue.push_back(&R_3hat);
                
                BaseRegion R_4hat = it_4hat->second;
                R_4hat.addLabelToNode(a, 0);
                R_4hat.addLabelToNode(b, 1);
                R_4hat.addLabelToNode(c, 2);
                R_4hat.addLabelToNode(node, 3);
                toGlue.push_back(&R_4hat);
                
                R.glue(toGlue);
                
                store_sign(R, signature_minimal);
                
            }
            
        }
    }
    
    // b-e node
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_1 = regions_3hat.begin(); it_3hat_1 != regions_3hat.end(); ++it_3hat_1) {
        for (map<vector<int>,BaseRegion>::const_iterator it_3hat_2 = regions_3hat.begin(); it_3hat_2 != regions_3hat.end(); ++it_3hat_2) {
            for (int edge_node_d = 0; edge_node_d <= 1; edge_node_d++) {
                HatRegion R(5, a);
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(b, node);
                R.addEdge(e, node);
                
                if(edge_node_d){
                    R.addEdge(node, d);
                }
                
                R.addLabelToNode(a, a);
                R.addLabelToNode(b, b);
                R.addLabelToNode(c, c);
                R.addLabelToNode(d, d);
                R.addLabelToNode(e, e);
                R.addLabelToNode(node, node);
                
                std::vector<BaseRegion*> toGlue;
                
                BaseRegion R_3hat_1 = it_3hat_1->second;
                R_3hat_1.addLabelToNode(a, 0);
                R_3hat_1.addLabelToNode(b, 1);
                R_3hat_1.addLabelToNode(node, 2);
                toGlue.push_back(&R_3hat_1);
                
                BaseRegion R_3hat_2 = it_3hat_2->second;
                R_3hat_2.addLabelToNode(a, 0);
                R_3hat_2.addLabelToNode(node, 1);
                R_3hat_2.addLabelToNode(e, 2);
                toGlue.push_back(&R_3hat_2);
                
                R.glue(toGlue);
                
                store_sign(R, signature_minimal);
            }
            
            
        }
    }
    
    // |S| = 0
    for (int dangling_n3 = 0; dangling_n3 <= 1; dangling_n3++) {
        for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
            for (int deg2_a_e = 0; deg2_a_e <= 1; deg2_a_e++) {
                
                for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                    for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                        
                        for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
                            for (int deg3_a_d_e = 0; deg3_a_d_e <= 1; deg3_a_d_e++) {
                                
                                
                                for (int deg3_a_c_d = 0; deg3_a_c_d <= 1; deg3_a_c_d++) {
                                    
                                    HatRegion R(5,a);
                                    
                                    for (int i = 0; i < dangling_n3; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_b; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, b);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_e; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, e);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_c; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, c);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_b_c; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, b);
                                        R.addEdge(node, c);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_d; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, d);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_d_e; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, d);
                                        R.addEdge(node, e);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_c_d; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, c);
                                        R.addEdge(node, d);
                                    }
                                    
                                    store_sign(R, signature_minimal);
                                    
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    // |S| > 0, s connected to c or d (symmetric), or a is as good
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
            HatRegion R(5, a);
            int s = R.addNode();
            R.addEdge(a, s);
            R.addEdge(c, s);
            
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(s, s);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_4hat_b = it_4hat_b->second;
            R_4hat_b.addLabelToNode(s, 0);
            R_4hat_b.addLabelToNode(a, 1);
            R_4hat_b.addLabelToNode(b, 2);
            R_4hat_b.addLabelToNode(c, 3);
            toGlue.push_back(&R_4hat_b);
            
            BaseRegion R_5hat_b = it_5hat_b->second;
            R_5hat_b.addLabelToNode(a, 0);
            R_5hat_b.addLabelToNode(s, 1);
            R_5hat_b.addLabelToNode(c, 2);
            R_5hat_b.addLabelToNode(d, 3);
            R_5hat_b.addLabelToNode(e, 4);
            toGlue.push_back(&R_5hat_b);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    
    
    // Add symmetries
    cout << "find symmetries"<< endl;
    std::map<vector<int>,BaseRegion> signature_minimal_copy(signature_minimal.begin(), signature_minimal.end());
    
    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy.begin(); it != signature_minimal_copy.end(); ++it) {
        HatRegion R(5,a);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        BaseRegion copy = it->second;
        copy.addLabelToNode(a, 0);
        copy.addLabelToNode(e, 1);
        copy.addLabelToNode(d, 2);
        copy.addLabelToNode(c, 3);
        copy.addLabelToNode(b, 4);
        
        R.glue(&copy);
        
        store_sign(R, signature_minimal);
    }
    
    cout << "done with 5hat_regions." << endl;
}

//
//  4_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/10/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "store_sign.h"
#include "InnerRegion.hpp"

#include "4_regions.hpp"

void generate_4_regions(std::map<vector<int>,BaseRegion> &signature_minimal,std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_3, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_5hat){
    cout << "in generate_4_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_3.empty() || regions_4hat.empty() || regions_5hat.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    // ---------------- S any size ----------------
    
    // a-c edge
    cout << "---------------- a-c edge ----------------" << endl;
    std::map<std::vector<int>,BaseRegion>::const_iterator it_3_a, it_3_b;
    for(it_3_a = regions_3.begin(); it_3_a != regions_3.end(); ++it_3_a){
        for(it_3_b = regions_3.begin(); it_3_b != regions_3.end(); ++it_3_b){
            InnerRegion R(4,a,c);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R1 = it_3_a->second;
            R1.addLabelToNode(a, 0);
            R1.addLabelToNode(b, 1);
            R1.addLabelToNode(c, 2);
            toGLue.push_back(&R1);
            
            BaseRegion R2 = it_3_b->second;
            R2.addLabelToNode(c, 0);
            R2.addLabelToNode(d, 1);
            R2.addLabelToNode(a, 2);
            toGLue.push_back(&R2);
            
            R.glue(toGLue);
            
            inner_region_store_sign(R, signature_minimal);
        }
    }
    
    // b-d edge
    cout << "---------------- b-d edge ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_3hat_a = regions_3hat.begin(); it_3hat_a != regions_3hat.end(); ++it_3hat_a){
        for(map<vector<int>,BaseRegion>::const_iterator it_3hat_b = regions_3hat.begin(); it_3hat_b != regions_3hat.end(); ++it_3hat_b){
            InnerRegion R(4,a,c);
            R.addEdge(b, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R1 = it_3hat_a->second;
            R1.addLabelToNode(a, 0);
            R1.addLabelToNode(b, 1);
            R1.addLabelToNode(d, 2);
            toGLue.push_back(&R1);
            
            BaseRegion R2 = it_3hat_b->second;
            R2.addLabelToNode(c, 0);
            R2.addLabelToNode(d, 1);
            R2.addLabelToNode(b, 2);
            toGLue.push_back(&R2);
            
            R.glue(toGLue);
            
            inner_region_store_sign(R, signature_minimal);
        }
    }
    
    // Node between b and d
    cout << "---------------- b-d node ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_4hat_a = regions_4hat.begin(); it_4hat_a != regions_4hat.end(); ++it_4hat_a){
        for(map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat.begin(); it_4hat_b != regions_4hat.end(); ++it_4hat_b){
            InnerRegion R(4,a,c);
            int e = R.addNode();
            R.addEdge(b, e);
            R.addEdge(e, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R1 = it_4hat_a->second;
            R1.addLabelToNode(a, 0);
            R1.addLabelToNode(b, 1);
            R1.addLabelToNode(e, 2);
            R1.addLabelToNode(d, 3);
            toGLue.push_back(&R1);
            
            BaseRegion R2 = it_4hat_b->second;
            R2.addLabelToNode(c, 0);
            R2.addLabelToNode(d, 1);
            R2.addLabelToNode(e, 2);
            R2.addLabelToNode(b, 3);
            toGLue.push_back(&R2);
            
            R.glue(toGLue);
            
            // because the middle node (e) might not be adjacent to endpoint
            //store_sign_if_valid(R, signature_minimal);
            inner_region_store_sign(R, signature_minimal);
        }
    }
    
    // ---------------- |S| = 0 ----------------
    cout << "---------------- |S| = 0 ----------------" << endl;
    for(int dangling_n3_a = 0; dangling_n3_a <= 1; dangling_n3_a++){
        for(int dangling_n3_c = 0; dangling_n3_c <= 1; dangling_n3_c++){
            for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
                for (int deg2_b_c = 0; deg2_b_c <= 1; deg2_b_c++) {
                    for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
                        for (int deg2_c_d = 0; deg2_c_d <= 1; deg2_c_d++) {
                            
                            for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                                for (int deg3_a_c_d = 0; deg3_a_c_d <= 1; deg3_a_c_d++) {
                                    for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                                        InnerRegion R(4, a, c);
                                        
                                        for (int i = 0; i < deg2_a_b; i++) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                            R.addEdge(b, node);
                                        }
                                        
                                        for (int i = 0; i < deg2_b_c; i++) {
                                            int node = R.addNode();
                                            R.addEdge(b, node);
                                            R.addEdge(c, node);
                                        }
                                        
                                        for (int i = 0; i < deg2_c_d; i++) {
                                            int node = R.addNode();
                                            R.addEdge(c, node);
                                            R.addEdge(d, node);
                                        }
                                        
                                        for (int i = 0; i < deg2_a_d; i++) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                            R.addEdge(d, node);
                                        }
                                        
                                        //TODO: check symmetri
                                        for (int i = 0; i < deg3_a_b_c; i++) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                            R.addEdge(b, node);
                                            R.addEdge(c, node);
                                        }
                                        
                                        for (int i = 0; i < deg3_a_c_d; i++) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                            R.addEdge(c, node);
                                            R.addEdge(d, node);
                                        }
                                        
                                        for (int i = 0; i < deg2_a_c; i++) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                            R.addEdge(c, node);
                                        }
                                        
                                        if(dangling_n3_a) {
                                            int node = R.addNode();
                                            R.addEdge(a, node);
                                        }
                                        
                                        if(dangling_n3_c) {
                                            int node = R.addNode();
                                            R.addEdge(c, node);
                                        }
                                        
                                        inner_region_store_sign(R, signature_minimal);
                                    }
                                    
                                }
                                
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    // ---------------- |S| > 1 ----------------
    
    cout << "---------------- |S| > 1 ----------------" << endl;
    
    // No node connected to c is handled by adding 4hat regions
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
        BaseRegion R = it_4hat->second;
        store_sign(R, signature_minimal); // TODO?
    }
    cout << "---------------- |S| > 1 + w ----------------" << endl;
    
    // At least one node connected to c
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat_a = regions_5hat.begin(); it_5hat_a != regions_5hat.end(); ++it_5hat_a){
        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat.begin(); it_5hat_b != regions_5hat.end(); ++it_5hat_b){
            InnerRegion R(4, a,c);
            int s = R.addNode();
            R.addEdge(a, s);
            
            int e = R.addNode();
            R.addEdge(e, c);
            R.addEdge(s, e);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(s, s);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R1 = it_5hat_a->second;
            R1.addLabelToNode(s, 0);
            R1.addLabelToNode(a, 1);
            R1.addLabelToNode(b, 2);
            R1.addLabelToNode(c, 3);
            R1.addLabelToNode(e, 4);
            toGLue.push_back(&R1);
            
            BaseRegion R2 = it_5hat_b->second;
            R2.addLabelToNode(s, 0);
            R2.addLabelToNode(e, 1);
            R2.addLabelToNode(c, 2);
            R2.addLabelToNode(d, 3);
            R2.addLabelToNode(a, 4);
            toGLue.push_back(&R2);
            
            R.glue(toGLue);
            
            // will lead to invalid regions, so only store those that are valid
            //store_sign_if_valid(R, signature_minimal);
            inner_region_store_sign(R, signature_minimal);
        }
    }
    
    // Add symmetries
    cout << "find symmetries"<< endl;
    std::map<vector<int>,BaseRegion> signature_minimal_copy(signature_minimal.begin(), signature_minimal.end());
    
    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy.begin(); it != signature_minimal_copy.end(); ++it) {
        InnerRegion R(4,a,c);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        
        BaseRegion copy = it->second;
        copy.addLabelToNode(c, 0);
        copy.addLabelToNode(b, 1);
        copy.addLabelToNode(a, 2);
        copy.addLabelToNode(d, 3);
        R.glue(&copy);
        
        inner_region_store_sign(R, signature_minimal);
    }
    
    cout << "done with 4_regions" << endl;
}
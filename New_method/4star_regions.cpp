//
//  4star_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 06/10/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "store_sign.h"
#include "InnerRegion.hpp"

#include "4star_regions.hpp"

void generate_4star_regions(std::map<vector<int>,BaseRegion> &signature_minimal,std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_3,std::map<std::vector<int>,BaseRegion> &regions_4hat,std::map<std::vector<int>,BaseRegion> &regions_6hat){
//    cout << "in generate_4star_regions" << endl;
//    
//    if(!signature_minimal.empty()){
//        cerr << "signminimal not empty";
//        exit(1);
//    }
//
//    if(regions_3hat.empty() || regions_3.empty() || regions_4hat.empty()|| regions_6hat.empty()){
//        cerr << "needed regions empty" << endl;
//        exit(1);
//    }
//    
//    int a = 0;
//    int b = 1;
//    int c = 2;
//    int d = 3;
//    // ---------------- S any size ----------------
//    
//    // a-c edge
//    cout << "---------------- a-c edge ----------------" << endl;
//    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
//        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_3 = regions_3.begin(); it_3 != regions_3.end(); ++it_3){
//            InnerRegion R(4,a,d);
//            R.addEdge(a, c);
//            R.addLabelToNode(a, a);
//            R.addLabelToNode(b, b);
//            R.addLabelToNode(c, c);
//            R.addLabelToNode(d, d);
//            
//            std::vector<BaseRegion*> toGLue;
//            
//            BaseRegion R_3hat = it_3hat->second;
//            R_3hat.addLabelToNode(a, 0);
//            R_3hat.addLabelToNode(b, 1);
//            R_3hat.addLabelToNode(c, 2);
//            toGLue.push_back(&R_3hat);
//            
//            BaseRegion R_3 = it_3->second;
//            R_3.addLabelToNode(a, 0);
//            R_3.addLabelToNode(c, 1);
//            R_3.addLabelToNode(d, 2);
//            toGLue.push_back(&R_3);
//            
//            R.glue(toGLue);
//            
//            inner_region_store_sign(R, signature_minimal);
//        }
//    }
//    
//    
//    // ---------------- |S| = 0 ----------------
//    cout << "---------------- |S| = 0 ----------------" << endl;
//    for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
//        for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
//            for (int deg2_c_d = 0; deg2_c_d <= 1; deg2_c_d++) {
//                for(int dangling_n3_a = 0; dangling_n3_a <= 1; dangling_n3_a++){
//                    for(int dangling_n3_d = 0; dangling_n3_d <= 1; dangling_n3_d++){
//                        
//                        for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
//                            for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
//                                int max_deg2_b_d = deg3_a_b_c || deg2_a_c ? 0 : 1;
//                                int max_deg3_b_c_d = max_deg2_b_d;
//                                for (int deg2_b_d = 0; deg2_b_d <= max_deg2_b_d; deg2_b_d++) {
//                                    for (int deg3_b_c_d = 0; deg3_b_c_d <= max_deg3_b_c_d; deg3_b_c_d++) {
//                                        
//                                        int max_deg3_a_b_d = deg2_a_c || deg3_a_b_c ? 0 : 1;
//                                        for (int deg3_a_b_d = 0; deg3_a_b_d <= max_deg3_a_b_d; deg3_a_b_d++) {
//                                            int max_deg3_a_c_d = deg2_b_d || deg3_b_c_d || deg3_a_b_d ? 0 : 1;
//                                            for (int deg3_a_c_d = 0; deg3_a_c_d <= max_deg3_a_c_d; deg3_a_c_d++) {
//                                                
//                                                int max_deg4 = deg2_a_c || deg3_a_b_c || deg2_b_d || deg3_b_c_d || deg3_a_b_d || deg3_a_c_d ? 0 : 1;
//                                                for (int deg4 = 0; deg4 <= max_deg4; deg4++) {
//                                                    InnerRegion R(4, a, d);
//                                                    
//                                                    for (int i = 0; i < deg2_a_b; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(b, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg2_c_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(c, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg2_a_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    if(dangling_n3_a) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                    }
//                                                    
//                                                    if(dangling_n3_d) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    //TODO: check symmetri
//                                                    for (int i = 0; i < deg3_a_b_c; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(b, node);
//                                                        R.addEdge(c, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg2_a_c; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(c, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg2_b_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(b, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    
//                                                    for (int i = 0; i < deg3_b_c_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(b, node);
//                                                        R.addEdge(c, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg3_a_b_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(b, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg3_a_c_d; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(c, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    for (int i = 0; i < deg4; i++) {
//                                                        int node = R.addNode();
//                                                        R.addEdge(a, node);
//                                                        R.addEdge(b, node);
//                                                        R.addEdge(c, node);
//                                                        R.addEdge(d, node);
//                                                    }
//                                                    
//                                                    inner_region_store_sign(R, signature_minimal);
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // ---------------- |S| > 1 ----------------
//
//    cout << "---------------- |S| > 1 ----------------" << endl;
//
//    // No node connected to d is handled by adding 4hat regions
//    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
//        BaseRegion R = it_4hat->second;
//        store_sign(R, signature_minimal); // TODO?
//    }
//    cout << "---------------- |S| > 1 + w ----------------" << endl;
//
//    // At least one node connected to d
//    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
//        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat = regions_6hat.begin(); it_6hat != regions_6hat.end(); ++it_6hat){
//            InnerRegion R(4, a,d);
//            int s = R.addNode();
//            R.addEdge(a, s);
//            
//            int node = R.addNode();
//            R.addEdge(s, node);
//            R.addEdge(node, d);
//            R.addLabelToNode(a, a);
//            R.addLabelToNode(b, b);
//            R.addLabelToNode(c, c);
//            R.addLabelToNode(d, d);
//            R.addLabelToNode(s, s);
//            R.addLabelToNode(node, node);
//            
//            std::vector<BaseRegion*> toGLue;
//            
//            BaseRegion R_4hat = it_4hat->second;
//            R_4hat.addLabelToNode(s, 0);
//            R_4hat.addLabelToNode(node, 1);
//            R_4hat.addLabelToNode(d, 2);
//            R_4hat.addLabelToNode(a, 3);
//            toGLue.push_back(&R_4hat);
//            
//            BaseRegion R_6hat = it_6hat->second;
//            R_6hat.addLabelToNode(s, 0);
//            R_6hat.addLabelToNode(a, 1);
//            R_6hat.addLabelToNode(b, 2);
//            R_6hat.addLabelToNode(c, 3);
//            R_6hat.addLabelToNode(d, 4);
//            R_6hat.addLabelToNode(node, 5);
//            toGLue.push_back(&R_6hat);
//            
//            R.glue(toGLue);
//            
//            // will lead to invalid regions, so only store those that are valid
//            // store_sign_if_valid(R, signature_minimal);
//            inner_region_store_sign(R, signature_minimal);
//        }
//    }
//    
//    // Add symmetries
//    cout << "find symmetries"<< endl;
//    std::map<vector<int>,BaseRegion> signature_minimal_copy(signature_minimal.begin(), signature_minimal.end());
//    
//    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy.begin(); it != signature_minimal_copy.end(); ++it) {
//        InnerRegion R(4,a,d);
//        
//        R.addLabelToNode(a, a);
//        R.addLabelToNode(b, b);
//        R.addLabelToNode(c, c);
//        R.addLabelToNode(d, d);
//        
//        BaseRegion copy = it->second;
//        copy.addLabelToNode(d, 0);
//        copy.addLabelToNode(c, 1);
//        copy.addLabelToNode(b, 2);
//        copy.addLabelToNode(a, 3);
//        R.glue(&copy);
//        
//        inner_region_store_sign(R, signature_minimal);
//    }
//    
//    cout << "done with 4star_regions" << endl;
}

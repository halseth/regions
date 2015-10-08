//
//  3_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/10/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//


#include <vector>
#include <iostream>
using namespace std;

#include "store_sign.h"
#include "Region.h"
#include "3_regions.hpp"

void generate_3_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_5hat){
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat.empty() || regions_5hat.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    
    // ---------------- |S| = 0 ----------------
    cout << "---------------- |S| =0 ----------------" << endl;
    for (int deg2_a_b = 0; deg2_a_b <= 2; deg2_a_b++) {
        for(int deg2_a_c = 0; deg2_a_c <= 2; deg2_a_c++){
            for(int deg2_b_c = 0; deg2_b_c <= 2; deg2_b_c++){
                for (int deg_3 = 0; deg_3 <= 1; deg_3++) {
                    
                    for(int dangling_n3_a = 0; dangling_n3_a <= 1; dangling_n3_a++){
                        for(int dangling_n3_c = 0; dangling_n3_c <= 1; dangling_n3_c++){
                            Region R(3, a, c);
                            
                            for (int i = 0; i < deg2_a_b; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                                R.addEdge(node, b);
                            }
                            for (int i = 0; i < deg2_a_c; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                                R.addEdge(node, c);
                            }
                            for (int i = 0; i < deg_3; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                                R.addEdge(node, b);
                                R.addEdge(node, c);
                            }
                            
                            if (dangling_n3_a) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                            }
                            
                            if (dangling_n3_c) {
                                int node = R.addNode();
                                R.addEdge(node, c);
                            }
                            
                            store_sign(R, signature_minimal);
                        }
                    }
                }
            }
        }
    }
    
    // ---------------- |S| > 1 ----------------
    cout << "---------------- |S| > 1 ----------------" << endl;
    // No node connected to c is handled by adding 3hat regions
    for(map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        BaseRegion R = it_3hat->second;
        store_sign(R, signature_minimal);
    }
    
    
    // At least one connected to c
    cout << "---------------- |S| > 1 + 1 ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
        for(map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
            Region R(3, a, c);
            
            // We have at least on node in S
            int s = R.addNode();
            R.addEdge(a, s);
            
            int node = R.addNode();
            R.addEdge(s, node);
            R.addEdge(c, node);
            
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(s, s);
            R.addLabelToNode(node, node);
            
            BaseRegion R_5hat = it_5hat->second;
            BaseRegion R_4hat = it_4hat->second;
            std::vector<BaseRegion*> toGLue;
            
            R_5hat.addLabelToNode(s, 0);
            R_5hat.addLabelToNode(a, 1);
            R_5hat.addLabelToNode(b, 2);
            R_5hat.addLabelToNode(c, 3);
            R_5hat.addLabelToNode(node, 4);
            toGLue.push_back(&R_5hat);
            
            R_4hat.addLabelToNode(s, 0);
            R_4hat.addLabelToNode(node, 1);
            R_4hat.addLabelToNode(c, 2);
            R_4hat.addLabelToNode(a, 3);
            toGLue.push_back(&R_4hat);
            
            R.glue(toGLue);
            
            // Will lead to invalid regions, so store only valid
            store_sign_if_valid(R, signature_minimal);
        }
    }

    // Add symmetries
//    cout << "find symmetries"<< endl;
//    std::map<vector<int>,BaseRegion> signature_minimal_copy(signature_minimal.begin(), signature_minimal.end());
//    
//    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy.begin(); it != signature_minimal_copy.end(); ++it) {
//        Region R(3,a,c);
//        
//        R.addLabelToNode(a, a);
//        R.addLabelToNode(b, b);
//        R.addLabelToNode(c, c);
//        
//        BaseRegion copy = it->second;
//        copy.addLabelToNode(c, 0);
//        copy.addLabelToNode(b, 1);
//        copy.addLabelToNode(a, 2);
//        R.glue(&copy);
//        
//        store_sign(R, signature_minimal);
//    }

    cout << "done with 3_regions" << endl;
}

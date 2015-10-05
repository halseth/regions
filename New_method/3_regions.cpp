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
    
    int v = 0;
    int a = 1;
    int w = 2;
    
    // ---------------- |S| = 0 ----------------
    for (int deg2_v_a = 0; deg2_v_a <= 2; deg2_v_a++) {
        for(int deg2_v_w = 0; deg2_v_w <= 2; deg2_v_w++){
            for(int deg2_w_a = 0; deg2_w_a <= 2; deg2_w_a++){
                for (int deg_3 = 0; deg_3 <= 1; deg_3++) {
                    
                    for(int dangling_n3_v = 0; dangling_n3_v <= 1; dangling_n3_v++){
                        for(int dangling_n3_w = 0; dangling_n3_w <= 1; dangling_n3_w++){
                            Region R(3, v, w);
                            
                            for (int i = 0; i < deg2_v_a; i++) {
                                int c = R.addNode();
                                R.addEdge(c, v);
                                R.addEdge(c, a);
                            }
                            for (int i = 0; i < deg2_v_w; i++) {
                                int c = R.addNode();
                                R.addEdge(c, v);
                                R.addEdge(c, w);
                            }
                            for (int i = 0; i < deg_3; i++) {
                                int c = R.addNode();
                                R.addEdge(c, v);
                                R.addEdge(c, a);
                                R.addEdge(c, w);
                            }
                            
                            if (dangling_n3_v) {
                                int c = R.addNode();
                                R.addEdge(c, v);
                            }
                            
                            if (dangling_n3_w) {
                                int c = R.addNode();
                                R.addEdge(c, w);
                            }
                            
                            store_sign(R, signature_minimal);
                        }
                    }
                }
            }
        }
    }
    
    // ---------------- |S| > 1 ----------------
    
    // No node connected to w is handled by adding 3hat regions
    std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat;
    for(it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        BaseRegion R = it_3hat->second;
        store_sign(R, signature_minimal);
    }
    
    
    // At least one connected to w
    std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat, it_4hat;
    for(it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
        for(it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
            Region R(3, v, w);
            
            // We have at least on node in S
            int s = R.addNode();
            R.addEdge(v, s);
            
            int c = R.addNode();
            R.addEdge(s, c);
            R.addEdge(w, c);
            
            BaseRegion R_5hat = it_5hat->second;
            BaseRegion R_4hat = it_4hat->second;
            std::vector<BaseRegion> toGLue;
            
            R.addLabelToNode(v, v);
            R.addLabelToNode(a, a);
            R.addLabelToNode(w, w);
            R.addLabelToNode(s, s);
            R.addLabelToNode(c, c);
            
            R_5hat.addLabelToNode(s, 0);
            R_5hat.addLabelToNode(v, 1);
            R_5hat.addLabelToNode(a, 2);
            R_5hat.addLabelToNode(w, 3);
            R_5hat.addLabelToNode(c, 4);
            toGLue.push_back(R_5hat);
            
            R_4hat.addLabelToNode(s, 0);
            R_4hat.addLabelToNode(c, 1);
            R_4hat.addLabelToNode(w, 2);
            R_4hat.addLabelToNode(v, 3);
            toGLue.push_back(R_4hat);
            
            R.glue(toGLue);
            
            // Will lead to invalid regions, so store only valid
            store_sign_if_valid(R, signature_minimal);
        }
    }

    // TODO: symmetri

    cout << "done with 3_regions" << endl;
}

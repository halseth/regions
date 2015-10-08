//
//  5_regions.cpp
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

#include "5_regions.hpp"

void generate_5_regions(std::map<vector<int>,BaseRegion> &signature_minimal,std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_3, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_4star, std::map<std::vector<int>,BaseRegion> &regions_4, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_6hat){
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_3.empty() || regions_4hat.empty()|| regions_4star.empty() || regions_4.empty() || regions_5hat.empty() || regions_6hat.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    // ---------------- S any size ----------------
    
    // a-c edge
    cout << "---------------- a-c edge ----------------" << endl;
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_4 = regions_4.begin(); it_4 != regions_4.end(); ++it_4){
            Region R(5,a,d);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(c, 2);
            toGLue.push_back(&R_3hat);
            
            BaseRegion R_4 = it_4->second;
            R_4.addLabelToNode(a, 0);
            R_4.addLabelToNode(c, 1);
            R_4.addLabelToNode(d, 2);
            R_4.addLabelToNode(e, 3);
            toGLue.push_back(&R_4);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
    }
    
    // a-d edge
    cout << "---------------- a-d edge ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_3 = regions_3.begin(); it_3 != regions_3.end(); ++it_3){
        for(map<vector<int>,BaseRegion>::const_iterator it_4star = regions_4star.begin(); it_4star != regions_4star.end(); ++it_4star){
            Region R(5,a,d);
            R.addEdge(a, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_3 = it_3->second;
            R_3.addLabelToNode(d, 0);
            R_3.addLabelToNode(e, 1);
            R_3.addLabelToNode(a, 2);
            toGLue.push_back(&R_3);
            
            BaseRegion R_4star = it_4star->second;
            R_4star.addLabelToNode(a, 0);
            R_4star.addLabelToNode(b, 1);
            R_4star.addLabelToNode(c, 2);
            R_4star.addLabelToNode(d, 3);
            toGLue.push_back(&R_4star);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
    }
    
    // b-e edge
    cout << "---------------- b-e edge ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        for(map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
            Region R(5,a,d);
            R.addEdge(b,e);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(e, 2);
            toGLue.push_back(&R_3hat);
            
            BaseRegion R_4hat = it_4hat->second;
            R_4hat.addLabelToNode(d, 0);
            R_4hat.addLabelToNode(e, 1);
            R_4hat.addLabelToNode(b, 2);
            R_4hat.addLabelToNode(c, 3);
            toGLue.push_back(&R_4hat);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
    }
    
    // Node between b and e
    cout << "---------------- b-e node ----------------" << endl;
    for(map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
        for(map<vector<int>,BaseRegion>::const_iterator it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
            Region R(5,a,d);
            int node = R.addNode();
            R.addEdge(b,node);
            R.addEdge(e,node);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(node, node);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_4hat = it_4hat->second;
            R_4hat.addLabelToNode(a, 0);
            R_4hat.addLabelToNode(b, 1);
            R_4hat.addLabelToNode(node, 2);
            R_4hat.addLabelToNode(e, 3);
            toGLue.push_back(&R_4hat);
            
            BaseRegion R_5hat = it_5hat->second;
            R_5hat.addLabelToNode(d, 0);
            R_5hat.addLabelToNode(e, 1);
            R_5hat.addLabelToNode(node, 2);
            R_5hat.addLabelToNode(b, 3);
            R_5hat.addLabelToNode(c, 4);
            toGLue.push_back(&R_5hat);
            
            R.glue(toGLue);
            
            // Since node might not be connected to an endpoint
            store_sign_if_valid(R, signature_minimal);
        }
    }
    
    // ---------------- |S| = 0 ----------------
    cout << "---------------- |S| = 0 ----------------" << endl;
    for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
        for (int deg2_d_c = 0; deg2_d_c <= 1; deg2_d_c++) {
            for (int deg2_a_e = 0; deg2_a_e <= 1; deg2_a_e++) {
                for (int deg2_d_e = 0; deg2_d_e <= 1; deg2_d_e++) {
                    for(int dangling_n3_a = 0; dangling_n3_a <= 1; dangling_n3_a++){
                        for(int dangling_n3_d = 0; dangling_n3_d <= 1; dangling_n3_d++){
                            
                            for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                                for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                                    for (int deg3_a_c_d = 0; deg3_a_c_d <= 1; deg3_a_c_d++) {
                                        int max_deg4_a_b_c_d = deg3_a_b_c || deg2_a_c || deg3_a_c_d ? 0 : 1;
                                        for (int deg4_a_b_c_d = 0; deg4_a_b_c_d <= max_deg4_a_b_c_d; deg4_a_b_c_d++) {
                                            
                                            int max_deg3_b_c_d = deg2_a_c || deg3_a_b_c || deg3_a_c_d || deg4_a_b_c_d ? 0 : 1;
                                            for (int deg3_b_c_d = 0; deg3_b_c_d <= max_deg3_b_c_d; deg3_b_c_d++) {
                                                
                                                int max_deg2_b_d = max_deg3_b_c_d;
                                                for (int deg2_b_d = 0; deg2_b_d <= max_deg2_b_d; deg2_b_d++) {
                                                    
                                                    for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
                                                        for (int deg3_a_d_e = 0; deg3_a_d_e <= 1; deg3_a_d_e++) {
                                                            
                                                            Region R(5, a, d);
                                                            
                                                            for (int i = 0; i < deg2_a_b; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(b, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_d_c; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(d, node);
                                                                R.addEdge(c, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_d_e; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(d, node);
                                                                R.addEdge(e, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_a_e; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(e, node);
                                                            }
                                                            
                                                            if(dangling_n3_a) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                            }
                                                            
                                                            if(dangling_n3_d) {
                                                                int node = R.addNode();
                                                                R.addEdge(d, node);
                                                            }
                                                            
                                                            //TODO: check symmetri
                                                            for (int i = 0; i < deg3_a_b_c; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(b, node);
                                                                R.addEdge(c, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_a_c; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(c, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg3_a_c_d; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(c, node);
                                                                R.addEdge(d, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg4_a_b_c_d; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(b, node);
                                                                R.addEdge(c, node);
                                                                R.addEdge(d, node);
                                                            }
                                                            
                                                            
                                                            for (int i = 0; i < deg3_b_c_d; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(b, node);
                                                                R.addEdge(c, node);
                                                                R.addEdge(d, node);
                                                            }
                                                    
                                                            
                                                            for (int i = 0; i < deg2_b_d; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(b, node);
                                                                R.addEdge(d, node);
                                                            }
                                                            
                                                            
                                                            for (int i = 0; i < deg2_a_d; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(d, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg3_a_d_e; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(d, node);
                                                                R.addEdge(e, node);
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
                        }
                    }
                }
            }
        }
    }
    
    // ---------------- |S| > 1 ----------------
    
    cout << "---------------- |S| > 1 ----------------" << endl;
    
    // No node connected to d is handled by adding 5hat regions
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
        BaseRegion R = it_5hat->second;
        store_sign(R, signature_minimal);
    }
    cout << "---------------- |S| > 1 + w ----------------" << endl;
    
    // At least one node connected to w
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat = regions_6hat.begin(); it_6hat != regions_6hat.end(); ++it_6hat){
            Region R(5, a,d);
            int s = R.addNode();
            R.addEdge(a, s);
            
            int node = R.addNode();
            R.addEdge(s, node);
            R.addEdge(node, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(s, s);
            R.addLabelToNode(node, node);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_5hat = it_5hat->second;
            R_5hat.addLabelToNode(s, 0);
            R_5hat.addLabelToNode(node, 1);
            R_5hat.addLabelToNode(d, 2);
            R_5hat.addLabelToNode(e, 3);
            R_5hat.addLabelToNode(a, 4);
            toGLue.push_back(&R_5hat);
            
            BaseRegion R_6hat = it_6hat->second;
            R_6hat.addLabelToNode(s, 0);
            R_6hat.addLabelToNode(a, 1);
            R_6hat.addLabelToNode(b, 2);
            R_6hat.addLabelToNode(c, 3);
            R_6hat.addLabelToNode(d, 4);
            R_6hat.addLabelToNode(node, 5);
            toGLue.push_back(&R_6hat);
            
            R.glue(toGLue);
            
            // will lead to invalid regions, so only store those that are valid
            store_sign_if_valid(R, signature_minimal);
        }
    }
    
    // Add symmetries
    cout << "find symmetries"<< endl;
    std::map<vector<int>,BaseRegion> signature_minimal_copy(signature_minimal.begin(), signature_minimal.end());
    
    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy.begin(); it != signature_minimal_copy.end(); ++it) {
        Region R(5,a,d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        BaseRegion copy = it->second;
        copy.addLabelToNode(d, 0);
        copy.addLabelToNode(c, 1);
        copy.addLabelToNode(b, 2);
        copy.addLabelToNode(a, 3);
        copy.addLabelToNode(e, 4);
        R.glue(&copy);
        
        store_sign(R, signature_minimal);
    }
    
    cout << "done with 5_regions" << endl;
}

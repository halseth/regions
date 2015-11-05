//
//  6_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 07/10/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

#include "store_sign.h"
#include "Region.h"

#include "6_regions.hpp"

void generate_6_regions(std::map<vector<int>,BaseRegion> &signature_minimal,std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_4star, std::map<std::vector<int>,BaseRegion> &regions_5, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_6hat){
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat.empty()|| regions_4star.empty() || regions_5hat.empty() || regions_5.empty() || regions_6hat.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    // Putting this first since it is heaviest task
    // Node between a and d
    cout << "---------------- a-d node ----------------" << endl;
    
    // Add to a vector for parallel for
    vector<BaseRegion> vec_5regions;
    for(map<vector<int>,BaseRegion>::const_iterator it_5_a = regions_5.begin(); it_5_a != regions_5.end(); ++it_5_a){
        vec_5regions.push_back(it_5_a->second);
    }
    
    
    
    
#pragma omp parallel
    {
        std::map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        
#pragma omp for
        for(int i = 0; i < vec_5regions.size(); i++){
            for(map<vector<int>,BaseRegion>::const_iterator it_5_b = regions_5.begin(); it_5_b != regions_5.end(); ++it_5_b){
                Region R(6,a,d);
                int node = R.addNode();
                R.addEdge(a,node);
                R.addEdge(d,node);
                R.addLabelToNode(a, a);
                R.addLabelToNode(b, b);
                R.addLabelToNode(c, c);
                R.addLabelToNode(d, d);
                R.addLabelToNode(e, e);
                R.addLabelToNode(f, f);
                R.addLabelToNode(node, node);
                
                std::vector<BaseRegion*> toGLue;
                
                BaseRegion R_5_a = vec_5regions[i];
                R_5_a.addLabelToNode(a, 0);
                R_5_a.addLabelToNode(b, 1);
                R_5_a.addLabelToNode(c, 2);
                R_5_a.addLabelToNode(d, 3);
                R_5_a.addLabelToNode(node, 4);
                toGLue.push_back(&R_5_a);
                
                BaseRegion R_5_b = it_5_b->second;
                R_5_b.addLabelToNode(d, 0);
                R_5_b.addLabelToNode(e, 1);
                R_5_b.addLabelToNode(f, 2);
                R_5_b.addLabelToNode(a, 3);
                R_5_b.addLabelToNode(node, 4);
                toGLue.push_back(&R_5_b);
                
                R.glue(toGLue);
                
                // Since node might not be connected to an endpoint
                store_sign_if_valid(R, priv_signature_minimal);
            }
            cout << "---------------- a-d node: Thread " << tid <<  " / " << nthreads << " done with " << i <<" ----------------" << endl;
        }
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to map " << endl;
            for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                BaseRegion R = it->second;
                store_sign(R, signature_minimal);
            }
        }
    } // parallel region over
    
    
    
    
    // Then do the rest
    
    // ---------------- S any size ----------------
    
    cout << "---------------- a-c edge ----------------" << endl;
    int local_total = regions_3hat.size();
    int local_counter = 0;
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_5 = regions_5.begin(); it_5 != regions_5.end(); ++it_5){
            Region R(6,a,d);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(c, 2);
            toGLue.push_back(&R_3hat);
            
            BaseRegion R_5 = it_5->second;
            R_5.addLabelToNode(d, 0);
            R_5.addLabelToNode(e, 1);
            R_5.addLabelToNode(f, 2);
            R_5.addLabelToNode(a, 3);
            R_5.addLabelToNode(c, 4);
            toGLue.push_back(&R_5);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- a-c edge: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // a-d edge
    cout << "---------------- a-d edge ----------------" << endl;
    local_total = regions_4star.size();
    local_counter = 0;
    for(map<vector<int>,BaseRegion>::const_iterator it_4star_a = regions_4star.begin(); it_4star_a != regions_4star.end(); ++it_4star_a){
        for(map<vector<int>,BaseRegion>::const_iterator it_4star_b = regions_4star.begin(); it_4star_b != regions_4star.end(); ++it_4star_b){
            Region R(6,a,d);
            R.addEdge(a, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_4star_a = it_4star_a->second;
            R_4star_a.addLabelToNode(a, 0);
            R_4star_a.addLabelToNode(b, 1);
            R_4star_a.addLabelToNode(c, 2);
            R_4star_a.addLabelToNode(d, 3);
            toGLue.push_back(&R_4star_a);
            
            BaseRegion R_4star_b = it_4star_b->second;
            R_4star_b.addLabelToNode(d, 0);
            R_4star_b.addLabelToNode(e, 1);
            R_4star_b.addLabelToNode(f, 2);
            R_4star_b.addLabelToNode(a, 3);
            toGLue.push_back(&R_4star_b);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- a-d edge: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // b-e edge
    cout << "---------------- b-e edge ----------------" << endl;
    local_total = regions_4hat.size();
    local_counter = 0;
    for(map<vector<int>,BaseRegion>::const_iterator it_4hat_a = regions_4hat.begin(); it_4hat_a != regions_4hat.end(); ++it_4hat_a){
        for(map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat.begin(); it_4hat_b != regions_4hat.end(); ++it_4hat_b){
            Region R(6,a,d);
            R.addEdge(b,e);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_4hat_a = it_4hat_a->second;
            R_4hat_a.addLabelToNode(a, 0);
            R_4hat_a.addLabelToNode(b, 1);
            R_4hat_a.addLabelToNode(e, 2);
            R_4hat_a.addLabelToNode(f, 3);
            toGLue.push_back(&R_4hat_a);
            
            BaseRegion R_4hat_b = it_4hat_b->second;
            R_4hat_b.addLabelToNode(d, 0);
            R_4hat_b.addLabelToNode(e, 1);
            R_4hat_b.addLabelToNode(b, 2);
            R_4hat_b.addLabelToNode(c, 3);
            toGLue.push_back(&R_4hat_b);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- b-e edge: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // b-f edge
    cout << "---------------- b-f edge ----------------" << endl;
    local_total = regions_3hat.size();
    local_counter = 0;
    for(map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat){
        for(map<vector<int>,BaseRegion>::const_iterator it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); ++it_5hat){
            Region R(6,a,d);
            R.addEdge(b,f);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(f, 2);
            toGLue.push_back(&R_3hat);
            
            BaseRegion R_5hat = it_5hat->second;
            R_5hat.addLabelToNode(d, 0);
            R_5hat.addLabelToNode(e, 1);
            R_5hat.addLabelToNode(f, 2);
            R_5hat.addLabelToNode(b, 3);
            R_5hat.addLabelToNode(c, 4);
            toGLue.push_back(&R_5hat);
            
            R.glue(toGLue);
            
            store_sign(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- b-f edge: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // Node between b and e
    cout << "---------------- b-e node ----------------" << endl;
    local_total = regions_5hat.size();
    local_counter = 0;
    for(map<vector<int>,BaseRegion>::const_iterator it_5hat_a = regions_5hat.begin(); it_5hat_a != regions_5hat.end(); ++it_5hat_a){
        for(map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat.begin(); it_5hat_b != regions_5hat.end(); ++it_5hat_b){
            Region R(6,a,d);
            int node = R.addNode();
            R.addEdge(b,node);
            R.addEdge(e,node);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            R.addLabelToNode(node, node);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_5hat_a = it_5hat_a->second;
            R_5hat_a.addLabelToNode(a, 0);
            R_5hat_a.addLabelToNode(b, 1);
            R_5hat_a.addLabelToNode(node, 2);
            R_5hat_a.addLabelToNode(e, 3);
            R_5hat_a.addLabelToNode(f, 4);
            toGLue.push_back(&R_5hat_a);
            
            BaseRegion R_5hat_b = it_5hat_b->second;
            R_5hat_b.addLabelToNode(d, 0);
            R_5hat_b.addLabelToNode(e, 1);
            R_5hat_b.addLabelToNode(node, 2);
            R_5hat_b.addLabelToNode(b, 3);
            R_5hat_b.addLabelToNode(c, 4);
            toGLue.push_back(&R_5hat_b);
            
            R.glue(toGLue);
            
            // Since node might not be connected to an endpoint
            store_sign_if_valid(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- b-e node: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // Node between b and f
    cout << "---------------- b-f node ----------------" << endl;
    local_total = regions_4hat.size();
    local_counter = 0;
    for(map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat){
        for(map<vector<int>,BaseRegion>::const_iterator it_6hat = regions_6hat.begin(); it_6hat != regions_6hat.end(); ++it_6hat){
            Region R(6,a,d);
            int node = R.addNode();
            R.addEdge(b,node);
            R.addEdge(f,node);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(f, f);
            R.addLabelToNode(node, node);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_4hat = it_4hat->second;
            R_4hat.addLabelToNode(a, 0);
            R_4hat.addLabelToNode(b, 1);
            R_4hat.addLabelToNode(node, 2);
            R_4hat.addLabelToNode(f, 3);
            toGLue.push_back(&R_4hat);
            
            BaseRegion R_6hat = it_6hat->second;
            R_6hat.addLabelToNode(d, 0);
            R_6hat.addLabelToNode(e, 1);
            R_6hat.addLabelToNode(f, 2);
            R_6hat.addLabelToNode(node, 3);
            R_6hat.addLabelToNode(b, 4);
            R_6hat.addLabelToNode(c, 5);
            toGLue.push_back(&R_6hat);
            
            R.glue(toGLue);
            
            // Since node might not be connected to an endpoint
            store_sign_if_valid(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- b-f node: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
//    // Node between a and d
//    cout << "---------------- a-d node ----------------" << endl;
//    local_total = regions_5.size();
//    local_counter = 0;
//    for(map<vector<int>,BaseRegion>::const_iterator it_5_a = regions_5.begin(); it_5_a != regions_5.end(); ++it_5_a){
//        for(map<vector<int>,BaseRegion>::const_iterator it_5_b = regions_5.begin(); it_5_b != regions_5.end(); ++it_5_b){
//            Region R(6,a,d);
//            int node = R.addNode();
//            R.addEdge(a,node);
//            R.addEdge(d,node);
//            R.addLabelToNode(a, a);
//            R.addLabelToNode(b, b);
//            R.addLabelToNode(c, c);
//            R.addLabelToNode(d, d);
//            R.addLabelToNode(e, e);
//            R.addLabelToNode(f, f);
//            R.addLabelToNode(node, node);
//            
//            std::vector<BaseRegion*> toGLue;
//            
//            BaseRegion R_5_a = it_5_a->second;
//            R_5_a.addLabelToNode(a, 0);
//            R_5_a.addLabelToNode(b, 1);
//            R_5_a.addLabelToNode(c, 2);
//            R_5_a.addLabelToNode(d, 3);
//            R_5_a.addLabelToNode(node, 4);
//            toGLue.push_back(&R_5_a);
//            
//            BaseRegion R_5_b = it_5_b->second;
//            R_5_b.addLabelToNode(d, 0);
//            R_5_b.addLabelToNode(e, 1);
//            R_5_b.addLabelToNode(f, 2);
//            R_5_b.addLabelToNode(a, 3);
//            R_5_b.addLabelToNode(node, 4);
//            toGLue.push_back(&R_5_b);
//            
//            R.glue(toGLue);
//            
//            // Since node might not be connected to an endpoint
//            store_sign_if_valid(R, signature_minimal);
//        }
//        local_counter++;
//        cout << "---------------- a-d node: " << local_counter << " / " << local_total << " ----------------" << endl;
//    }
    
    // ---------------- |S| = 0 ----------------
    cout << "---------------- |S| = 0 ----------------" << endl;
    for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
        for (int deg2_d_c = 0; deg2_d_c <= 1; deg2_d_c++) {
            for (int deg2_a_f = 0; deg2_a_f <= 1; deg2_a_f++) {
                for (int deg2_d_e = 0; deg2_d_e <= 1; deg2_d_e++) {
                    for(int dangling_n3_a = 0; dangling_n3_a <= 1; dangling_n3_a++){
                        for(int dangling_n3_d = 0; dangling_n3_d <= 1; dangling_n3_d++){
                            
                            for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                                for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                                    for (int deg3_a_e_f = 0; deg3_a_e_f <= 1; deg3_a_e_f++) {
                                        for (int deg2_a_e = 0; deg2_a_e <= 1; deg2_a_e++) {
                                            
                                            int max_deg3_b_c_d = deg2_a_c || deg3_a_b_c ? 0 : 1;
                                            for (int deg3_b_c_d = 0; deg3_b_c_d <= max_deg3_b_c_d; deg3_b_c_d++) {
                                                
                                                int max_deg2_b_d = max_deg3_b_c_d;
                                                for (int deg2_b_d = 0; deg2_b_d <= max_deg2_b_d; deg2_b_d++) {
                                                    
                                                    int max_deg3_d_e_f = deg3_a_e_f || deg2_a_e ? 0 : 1;
                                                    for (int deg3_d_e_f = 0; deg3_d_e_f <= max_deg3_d_e_f; deg3_d_e_f++) {
                                                        int max_deg2_d_f = max_deg3_d_e_f;
                                                        for (int deg2_d_f = 0; deg2_d_f <= max_deg3_d_e_f; deg2_d_f++) {
                                                            
                                                            Region R(6, a, d);
                                                            
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
                                                            
                                                            for (int i = 0; i < deg2_a_f; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(f, node);
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
                                                            
                                                            for (int i = 0; i < deg3_a_e_f; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(e, node);
                                                                R.addEdge(f, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_a_e; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(a, node);
                                                                R.addEdge(e, node);
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
                                                            
                                                            
                                                            for (int i = 0; i < deg3_d_e_f; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(d, node);
                                                                R.addEdge(e, node);
                                                                R.addEdge(f, node);
                                                            }
                                                            
                                                            for (int i = 0; i < deg2_d_f; i++) {
                                                                int node = R.addNode();
                                                                R.addEdge(d, node);
                                                                R.addEdge(f, node);
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
    
    // No node connected to d is handled by adding 6hat regions
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat = regions_6hat.begin(); it_6hat != regions_6hat.end(); ++it_6hat){
        BaseRegion R = it_6hat->second;
        store_sign(R, signature_minimal);
    }
    cout << "---------------- |S| > 1 + w ----------------" << endl;
    
    // At least one node connected to w
    local_total = regions_6hat.size();
    local_counter = 0;
    for(std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat_a = regions_6hat.begin(); it_6hat_a != regions_6hat.end(); ++it_6hat_a){
        for(std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat_b = regions_6hat.begin(); it_6hat_b != regions_6hat.end(); ++it_6hat_b){
            Region R(6, a,d);
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
            R.addLabelToNode(f, f);
            R.addLabelToNode(s, s);
            R.addLabelToNode(node, node);
            
            std::vector<BaseRegion*> toGLue;
            
            BaseRegion R_6hat_a = it_6hat_a->second;
            R_6hat_a.addLabelToNode(s, 0);
            R_6hat_a.addLabelToNode(a, 1);
            R_6hat_a.addLabelToNode(b, 2);
            R_6hat_a.addLabelToNode(c, 3);
            R_6hat_a.addLabelToNode(d, 4);
            R_6hat_a.addLabelToNode(node, 5);
            toGLue.push_back(&R_6hat_a);
            
            BaseRegion R_6hat_b = it_6hat_b->second;
            R_6hat_b.addLabelToNode(s, 0);
            R_6hat_b.addLabelToNode(node, 1);
            R_6hat_b.addLabelToNode(d, 2);
            R_6hat_b.addLabelToNode(e, 3);
            R_6hat_b.addLabelToNode(f, 4);
            R_6hat_b.addLabelToNode(a, 5);
            toGLue.push_back(&R_6hat_b);
            
            R.glue(toGLue);
            
            // will lead to invalid regions, so only store those that are valid
            store_sign_if_valid(R, signature_minimal);
        }
        local_counter++;
        cout << "---------------- |S| > 1 + w: " << local_counter << " / " << local_total << " ----------------" << endl;
    }
    
    // Add symmetries
    cout << "find symmetries"<< endl;
    
    std::map<vector<int>,BaseRegion> signature_minimal_copy1(signature_minimal.begin(), signature_minimal.end());
    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy1.begin(); it != signature_minimal_copy1.end(); ++it) {
        Region R(6,a,d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        BaseRegion copy = it->second;
        copy.addLabelToNode(d, 0);
        copy.addLabelToNode(c, 1);
        copy.addLabelToNode(b, 2);
        copy.addLabelToNode(a, 3);
        copy.addLabelToNode(f, 4);
        copy.addLabelToNode(e, 5);
        R.glue(&copy);
        
        store_sign(R, signature_minimal);
    }
    
    std::map<vector<int>,BaseRegion> signature_minimal_copy2(signature_minimal.begin(), signature_minimal.end());
    for (map<vector<int>,BaseRegion>::const_iterator it = signature_minimal_copy2.begin(); it != signature_minimal_copy2.end(); ++it) {
        Region R(6,a,d);
        
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        R.addLabelToNode(f, f);
        
        BaseRegion copy = it->second;
        copy.addLabelToNode(a, 0);
        copy.addLabelToNode(f, 1);
        copy.addLabelToNode(e, 2);
        copy.addLabelToNode(d, 3);
        copy.addLabelToNode(c, 4);
        copy.addLabelToNode(b, 5);
        R.glue(&copy);
        
        store_sign(R, signature_minimal);
    }
    
    cout << "done with 6_regions" << endl;
}
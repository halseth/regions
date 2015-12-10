//
//  enumerate_outer.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "enumerate_outer.hpp"
#include "HatRegion.h"
#include "BaseRegion.h"

void enumerate_non_dominator_outer_3regions(vector<BaseRegion> &outer_non_dom_3regions) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    
    for (int a_b_node = 0; a_b_node <= 1; a_b_node++) {
        int max_a_b_c_node = a_b_node == 0 ? 1 : 0;
        for (int a_b_c_node = 0; a_b_c_node <= max_a_b_c_node; a_b_c_node++) {
            HatRegion R(3,a);
            
            if (a_b_node) {
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(b, node);
            }
            
            if (a_b_c_node) {
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(b, node);
                R.addEdge(c, node);
            }
            
            if (!R.isValid()) {
                cout << "not valid"<< endl;
                R.printRegion();
                exit(0);
            }
            
            outer_non_dom_3regions.push_back(R);
        }
        
    }
    
    
    cout << "Done enumeratin non-dominating outer 3regions: " << outer_non_dom_3regions.size() << endl;
}

void enumerate_non_dominator_outer_4regions(vector<BaseRegion> &outer_non_dom_4regions) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    for (int a_b_node = 0; a_b_node <= 1; a_b_node++) {
        
        for (int a_c_node = 0; a_c_node <= 1; a_c_node++) {
                
                int max_a_b_c_d_node = a_b_node == 0 && a_c_node == 0 ? 1 : 0;
                for (int a_b_c_d_node = 0; a_b_c_d_node <= max_a_b_c_d_node; a_b_c_d_node++) {
                    
                    int max_a_b_d_node = a_b_node == 0 && a_c_node == 0 && a_b_c_d_node == 0 ? 1 : 0;
                    for (int a_b_d_node = 0; a_b_d_node <= max_a_b_d_node; a_b_d_node++) {
                        
                        int max_a_c_d_node = (a_b_node == 1 && a_c_node == 0) ||  (a_b_node == 0 && a_c_node == 0 && a_b_c_d_node == 0 && a_b_d_node == 0) ? 1 : 0;
                        for (int a_c_d_node = 0; a_c_d_node <= max_a_c_d_node; a_c_d_node++) {
                            
                            int max_a_b_c_node = a_b_node == 0 && a_c_node == 0 && a_b_c_d_node == 0 && a_b_d_node == 0 ? 1 : 0;
                            for (int a_b_c_node = 0; a_b_c_node <= max_a_b_c_node; a_b_c_node++) {
                                
                                HatRegion R(4, a);
                                
                                if (a_b_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(b, node);
                                }
                                
                                if (a_b_c_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(b, node);
                                    R.addEdge(c, node);
                                }
                                
                                if (a_c_d_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(c, node);
                                    R.addEdge(d, node);
                                }
                                
                                if (a_c_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(c, node);
                                }
                                
                                if (a_b_d_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(b, node);
                                    R.addEdge(d, node);
                                }
                                
                                if (a_b_c_d_node) {
                                    int node = R.addNode();
                                    R.addEdge(a, node);
                                    R.addEdge(b, node);
                                    R.addEdge(c, node);
                                    R.addEdge(d, node);
                                }
                                
                                if (!R.isValid()) {
                                    cout << "not valid"<< endl;
                                    R.printRegion();
                                    exit(0);
                                }
                                
                                outer_non_dom_4regions.push_back(R);

                            }
                            
                        }
                    }
                    
                
            }
        }
        
    }
    
    cout << "Done enumeratin non-dominating outer 4regions: " << outer_non_dom_4regions.size() << endl;
}

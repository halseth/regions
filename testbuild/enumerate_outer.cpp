//
//  enumerate_outer.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <sstream>

#include "enumerate_outer.hpp"
#include "generate_from_inner.hpp"
#include "HatRegion.h"
#include "BaseRegion.h"
#include "store_sign.h"

void enumerate_non_dominator_outer_3regions(vector<BaseRegion> &outer_non_dom_3regions, bool removeEdge) {
    
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
            
            if (removeEdge) {
                R.removeEdge(a, c);
            }
            
            outer_non_dom_3regions.push_back(R);
        }
        
    }
    
    
    cout << "Done enumeratin non-dominating outer 3regions: " << outer_non_dom_3regions.size() << endl;
}

void enumerate_non_dominator_outer_4regions(vector<BaseRegion> &outer_non_dom_4regions, bool removeEdge) {
    
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
                                
                                if (removeEdge) {
                                    R.removeEdge(a, d);
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

void generate_4star_regions(map<vector<int>,BaseRegion> &signature_minimal) {
    
}

void generate_outer_6regions(map<vector<int>,BaseRegion> &signature_minimal_000,
                             map<vector<int>,BaseRegion> &signature_minimal_001,
                             map<vector<int>,BaseRegion> &signature_minimal_010,
                             map<vector<int>,BaseRegion> &signature_minimal_011,
                             map<vector<int>,BaseRegion> &signature_minimal_100,
                             map<vector<int>,BaseRegion> &signature_minimal_101,
                             map<vector<int>,BaseRegion> &signature_minimal_110,
                             map<vector<int>,BaseRegion> &signature_minimal_111,
                                            const vector<BaseRegion> &outer_3regions_with_edge,
                                            const vector<BaseRegion> &outer_4regions_with_edge,
                                            const vector<BaseRegion> &outer_3regions_without_edge,
                                            const vector<BaseRegion> &outer_4regions_without_edge
                                            ) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    map<vector<int>,BaseRegion> signature_minimal;
    
    for (int edges = 0; edges <= 0b111; edges++) {
        BaseRegion R(6);
        if ( (edges & 0b100) == 0) {
            R.removeEdge(a, f);
        }
        if ( (edges & 0b010) == 0) {
            R.removeEdge(f, e);
        }
        if ( (edges & 0b001) == 0) {
            R.removeEdge(e, d);
        }
        
        // Regions 3-4
        vector<BaseRegion> left = choose_outer_regions(R.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge);
        vector<BaseRegion> right = choose_outer_regions(R.isAdjacent(e, d), outer_4regions_with_edge, outer_4regions_without_edge);
        
        
        for (vector<BaseRegion>::const_iterator it_left = left.begin(); it_left != left.end(); it_left++) {
            for (vector<BaseRegion>::const_iterator it_right = right.begin(); it_right != right.end(); it_right++) {
                
                BaseRegion R2(R);
                
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, d);
                R2.addLabelToNode(4, e);
                R2.addLabelToNode(5, f);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion reg_left = *it_left;
                reg_left.addLabelToNode(0, a);
                reg_left.addLabelToNode(1, b);
                reg_left.addLabelToNode(5, c);
                toGlue.push_back(&reg_left);
                
                BaseRegion reg_right = *it_right;
                reg_right.addLabelToNode(3, a);
                reg_right.addLabelToNode(2, b);
                reg_right.addLabelToNode(1, c);
                reg_right.addLabelToNode(4, d);
                toGlue.push_back(&reg_right);
                
                R2.glue(toGlue);
                
                store_general_sign(R2, signature_minimal);
            }
        }
        
        // 3-3
        
        left = choose_outer_regions(R.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge);
        right = choose_outer_regions(R.isAdjacent(e, d), outer_3regions_with_edge, outer_3regions_without_edge);
        
        
        for (vector<BaseRegion>::const_iterator it_left = left.begin(); it_left != left.end(); it_left++) {
            for (vector<BaseRegion>::const_iterator it_right = right.begin(); it_right != right.end(); it_right++) {
                
                for (int between_edge_up = 0; between_edge_up <= 2; between_edge_up++) {
                    BaseRegion R2(R);
                    
                    if (between_edge_up == 1) {
                        R2.addEdge(b, e);
                    }
                    if(between_edge_up == 2) {
                        R2.addEdge(c, f);
                    }
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, f);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion reg_left = *it_left;
                    reg_left.addLabelToNode(0, a);
                    reg_left.addLabelToNode(1, b);
                    reg_left.addLabelToNode(5, c);
                    toGlue.push_back(&reg_left);
                    
                    BaseRegion reg_right = *it_right;
                    reg_right.addLabelToNode(3, a);
                    reg_right.addLabelToNode(2, b);
                    reg_right.addLabelToNode(4, c);
                    toGlue.push_back(&reg_right);
                    
                    R2.glue(toGlue);
                    
                    store_general_sign(R2, signature_minimal);
                    
                }
            }
        }

    }
    
    
    // Symmetries
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        BaseRegion sym(6);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, d);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, c);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, b);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, a);
        sym.addLabelToNode(4, e); reg.addLabelToNode(4, f);
        sym.addLabelToNode(5, f); reg.addLabelToNode(5, e);
        
        sym.glue(&reg);
        
        store_general_sign(sym, signature_minimal);
    }
    
    cout << "Done.";
    print_map(signature_minimal);
    
    // Add to right maps
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        BaseRegion R = it->second;
        if (!R.isAdjacent(a, f) && !R.isAdjacent(f, e) && !R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_000);
        }
        if (!R.isAdjacent(a, f) && !R.isAdjacent(f, e) && R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_001);
        }
        if (!R.isAdjacent(a, f) && R.isAdjacent(f, e) && !R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_010);
        }
        if (!R.isAdjacent(a, f) && R.isAdjacent(f, e) && R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_011);
        }
        if (R.isAdjacent(a, f) && !R.isAdjacent(f, e) && !R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_100);
        }
        if (R.isAdjacent(a, f) && !R.isAdjacent(f, e) && R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_101);
        }
        if (R.isAdjacent(a, f) && R.isAdjacent(f, e) && !R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_110);
        }
        if (R.isAdjacent(a, f) && R.isAdjacent(f, e) && R.isAdjacent(e, d)) {
            store_general_sign(R, signature_minimal_111);
        }
    }
}



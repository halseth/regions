//
//  generate_hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 22/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_hat_regions.hpp"
#include "choose_regions.hpp"
#include "parallization.h"

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

void generate_3hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                                  bool with_ac_edge
                                  ){
    
    cout << "Starting generate_3hat_regions with ac_edge: " << with_ac_edge << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    HatRegion R(3,a);
    if (!with_ac_edge) {
        R.removeEdge(a, c);
    }
    
    // 4 is the max number of internal nodes
    for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
        HatRegion R1(R);
        
        int node = -1;
        for (int i = 0; i < num_internal_nodes; i++) {
            int nn = R1.addNode();
            if(node == -1) node = nn;
        }
        
        int max_internal_edges = 0;
        // calculate set of edges among internal nodes
        for (int i = 0; i < num_internal_nodes; i++) {
            for (int j = i+1; j < num_internal_nodes; j++) {
                max_internal_edges = (max_internal_edges << 1) + 1;
            }
        }
        
        for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
            HatRegion R2(R1);
            
            // Add edges between internal nodes
            int edge = 1;
            for (int i = 0; i < num_internal_nodes; i++) {
                for (int j = i+1; j < num_internal_nodes; j++) {
                    if ( (internal_edges & edge) != 0 ) {
                        R2.addEdge(node+i, node+j);
                    }
                    edge = edge << 1;
                }
            }
            
            // Edges from boundary nodes to internal nodes
            int max_to_internal_edges = (1 << num_internal_nodes) -1;
            for (int a_to_internal_edges = 0; a_to_internal_edges <= max_to_internal_edges; a_to_internal_edges++) {
                for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                    for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                        
                        HatRegion R3(R2);
                        for (int i = 0; i <= num_internal_nodes; i++) {
                            if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                R3.addEdge(a, node+i);
                            }
                        }
                        
                        for (int i = 0; i <= num_internal_nodes; i++) {
                            if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                R3.addEdge(b, node+i);
                            }
                        }
                        
                        for (int i = 0; i <= num_internal_nodes; i++) {
                            if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                R3.addEdge(c, node+i);
                            }
                        }
                        
                        if (R3.isValid()) {
                            store_sign(R3, signature_minimal);
                        }
                    }
                }
            }
        }
    }
}

void generate_4hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edge,
                           const vector<BaseRegion> &regions_3hat_without_edge,
                           const vector<BaseRegion> &inner_2hat_regions,
                           const vector<BaseRegion> &inner_3hat_regions,
                           const vector<BaseRegion> &inner_4hat_regions,
                           bool with_bc_edge,
                           bool with_ad_edge
                           ){
    cout << "Starting generate_4hat_regions with_bc_edge: " << with_bc_edge << ", with_ad_edge: " << with_ad_edge << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat_with_edge.empty() || regions_3hat_without_edge.empty() || inner_2hat_regions.empty() || inner_3hat_regions.empty() ||  inner_4hat_regions.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    HatRegion R(4,a);
    
    if (!with_ad_edge) {
        R.removeEdge(a, d);
    }
    if (!with_bc_edge) {
        R.removeEdge(b, c);
    }
    
    cout << "b-d edge" << endl;
    vector<BaseRegion> lower = choose_outer_regions(R.isAdjacent(a, d), regions_3hat_with_edge, regions_3hat_without_edge);
    
    for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
        HatRegion R2(R);
        
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, d);
        
        BaseRegion lower_left = *it_lower;
        lower_left.addLabelToNode(0, a);
        lower_left.addLabelToNode(1, b);
        lower_left.addLabelToNode(2, c);
        
        R2.glue(&lower_left);
        
        if (!R2.isAdjacent(b, d)) {
            cout << "ERROR: bd not adj";
            exit(1);
        }
        
        if (R2.isAdjacent(a, d) != R.isAdjacent(a, d)) {
            cout << "ERROR: R2.isAdjacent(a, d) != R.isAdjacent(a, d)";
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
        
    }
    
    cout << "b-d node" << endl;
    lower = choose_outer_regions(R.isAdjacent(a, d), regions_3hat_with_edge, regions_3hat_without_edge);
    vector<BaseRegion> upper = regions_3hat_with_edge;
    
    for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
        for (vector<BaseRegion>::const_iterator it_upper = upper.begin(); it_upper != upper.end(); it_upper++) {
            for (int node_c_edge = 0; node_c_edge <= 1; node_c_edge++) {
                HatRegion R2(R);
                int node = R2.addNode();
                
                if (node_c_edge) {
                    R2.addEdge(node, c);
                }
                
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, node);
                R2.addLabelToNode(3, d);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion upper_left = *it_upper;
                upper_left.addLabelToNode(0, a);
                upper_left.addLabelToNode(1, b);
                upper_left.addLabelToNode(2, c);
                toGlue.push_back(&upper_left);
                
                BaseRegion lower_left = *it_lower;
                lower_left.addLabelToNode(0, a);
                lower_left.addLabelToNode(2, b);
                lower_left.addLabelToNode(3, c);
                toGlue.push_back(&lower_left);
                
                if (!lower_left.isAdjacent(b, c)) {
                    cout << "b c not adjacent"<< endl;
                    exit(1);
                }
                
                R2.glue(toGlue);
                
                if (!R2.isAdjacent(a, node)) {
                    cout << "ERROR: a-node not adj";
                    exit(1);
                }
                
                if (R2.isAdjacent(a, d) != R.isAdjacent(a, d)) {
                    cout << "ERROR: R2.isAdjacent(a, d) != R.isAdjacent(a, d)";
                    exit(1);
                }
                
                store_sign(R2, signature_minimal);
            }
        }
    }
    
    cout << "inner 4region" << endl;
    int current = 0;
    unsigned long mmax = inner_4hat_regions.size();
#pragma omp parallel
    {
        int priv_current = 0;
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4hat_regions.size(); i++) {
            BaseRegion inner = inner_4hat_regions[i];
            if (!inner.isAdjacent(a, b) || !inner.isAdjacent(a, d)) {
                cout << "!inner.isAdjacent(a, b) || !inner.isAdjacent(a, d)" << endl;
                exit(1);
            }
            
            HatRegion R2(R);
            int inner_b = R2.addNode();
            int inner_d = R2.addNode();
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, inner_b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, inner_d);
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            R2.glue(&inner);
            
            if (!R2.isValid()) {
                cout << "!R2.isValid()" << endl;
                exit(1);
            }
            
            vector<BaseRegion> lower3hat = choose_outer_regions(R.isAdjacent(a, d), regions_3hat_with_edge, regions_3hat_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_lower = lower3hat.begin(); it_lower != lower3hat.end(); it_lower++) {
                for (vector<BaseRegion>::const_iterator it_upper = regions_3hat_with_edge.begin(); it_upper != regions_3hat_with_edge.end(); it_upper++) {
                    
                    HatRegion R3(R2);
                    R3.addLabelToNode(0, a);
                    R3.addLabelToNode(1, b);
                    R3.addLabelToNode(2, inner_b);
                    R3.addLabelToNode(3, inner_d);
                    R3.addLabelToNode(4, d);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper_left = *it_upper;
                    upper_left.addLabelToNode(0, a);
                    upper_left.addLabelToNode(1, b);
                    upper_left.addLabelToNode(2, c);
                    toGlue.push_back(&upper_left);
                    
                    BaseRegion lower_left = *it_lower;
                    lower_left.addLabelToNode(0, a);
                    lower_left.addLabelToNode(3, b);
                    lower_left.addLabelToNode(4, c);
                    toGlue.push_back(&lower_left);
                    
                    R3.glue(toGlue);
                    
                    if (!R3.isAdjacent(inner_d, d)) {
                        cout << "inner_d d not adj" << endl;
                        exit(1);
                    }
                    
                    if (!R3.isAdjacent(inner_b, b)) {
                        cout << "inner_b b not adj" << endl;
                        exit(1);
                    }
                    
                    if (R3.isAdjacent(a, d) != R.isAdjacent(a, d)) {
                        cout << "ERROR: a and d adjacent" << endl;
                        exit(1);
                    }
                    
                    store_sign(R3, priv_signature_minimal);
                }
            }
            
            priv_current++;
            if(priv_current%100 == 0) {
#pragma omp critical
                {
                    current+=100;
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
            }
        }
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to signature_minimal " << endl;
            for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                BaseRegion _R = it->second;
                store_sign(_R, signature_minimal);
            }
        }
    } // parallel over
    
    
    cout << "inner3 with node up" << endl;
    for (vector<BaseRegion>::const_iterator it_inner = inner_3hat_regions.begin(); it_inner != inner_3hat_regions.end(); it_inner++) {
        
        BaseRegion inner = *it_inner;
        
        // Must be adjacent for it to be hat region
        if (!inner.isAdjacent(a, b)) {
            cout << "!inner.isAdjacent(a, b)" << endl;
            exit(1);
        }
        
        HatRegion R2(R);
        int inner_b = R2.addNode();
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, inner_b);
        R2.addLabelToNode(2, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        inner.addLabelToNode(2, c);
        
        R2.glue(&inner);
        
        if (!R2.isValid()) {
            cout << "!R2.isValid()" << endl;
            exit(1);
        }
        
        for (vector<BaseRegion>::const_iterator it_upper = regions_3hat_with_edge.begin(); it_upper != regions_3hat_with_edge.end(); it_upper++) {
            
            HatRegion R3(R2);
            R3.addLabelToNode(0, a);
            R3.addLabelToNode(1, b);
            R3.addLabelToNode(2, inner_b);
            
            BaseRegion upper_left = *it_upper;
            upper_left.addLabelToNode(0, a);
            upper_left.addLabelToNode(1, b);
            upper_left.addLabelToNode(2, c);
            
            R3.glue(&upper_left);
            
            if (!R3.isAdjacent(inner_b, b)) {
                cout << "inner_b b not adj" << endl;
                exit(1);
            }
            
            store_sign(R3, signature_minimal);
        }
        
    }
    
    cout << "inner3 with node down" << endl;
    for (vector<BaseRegion>::const_iterator it_inner = inner_3hat_regions.begin(); it_inner != inner_3hat_regions.end(); it_inner++) {
        
        BaseRegion inner = *it_inner;
        
        // Must be adjacent for it to be hat region
        if (!inner.isAdjacent(a, b)) {
            cout << "!inner.isAdjacent(a, b)" << endl;
            exit(1);
        }
        
        HatRegion R2(R);
        int inner_d = R2.addNode();
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, inner_d);
        R2.addLabelToNode(2, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        inner.addLabelToNode(2, c);
        
        R2.glue(&inner);
        
        if (!R2.isValid()) {
            cout << "!R2.isValid()" << endl;
            exit(1);
        }
        
        lower = choose_outer_regions(R.isAdjacent(a, d), regions_3hat_with_edge, regions_3hat_without_edge);
        for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
            
            HatRegion R3(R2);
            R3.addLabelToNode(0, a);
            R3.addLabelToNode(1, inner_d);
            R3.addLabelToNode(2, d);
            
            BaseRegion lower_left = *it_lower;
            lower_left.addLabelToNode(0, a);
            lower_left.addLabelToNode(1, b);
            lower_left.addLabelToNode(2, c);
            
            R3.glue(&lower_left);
            
            if (R3.isAdjacent(a, d) != R.isAdjacent(a, d)) {
                cout << "wrong with edge" << endl;
                exit(1);
            }
            
            if (!R3.isAdjacent(inner_d, d)) {
                cout << "inner_d d not adj" << endl;
                exit(1);
            }
            
            store_sign(R3, signature_minimal);
        }
        
    }
    
    cout << "inner2 regions" << endl;
    for (vector<BaseRegion>::const_iterator it_inner = inner_2hat_regions.begin(); it_inner != inner_2hat_regions.end(); it_inner++) {
        
        BaseRegion inner = *it_inner;
        
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        
        R2.glue(&inner);
        
        // Check if hat region
        if (!R2.isValid()) {
            cout << "!R2.isValid()" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }

    
}

void generate_5hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edge,
                           const vector<BaseRegion> &regions_3hat_without_ac_edge,
                           const vector<BaseRegion> &regions_4hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_without_bc_edge,
                           const vector<BaseRegion> &regions_4hat_without_ad_edge,
                           const vector<BaseRegion> &regions_4hat_without_bc_ad_edges,
                           bool with_de_edge
                           ){
    cout << "Starting generate_5hat_regions with_de_edge: " << with_de_edge << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat_with_edge.empty() || regions_3hat_without_ac_edge.empty() || regions_4hat_with_edges.empty() || regions_4hat_without_bc_edge.empty() ||  regions_4hat_without_ad_edge.empty() || regions_4hat_without_bc_ad_edges.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    HatRegion R(5,a);
    if (!with_de_edge) {
        R.removeEdge(d, e);
    }
    
    
    cout << "a-c node" << endl;
    for (int noose_edge = 0; noose_edge <= 1; noose_edge++) {
        
        vector<BaseRegion> upper = choose_outer_regions(noose_edge, regions_4hat_with_edges, regions_4hat_without_bc_edge);
        for (vector<BaseRegion>::const_iterator it_upper = upper.begin(); it_upper != upper.end(); it_upper++) {
            
            HatRegion R2(R);
            int node = R2.addNode();
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, node);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, b);
            
            BaseRegion upper4 = *it_upper;
            upper4.addLabelToNode(0, a);
            upper4.addLabelToNode(1, b);
            upper4.addLabelToNode(2, c);
            upper4.addLabelToNode(3, d);
            
            R2.glue(&upper4);
            
            // Lower part is 3 region
            vector<BaseRegion> lower = regions_3hat_with_edge;
            for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
                HatRegion R3(R2);
                R3.addLabelToNode(0, a);
                R3.addLabelToNode(1, node);
                R3.addLabelToNode(2, e);
                
                BaseRegion lower3 = *it_lower;
                lower3.addLabelToNode(0, a);
                lower3.addLabelToNode(1, b);
                lower3.addLabelToNode(2, c);
                
                R3.glue(&lower3);
                    
                store_sign(R3, signature_minimal);
            }
            
            // Lower part is 4 region
            lower = choose_outer_regions(R2.isAdjacent(e, d), regions_4hat_with_edges, regions_4hat_without_bc_edge);
            for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
                HatRegion R3(R2);
                R3.addLabelToNode(0, a);
                R3.addLabelToNode(1, e);
                R3.addLabelToNode(2, d);
                R3.addLabelToNode(3, node);
                
                BaseRegion lower4 = *it_lower;
                lower4.addLabelToNode(0, a);
                lower4.addLabelToNode(1, b);
                lower4.addLabelToNode(2, c);
                lower4.addLabelToNode(3, d);
                
                R3.glue(&lower4);
                
                store_sign(R3, signature_minimal);
            }
        }
    }
    
    cout << "a-c noose" << endl;
    for (int edge = 0; edge <= 1; edge++) {
        vector<BaseRegion> upper = choose_outer_regions(edge, regions_3hat_with_edge, regions_3hat_without_ac_edge);
        
        vector<BaseRegion> lower_without_edge = choose_outer_regions(R.isAdjacent(e, d), regions_4hat_without_ad_edge, regions_4hat_without_bc_ad_edges);
        vector<BaseRegion> lower_with_edge = choose_outer_regions(R.isAdjacent(e, d), regions_4hat_with_edges, regions_4hat_without_bc_edge);
        
        vector<BaseRegion> lower = choose_outer_regions(edge, lower_with_edge, lower_without_edge);
       
        for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
            for (vector<BaseRegion>::const_iterator it_upper = upper.begin(); it_upper != upper.end(); it_upper++) {
                HatRegion R2(R);
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, d);
                R2.addLabelToNode(4, e);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion upper3 = *it_upper;
                upper3.addLabelToNode(0, a);
                upper3.addLabelToNode(1, b);
                upper3.addLabelToNode(2, c);
                toGlue.push_back(&upper3);
                
                BaseRegion lower4 = *it_lower;
                lower4.addLabelToNode(0, a);
                lower4.addLabelToNode(4, b);
                lower4.addLabelToNode(3, c);
                lower4.addLabelToNode(2, d);
                toGlue.push_back(&lower4);
                
                R2.glue(toGlue);
                
                // sanity checks
                if (R2.isAdjacent(a, c) != edge) {
                    cout << "R2.isAdjacent(a, c) != edge" << endl;
                    exit(1);
                }
                
                if (R2.isAdjacent(d, e) != R.isAdjacent(d, e)) {
                    cout << "R2.isAdjacent(d, e) != R.isAdjacent(d, e)" << endl;
                    exit(1);
                }
                
                store_sign(R2, signature_minimal);
            }
        }
        
    }
    
    cout << "b-e edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_3hat_with_edge.begin(); it_left != regions_3hat_with_edge.end(); it_left++) {
        
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, e);
        
        BaseRegion left = *it_left;
        left.addLabelToNode(0, a);
        left.addLabelToNode(1, b);
        left.addLabelToNode(2, c);
        
        R2.glue(&left);
        
        if (!R2.isAdjacent(b, e)) {
            cout << "b-e not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
        
    }

    cout << "bd edge" << endl;
    vector<BaseRegion> left = choose_outer_regions(R.isAdjacent(e, d), regions_4hat_with_edges, regions_4hat_without_bc_edge);
    for (vector<BaseRegion>::const_iterator it_left = left.begin(); it_left != left.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, e);
        R2.addLabelToNode(2, d);
        R2.addLabelToNode(3, b);
        
        BaseRegion left4 = *it_left;
        left4.addLabelToNode(0, a);
        left4.addLabelToNode(1, b);
        left4.addLabelToNode(2, c);
        left4.addLabelToNode(3, d);
        
        R2.glue(&left4);
        
        if (!R2.isAdjacent(b, d)) {
            cout << "b-d not adj" << endl;
            exit(1);
        }
        
        if (R2.isAdjacent(e, d) != R.isAdjacent(e, d)) {
            cout << "R2.isAdjacent(e, d) != R.isAdjacent(e, d)" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
    
    cout << "ce edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_4hat_with_edges.begin(); it_left != regions_4hat_with_edges.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, c);
        R2.addLabelToNode(3, e);
        
        BaseRegion left4 = *it_left;
        left4.addLabelToNode(0, a);
        left4.addLabelToNode(1, b);
        left4.addLabelToNode(2, c);
        left4.addLabelToNode(3, d);
        
        R2.glue(&left4);
        
        if (!R2.isAdjacent(c, e)) {
            cout << "c-e not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
}

void generate_6hat_regions(map<vector<int>,BaseRegion> &signature_minimal,
                           const vector<BaseRegion> &regions_3hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_with_edges,
                           const vector<BaseRegion> &regions_4hat_without_ad_edge,
                           const vector<BaseRegion> &regions_5hat_with_edges,
                           const vector<BaseRegion> &regions_5hat_without_de_edge
                           ){

    cout << "Starting generate_6hat_regions"<< endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat_with_edges.empty() || regions_4hat_with_edges.empty() || regions_4hat_without_ad_edge.empty() || regions_5hat_with_edges.empty() ||  regions_5hat_without_de_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    HatRegion R(6,a);
    
    
    cout << "c-e edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_5hat_with_edges.begin(); it_left != regions_5hat_with_edges.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, c);
        R2.addLabelToNode(3, e);
        R2.addLabelToNode(4, f);
        
        BaseRegion left5 = *it_left;
        left5.addLabelToNode(0, a);
        left5.addLabelToNode(1, b);
        left5.addLabelToNode(2, c);
        left5.addLabelToNode(3, d);
        left5.addLabelToNode(4, e);
        
        R2.glue(&left5);
        
        if (!R2.isAdjacent(c, e)) {
            cout << "c-e not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
    
    cout << "b-d edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_5hat_with_edges.begin(); it_left != regions_5hat_with_edges.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, d);
        R2.addLabelToNode(3, e);
        R2.addLabelToNode(4, f);
        
        BaseRegion left5 = *it_left;
        left5.addLabelToNode(0, a);
        left5.addLabelToNode(1, b);
        left5.addLabelToNode(2, c);
        left5.addLabelToNode(3, d);
        left5.addLabelToNode(4, e);
        
        R2.glue(&left5);
        
        if (!R2.isAdjacent(b, d)) {
            cout << "b-d not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
    
    cout << "b-e edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_4hat_with_edges.begin(); it_left != regions_4hat_with_edges.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, e);
        R2.addLabelToNode(3, f);
        
        BaseRegion left4 = *it_left;
        left4.addLabelToNode(0, a);
        left4.addLabelToNode(1, b);
        left4.addLabelToNode(2, c);
        left4.addLabelToNode(3, d);
        
        R2.glue(&left4);
        
        if (!R2.isAdjacent(b, e)) {
            cout << "b-e not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
    
    cout << "b-f edge" << endl;
    for (vector<BaseRegion>::const_iterator it_left = regions_3hat_with_edges.begin(); it_left != regions_3hat_with_edges.end(); it_left++) {
        HatRegion R2(R);
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, b);
        R2.addLabelToNode(2, f);
        
        BaseRegion left3 = *it_left;
        left3.addLabelToNode(0, a);
        left3.addLabelToNode(1, b);
        left3.addLabelToNode(2, c);
        
        R2.glue(&left3);
        
        if (!R2.isAdjacent(b, f)) {
            cout << "b-f not adj" << endl;
            exit(1);
        }
        
        store_sign(R2, signature_minimal);
    }
    
    cout << "a-d noose" << endl;
    
    for (int ad_edge = 0; ad_edge <= 1; ad_edge++) {
        cout << "ad edge = " << ad_edge << endl;
        
        vector<BaseRegion> upper = choose_outer_regions(ad_edge, regions_4hat_with_edges, regions_4hat_without_ad_edge);
        vector<BaseRegion> lower = choose_outer_regions(ad_edge, regions_4hat_with_edges, regions_4hat_without_ad_edge);
        
#pragma omp parallel
        {
            map<vector<int>,BaseRegion> priv_signature_minimal;
            int tid = THREAD_ID;
            
#pragma omp for schedule(dynamic) nowait
            for (int i = 0; i < upper.size(); i++){
                for (int j = 0; j < lower.size(); j++) {
                    HatRegion R2(R);
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, f);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper4 = upper[i];
                    upper4.addLabelToNode(0, a);
                    upper4.addLabelToNode(1, b);
                    upper4.addLabelToNode(2, c);
                    upper4.addLabelToNode(3, d);
                    toGlue.push_back(&upper4);
                    
                    BaseRegion lower4 = lower[j];
                    lower4.addLabelToNode(0, a);
                    lower4.addLabelToNode(5, b);
                    lower4.addLabelToNode(4, c);
                    lower4.addLabelToNode(3, d);
                    toGlue.push_back(&lower4);
                    
                    R2.glue(toGlue);
                    
                    if (R2.isAdjacent(a, d) != ad_edge) {
                        cout << "R2.isAdjacent(a, d) != ad_edge" << endl;
                        exit(1);
                    }
                    
                    store_sign(R2, priv_signature_minimal);
                }
            }
            
#pragma omp critical
            {
                cout << "Thread " << tid << " done and now adding to signature_minimal " << endl;
                for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                    BaseRegion R = it->second;
                    store_sign(R, signature_minimal);
                }
            }
        } // parallel over
    }

    
    cout << "a-d node" << endl;
    for (int node_d_edge = 0; node_d_edge <= 1; node_d_edge++) {
        cout << "node_d_edge = " << node_d_edge << endl;
        
        vector<BaseRegion> upper = choose_outer_regions(node_d_edge, regions_5hat_with_edges, regions_5hat_without_de_edge);
        vector<BaseRegion> lower = choose_outer_regions(node_d_edge, regions_5hat_with_edges, regions_5hat_without_de_edge);
        
#pragma omp parallel
        {
            map<vector<int>,BaseRegion> priv_signature_minimal;
            int tid = THREAD_ID;
            
#pragma omp for schedule(dynamic) nowait
            for (int i = 0; i < upper.size(); i++){
                for (int j = 0; j < lower.size(); j++) {
                    HatRegion R2(R);
                    int node = R2.addNode();
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, f);
                    R2.addLabelToNode(6, node);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper5 = upper[i];
                    upper5.addLabelToNode(0, a);
                    upper5.addLabelToNode(1, b);
                    upper5.addLabelToNode(2, c);
                    upper5.addLabelToNode(3, d);
                    upper5.addLabelToNode(6, e);
                    toGlue.push_back(&upper5);
                    
                    BaseRegion lower5 = lower[j];
                    lower5.addLabelToNode(0, a);
                    lower5.addLabelToNode(5, b);
                    lower5.addLabelToNode(4, c);
                    lower5.addLabelToNode(3, d);
                    lower5.addLabelToNode(6, e);
                    toGlue.push_back(&lower5);
                    
                    R2.glue(toGlue);
                    
                    //sanity checks
                    if (!R2.isAdjacent(a, node)) {
                        cout << "a-node not adj" << endl;
                        exit(1);
                    }
                    if (R2.isAdjacent(node, d) != node_d_edge) {
                        cout << "R2.isAdjacent(node, d) != node_d_edge" << endl;
                        upper5.printRegion();
                        lower5.printRegion();
                        R2.printRegion();
                        exit(1);
                    }
                    
                    store_sign(R2, priv_signature_minimal);
                }
            }
            
#pragma omp critical
            {
                cout << "Thread " << tid << " done and now adding to signature_minimal " << endl;
                for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                    BaseRegion R = it->second;
                    store_sign(R, signature_minimal);
                }
            }
        }// parallel over
        
    }
    
    // Symmetries
    cout << "Finding symmetries"<< endl;
    
    // Flip around horisontal
    cout << "Around horistontal" << endl;
    
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        HatRegion sym(6,a);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, a);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, f);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, e);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, d);
        sym.addLabelToNode(4, e); reg.addLabelToNode(4, c);
        sym.addLabelToNode(5, f); reg.addLabelToNode(5, b);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }

    cout << "Done generate_6hat_regions"<< endl;
}
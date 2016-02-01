//
//  enumerate_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 03/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <iostream>
//#include <omp.h>
using namespace std;

#include "parallization.h"

#include "enumerate_inner.hpp"
#include "InnerRegion.hpp"
#include "store_sign.h"
#include <stdlib.h>

void generate_inner(map<vector<int>, BaseRegion> &sign_minimal, int size, int endpoint1, int endpoint2) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    cout << "Starting generating inner "<< size << "-regions." << endl;
    
    int edges = 0;
    // calculate max set of edges among boundary nodes
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            edges = (edges << 1) + 1;
        }
    }
    
    const int mmax = edges+1;
    int current = 0;
    
#pragma omp parallel
    {
        map<vector<int>, BaseRegion> priv_sign_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;        
        
#pragma omp for schedule(dynamic) nowait
        for (int boundary_neighbors = 0; boundary_neighbors <= edges; boundary_neighbors++) {
            
            InnerRegion R(size, endpoint1, endpoint2);
            
            // Add edges between boundary nodes
            int edge = 1;
            for (int i = 0; i < size; i++) {
                for (int j = i+1; j < size; j++) {
                    if ( (boundary_neighbors & edge) != 0 ) {
                        R.addEdge(i, j);
                    }
                    edge = edge << 1;
                }
            }
            
            if (!R.isPlanar()) {
                priv_current++;
                if(priv_current%100 == 0) {
#pragma omp critical
                    {
                        current+=100;
                        std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                    }
                }
                continue;
            }
            
            // Internal nodes
            for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
                InnerRegion R1(R);
                
                int node = -1;
                for (int i = 0; i < num_internal_nodes; i++) {
                    int nn = R1.addNode();
                    if(node == -1) node = nn;
                }
                
                // Handle special case with 4 internal nodes
                if (num_internal_nodes == 4) {
                    // Two internal dominators
                    R1.addEdge(node, node+1);
                    R1.addEdge(node, node+2);
                    R1.addEdge(node, node+3);
                    R1.addEdge(node+1, node+2);
                    R1.addEdge(node+1, node+3);
                    
                    for (int a_to_internal_edges = 0; a_to_internal_edges <= 0b1111; a_to_internal_edges++) {
                        
                        // A vertex that is not an endpoint can only have edges to the two internal dominators.
                        // The reason being if it to be a potential dominator, it would need to dominate all internal, but that would make a K_{2,3}
                        int max_b_edges = endpoint2 == b ? 0b1111 : 0b11;
                        for (int b_to_internal_edges = 0; b_to_internal_edges <= max_b_edges; b_to_internal_edges++) {
                            
                            int max_c_edges = endpoint2 == c ? 0b1111 : 0b11;
                            int max_c_to_internal_edges = size >= 3 ? max_c_edges : 0;
                            for (int c_to_internal_edges = 0; c_to_internal_edges <= max_c_to_internal_edges; c_to_internal_edges++) {
                                
                                int max_d_edges = endpoint2 == d ? 0b1111 : 0b11;
                                int max_d_to_internal_edges = size >= 4 ? max_d_edges : 0;
                                for (int d_to_internal_edges = 0; d_to_internal_edges <= max_d_to_internal_edges; d_to_internal_edges++) {
                                    
                                    int max_e_edges = endpoint2 == e ? 0b1111 : 0b11;
                                    int max_e_to_internal_edges = size >= 5 ? max_e_edges : 0;
                                    for (int e_to_internal_edges = 0; e_to_internal_edges <= max_e_to_internal_edges; e_to_internal_edges++) {
                                        
                                        int max_f_edges = endpoint2 == f ? 0b1111 : 0b11;
                                        int max_f_to_internal_edges = size >= 6 ? max_f_edges : 0;
                                        for (int f_to_internal_edges = 0; f_to_internal_edges <= max_f_to_internal_edges; f_to_internal_edges++) {
                                            
                                            InnerRegion R2(R1);
                                            for (int i = 0; i < 4; i++) {
                                                if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(a, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i < 4; i++) {
                                                if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(b, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i < 4; i++) {
                                                if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(c, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i < 4; i++) {
                                                if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(d, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i < 4; i++) {
                                                if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(e, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i < 4; i++) {
                                                if ( (f_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(f, node+i);
                                                }
                                            }
                                            
                                            // Check if planar and dominates internal nodes
                                            if (R2.isValid()) {
                                                store_sign(R2, priv_sign_minimal);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                } else {
                    
                    // Edges among internal nodes
                    for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
                        InnerRegion R2(R1);
                        
                        // Since at most 3 internal nodes, add edges in circle
                        if (num_internal_nodes > 1) {
                            for (int i = 0; i < num_internal_nodes; i++) {
                                if ( (internal_edges & (1 << i)) != 0 ) {
                                    R2.addEdge(node+i, node + ( (i+1) % num_internal_nodes) );
                                }
                            }
                        }
                        
                        
                        // Edges from boundary nodes to internal nodes
                        int max_to_internal_edges = (1 << num_internal_nodes) -1;
                        for (int a_to_internal_edges = 0; a_to_internal_edges <= max_to_internal_edges; a_to_internal_edges++) {
                            for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                                
                                int max_c_to_internal_edges = size >= 3 ? max_to_internal_edges : 0;
                                for (int c_to_internal_edges = 0; c_to_internal_edges <= max_c_to_internal_edges; c_to_internal_edges++) {
                                    
                                    int max_d_to_internal_edges = size >= 4 ? max_to_internal_edges : 0;
                                    for (int d_to_internal_edges = 0; d_to_internal_edges <= max_d_to_internal_edges; d_to_internal_edges++) {
                                        
                                        int max_e_to_internal_edges = size >= 5 ? max_to_internal_edges : 0;
                                        for (int e_to_internal_edges = 0; e_to_internal_edges <= max_e_to_internal_edges; e_to_internal_edges++) {
                                            
                                            int max_f_to_internal_edges = size >= 6 ? max_to_internal_edges : 0;
                                            for (int f_to_internal_edges = 0; f_to_internal_edges <= max_f_to_internal_edges; f_to_internal_edges++) {
                                                
                                                InnerRegion R3(R2);
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(a, node+i);
                                                    }
                                                }
                                                
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(b, node+i);
                                                    }
                                                }
                                                
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(c, node+i);
                                                    }
                                                }
                                                
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(d, node+i);
                                                    }
                                                }
                                                
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(e, node+i);
                                                    }
                                                }
                                                
                                                for (int i = 0; i < num_internal_nodes; i++) {
                                                    if ( (f_to_internal_edges & (1 << i)) != 0 ) {
                                                        R3.addEdge(f, node+i);
                                                    }
                                                }
                                                
                                                // Check if planar and dominates internal nodes
                                                if (R3.isValid()) {
                                                    store_sign(R3, priv_sign_minimal);
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
            
            priv_current++;
            if(priv_current%100 == 0) {
#pragma omp critical
                {
                    current+=100;
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
            }
        }
        std::cout << "Thread " << tid << " end." << std::endl;
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to sign minimal " << endl;
            for (map<vector<int>, BaseRegion>::const_iterator it = priv_sign_minimal.begin(); it != priv_sign_minimal.end(); ++it) {
                BaseRegion R = it->second;
                store_sign(R, sign_minimal);
            }
            
        }
    } // parallel region over
    
    cout << "Total sign minimal size: " << sign_minimal.size() << "Final map:" << endl;
    print_map(sign_minimal);
}

void enumerate_inner_hat_regions(vector<BaseRegion> &hat_regions, int size, int endpoint1, int endpoint2) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    cout << "Starting generating inner hat regions of size "<< size << endl;
    
    if (endpoint1 != a) {
        cout << "assumed endpoint1 == a" << endl;
        exit(1);
    }
    
    if (size > 4) {
        cout << "only size up to 4 supported" << endl;
        exit(1);
    }
    
    int edges = 0;
    // calculate set of edges among boundary nodes
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            edges = (edges << 1) + 1;
        }
    }
    
    const int mmax = edges+1;
    int current = 0;
    
#pragma omp parallel
    {
        vector<BaseRegion> priv_hat_regions;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int boundary_neighbors = 0; boundary_neighbors <= edges; boundary_neighbors++) {
            cout << "boundary_neighbors = " << boundary_neighbors << " / " << edges << endl;
            
            InnerRegion R(size, endpoint1, endpoint2);
            
            // Add edges between boundary nodes
            int edge = 1;
            for (int i = 0; i < size; i++) {
                for (int j = i+1; j < size; j++) {
                    if ( (boundary_neighbors & edge) != 0 ) {
                        R.addEdge(i, j);
                    }
                    edge = edge << 1;
                }
            }
            
            bool valid = true;
            
            // Enpoint must dominate all vertices except endpoint2
            for (int i = 0; i < R.getSize(); i++) {
                if (i == endpoint1 || i == endpoint2) {
                    continue;
                }
                if (!R.isAdjacent(endpoint1, i)) {
                    valid = false;
                }
            }
            
            // must be planar
            if (!R.isPlanar()){
                valid = false;
            }
            
            if (!valid) {
                priv_current++;
                if(priv_current%100 == 0) {
#pragma omp critical
                    {
                        current+=100;
                        std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                    }
                }
                continue;
            }
            
            // Check if planar and dominates internal nodes
            if (!R.isValid()) {
                cout << "should not happen";
                R.printRegion();
                exit(1);
            }
            
            // Internal nodes
            for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
                cout << "num_internal_nodes=" << num_internal_nodes << "/4" << endl;
                InnerRegion R1(R);
                
                int node = -1;
                for (int i = 0; i < num_internal_nodes; i++) {
                    int nn = R1.addNode();
                    if(node == -1) node = nn;
                }
                
                // Endpoint dominates all internal
                if (node != -1) {
                    for (int i = node; i < R1.getSize(); i++) {
                        R1.addEdge(endpoint1, i);
                    }
                }
                
                
                int max_internal_edges = 0;
                // calculate set of edges among internal nodes
                for (int i = 0; i < num_internal_nodes; i++) {
                    for (int j = i+1; j < num_internal_nodes; j++) {
                        max_internal_edges = (max_internal_edges << 1) + 1;
                    }
                }
                
                // Edges among internal nodes
                for (int internal_edges = 0; internal_edges <= max_internal_edges; internal_edges++) {
                    InnerRegion R2(R1);
                    
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
                    for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                        
                        int max_c_to_internal_edges = size >= 3 ? max_to_internal_edges : 0;
                        for (int c_to_internal_edges = 0; c_to_internal_edges <= max_c_to_internal_edges; c_to_internal_edges++) {
                            
                            int max_d_to_internal_edges = size >= 4 ? max_to_internal_edges : 0;
                            for (int d_to_internal_edges = 0; d_to_internal_edges <= max_d_to_internal_edges; d_to_internal_edges++) {
                                
                                InnerRegion R3(R2);
                                
                                for (int i = 0; i < num_internal_nodes; i++) {
                                    if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                        R3.addEdge(b, node+i);
                                    }
                                }
                                
                                for (int i = 0; i < num_internal_nodes; i++) {
                                    if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                        R3.addEdge(c, node+i);
                                    }
                                }
                                
                                for (int i = 0; i < num_internal_nodes; i++) {
                                    if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                        R3.addEdge(d, node+i);
                                    }
                                }
                                
                                if (!R3.isPlanar()) {
                                    continue;
                                }
                                
                                
                                if (!R3.isValid()) {
                                    cout << "not valid:" << endl;
                                    R3.printRegion();
                                    exit(1);
                                }
                                
                                priv_hat_regions.push_back(R3);
                            }
                        }
                    }
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
        std::cout << "Thread " << tid << " end." << std::endl;
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to sign minimal " << endl;
            for (vector<BaseRegion>::const_iterator it = priv_hat_regions.begin(); it != priv_hat_regions.end(); ++it) {
                BaseRegion R = *it;
                hat_regions.push_back(R);
            }
            
        }
    } // parallel region over
    
    cout << "Total hat_regions size: " << hat_regions.size() << endl;
}



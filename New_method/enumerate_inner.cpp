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
#include "Region.h"
#include "store_sign.h"

void generate_inner(map<vector<int>, BaseRegion> &sign_minimal, int size, int endpoint1, int endpoint2) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    cout << "Starting generating inner "<< size << "-regions." << endl;
    
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
        map<vector<int>, BaseRegion> priv_sign_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
        
#pragma omp for schedule(dynamic) nowait
        for (int boundary_neighbors = 0; boundary_neighbors <= edges; boundary_neighbors++) {
            
            Region R(size, endpoint1, endpoint2);
            // Remove all edges on boundary
            for (int i = 0; i < size; i++) {
                R.removeEdge(i, (i+1)%size);
            }
            
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
            
            if (!R.isValid()) {
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
                Region R1(R);
                
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
                                            
                                            Region R2(R1);
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
                        Region R2(R1);
                        
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
                                                
                                                Region R3(R2);
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

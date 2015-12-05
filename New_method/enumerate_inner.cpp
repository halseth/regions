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

#include "enumerate_inner.hpp"
#include "Region.h"

void enumerate_inner_2regions(std::vector<BaseRegion> &inner_2regions) {
    
    int a = 0;
    int b = 1;
    
    int num_valid = 0;
    
    for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
        Region R(2,a,b);
        
        int node = -1;
        for (int i = 0; i < num_internal_nodes; i++) {
            int nn = R.addNode();
            if(node == -1) node = nn;
        }
        
        // Edges among internal nodes
        for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
            Region R1(R);
            
            if (num_internal_nodes > 1) {
                for (int i = 0; i < num_internal_nodes; i++) {
                    if ( (internal_edges & (1 << i)) != 0 ) {
                        R1.addEdge(node+i, node + ( (i+1) % num_internal_nodes) );
                    }
                }
            }
            
            
            // Edges from boundary nodes to internal nodes
            int max_to_internal_edges = (1 << num_internal_nodes) -1;
            for (int a_to_internal_edges = 0; a_to_internal_edges <= max_to_internal_edges; a_to_internal_edges++) {
                for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                        
                    Region R3(R1);
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
                    
                    if (R3.isValid()) {
                        inner_2regions.push_back(R3);
                        num_valid++;
                    }                    
                }
            }
        }
    }
    std::cout << "End. Num valid: " << num_valid << std::endl;
    cout << "All threads done. Enumerating over. Total size: " << inner_2regions.size() << endl;
    
}

void enumerate_inner_3regions(std::vector<BaseRegion> &inner_3regions) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    
    int num_valid = 0;
    
    for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
        Region R(3,a,c);
        
        int node = -1;
        for (int i = 0; i < num_internal_nodes; i++) {
            int nn = R.addNode();
            if(node == -1) node = nn;
        }
        
        // Edges among internal nodes
        for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
            Region R1(R);
            
            if (num_internal_nodes > 1) {
                for (int i = 0; i < num_internal_nodes; i++) {
                    if ( (internal_edges & (1 << i)) != 0 ) {
                        R1.addEdge(node+i, node + ( (i+1) % num_internal_nodes) );
                    }
                }
            }
            
            
            // Edges from boundary nodes to internal nodes
            int max_to_internal_edges = (1 << num_internal_nodes) -1;
            for (int a_to_internal_edges = 0; a_to_internal_edges <= max_to_internal_edges; a_to_internal_edges++) {
                for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                    for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                        
                        Region R3(R1);
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
                            inner_3regions.push_back(R3);
                            num_valid++;
                        }
                    }
                }
            }
        }
    }
    std::cout << "End. Num valid: " << num_valid << std::endl;
    cout << "All threads done. Enumerating over. Total size: " << inner_3regions.size() << endl;
    
}

void enumerate_inner_4regions(std::vector<BaseRegion> &inner_4regions) {
    
    cout << "Starting gnerating inner 4regions" << endl;
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    
    // edges among nodes on boundary
    const int mmax = 0b11+1;
    
    int num_valid = 0;
    int current = 0;
    
    // Boundary neighbors, in this order: (a-c)(b-d)
    for (int boundary_neighbors = 0; boundary_neighbors <= 0b11; boundary_neighbors++) {
        
        Region R(4, a, c);
        
        if ( (boundary_neighbors & 0b10) != 0 ) {
            R.addEdge(a, c);
        }
        if ( (boundary_neighbors & 0b01) != 0 ) {
            R.addEdge(b, d);
        }
        
        if(!R.isValid()) {
            current++;
            std::cout << "Done with iteration " << current << " of " << mmax << std::endl;
            std::cout << "Num valid found: " << num_valid << std::endl;
            
            continue;
        }
        
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
                    for (int b_to_internal_edges = 0; b_to_internal_edges <= 0b11; b_to_internal_edges++) {
                        for (int c_to_internal_edges = 0; c_to_internal_edges <= 0b1111; c_to_internal_edges++) {
                            for (int d_to_internal_edges = 0; d_to_internal_edges <= 0b11; d_to_internal_edges++) {
                                
                                Region R2(R1);
                                for (int i = 0; i <= 4; i++) {
                                    if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(a, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 2; i++) {
                                    if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(b, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 2; i++) {
                                    if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(c, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 4; i++) {
                                    if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(d, node+i);
                                    }
                                }
                                
                                if (R2.isValid()) {
                                    inner_4regions.push_back(R2);
                                    num_valid++;
                                }
                            }
                        }
                    }
                }
                
            } else {
                
                // Edges among internal nodes
                for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
                    Region R2(R1);
                    
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
                            for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                                for (int d_to_internal_edges = 0; d_to_internal_edges <= max_to_internal_edges; d_to_internal_edges++) {
                                    
                                    Region R3(R2);
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
                                    
                                    for (int i = 0; i <= num_internal_nodes; i++) {
                                        if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                            R3.addEdge(d, node+i);
                                        }
                                    }
                                    
                                    if (R3.isValid()) {
                                        inner_4regions.push_back(R3);
                                        num_valid++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        current++;
        std::cout << "Done with iteration " << current << " of " << mmax << std::endl;
        std::cout << "Num valid found: " << num_valid << std::endl;
        
    }
    std::cout << "End. Num valid: " << num_valid << std::endl;
    
    cout << "All threads done. Enumerating over. Total size: " << inner_4regions.size() << endl;
}

void enumerate_inner_4starregions(std::vector<BaseRegion> &inner_4starregions) {
    
    cout << "Starting generating inner 4star regions" << endl;
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    
    // edges among nodes on boundary
    const int mmax = 0b11+1;
    
    int num_valid = 0;
    int current = 0;
    
    // Boundary neighbors, in this order: (a-c)(b-d)
    for (int boundary_neighbors = 0; boundary_neighbors <= 0b11; boundary_neighbors++) {
        
        Region R(4, a, d);
        
        if ( (boundary_neighbors & 0b10) != 0 ) {
            R.addEdge(a, c);
        }
        if ( (boundary_neighbors & 0b01) != 0 ) {
            R.addEdge(b, d);
        }
        
        if(!R.isValid()) {
            current++;
            std::cout << "Done with iteration " << current << " of " << mmax << std::endl;
            std::cout << "Num valid found: " << num_valid << std::endl;
            
            continue;
        }
        
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
                    for (int b_to_internal_edges = 0; b_to_internal_edges <= 0b11; b_to_internal_edges++) {
                        for (int c_to_internal_edges = 0; c_to_internal_edges <= 0b11; c_to_internal_edges++) {
                            for (int d_to_internal_edges = 0; d_to_internal_edges <= 0b1111; d_to_internal_edges++) {
                                
                                Region R2(R1);
                                for (int i = 0; i <= 4; i++) {
                                    if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(a, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 2; i++) {
                                    if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(b, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 2; i++) {
                                    if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(c, node+i);
                                    }
                                }
                                
                                for (int i = 0; i <= 4; i++) {
                                    if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                        R2.addEdge(d, node+i);
                                    }
                                }
                                
                                if (R2.isValid()) {
                                    inner_4starregions.push_back(R2);
                                    num_valid++;
                                }
                            }
                        }
                    }
                }
                
            } else {
                
                
                // Edges among internal nodes
                for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
                    Region R2(R1);
                    
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
                            for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                                for (int d_to_internal_edges = 0; d_to_internal_edges <= max_to_internal_edges; d_to_internal_edges++) {
                                    
                                    Region R3(R2);
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
                                    
                                    for (int i = 0; i <= num_internal_nodes; i++) {
                                        if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                            R3.addEdge(d, node+i);
                                        }
                                    }
                                    
                                    if (R3.isValid()) {
                                        inner_4starregions.push_back(R3);
                                        num_valid++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        current++;
        std::cout << "Done with iteration " << current << " of " << mmax << std::endl;
        std::cout << "Num valid found: " << num_valid << std::endl;
        
    }
    std::cout << "End. Num valid: " << num_valid << std::endl;
    
    cout << "All threads done. Enumerating over. Total size: " << inner_4starregions.size() << endl;
}

void enumerate_inner_5regions(std::vector<BaseRegion> &inner_5regions) {
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    
    
    // edges among nodes on boundary
    const int mmax = 0b11111+1;
    int current = 0;
    
#pragma omp parallel
    {
        vector<BaseRegion> priv_regions;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        int num_valid = 0;
        
        
#pragma omp for
        
        // Boundary neighbors, in this order: (a-c)(a-d)(b-d)(b-e)(c-e)
        for (int boundary_neighbors = 0; boundary_neighbors <= 0b11111; boundary_neighbors++) {
            
            
            Region R(5, a, d);
            
            if ( (boundary_neighbors & 0b10000) != 0 ) {
                R.addEdge(a, c);
            }
            if ( (boundary_neighbors & 0b01000) != 0 ) {
                R.addEdge(a, d);
            }
            if ( (boundary_neighbors & 0b00100) != 0 ) {
                R.addEdge(b, d);
            }
            if ( (boundary_neighbors & 0b00010) != 0 ) {
                R.addEdge(b, e);
            }
            if ( (boundary_neighbors & 0b00001) != 0 ) {
                R.addEdge(c, e);
            }
            if(!R.isValid()) {
#pragma omp critical
                {
                    current++;
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                    std::cout << "Num valid found: " << num_valid << std::endl;
                }
                continue;
            }
            
            for (int num_internal_nodes = 0; num_internal_nodes<=4; num_internal_nodes++) {
                Region R1(R);
                
                int node = -1;
                for (int i = 0; i < num_internal_nodes; i++) {
                    int nn = R1.addNode();
                    if(node == -1) node = nn;
                }
                
                // Edges among internal nodes
                for (int internal_edges = 0; internal_edges <= ((1 << num_internal_nodes) - 1); internal_edges++) {
                    Region R2(R1);
                    
                    if (num_internal_nodes > 1) {
                        for (int i = 0; i < num_internal_nodes; i++) {
                            if ( (internal_edges & (1 << i)) != 0 ) {
                                R2.addEdge(node+i, node + ( (i+1) % num_internal_nodes) );
                            }
                        }
                    }
                    
                    // Special case
                    if (num_internal_nodes == 4) {
                        // Two internal dominators
                        R1.addEdge(node, node+1);
                        R1.addEdge(node, node+2);
                        R1.addEdge(node, node+3);
                        R1.addEdge(node+1, node+2);
                        R1.addEdge(node+1, node+3);
                        
                        for (int a_to_internal_edges = 0; a_to_internal_edges <= 0b1111; a_to_internal_edges++) {
                            for (int b_to_internal_edges = 0; b_to_internal_edges <= 0b11; b_to_internal_edges++) {
                                for (int c_to_internal_edges = 0; c_to_internal_edges <= 0b11; c_to_internal_edges++) {
                                    for (int d_to_internal_edges = 0; d_to_internal_edges <= 0b1111; d_to_internal_edges++) {
                                        for (int e_to_internal_edges = 0; e_to_internal_edges <= 0b11; e_to_internal_edges++) {
                                            
                                            Region R2(R1);
                                            for (int i = 0; i <= 4; i++) {
                                                if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(a, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= 2; i++) {
                                                if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(b, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= 2; i++) {
                                                if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(c, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= 4; i++) {
                                                if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(d, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= 2; i++) {
                                                if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                    R2.addEdge(e, node+i);
                                                }
                                            }
                                            
                                            if (R2.isValid()) {
                                                priv_regions.push_back(R2);
                                                num_valid++;
                                            }
                                            
                                        }
                                    }
                                }
                            }
                        }
                        
                    } else {
                        
                        
                        // Edges from boundary nodes to internal nodes
                        int max_to_internal_edges = (1 << num_internal_nodes) -1;
                        for (int a_to_internal_edges = 0; a_to_internal_edges <= max_to_internal_edges; a_to_internal_edges++) {
                            for (int b_to_internal_edges = 0; b_to_internal_edges <= max_to_internal_edges; b_to_internal_edges++) {
                                for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                                    for (int d_to_internal_edges = 0; d_to_internal_edges <= max_to_internal_edges; d_to_internal_edges++) {
                                        for (int e_to_internal_edges = 0; e_to_internal_edges <= max_to_internal_edges; e_to_internal_edges++) {
                                            
                                            Region R3(R2);
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
                                            
                                            for (int i = 0; i <= num_internal_nodes; i++) {
                                                if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                    R3.addEdge(d, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= num_internal_nodes; i++) {
                                                if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                    R3.addEdge(e, node+i);
                                                }
                                            }
                                            
                                            if (R3.isValid()) {
                                                priv_regions.push_back(R3);
                                                //inner_6regions.push_back(R3);
                                                num_valid++;
                                                //std::cout << "Num valid: " << num_valid << std::endl;
                                                //if(num_valid > 10) return;
                                                
                                            }
                                            
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            #pragma omp critical
            {
                current++;
                std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                std::cout << "Num valid found: " << num_valid << std::endl;
            }
        }
        std::cout << "End. Num valid: " << num_valid << std::endl;
        
        #pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to vector " << endl;
            for (vector<BaseRegion>::const_iterator it = priv_regions.begin(); it != priv_regions.end(); ++it) {
                BaseRegion R = *it;
                inner_5regions.push_back(R);
            }
        }
    } // parallel region over
    
    cout << "All threads done. Enumerating over. Total size: " << inner_5regions.size() << endl;
    
}

void enumerate_inner_6regions(std::vector<BaseRegion> &inner_6regions) {
  
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
   
   
    // edges among nodes on boundary
    const int mmax = 0b111111111+1;
    int current = 0;
    
#pragma omp parallel
    {
        vector<BaseRegion> priv_regions;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        int num_valid = 0;
        
        
#pragma omp for
    
    // Boundary neighbors, in this order: (a-c)(a-d)(a-e)(b-d)(b-e)(b-f)(c-e)(c-f)(d-f)
    for (int boundary_neighbors = 0; boundary_neighbors <= 0b111111111; boundary_neighbors++) {
        
        Region R(6, a, d);
        
        if ( (boundary_neighbors & 0b100000000) != 0 ) {
            R.addEdge(a, c);
        }
        if ( (boundary_neighbors & 0b010000000) != 0 ) {
            R.addEdge(a, d);
        }
        if ( (boundary_neighbors & 0b001000000) != 0 ) {
            R.addEdge(a, e);
        }
        if ( (boundary_neighbors & 0b000100000) != 0 ) {
            R.addEdge(b, d);
        }
        if ( (boundary_neighbors & 0b000010000) != 0 ) {
            R.addEdge(b, e);
        }
        if ( (boundary_neighbors & 0b000001000) != 0 ) {
            R.addEdge(b, f);
        }
        if ( (boundary_neighbors & 0b000000100) != 0 ) {
            R.addEdge(c, e);
        }
        if ( (boundary_neighbors & 0b000000010) != 0 ) {
            R.addEdge(c, f);
        }
        if ( (boundary_neighbors & 0b000000001) != 0 ) {
            R.addEdge(d, f);
        }
        
        if(!R.isValid()) {
            #pragma omp critical
            {
                current++;
                std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                std::cout << "Num valid found: " << num_valid << std::endl;
            }
            continue;
        }
        
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
                    for (int b_to_internal_edges = 0; b_to_internal_edges <= 0b11; b_to_internal_edges++) {
                        for (int c_to_internal_edges = 0; c_to_internal_edges <= 0b11; c_to_internal_edges++) {
                            for (int d_to_internal_edges = 0; d_to_internal_edges <= 0b1111; d_to_internal_edges++) {
                                for (int e_to_internal_edges = 0; e_to_internal_edges <= 0b11; e_to_internal_edges++) {
                                    for (int f_to_internal_edges = 0; f_to_internal_edges <= 0b11; f_to_internal_edges++) {
                                        
                                        Region R2(R1);
                                        for (int i = 0; i <= 4; i++) {
                                            if ( (a_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(a, node+i);
                                            }
                                        }
                                        
                                        for (int i = 0; i <= 2; i++) {
                                            if ( (b_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(b, node+i);
                                            }
                                        }
                                        
                                        for (int i = 0; i <= 2; i++) {
                                            if ( (c_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(c, node+i);
                                            }
                                        }
                                        
                                        for (int i = 0; i <= 4; i++) {
                                            if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(d, node+i);
                                            }
                                        }
                                        
                                        for (int i = 0; i <= 2; i++) {
                                            if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(e, node+i);
                                            }
                                        }
                                        
                                        for (int i = 0; i <= 2; i++) {
                                            if ( (f_to_internal_edges & (1 << i)) != 0 ) {
                                                R2.addEdge(f, node+i);
                                            }
                                        }
                                        
                                        if (R2.isValid()) {
                                            priv_regions.push_back(R2);
                                            num_valid++;
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
                            for (int c_to_internal_edges = 0; c_to_internal_edges <= max_to_internal_edges; c_to_internal_edges++) {
                                for (int d_to_internal_edges = 0; d_to_internal_edges <= max_to_internal_edges; d_to_internal_edges++) {
                                    for (int e_to_internal_edges = 0; e_to_internal_edges <= max_to_internal_edges; e_to_internal_edges++) {
                                        for (int f_to_internal_edges = 0; f_to_internal_edges <= max_to_internal_edges; f_to_internal_edges++) {
                                            
                                            Region R3(R2);
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
                                            
                                            for (int i = 0; i <= num_internal_nodes; i++) {
                                                if ( (d_to_internal_edges & (1 << i)) != 0 ) {
                                                    R3.addEdge(d, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= num_internal_nodes; i++) {
                                                if ( (e_to_internal_edges & (1 << i)) != 0 ) {
                                                    R3.addEdge(e, node+i);
                                                }
                                            }
                                            
                                            for (int i = 0; i <= num_internal_nodes; i++) {
                                                if ( (f_to_internal_edges & (1 << i)) != 0 ) {
                                                    R3.addEdge(f, node+i);
                                                }
                                            }
                                            
                                            if (R3.isValid()) {
                                                priv_regions.push_back(R3);
                                                //inner_6regions.push_back(R3);
                                                num_valid++;
                                                //std::cout << "Num valid: " << num_valid << std::endl;
                                                //if(num_valid > 10) return;
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
        
        #pragma omp critical
        {
            current++;
            std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
            std::cout << "Num valid found: " << num_valid << std::endl;
        }
    }
    std::cout << "End. Num valid: " << num_valid << std::endl;
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to vector " << endl;
            for (vector<BaseRegion>::const_iterator it = priv_regions.begin(); it != priv_regions.end(); ++it) {
                BaseRegion R = *it;
                inner_6regions.push_back(R);
            }
        }
    } // parallel region over
    
    cout << "All threads done. Enumerating over. Total size: " << inner_6regions.size() << endl;
    
}

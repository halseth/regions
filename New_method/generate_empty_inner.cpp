//
//  generate_empty_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 16/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include "parallization.h"
#include "BaseRegion.h"
#include "InnerRegion.hpp"
#include "generate_empty_inner.hpp"
#include "store_sign.h"

void generate_empty_inner(map<vector<int>, BaseRegion> &sign_minimal, int size, int endpoint1, int endpoint2) {
    cout << "Starting generating empty inner "<< size << "-regions." << endl;
    
    int edges = 0;
    // find max edges
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            edges = (edges << 1) + 1;
        }
    }
    
    // edges among nodes on boundary
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
            
            // Check if planar and dominates boundary nodes
            if (R.isValid()) {
                store_sign(R, priv_sign_minimal);
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

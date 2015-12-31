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

// without OMP
#define THREAD_ID 0
#define NUM_THREADS 1

// with OMP
//#include <omp.h>
//#define THREAD_ID omp_get_thread_num()
//#define NUM_THREADS omp_get_num_threads()

#include "BaseRegion.h"
#include "Region.h"
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
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        
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

void generate_empty_inner6(map<vector<int>, BaseRegion> &sign_minimal) {
    
    cout << "Starting generating empty inner 6-regions." << endl;
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    
    // edges among nodes on boundary
    const int mmax = 0b111111111111111+1;
    int current = 0;
    
#pragma omp parallel
    {
        map<vector<int>, BaseRegion> priv_sign_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        
#pragma omp for schedule(dynamic) nowait
        
        // Boundary neighbors, in this order: (a-b)(a-c)(a-d)(a-e)(a-f)(b-c)(b-d)(b-e)(b-f)(c-d)(c-e)(c-f)(d-e)(d-f)(e-f)
        for (int boundary_neighbors = 0; boundary_neighbors <= 0b111111111111111; boundary_neighbors++) {
            
            Region R(6, a, d);
            // Remove all edges on boundary
            for (int i = 0; i < 6; i++) {
                R.removeEdge(i, (i+1)%6);
            }
            
            if ( (boundary_neighbors & 0b100000000000000) != 0 ) {
                R.addEdge(a, b);
            }
            if ( (boundary_neighbors & 0b010000000000000) != 0 ) {
                R.addEdge(a, c);
            }
            if ( (boundary_neighbors & 0b001000000000000) != 0 ) {
                R.addEdge(a, d);
            }
            if ( (boundary_neighbors & 0b000100000000000) != 0 ) {
                R.addEdge(a, e);
            }
            if ( (boundary_neighbors & 0b000010000000000) != 0 ) {
                R.addEdge(a, f);
            }
            if ( (boundary_neighbors & 0b000001000000000) != 0 ) {
                R.addEdge(b, c);
            }
            if ( (boundary_neighbors & 0b000000100000000) != 0 ) {
                R.addEdge(b, d);
            }
            if ( (boundary_neighbors & 0b000000010000000) != 0 ) {
                R.addEdge(b, e);
            }
            if ( (boundary_neighbors & 0b000000001000000) != 0 ) {
                R.addEdge(b, f);
            }
            if ( (boundary_neighbors & 0b000000000100000) != 0 ) {
                R.addEdge(c, d);
            }
            if ( (boundary_neighbors & 0b000000000010000) != 0 ) {
                R.addEdge(c, e);
            }
            if ( (boundary_neighbors & 0b000000000001000) != 0 ) {
                R.addEdge(c, f);
            }
            if ( (boundary_neighbors & 0b000000000000100) != 0 ) {
                R.addEdge(d, e);
            }
            if ( (boundary_neighbors & 0b000000000000010) != 0 ) {
                R.addEdge(d, f);
            }
            if ( (boundary_neighbors & 0b000000000000001) != 0 ) {
                R.addEdge(e, f);
            }
            
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

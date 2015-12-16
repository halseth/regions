//
//  generate_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//


// without OMP
#define THREAD_ID 0
#define NUM_THREADS 1

// with OMP
//#include <omp.h>
//#define THREAD_ID omp_get_thread_num()
//#define NUM_THREADS omp_get_num_threads()

#include "generate_from_inner.hpp"


const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

void generate_from_inner2(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_2regions
                          ){
    cout << "Starting inner 2-regions" << endl;
    int current = 0;
    int mmax = inner_2regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        
        // Inner 2-regions. Outer regions will be empty
#pragma omp for nowait
        for (int i = 0; i < inner_2regions.size(); i++) {
            for (int edge_over = 0; edge_over <= 1; edge_over++) {
                
                BaseRegion inner = inner_2regions[i];
                inner.removeEdge(a, b);
                if (edge_over) {
                    inner.addEdge(a, b);
                }
                inner.addLabelToNode(0, a);
                inner.addLabelToNode(1, b);
                
                Region R(6,a,d);
                R.addLabelToNode(0, a);
                R.addLabelToNode(1, d);
                
                R.glue(&inner);
                
                store_sign(R, priv_signature_minimal);
            }
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    } // parallel region over
    
    cout << "Done with inner 2-regions" << endl;
}

void generate_from_inner3(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_3regions
                          ){
    cout << "Starting inner 3-regions" << endl;
    
    int current = 0;
    int mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        // Inner 3-regions. Outer regions will be empty
#pragma omp for nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            for (int inner_boundary_edges = 0; inner_boundary_edges <= 0b111; inner_boundary_edges++) {
                // At least one edge up
                for (int edges_up = 0b01; edges_up <= 0b11; edges_up++) {
                    BaseRegion inner = inner_3regions[i];
                    inner.removeEdge(a, b);
                    inner.removeEdge(b, c);
                    inner.removeEdge(a, c);
                    if ( (inner_boundary_edges & (0b100)) != 0) {
                        inner.addEdge(a, b);
                    }
                    if ( (inner_boundary_edges & (0b010)) != 0) {
                        inner.addEdge(b, c);
                    }
                    if ( (inner_boundary_edges & (0b001)) != 0) {
                        inner.addEdge(a, c);
                    }
                    inner.addLabelToNode(0, a);
                    inner.addLabelToNode(1, b);
                    inner.addLabelToNode(2, c);
                    
                    Region R(6,a,d);
                    
                    int node = R.addNode();
                    R.addLabelToNode(1, node);
                    if ( (edges_up & 0b10) != 0) {
                        R.addEdge(node, b);
                    }
                    if ( (edges_up & 0b01) != 0) {
                        R.addEdge(node, c);
                    }
                    
                    R.addLabelToNode(0, a);
                    R.addLabelToNode(2, d);
                    
                    
                    R.glue(&inner);
                    
                    store_sign(R, priv_signature_minimal);
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner 3-regions" << endl;
}

void generate_from_inner4(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_4regions){
    cout << "Starting inner 4-regions" << endl;
    
    int current = 0;
    int mmax = inner_4regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        // Inner 4-regions. Outer regions will be empty
#pragma omp for nowait
        for (int i = 0; i < inner_4regions.size(); i++) {
            for (int inner_boundary_edges = 0; inner_boundary_edges <= 0b1111; inner_boundary_edges++) {
                for (int edges_up = 0b01; edges_up <= 0b11; edges_up++) {
                    for (int edges_down = 0b01; edges_down <= 0b11; edges_down++) {
                        BaseRegion inner = inner_4regions[i];
                        inner.removeEdge(a, b);
                        inner.removeEdge(b, c);
                        inner.removeEdge(c, d);
                        inner.removeEdge(a, d);
                        if ( (inner_boundary_edges & (0b1000)) != 0) {
                            inner.addEdge(a, b);
                        }
                        if ( (inner_boundary_edges & (0b0100)) != 0) {
                            inner.addEdge(b, c);
                        }
                        if ( (inner_boundary_edges & (0b0010)) != 0) {
                            inner.addEdge(c, d);
                        }
                        if ( (inner_boundary_edges & (0b0001)) != 0) {
                            inner.addEdge(a, d);
                        }
                        inner.addLabelToNode(0, a);
                        inner.addLabelToNode(1, b);
                        inner.addLabelToNode(2, c);
                        inner.addLabelToNode(3, d);
                        
                        Region R(6,a,d);
                        
                        int node = R.addNode();
                        R.addLabelToNode(1, node);
                        if ( (edges_up & 0b10) != 0) {
                            R.addEdge(node, b);
                        }
                        if ( (edges_up & 0b01) != 0) {
                            R.addEdge(node, c);
                        }
                        
                        int node2 = R.addNode();
                        R.addLabelToNode(3, node2);
                        if ( (edges_down & 0b10) != 0) {
                            R.addEdge(node2, e);
                        }
                        if ( (edges_down & 0b01) != 0) {
                            R.addEdge(node2, f);
                        }
                        
                        R.addLabelToNode(0, a);
                        R.addLabelToNode(2, d);
                        
                        
                        R.glue(&inner);
                        
                        store_sign(R, priv_signature_minimal);
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner 4-regions" << endl;
}

void generate_from_inner4star_33(map<vector<int>,BaseRegion> &signature_minimal,
                             const vector<BaseRegion> &inner_4starregions,
                             const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                             const vector<BaseRegion> &outer_non_dom_3regions_without_edge
                             ) {
    
    cout << "Starting inner non-empty 4star-regions. Outer: 3-3" << endl;
    
    int current = 0;
    int mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            
            BaseRegion inner = inner_4starregions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_3regions_with_edge;
            } else {
                upper_right = outer_non_dom_3regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                        for (int between_edge = 0; between_edge <= 1; between_edge++) {
                            Region R2(R);
                            
                            if (between_edge) {
                                R2.addEdge(b, inner_c);
                            }
                            
                            R2.addLabelToNode(0, a);
                            R2.addLabelToNode(1, b);
                            R2.addLabelToNode(2, c);
                            R2.addLabelToNode(3, d);
                            R2.addLabelToNode(4, e);
                            R2.addLabelToNode(5, f);
                            R2.addLabelToNode(6, inner_b);
                            R2.addLabelToNode(7, inner_c);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(6, c);
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(7, c);
                            toGlue.push_back(&upper_right);
                            
                            R2.glue(toGlue);
                            
                            store_sign(R2, priv_signature_minimal);
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 4star-regions. Outer: 3-3" << endl;
    
}

void generate_from_inner4star_34(map<vector<int>,BaseRegion> &signature_minimal,
                             const vector<BaseRegion> &inner_4starregions,
                             const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                             const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                             const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                             const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                             ) {
    
    cout << "Starting inner non-empty 4star-regions. Outer: 3-4" << endl;
    
    int current = 0;
    int mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            
            BaseRegion inner = inner_4starregions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_4regions_with_edge;
            } else {
                upper_right = outer_non_dom_4regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                        Region R2(R);
                        
                        R2.addLabelToNode(0, a);
                        R2.addLabelToNode(1, b);
                        R2.addLabelToNode(2, c);
                        R2.addLabelToNode(3, d);
                        R2.addLabelToNode(4, e);
                        R2.addLabelToNode(5, f);
                        R2.addLabelToNode(6, inner_b);
                        R2.addLabelToNode(7, inner_c);
                        
                        vector<BaseRegion*> toGlue;
                        
                        BaseRegion upper_left = *it_upper_left;
                        upper_left.addLabelToNode(0, a);
                        upper_left.addLabelToNode(1, b);
                        upper_left.addLabelToNode(6, c);
                        toGlue.push_back(&upper_left);
                        
                        BaseRegion upper_right = *it_upper_right;
                        upper_right.addLabelToNode(3, a);
                        upper_right.addLabelToNode(2, b);
                        upper_right.addLabelToNode(1, c);
                        upper_right.addLabelToNode(7, d);
                        toGlue.push_back(&upper_right);
                        
                        R2.glue(toGlue);
                        
                        store_sign(R2, priv_signature_minimal);
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 4star-regions. Outer: 3-4" << endl;
    
}


void generate_from_inner5_33(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &inner_5regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge
                               ) {
    
    cout << "Starting inner non-empty 5-regions. Outer: 3-3" << endl;
    
    int current = 0;
    int mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_5regions.size(); i++) {
            
            BaseRegion inner = inner_5regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_3regions_with_edge;
            } else {
                upper_right = outer_non_dom_3regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (int edges_down = 0b01; edges_down <= 0b11; edges_down++) {
                        for (int between_edge = 0; between_edge <= 1; between_edge++) {
                            Region R2(R);
                            
                            if ((edges_down & 0b10) != 0) {
                                R2.addEdge(inner_e, e);
                            }
                            if ((edges_down & 0b01) != 0) {
                                R2.addEdge(inner_e, f);
                            }
                            
                            if (between_edge) {
                                R2.addEdge(b, inner_c);
                            }
                            
                            R2.addLabelToNode(0, a);
                            R2.addLabelToNode(1, b);
                            R2.addLabelToNode(2, c);
                            R2.addLabelToNode(3, d);
                            R2.addLabelToNode(4, e);
                            R2.addLabelToNode(5, f);
                            R2.addLabelToNode(6, inner_b);
                            R2.addLabelToNode(7, inner_c);
                            R2.addLabelToNode(8, inner_e);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(6, c);
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(7, c);
                            toGlue.push_back(&upper_right);
                            
                            R2.glue(toGlue);
                            
                            store_sign(R2, priv_signature_minimal);
                        }
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 5-regions. Outer: 3-4" << endl;
    
}

void generate_from_inner5_34(map<vector<int>,BaseRegion> &signature_minimal,
                             const vector<BaseRegion> &inner_5regions,
                             const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                             const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                             const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                             const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                             ) {
    
    cout << "Starting inner non-empty 5-regions. Outer: 3-4" << endl;
    
    int current = 0;
    int mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_5regions.size(); i++) {
            
            BaseRegion inner = inner_5regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_4regions_with_edge;
            } else {
                upper_right = outer_non_dom_4regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (int edges_down = 0b01; edges_down <= 0b11; edges_down++) {
                        Region R2(R);
                        
                        if ((edges_down & 0b10) != 0) {
                            R2.addEdge(inner_e, e);
                        }
                        if ((edges_down & 0b01) != 0) {
                            R2.addEdge(inner_e, f);
                        }
                        
                        R2.addLabelToNode(0, a);
                        R2.addLabelToNode(1, b);
                        R2.addLabelToNode(2, c);
                        R2.addLabelToNode(3, d);
                        R2.addLabelToNode(4, e);
                        R2.addLabelToNode(5, f);
                        R2.addLabelToNode(6, inner_b);
                        R2.addLabelToNode(7, inner_c);
                        R2.addLabelToNode(8, inner_e);
                        
                        vector<BaseRegion*> toGlue;
                        
                        BaseRegion upper_left = *it_upper_left;
                        upper_left.addLabelToNode(0, a);
                        upper_left.addLabelToNode(1, b);
                        upper_left.addLabelToNode(6, c);
                        toGlue.push_back(&upper_left);
                        
                        BaseRegion upper_right = *it_upper_right;
                        upper_right.addLabelToNode(3, a);
                        upper_right.addLabelToNode(2, b);
                        upper_right.addLabelToNode(1, c);
                        upper_right.addLabelToNode(7, d);
                        toGlue.push_back(&upper_right);
                        
                        R2.glue(toGlue);
                        
                        store_sign(R2, priv_signature_minimal);
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 5-regions. Outer: 3-4" << endl;
    
}

void generate_from_inner6_3333(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &inner_6regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge
                               ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-3-3-3" << endl;
    
    int current = 0;
    int mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            int inner_f = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            R.addLabelToNode(5, inner_f);
            
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            vector<BaseRegion> lower_left;
            vector<BaseRegion> lower_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_3regions_with_edge;
            } else {
                upper_right = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(d, e)) {
                lower_right = outer_non_dom_3regions_with_edge;
            } else {
                lower_right = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(a, f)) {
                lower_left = outer_non_dom_3regions_with_edge;
            } else {
                lower_left = outer_non_dom_3regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            for (int up_between_edge = 0; up_between_edge <= 2; up_between_edge++) {
                                for (int down_between_edge = 0; down_between_edge <= 2; down_between_edge++) {
                                    Region R2(R);
                                    
                                    if (up_between_edge == 1) {
                                        R2.addEdge(b, inner_c);
                                    }
                                    if(up_between_edge == 2) {
                                        R2.addEdge(c, inner_b);
                                    }
                                    
                                    if (down_between_edge == 1) {
                                        R2.addEdge(f, inner_e);
                                    }
                                    if(down_between_edge == 2) {
                                        R2.addEdge(e, inner_f);
                                    }
                                    
                                    R2.addLabelToNode(0, a);
                                    R2.addLabelToNode(1, b);
                                    R2.addLabelToNode(2, c);
                                    R2.addLabelToNode(3, d);
                                    R2.addLabelToNode(4, e);
                                    R2.addLabelToNode(5, f);
                                    R2.addLabelToNode(6, inner_b);
                                    R2.addLabelToNode(7, inner_c);
                                    R2.addLabelToNode(8, inner_e);
                                    R2.addLabelToNode(9, inner_f);
                                    
                                    vector<BaseRegion*> toGlue;
                                    
                                    BaseRegion upper_left = *it_upper_left;
                                    upper_left.addLabelToNode(0, a);
                                    upper_left.addLabelToNode(1, b);
                                    upper_left.addLabelToNode(6, c);
                                    toGlue.push_back(&upper_left);
                                    
                                    BaseRegion upper_right = *it_upper_right;
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(7, c);
                                    toGlue.push_back(&upper_right);
                                    
                                    BaseRegion lower_left = *it_lower_left;
                                    lower_left.addLabelToNode(0, a);
                                    lower_left.addLabelToNode(5, b);
                                    lower_left.addLabelToNode(9, c);
                                    toGlue.push_back(&lower_left);
                                    
                                    BaseRegion lower_right = *it_lower_right;
                                    lower_right.addLabelToNode(3, a);
                                    lower_right.addLabelToNode(4, b);
                                    lower_right.addLabelToNode(8, c);
                                    toGlue.push_back(&lower_right);
                                    
                                    R2.glue(toGlue);
                                    
                                    store_sign(R2, priv_signature_minimal);
                                }
                                
                            }
                            
                        }
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 6-regions. Outer: 3-3-3-3" << endl;
    
}


void generate_from_inner6_3433(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &inner_6regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                               ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-4-3-3" << endl;
    
    int current = 0;
    int mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            int inner_f = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            R.addLabelToNode(5, inner_f);
            
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            vector<BaseRegion> lower_left;
            vector<BaseRegion> lower_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_4regions_with_edge;
            } else {
                upper_right = outer_non_dom_4regions_without_edge;
            }
            if (inner.isAdjacent(d, e)) {
                lower_right = outer_non_dom_3regions_with_edge;
            } else {
                lower_right = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(a, f)) {
                lower_left = outer_non_dom_3regions_with_edge;
            } else {
                lower_left = outer_non_dom_3regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            for (int between_edge = 0; between_edge <= 2; between_edge++) {
                                Region R2(R);
                                
                                if (between_edge == 1) {
                                    R2.addEdge(f, inner_e);
                                }
                                if(between_edge == 2) {
                                    R2.addEdge(e, inner_f);
                                }
                                
                                R2.addLabelToNode(0, a);
                                R2.addLabelToNode(1, b);
                                R2.addLabelToNode(2, c);
                                R2.addLabelToNode(3, d);
                                R2.addLabelToNode(4, e);
                                R2.addLabelToNode(5, f);
                                R2.addLabelToNode(6, inner_b);
                                R2.addLabelToNode(7, inner_c);
                                R2.addLabelToNode(8, inner_e);
                                R2.addLabelToNode(9, inner_f);
                                
                                vector<BaseRegion*> toGlue;
                                
                                BaseRegion upper_left = *it_upper_left;
                                upper_left.addLabelToNode(0, a);
                                upper_left.addLabelToNode(1, b);
                                upper_left.addLabelToNode(6, c);
                                toGlue.push_back(&upper_left);
                                
                                BaseRegion upper_right = *it_upper_right;
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(1, c);
                                upper_right.addLabelToNode(7, d);
                                toGlue.push_back(&upper_right);
                                
                                BaseRegion lower_left = *it_lower_left;
                                lower_left.addLabelToNode(0, a);
                                lower_left.addLabelToNode(5, b);
                                lower_left.addLabelToNode(9, c);
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                lower_right.addLabelToNode(3, a);
                                lower_right.addLabelToNode(4, b);
                                lower_right.addLabelToNode(8, c);
                                toGlue.push_back(&lower_right);
                                
                                R2.glue(toGlue);
                                
                                store_sign(R2, priv_signature_minimal);
                            }
                            
                        }
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-3-3" << endl;
    
}

void generate_from_inner6_3443(map<vector<int>,BaseRegion> &signature_minimal,
                              const vector<BaseRegion> &inner_6regions,
                              const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                              const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                              const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                              const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                              ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-4-4-3" << endl;
    
    int current = 0;
    int mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        #pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            int inner_f = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            R.addLabelToNode(5, inner_f);
            
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            vector<BaseRegion> lower_left;
            vector<BaseRegion> lower_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_4regions_with_edge;
            } else {
                upper_right = outer_non_dom_4regions_without_edge;
            }
            if (inner.isAdjacent(d, e)) {
                lower_right = outer_non_dom_3regions_with_edge;
            } else {
                lower_right = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(a, f)) {
                lower_left = outer_non_dom_4regions_with_edge;
            } else {
                lower_left = outer_non_dom_4regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            Region R2(R);
                            
                            R2.addLabelToNode(0, a);
                            R2.addLabelToNode(1, b);
                            R2.addLabelToNode(2, c);
                            R2.addLabelToNode(3, d);
                            R2.addLabelToNode(4, e);
                            R2.addLabelToNode(5, f);
                            R2.addLabelToNode(6, inner_b);
                            R2.addLabelToNode(7, inner_c);
                            R2.addLabelToNode(8, inner_e);
                            R2.addLabelToNode(9, inner_f);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(6, c);
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(1, c);
                            upper_right.addLabelToNode(7, d);
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower_left = *it_lower_left;
                            lower_left.addLabelToNode(0, a);
                            lower_left.addLabelToNode(5, b);
                            lower_left.addLabelToNode(4, c);
                            lower_left.addLabelToNode(9, d);
                            toGlue.push_back(&lower_left);
                            
                            BaseRegion lower_right = *it_lower_right;
                            lower_right.addLabelToNode(3, a);
                            lower_right.addLabelToNode(4, b);
                            lower_right.addLabelToNode(8, c);
                            toGlue.push_back(&lower_right);
                            
                            R2.glue(toGlue);
                            
                            store_sign(R2, priv_signature_minimal);
                        }
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-4-3" << endl;
    
}

void generate_from_inner6_3434(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &inner_6regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                               ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-4-3-4" << endl;
    
    int current = 0;
    int mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            int inner_f = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            R.addLabelToNode(5, inner_f);
            
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left;
            vector<BaseRegion> upper_right;
            vector<BaseRegion> lower_left;
            vector<BaseRegion> lower_right;
            
            // Check if edges are there
            if (inner.isAdjacent(a, b)) {
                upper_left = outer_non_dom_3regions_with_edge;
            } else {
                upper_left = outer_non_dom_3regions_without_edge;
            }
            if (inner.isAdjacent(c, d)) {
                upper_right = outer_non_dom_4regions_with_edge;
            } else {
                upper_right = outer_non_dom_4regions_without_edge;
            }
            if (inner.isAdjacent(d, e)) {
                lower_right = outer_non_dom_4regions_with_edge;
            } else {
                lower_right = outer_non_dom_4regions_without_edge;
            }
            if (inner.isAdjacent(a, f)) {
                lower_left = outer_non_dom_3regions_with_edge;
            } else {
                lower_left = outer_non_dom_3regions_without_edge;
            }
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            Region R2(R);
                            
                            R2.addLabelToNode(0, a);
                            R2.addLabelToNode(1, b);
                            R2.addLabelToNode(2, c);
                            R2.addLabelToNode(3, d);
                            R2.addLabelToNode(4, e);
                            R2.addLabelToNode(5, f);
                            R2.addLabelToNode(6, inner_b);
                            R2.addLabelToNode(7, inner_c);
                            R2.addLabelToNode(8, inner_e);
                            R2.addLabelToNode(9, inner_f);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(6, c);
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(1, c);
                            upper_right.addLabelToNode(7, d);
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower_left = *it_lower_left;
                            lower_left.addLabelToNode(0, a);
                            lower_left.addLabelToNode(5, b);
                            lower_left.addLabelToNode(9, c);
                            toGlue.push_back(&lower_left);
                            
                            BaseRegion lower_right = *it_lower_right;
                            lower_right.addLabelToNode(3, a);
                            lower_right.addLabelToNode(4, b);
                            lower_right.addLabelToNode(5, c);
                            lower_right.addLabelToNode(8, d);
                            toGlue.push_back(&lower_right);
                            
                            R2.glue(toGlue);
                            
                            store_sign(R2, priv_signature_minimal);
                        }
                    }
                }
            }
            
            
#pragma omp critical
            {
                current++;
                if (current%100 == 0) {
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
                }
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
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-3-4" << endl;
    
}


void generate_from_nonempty_inner(map<vector<int>,BaseRegion> &signature_minimal,
                         const vector<BaseRegion> &inner_2regions,
                         const vector<BaseRegion> &inner_3regions,
                         const vector<BaseRegion> &inner_4regions,
                         const vector<BaseRegion> &inner_4starregions,
                         const vector<BaseRegion> &inner_5regions,
                         const vector<BaseRegion> &inner_6regions,
                         const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                         const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                         const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                         const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                         ) {
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_4starregions.empty() || inner_4regions.empty() || inner_5regions.empty() || inner_6regions.empty() || inner_2regions.empty() || inner_3regions.empty()
       || outer_non_dom_3regions_with_edge.empty() || outer_non_dom_4regions_with_edge.empty() | outer_non_dom_3regions_without_edge.empty() || outer_non_dom_4regions_without_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    
    generate_from_inner6_3443(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    generate_from_inner6_3333(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_3regions_without_edge);
    generate_from_inner6_3433(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    generate_from_inner6_3434(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    
    generate_from_inner2(signature_minimal, inner_2regions);
    generate_from_inner3(signature_minimal, inner_3regions);
    
    generate_from_inner4(signature_minimal, inner_4regions);
    generate_from_inner4star_33(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_3regions_without_edge);
    generate_from_inner4star_34(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    
    generate_from_inner5_33(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_3regions_without_edge);
    generate_from_inner5_34(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);


    


    

    
    
}

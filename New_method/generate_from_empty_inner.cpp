//
//  generate_from_empty_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 15/12/15.
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
#include "store_sign.h"
#include "generate_from_empty_inner.hpp"


const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;


void generate_from_empty_inner6_3443(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &empty_inner_6regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                               ) {
    
    cout << "Starting inner empty 6-regions. Outer: 3-4-4-3" << endl;
    
    int current = 0;
    unsigned long mmax = empty_inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < empty_inner_6regions.size(); i++) {
            
            BaseRegion inner = empty_inner_6regions[i];
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
                BaseRegion R = it->second;
                store_sign(R, signature_minimal);
            }
        }
        
    } // parallel over
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-4-3" << endl;
    
}

void generate_from_empty_inner6_3434(map<vector<int>,BaseRegion> &signature_minimal,
                               const vector<BaseRegion> &empty_inner_6regions,
                               const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                               const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                               const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                               ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-4-3-4" << endl;
    
    int current = 0;
    unsigned long mmax = empty_inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < empty_inner_6regions.size(); i++) {
            
            BaseRegion inner = empty_inner_6regions[i];
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
                BaseRegion R = it->second;
                store_sign(R, signature_minimal);
            }
        }
        
    } // parallel over
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-3-4" << endl;
    
}

void generate_from_empty_inner(map<vector<int>,BaseRegion> &signature_minimal,
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
    
    // inner 2
    // 4star with a-d edge missing up and down, or we can argue that a-c or b-d edge must be there for outer regions not to be empty
    
    //inner 3.
    // Must have edge up 33 or 34 up, 4star down
    
    // inner 4
    // 33 or 34 up and down
    
    // inner 4star, 33 or 34 up, 4star down
    
    // inner 5
    // 33/34 up, 33/34 down
    
    // inner 6
    // 33/34 up, 33/34 down
    
}

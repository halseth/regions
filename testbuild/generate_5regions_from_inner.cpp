//
//  generate_5regions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_5regions_from_inner.hpp"
#include "generate_from_inner.hpp"
#include "parallization.h"

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

void generate_5regions_from_inner2(map<vector<int>,BaseRegion> &signature_minimal,
                                            const vector<BaseRegion> &inner_2regions
                                            ) {
    
    cout << "Starting 5regions from inner 2-regions" << endl;
    
    int current = 0;
    unsigned long mmax = inner_2regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_2regions.size(); i++) {
            
            BaseRegion inner = inner_2regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            
            Region R(5,a,d);
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, d);
            
            R.glue(&inner);
                    
            store_sign(R, priv_signature_minimal);
            
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
    cout << "Done with inner 2-regions" << endl;
    
}

void generate_5regions_from_inner3_one_down(map<vector<int>,BaseRegion> &signature_minimal,
                                   const vector<BaseRegion> &inner_3regions,
                                   const vector<BaseRegion> &outer_3regions_with_edge,
                                   const vector<BaseRegion> &outer_4regions_with_edge,
                                   const vector<BaseRegion> &outer_3regions_without_edge,
                                   const vector<BaseRegion> &outer_4regions_without_edge
                                   ) {
    
    cout << "Starting 5regions from inner 3-regions down. Outer: " << 3 << "-"<< 3 << endl;
    
    int current = 0;
    unsigned long mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            
            BaseRegion inner = inner_3regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(b, c), outer_3regions_with_edge, outer_3regions_without_edge);
            for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                    
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, inner_b);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion lower_left = *it_lower_left;
                    lower_left.addLabelToNode(0, a);
                    lower_left.addLabelToNode(4, b);
                    lower_left.addLabelToNode(5, c);
                    toGlue.push_back(&lower_left);
                    
                    BaseRegion lower_right = *it_lower_right;
                    lower_right.addLabelToNode(3, a);
                    lower_right.addLabelToNode(4, b);
                    lower_right.addLabelToNode(5, c);
                    toGlue.push_back(&lower_right);
                    
                    R2.glue(toGlue);
                    
                    store_sign(R2, priv_signature_minimal);
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
    cout << "Done with inner 3-regions down" << endl;
    
}


void generate_5regions_from_inner3_one_up(map<vector<int>,BaseRegion> &signature_minimal,
                                   const vector<BaseRegion> &inner_3regions,
                                   const vector<BaseRegion> &outer_3regions_with_edge,
                                   const vector<BaseRegion> &outer_4regions_with_edge,
                                   const vector<BaseRegion> &outer_3regions_without_edge,
                                   const vector<BaseRegion> &outer_4regions_without_edge,
                                   int upper_left_size,
                                   int upper_right_size
                                   ) {
    
    cout << "Starting 5regions from inner 3-regions up. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            
            BaseRegion inner = inner_3regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(b, c), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, inner_b);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper_left = *it_upper_left;
                    if (upper_left_size == 3) {
                        upper_left.addLabelToNode(0, a);
                        upper_left.addLabelToNode(1, b);
                        upper_left.addLabelToNode(5, c);
                    } else {
                        cout << "assume always 3" << endl;
                        exit(0);
                    }
                    toGlue.push_back(&upper_left);
                    
                    BaseRegion upper_right = *it_upper_right;
                    if (upper_right_size == 3) {
                        upper_right.addLabelToNode(3, a);
                        upper_right.addLabelToNode(2, b);
                        upper_right.addLabelToNode(5, c);
                    } else {
                        upper_right.addLabelToNode(3, a);
                        upper_right.addLabelToNode(2, b);
                        upper_right.addLabelToNode(1, c);
                        upper_right.addLabelToNode(5, d);
                    }
                    toGlue.push_back(&upper_right);
                    
                    R2.glue(toGlue);
                    
                    store_sign(R2, priv_signature_minimal);
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
    cout << "Done with inner 3-regions up" << endl;
    
}


void generate_5regions_from_inner4star_two_down(map<vector<int>,BaseRegion> &signature_minimal,
                                            const vector<BaseRegion> &inner_4starregions,
                                            const vector<BaseRegion> &outer_3regions_with_edge,
                                            const vector<BaseRegion> &outer_4regions_with_edge,
                                            const vector<BaseRegion> &outer_3regions_without_edge,
                                            const vector<BaseRegion> &outer_4regions_without_edge
                                            ) {
    
    cout << "Starting 5regions from inner 4*-regions down. Outer: " << 3 << "-"<< 3 << endl;
    
    int current = 0;
    unsigned long mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            
            BaseRegion inner = inner_4starregions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge);
            for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, inner_c);
                    R2.addLabelToNode(6, inner_b);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion lower_left = *it_lower_left;
                    lower_left.addLabelToNode(0, a);
                    lower_left.addLabelToNode(4, b);
                    lower_left.addLabelToNode(6, c);
                    toGlue.push_back(&lower_left);
                    
                    BaseRegion lower_right = *it_lower_right;
                    lower_right.addLabelToNode(3, a);
                    lower_right.addLabelToNode(4, b);
                    lower_right.addLabelToNode(5, c);
                    toGlue.push_back(&lower_right);
                    
                    R2.glue(toGlue);
                    
                    store_sign(R2, priv_signature_minimal);
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
    cout << "Done with inner 4*star-regions down" << endl;
    
}

void generate_5regions_from_inner4star_two_up(map<vector<int>,BaseRegion> &signature_minimal,
                                          const vector<BaseRegion> &inner_4starregions,
                                          const vector<BaseRegion> &outer_3regions_with_edge,
                                          const vector<BaseRegion> &outer_4regions_with_edge,
                                          const vector<BaseRegion> &outer_3regions_without_edge,
                                          const vector<BaseRegion> &outer_4regions_without_edge,
                                          int upper_left_size,
                                          int upper_right_size
                                          ) {
    
    cout << "Starting 5regions from inner 4*-regions up. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            
            BaseRegion inner = inner_4starregions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    int max_between_edge_up = upper_left_size == 3 && upper_right_size == 3 ? 2 : 0;
                    
                    for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                        Region R2(R);
                        
                        if (between_edge_up == 1) {
                            R2.addEdge(b, inner_c);
                        }
                        if(between_edge_up == 2) {
                            R2.addEdge(c, inner_b);
                        }
                        
                        R2.addLabelToNode(0, a);
                        R2.addLabelToNode(1, b);
                        R2.addLabelToNode(2, c);
                        R2.addLabelToNode(3, d);
                        R2.addLabelToNode(4, e);
                        R2.addLabelToNode(5, inner_b);
                        R2.addLabelToNode(6, inner_c);
                        
                        vector<BaseRegion*> toGlue;
                        
                        BaseRegion upper_left = *it_upper_left;
                        if (upper_left_size == 3) {
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(5, c);
                        } else {
                            cout << "assume always 3" << endl;
                            exit(0);
                        }
                        toGlue.push_back(&upper_left);
                        
                        BaseRegion upper_right = *it_upper_right;
                        if (upper_right_size == 3) {
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(6, c);
                        } else {
                            upper_right.addLabelToNode(3, a);
                            upper_right.addLabelToNode(2, b);
                            upper_right.addLabelToNode(1, c);
                            upper_right.addLabelToNode(6, d);
                        }
                        toGlue.push_back(&upper_right);
                        
                        R2.glue(toGlue);
                        
                        store_sign(R2, priv_signature_minimal);
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
    cout << "Done with inner 5-regions up" << endl;
    
}

void generate_5regions_from_inner4(map<vector<int>,BaseRegion> &signature_minimal,
                                          const vector<BaseRegion> &inner_4regions,
                                          const vector<BaseRegion> &outer_3regions_with_edge,
                                          const vector<BaseRegion> &outer_4regions_with_edge,
                                          const vector<BaseRegion> &outer_3regions_without_edge,
                                          const vector<BaseRegion> &outer_4regions_without_edge,
                                          int upper_left_size,
                                          int upper_right_size
                                          ) {
    
    cout << "Starting 5regions from inner 4-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_4regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4regions.size(); i++) {
            
            BaseRegion inner = inner_4regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            int inner_d = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            R.addLabelToNode(3, inner_d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(b, c), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(a, d), outer_3regions_with_edge, outer_3regions_without_edge);
            
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
                            R2.addLabelToNode(5, inner_b);
                            R2.addLabelToNode(6, inner_d);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            if (upper_left_size == 3) {
                                upper_left.addLabelToNode(0, a);
                                upper_left.addLabelToNode(1, b);
                                upper_left.addLabelToNode(5, c);
                            } else {
                                cout << "assume always 3" << endl;
                                exit(0);
                            }
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            if (upper_right_size == 3) {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(5, c);
                            } else {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(1, c);
                                upper_right.addLabelToNode(5, d);
                            }
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower_left = *it_lower_left;
                            lower_left.addLabelToNode(0, a);
                            lower_left.addLabelToNode(4, b);
                            lower_left.addLabelToNode(6, c);
                            toGlue.push_back(&lower_left);
                            
                            BaseRegion lower_right = *it_lower_right;
                            lower_right.addLabelToNode(3, a);
                            lower_right.addLabelToNode(4, b);
                            lower_right.addLabelToNode(6, c);
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
    cout << "Done with inner 4-regions" << endl;
    
}

void generate_5regions_from_inner5_two_down(map<vector<int>,BaseRegion> &signature_minimal,
                                          const vector<BaseRegion> &inner_5regions,
                                          const vector<BaseRegion> &outer_3regions_with_edge,
                                          const vector<BaseRegion> &outer_4regions_with_edge,
                                          const vector<BaseRegion> &outer_3regions_without_edge,
                                          const vector<BaseRegion> &outer_4regions_without_edge,
                                          int upper_left_size,
                                          int upper_right_size
                                          ) {
    
    cout << "Starting 5regions from inner 5-regions down. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_5regions.size(); i++) {
            
            BaseRegion inner = inner_5regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, e), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge);
            
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
                            R2.addLabelToNode(5, inner_e);
                            R2.addLabelToNode(6, inner_c);
                            R2.addLabelToNode(7, inner_b);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            if (upper_left_size == 3) {
                                upper_left.addLabelToNode(0, a);
                                upper_left.addLabelToNode(1, b);
                                upper_left.addLabelToNode(5, c);
                            } else {
                                cout << "assume always 3" << endl;
                                exit(0);
                            }
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            if (upper_right_size == 3) {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(5, c);
                            } else {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(1, c);
                                upper_right.addLabelToNode(5, d);
                            }
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower_left = *it_lower_left;
                            lower_left.addLabelToNode(0, a);
                            lower_left.addLabelToNode(4, b);
                            lower_left.addLabelToNode(7, c);
                            toGlue.push_back(&lower_left);
                            
                            BaseRegion lower_right = *it_lower_right;
                            lower_right.addLabelToNode(3, a);
                            lower_right.addLabelToNode(4, b);
                            lower_right.addLabelToNode(6, c);
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
    cout << "Done with inner 5-regions up" << endl;
    
}

void generate_5regions_from_inner5_two_up(map<vector<int>,BaseRegion> &signature_minimal,
                                   const vector<BaseRegion> &inner_5regions,
                                   const vector<BaseRegion> &outer_3regions_with_edge,
                                   const vector<BaseRegion> &outer_4regions_with_edge,
                                   const vector<BaseRegion> &outer_3regions_without_edge,
                                   const vector<BaseRegion> &outer_4regions_without_edge,
                                   int upper_left_size,
                                   int upper_right_size
                                   ) {
    
    cout << "Starting 5regions from inner 5-regions up. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_5regions.size(); i++) {
            
            BaseRegion inner = inner_5regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            
            Region R(5,a,d);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, inner_e);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(a, e), outer_3regions_with_edge, outer_3regions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            int max_between_edge_up = upper_left_size == 3 && upper_right_size == 3 ? 2 : 0;
                            
                            for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                                Region R2(R);
                                
                                if (between_edge_up == 1) {
                                    R2.addEdge(b, inner_c);
                                }
                                if(between_edge_up == 2) {
                                    R2.addEdge(c, inner_b);
                                }
                                
                                R2.addLabelToNode(0, a);
                                R2.addLabelToNode(1, b);
                                R2.addLabelToNode(2, c);
                                R2.addLabelToNode(3, d);
                                R2.addLabelToNode(4, e);
                                R2.addLabelToNode(5, inner_b);
                                R2.addLabelToNode(6, inner_c);
                                R2.addLabelToNode(7, inner_e);
                                
                                vector<BaseRegion*> toGlue;
                                
                                BaseRegion upper_left = *it_upper_left;
                                if (upper_left_size == 3) {
                                    upper_left.addLabelToNode(0, a);
                                    upper_left.addLabelToNode(1, b);
                                    upper_left.addLabelToNode(5, c);
                                } else {
                                    cout << "assume always 3" << endl;
                                    exit(0);
                                }
                                toGlue.push_back(&upper_left);
                                
                                BaseRegion upper_right = *it_upper_right;
                                if (upper_right_size == 3) {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(6, c);
                                } else {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(1, c);
                                    upper_right.addLabelToNode(6, d);
                                }
                                toGlue.push_back(&upper_right);
                                
                                BaseRegion lower_left = *it_lower_left;
                                lower_left.addLabelToNode(0, a);
                                lower_left.addLabelToNode(4, b);
                                lower_left.addLabelToNode(7, c);
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                lower_right.addLabelToNode(3, a);
                                lower_right.addLabelToNode(4, b);
                                lower_right.addLabelToNode(7, c);
                                toGlue.push_back(&lower_right);
                                
                                R2.glue(toGlue);
                                
                                store_sign(R2, priv_signature_minimal);
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
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to signature_minimal " << endl;
            for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                BaseRegion R = it->second;
                store_sign(R, signature_minimal);
            }
        }
        
    } // parallel over
    cout << "Done with inner 5-regions up" << endl;
    
}


void generate_5regions_from_inner6(map<vector<int>,BaseRegion> &signature_minimal,
                                   const vector<BaseRegion> &inner_6regions,
                                   const vector<BaseRegion> &outer_3regions_with_edge,
                                   const vector<BaseRegion> &outer_4regions_with_edge,
                                   const vector<BaseRegion> &outer_3regions_without_edge,
                                   const vector<BaseRegion> &outer_4regions_without_edge,
                                   int upper_left_size,
                                   int upper_right_size
                                   ) {
    
    cout << "Starting 5regions from inner 6-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(5,a,d);
            
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
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            int max_between_edge_up = upper_left_size == 3 && upper_right_size == 3 ? 2 : 0;
                            
                            for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                                Region R2(R);
                                
                                if (between_edge_up == 1) {
                                    R2.addEdge(b, inner_c);
                                }
                                if(between_edge_up == 2) {
                                    R2.addEdge(c, inner_b);
                                }
                                
                                R2.addLabelToNode(0, a);
                                R2.addLabelToNode(1, b);
                                R2.addLabelToNode(2, c);
                                R2.addLabelToNode(3, d);
                                R2.addLabelToNode(4, e);
                                R2.addLabelToNode(5, inner_b);
                                R2.addLabelToNode(6, inner_c);
                                R2.addLabelToNode(7, inner_e);
                                R2.addLabelToNode(8, inner_f);
                                
                                vector<BaseRegion*> toGlue;
                                
                                BaseRegion upper_left = *it_upper_left;
                                if (upper_left_size == 3) {
                                    upper_left.addLabelToNode(0, a);
                                    upper_left.addLabelToNode(1, b);
                                    upper_left.addLabelToNode(5, c);
                                } else {
                                    cout << "assume always 3" << endl;
                                    exit(0);
                                }
                                toGlue.push_back(&upper_left);
                                
                                BaseRegion upper_right = *it_upper_right;
                                if (upper_right_size == 3) {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(6, c);
                                } else {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(1, c);
                                    upper_right.addLabelToNode(6, d);
                                }
                                toGlue.push_back(&upper_right);
                                
                                BaseRegion lower_left = *it_lower_left;
                                lower_left.addLabelToNode(0, a);
                                lower_left.addLabelToNode(4, b);
                                lower_left.addLabelToNode(8, c);
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                lower_right.addLabelToNode(3, a);
                                lower_right.addLabelToNode(4, b);
                                lower_right.addLabelToNode(7, c);
                                toGlue.push_back(&lower_right);
                                
                                R2.glue(toGlue);
                                
                                store_sign(R2, priv_signature_minimal);
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
        
#pragma omp critical
        {
            cout << "Thread " << tid << " done and now adding to signature_minimal " << endl;
            for (map<vector<int>,BaseRegion>::const_iterator it = priv_signature_minimal.begin(); it != priv_signature_minimal.end(); ++it) {
                BaseRegion R = it->second;
                store_sign(R, signature_minimal);
            }
        }
        
    } // parallel over
    cout << "Done with inner 6-regions" << endl;
    
}

void generate_5regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &inner_2regions,
                                  const vector<BaseRegion> &inner_3regions,
                                  const vector<BaseRegion> &inner_4regions,
                                  const vector<BaseRegion> &inner_4starregions,
                                  const vector<BaseRegion> &inner_5regions,
                                  const vector<BaseRegion> &inner_6regions,
                                  const vector<BaseRegion> &regions_3hat_with_edges,
                                  const vector<BaseRegion> &regions_3hat_without_ac_edge,
                                  const vector<BaseRegion> &regions_4hat_with_edges,
                                  const vector<BaseRegion> &regions_4hat_without_ad_edge,
                                  const vector<BaseRegion> &regions_3,
                                  const vector<BaseRegion> &regions_4
                                  ){
    
    
    cout << "Starting 5-regions from inner" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_2regions.empty() || inner_3regions.empty() || inner_4regions.empty() || inner_4starregions.empty() || inner_5regions.empty() || inner_6regions.empty() || regions_3hat_with_edges.empty() ||  regions_3hat_without_ac_edge.empty() || regions_4hat_with_edges.empty() || regions_4hat_without_ad_edge.empty() || regions_3.empty() || regions_4.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    cout << "b-d edge" << endl;
    
    for (int i = 0; i < regions_4.size(); i++) {
        for (int j = 0; j < regions_3hat_with_edges.size(); j++) {
            BaseRegion reg4 = regions_4[i];
            BaseRegion reg3hat = regions_3hat_with_edges[j];
            
            Region R(5,a,d);
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, b);
            R.addLabelToNode(2, c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, e);
            
            vector<BaseRegion*> toGlue;
            
            reg4.addLabelToNode(0, a);
            reg4.addLabelToNode(1, b);
            reg4.addLabelToNode(3, c);
            reg4.addLabelToNode(4, d);
            toGlue.push_back(&reg4);
            
            reg3hat.addLabelToNode(3, a);
            reg3hat.addLabelToNode(2, b);
            reg3hat.addLabelToNode(1, c);
            toGlue.push_back(&reg3hat);
            
            R.glue(toGlue);
            
            if (!R.isAdjacent(b, d)) {
                cout << "b-d not adj";
                exit(1);
            }
            
            store_sign(R, signature_minimal);
        }
    }
    
    cout << "c-e edge" << endl;
    for (int i = 0; i < regions_4hat_with_edges.size(); i++) {
        for (int j = 0; j < regions_3hat_with_edges.size(); j++) {
            BaseRegion reg4 = regions_4hat_with_edges[i];
            BaseRegion reg3 = regions_3hat_with_edges[j];
            
            Region R(5,a,d);
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, b);
            R.addLabelToNode(2, c);
            R.addLabelToNode(3, d);
            R.addLabelToNode(4, e);
            
            vector<BaseRegion*> toGlue;
            
            reg4.addLabelToNode(0, a);
            reg4.addLabelToNode(1, b);
            reg4.addLabelToNode(2, c);
            reg4.addLabelToNode(4, d);
            toGlue.push_back(&reg4);
            
            reg3.addLabelToNode(3, a);
            reg3.addLabelToNode(2, b);
            reg3.addLabelToNode(4, c);
            toGlue.push_back(&reg3);
            
            R.glue(toGlue);
            
            if (!R.isAdjacent(c, e)) {
                cout << "c-e not adj";
                exit(1);
            }
            
            if (!R.isValid()) {
                cout << "reg4:";
                reg4.printRegion();
                cout << "reg3:";
                reg3.printRegion();
            }
            
            store_sign(R, signature_minimal);
        }
    }
    
    generate_5regions_from_inner2(signature_minimal, inner_2regions);
    
    generate_5regions_from_inner3_one_up(signature_minimal, inner_3regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner3_one_up(signature_minimal, inner_3regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    
    generate_5regions_from_inner3_one_down(signature_minimal, inner_3regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge);
    
    generate_5regions_from_inner4(signature_minimal, inner_4regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner4(signature_minimal, inner_4regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    
    generate_5regions_from_inner4star_two_up(signature_minimal, inner_4starregions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner4star_two_up(signature_minimal, inner_4starregions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    generate_5regions_from_inner4star_two_down(signature_minimal, inner_4starregions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge);
    
    generate_5regions_from_inner5_two_up(signature_minimal, inner_5regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner5_two_up(signature_minimal, inner_5regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    generate_5regions_from_inner5_two_down(signature_minimal, inner_5regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner5_two_down(signature_minimal, inner_5regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    
    generate_5regions_from_inner6(signature_minimal, inner_6regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 3);
    generate_5regions_from_inner6(signature_minimal, inner_6regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, 3, 4);
    
    // Symmetries
    cout << "Finding symmetries"<< endl;
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        BaseRegion sym(5);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, d);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, c);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, b);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, a);
        sym.addLabelToNode(4, e); reg.addLabelToNode(4, e);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }
    
    cout << "Done with 5-regions" << endl;
    print_map(signature_minimal);

}
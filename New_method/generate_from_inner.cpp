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
#include <stdlib.h>


const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;


vector<BaseRegion> choose_outer_regions(int size, bool edge,
                                        const vector<BaseRegion> &outer_3regions_with_edge,
                                        const vector<BaseRegion> &outer_3regions_without_edge,
                                        const vector<BaseRegion> &outer_4regions_with_edge,
                                        const vector<BaseRegion> &outer_4regions_without_edge
                                        ){
    if (size == 3) {
        if (edge) return outer_3regions_with_edge;
        else return outer_3regions_without_edge;
    } else if (size == 4) {
        if (edge) return outer_4regions_with_edge;
        else return outer_4regions_without_edge;
    } else {
        cout << "Ivalid size: " << size << endl;
        exit(1);
    }
}

vector<BaseRegion> choose_outer_regions(bool edge,
                                        const vector<BaseRegion> &regions_with_edge,
                                        const vector<BaseRegion> &regions_without_edge
                                        ){
    if (edge) return regions_with_edge;
    else return regions_without_edge;
}

void generate_from_inner2(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_2regions,
                          const vector<BaseRegion> &outer_4starregions_with_edge,
                          const vector<BaseRegion> &outer_4starregions_without_edge
                          ) {
    
    cout << "Starting from inner 2-regions" << endl;
    
    int current = 0;
    unsigned long mmax = inner_2regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_2regions.size(); i++) {
            
            BaseRegion inner = inner_2regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            
            Region R(6,a,d);
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper = choose_outer_regions(inner.isAdjacent(a, d), outer_4starregions_with_edge, outer_4starregions_without_edge);
            vector<BaseRegion> lower = choose_outer_regions(inner.isAdjacent(a, d), outer_4starregions_with_edge, outer_4starregions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper = upper.begin(); it_upper != upper.end(); it_upper++) {
                for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, e);
                    R2.addLabelToNode(5, f);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper = *it_upper;
                    upper.addLabelToNode(0, a);
                    upper.addLabelToNode(1, b);
                    upper.addLabelToNode(2, c);
                    upper.addLabelToNode(3, d);
                    toGlue.push_back(&upper);
                    
                    BaseRegion lower_left = *it_lower;
                    lower_left.addLabelToNode(3, a);
                    lower_left.addLabelToNode(4, b);
                    lower_left.addLabelToNode(5, c);
                    lower_left.addLabelToNode(0, d);
                    toGlue.push_back(&lower_left);
                    
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
    cout << "Done with inner 2-regions." << endl;
    
}

void generate_from_inner3(map<vector<int>,BaseRegion> &signature_minimal,
                              const vector<BaseRegion> &inner_3regions,
                              const vector<BaseRegion> &outer_3regions_with_edge,
                              const vector<BaseRegion> &outer_4regions_with_edge,
                              const vector<BaseRegion> &outer_3regions_without_edge,
                              const vector<BaseRegion> &outer_4regions_without_edge,
                              const vector<BaseRegion> &outer_4starregions_with_edge,
                              const vector<BaseRegion> &outer_4starregions_without_edge,
                              int upper_left_size,
                              int upper_right_size
                              ) {
    
    cout << "Starting from inner 3-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            
            BaseRegion inner = inner_3regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower = choose_outer_regions(inner.isAdjacent(a, d), outer_4starregions_with_edge, outer_4starregions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
                        Region R2(R);
                        
                        R2.addLabelToNode(0, a);
                        R2.addLabelToNode(1, b);
                        R2.addLabelToNode(2, c);
                        R2.addLabelToNode(3, d);
                        R2.addLabelToNode(4, e);
                        R2.addLabelToNode(5, f);
                        R2.addLabelToNode(6, inner_b);
                        
                        vector<BaseRegion*> toGlue;
                        
                        BaseRegion upper_left = *it_upper_left;
                        if (upper_left_size == 3) {
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(6, c);
                        } else {
                            cout << "errro. upper left should be 3" << endl;
                            exit(1);
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
                        
                        BaseRegion lower = *it_lower;
                        lower.addLabelToNode(3, a);
                        lower.addLabelToNode(4, b);
                        lower.addLabelToNode(5, c);
                        lower.addLabelToNode(0, d);
                        toGlue.push_back(&lower);
                        
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
    cout << "Done with inner 3-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
}

void generate_from_inner4(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_4regions,
                          const vector<BaseRegion> &outer_3regions_with_edge,
                          const vector<BaseRegion> &outer_4regions_with_edge,
                          const vector<BaseRegion> &outer_3regions_without_edge,
                          const vector<BaseRegion> &outer_4regions_without_edge,
                          int upper_left_size,
                          int upper_right_size,
                          int lower_left_size,
                          int lower_right_size
                          ) {
    
    cout << "Starting from inner 4-regions. Outer: " << upper_left_size << "-"<< upper_right_size<<"-"<< lower_left_size<< "-"<< lower_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_4regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4regions.size(); i++) {
            
            BaseRegion inner = inner_4regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_d = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            R.addLabelToNode(3, inner_d);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(lower_left_size, inner.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower_right = choose_outer_regions(lower_right_size, inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
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
                                R2.addLabelToNode(7, inner_d);
                                
                                vector<BaseRegion*> toGlue;
                                
                                BaseRegion upper_left = *it_upper_left;
                                if (upper_left_size == 3) {
                                    upper_left.addLabelToNode(0, a);
                                    upper_left.addLabelToNode(1, b);
                                    upper_left.addLabelToNode(6, c);
                                } else {
                                    cout << "errro. upper left should be 3" << endl;
                                    exit(1);
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
                                if (lower_left_size == 3) {
                                    lower_left.addLabelToNode(0, a);
                                    lower_left.addLabelToNode(5, b);
                                    lower_left.addLabelToNode(7, c);
                                } else {
                                    lower_left.addLabelToNode(0, a);
                                    lower_left.addLabelToNode(5, b);
                                    lower_left.addLabelToNode(4, c);
                                    lower_left.addLabelToNode(7, d);
                                }
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                if (lower_right_size == 3) {
                                    lower_right.addLabelToNode(3, a);
                                    lower_right.addLabelToNode(4, b);
                                    lower_right.addLabelToNode(7, c);
                                } else {
                                    lower_right.addLabelToNode(3, a);
                                    lower_right.addLabelToNode(4, b);
                                    lower_right.addLabelToNode(5, c);
                                    lower_right.addLabelToNode(7, d);
                                }
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
    cout << "Done with inner non-empty 4-regions" << endl;
    
}

void generate_from_inner4star(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_4starregions,
                          const vector<BaseRegion> &outer_3regions_with_edge,
                          const vector<BaseRegion> &outer_4regions_with_edge,
                          const vector<BaseRegion> &outer_3regions_without_edge,
                              const vector<BaseRegion> &outer_4regions_without_edge,
                              const vector<BaseRegion> &outer_4starregions_with_edge,
                              const vector<BaseRegion> &outer_4starregions_without_edge,
                          int upper_left_size,
                          int upper_right_size
                          ) {
    
    cout << "Starting from inner 4star-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
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
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower = choose_outer_regions(inner.isAdjacent(a, d), outer_4starregions_with_edge, outer_4starregions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower = lower.begin(); it_lower != lower.end(); it_lower++) {
                        
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
                            R2.addLabelToNode(5, f);
                            R2.addLabelToNode(6, inner_b);
                            R2.addLabelToNode(7, inner_c);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            if (upper_left_size == 3) {
                                upper_left.addLabelToNode(0, a);
                                upper_left.addLabelToNode(1, b);
                                upper_left.addLabelToNode(6, c);
                            } else {
                                cout << "errro. upper left should be 3" << endl;
                                exit(1);
                            }
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            if (upper_right_size == 3) {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(7, c);
                            } else {
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(1, c);
                                upper_right.addLabelToNode(7, d);
                            }
                            
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower = *it_lower;
                            lower.addLabelToNode(3, a);
                            lower.addLabelToNode(4, b);
                            lower.addLabelToNode(5, c);
                            lower.addLabelToNode(0, d);
                            toGlue.push_back(&lower);
                            
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
    cout << "Done with inner 4star-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
}

void generate_from_inner5(map<vector<int>,BaseRegion> &signature_minimal,
                             const vector<BaseRegion> &inner_5regions,
                             const vector<BaseRegion> &outer_3regions_with_edge,
                             const vector<BaseRegion> &outer_4regions_with_edge,
                             const vector<BaseRegion> &outer_3regions_without_edge,
                          const vector<BaseRegion> &outer_4regions_without_edge,
                          int upper_left_size,
                          int upper_right_size,
                          int lower_left_size,
                          int lower_right_size
                             ) {
    
    cout << "Starting from inner 5-regions. Outer: " << upper_left_size << "-"<< upper_right_size<<"-"<< lower_left_size<< "-"<< lower_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
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
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(lower_left_size, inner.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower_right = choose_outer_regions(lower_right_size, inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
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
                                R2.addLabelToNode(5, f);
                                R2.addLabelToNode(6, inner_b);
                                R2.addLabelToNode(7, inner_c);
                                R2.addLabelToNode(8, inner_e);
                                
                                vector<BaseRegion*> toGlue;
                                
                                BaseRegion upper_left = *it_upper_left;
                                if (upper_left_size == 3) {
                                    upper_left.addLabelToNode(0, a);
                                    upper_left.addLabelToNode(1, b);
                                    upper_left.addLabelToNode(6, c);
                                } else {
                                    cout << "errro. upper left should be 3" << endl;
                                    exit(1);
                                }
                                toGlue.push_back(&upper_left);
                                
                                BaseRegion upper_right = *it_upper_right;
                                if (upper_right_size == 3) {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(7, c);
                                } else {
                                    upper_right.addLabelToNode(3, a);
                                    upper_right.addLabelToNode(2, b);
                                    upper_right.addLabelToNode(1, c);
                                    upper_right.addLabelToNode(7, d);
                                }
                                
                                toGlue.push_back(&upper_right);
                                
                                BaseRegion lower_left = *it_lower_left;
                                if (lower_left_size == 3) {
                                    lower_left.addLabelToNode(0, a);
                                    lower_left.addLabelToNode(5, b);
                                    lower_left.addLabelToNode(8, c);
                                } else {
                                    lower_left.addLabelToNode(0, a);
                                    lower_left.addLabelToNode(5, b);
                                    lower_left.addLabelToNode(4, c);
                                    lower_left.addLabelToNode(8, d);
                                }
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                if (lower_right_size == 3) {
                                    lower_right.addLabelToNode(3, a);
                                    lower_right.addLabelToNode(4, b);
                                    lower_right.addLabelToNode(8, c);
                                } else {
                                    lower_right.addLabelToNode(3, a);
                                    lower_right.addLabelToNode(4, b);
                                    lower_right.addLabelToNode(5, c);
                                    lower_right.addLabelToNode(8, d);
                                }
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
    cout << "Done with inner non-empty 5-regions. Outer: 3-4" << endl;
    
}

void generate_from_inner6(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_6regions,
                          const vector<BaseRegion> &outer_3regions_with_edge,
                          const vector<BaseRegion> &outer_4regions_with_edge,
                          const vector<BaseRegion> &outer_3regions_without_edge,
                          const vector<BaseRegion> &outer_4regions_without_edge,
                          int upper_left_size,
                          int upper_right_size,
                          int lower_left_size,
                          int lower_right_size
                               ) {
    
    cout << "Starting inner non-empty 6-regions. Outer: " << upper_left_size << "-"<< upper_right_size<<"-"<< lower_left_size<< "-"<< lower_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
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
            
            vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            vector<BaseRegion> lower_right = choose_outer_regions(lower_right_size, inner.isAdjacent(d, e), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(lower_left_size, inner.isAdjacent(a, f), outer_3regions_with_edge, outer_3regions_without_edge, outer_4regions_with_edge, outer_4regions_without_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            int max_between_edge_up = upper_left_size == 3 && upper_right_size == 3 ? 2 : 0;
                            int max_between_edge_down = lower_left_size == 3 && lower_right_size == 3 ? 2 : 0;
                            
                            for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                                for (int between_edge_down = 0; between_edge_down <= max_between_edge_down; between_edge_down++) {
                                    Region R2(R);
                                    
                                    if (between_edge_up == 1) {
                                        R2.addEdge(b, inner_c);
                                    }
                                    if(between_edge_up == 2) {
                                        R2.addEdge(c, inner_b);
                                    }
                                    
                                    if (between_edge_down == 1) {
                                        R2.addEdge(f, inner_e);
                                    }
                                    if(between_edge_down == 2) {
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
                                    if (upper_left_size == 3) {
                                        upper_left.addLabelToNode(0, a);
                                        upper_left.addLabelToNode(1, b);
                                        upper_left.addLabelToNode(6, c);
                                    } else {
                                        cout << "assume always 3" << endl;
                                        exit(0);
                                    }
                                    toGlue.push_back(&upper_left);
                                    
                                    BaseRegion upper_right = *it_upper_right;
                                    if (upper_right_size == 3) {
                                        upper_right.addLabelToNode(3, a);
                                        upper_right.addLabelToNode(2, b);
                                        upper_right.addLabelToNode(7, c);
                                    } else {
                                        upper_right.addLabelToNode(3, a);
                                        upper_right.addLabelToNode(2, b);
                                        upper_right.addLabelToNode(1, c);
                                        upper_right.addLabelToNode(7, d);
                                    }
                                    toGlue.push_back(&upper_right);
                                    
                                    BaseRegion lower_left = *it_lower_left;
                                    if (lower_left_size == 3) {
                                        lower_left.addLabelToNode(0, a);
                                        lower_left.addLabelToNode(5, b);
                                        lower_left.addLabelToNode(9, c);
                                    } else {
                                        lower_left.addLabelToNode(0, a);
                                        lower_left.addLabelToNode(5, b);
                                        lower_left.addLabelToNode(4, c);
                                        lower_left.addLabelToNode(9, d);
                                    }
                                    toGlue.push_back(&lower_left);
                                    
                                    BaseRegion lower_right = *it_lower_right;
                                    if (lower_right_size == 3) {
                                        lower_right.addLabelToNode(3, a);
                                        lower_right.addLabelToNode(4, b);
                                        lower_right.addLabelToNode(8, c);
                                    } else {
                                        lower_right.addLabelToNode(3, a);
                                        lower_right.addLabelToNode(4, b);
                                        lower_right.addLabelToNode(5, c);
                                        lower_right.addLabelToNode(8, d);
                                    }
                                    toGlue.push_back(&lower_right);
                                    
                                    R2.glue(toGlue);
                                    
                                    store_sign(R2, priv_signature_minimal);
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


void generate_6regions_from_nonempty_inner(map<vector<int>,BaseRegion> &signature_minimal,
                         const vector<BaseRegion> &inner_2regions,
                         const vector<BaseRegion> &inner_3regions,
                         const vector<BaseRegion> &inner_4regions,
                         const vector<BaseRegion> &inner_4starregions,
                         const vector<BaseRegion> &inner_5regions,
                         const vector<BaseRegion> &inner_6regions,
                         const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                         const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                         const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                                  const vector<BaseRegion> &outer_non_dom_4regions_without_edge,
                                  const vector<BaseRegion> &outer_non_dom_4starregions_without_edge,
                                  const vector<BaseRegion> &outer_non_dom_4starregions_with_edge
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
    
    int num = 0;
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, inner_6regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4(signature_minimal, inner_4regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, inner_4regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, inner_4regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, inner_4regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4star(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, outer_non_dom_4starregions_with_edge, outer_non_dom_4starregions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4star(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, outer_non_dom_4starregions_with_edge, outer_non_dom_4starregions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner3(signature_minimal, inner_3regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, outer_non_dom_4starregions_with_edge, outer_non_dom_4starregions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner3(signature_minimal, inner_3regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, outer_non_dom_4starregions_with_edge, outer_non_dom_4starregions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner2(signature_minimal, inner_2regions, outer_non_dom_4starregions_with_edge, outer_non_dom_4starregions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
}

void generate_6regions_from_empty_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &empty_inner_2regions,
                                  const vector<BaseRegion> &empty_inner_3regions,
                                  const vector<BaseRegion> &empty_inner_4regions,
                                  const vector<BaseRegion> &empty_inner_4starregions,
                                  const vector<BaseRegion> &empty_inner_5regions,
                                  const vector<BaseRegion> &empty_inner_6regions,
                                  const vector<BaseRegion> &outer_general_3regions_with_edge,
                                  const vector<BaseRegion> &outer_general_4regions_with_edge,
                                  const vector<BaseRegion> &outer_general_3regions_without_edge,
                               const vector<BaseRegion> &outer_general_4regions_without_edge,
                               const vector<BaseRegion> &outer_general_4starregions_with_edge,
                               const vector<BaseRegion> &outer_general_4starregions_without_edge
                                  ) {
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(empty_inner_4starregions.empty() || empty_inner_4regions.empty() || empty_inner_5regions.empty() || empty_inner_6regions.empty() || empty_inner_2regions.empty() || empty_inner_3regions.empty()
       || outer_general_3regions_with_edge.empty() || outer_general_4regions_with_edge.empty() | outer_general_3regions_without_edge.empty() || outer_general_4regions_without_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int num = 0;
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4(signature_minimal, empty_inner_4regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, empty_inner_4regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, empty_inner_4regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4(signature_minimal, empty_inner_4regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4star(signature_minimal, empty_inner_4starregions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_general_4starregions_with_edge, outer_general_4starregions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4star(signature_minimal, empty_inner_4starregions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_general_4starregions_with_edge, outer_general_4starregions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner3(signature_minimal, empty_inner_3regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_general_4starregions_with_edge, outer_general_4starregions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner3(signature_minimal, empty_inner_3regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_general_4starregions_with_edge, outer_general_4starregions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner2(signature_minimal, empty_inner_2regions, outer_general_4starregions_with_edge, outer_general_4regions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
}

void generate_6regions_with_no_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                     const vector<BaseRegion> &regions_3hat_with_edges,
                                     const vector<BaseRegion> &regions_4hat_with_edges,
                                     const vector<BaseRegion> &regions_5hat_with_edges,
                                     const vector<BaseRegion> &regions_6hat_with_edges
                                     ) {
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if (regions_3hat_with_edges.empty() || regions_4hat_with_edges.empty() || regions_5hat_with_edges.empty() || regions_6hat_with_edges.empty()) {
        cout << "needed regions empty!" << endl;
        exit(1);
    }
    
    Region R(6,a,d);
    
    cout << "c-e edge" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_5hat_with_edges.begin(); it_left != regions_5hat_with_edges.end(); it_left++) {
        for (vector<BaseRegion>::const_iterator it_right = regions_3hat_with_edges.begin(); it_right != regions_3hat_with_edges.end(); it_right++) {
            Region R2(R);
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, d);
            R2.addLabelToNode(4, e);
            R2.addLabelToNode(5, f);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left5 = *it_left;
            left5.addLabelToNode(0, a);
            left5.addLabelToNode(1, b);
            left5.addLabelToNode(2, c);
            left5.addLabelToNode(4, d);
            left5.addLabelToNode(5, e);
            toGlue.push_back(&left5);
            
            BaseRegion right3 = *it_right;
            right3.addLabelToNode(3, a);
            right3.addLabelToNode(4, b);
            right3.addLabelToNode(2, c);
            toGlue.push_back(&right3);
            
            R2.glue(toGlue);
            
            store_sign(R2, signature_minimal);
        }
    }
    
    cout << "b-e edge" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_4hat_with_edges.begin(); it_left != regions_4hat_with_edges.end(); it_left++) {
        for (vector<BaseRegion>::const_iterator it_right = regions_4hat_with_edges.begin(); it_right != regions_4hat_with_edges.end(); it_right++) {
            Region R2(R);
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, d);
            R2.addLabelToNode(4, e);
            R2.addLabelToNode(5, f);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left4 = *it_left;
            left4.addLabelToNode(0, a);
            left4.addLabelToNode(1, b);
            left4.addLabelToNode(4, c);
            left4.addLabelToNode(5, d);
            toGlue.push_back(&left4);
            
            BaseRegion right4 = *it_right;
            right4.addLabelToNode(3, a);
            right4.addLabelToNode(4, b);
            right4.addLabelToNode(1, c);
            right4.addLabelToNode(2, d);
            toGlue.push_back(&right4);
            
            R2.glue(toGlue);
            
            store_sign(R2, signature_minimal);
        }
    }
    
    cout << "b-e node" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_5hat_with_edges.begin(); it_left != regions_5hat_with_edges.end(); it_left++) {
        for (vector<BaseRegion>::const_iterator it_right = regions_5hat_with_edges.begin(); it_right != regions_5hat_with_edges.end(); it_right++) {
            Region R2(R);
            int node = R2.addNode();
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, d);
            R2.addLabelToNode(4, e);
            R2.addLabelToNode(5, f);
            R2.addLabelToNode(6, node);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left5 = *it_left;
            left5.addLabelToNode(0, a);
            left5.addLabelToNode(1, b);
            left5.addLabelToNode(6, c);
            left5.addLabelToNode(4, d);
            left5.addLabelToNode(5, e);
            toGlue.push_back(&left5);
            
            BaseRegion right5 = *it_right;
            right5.addLabelToNode(3, a);
            right5.addLabelToNode(4, b);
            right5.addLabelToNode(6, c);
            right5.addLabelToNode(1, d);
            right5.addLabelToNode(2, e);
            toGlue.push_back(&right5);
            
            R2.glue(toGlue);
            
            
            store_sign_if_valid(R2, signature_minimal);
        }
    }
    
    cout << "c-e node" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_6hat_with_edges.begin(); it_left != regions_6hat_with_edges.end(); it_left++) {
        for (vector<BaseRegion>::const_iterator it_right = regions_4hat_with_edges.begin(); it_right != regions_4hat_with_edges.end(); it_right++) {
            Region R2(R);
            int node = R2.addNode();
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, d);
            R2.addLabelToNode(4, e);
            R2.addLabelToNode(5, f);
            R2.addLabelToNode(6, node);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left6 = *it_left;
            left6.addLabelToNode(0, a);
            left6.addLabelToNode(1, b);
            left6.addLabelToNode(2, c);
            left6.addLabelToNode(6, d);
            left6.addLabelToNode(4, e);
            left6.addLabelToNode(5, f);
            toGlue.push_back(&left6);
            
            BaseRegion right4 = *it_right;
            right4.addLabelToNode(3, a);
            right4.addLabelToNode(4, b);
            right4.addLabelToNode(5, c);
            right4.addLabelToNode(2, d);
            toGlue.push_back(&right4);
            
            R2.glue(toGlue);
            
            store_sign_if_valid(R2, signature_minimal);
        }
    }
}

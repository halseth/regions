//
//  generate_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//


#include "parallization.h"
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
                          const vector<BaseRegion> &inner_2regions
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
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_2regions.size(); i++) {
            
            BaseRegion inner = inner_2regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            
            Region R(6,a,d);
            
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
    cout << "Done with inner 2-regions." << endl;
    
}

void generate_from_inner3(map<vector<int>,BaseRegion> &signature_minimal,
                              const vector<BaseRegion> &inner_3regions,
                              const vector<BaseRegion> &outer_3regions_with_edge,
                              const vector<BaseRegion> &outer_4regions_with_edge,
                              const vector<BaseRegion> &outer_3regions_without_edge,
                              const vector<BaseRegion> &outer_4regions_without_edge
                              ) {
    
    cout << "Starting from inner 3-regions" << endl;
    
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
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            
            R.glue(&inner);
            
            for (int up_edges = 1; up_edges <= 0b11; up_edges++) {
                Region R2(R);
                
                if ((up_edges & 0b10) != 0) {
                    R2.addEdge(inner_b, b);
                }
                if ((up_edges & 0b01) != 0) {
                    R2.addEdge(inner_b, c);
                }
                
                store_sign(R2, priv_signature_minimal);
                
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
    cout << "Done with inner 3-regions." << endl;
    
}

void generate_from_inner4(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_4regions,
                          const vector<BaseRegion> &outer_3regions_with_edge,
                          const vector<BaseRegion> &outer_4regions_with_edge,
                          const vector<BaseRegion> &outer_3regions_without_edge,
                          const vector<BaseRegion> &outer_4regions_without_edge
                          ) {
    
    cout << "Starting from inner 4-regions." << endl;
    
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
            
            Region R(6,a,d);
            
            int inner_b = R.addNode();
            int inner_d = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, d);
            R.addLabelToNode(3, inner_d);
            
            R.glue(&inner);
            
            for (int up_edges = 1; up_edges <= 0b11; up_edges++) {
                for (int down_edges = 1; down_edges <= 0b11; down_edges++) {
                    Region R2(R);
                    
                    if ((up_edges & 0b10) != 0) {
                        R2.addEdge(inner_b, b);
                    }
                    if ((up_edges & 0b01) != 0) {
                        R2.addEdge(inner_b, c);
                    }
                    
                    if ((down_edges & 0b10) != 0) {
                        R2.addEdge(inner_d, e);
                    }
                    if ((down_edges & 0b01) != 0) {
                        R2.addEdge(inner_d, f);
                    }
                    
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
    cout << "Done with inner non-empty 4-regions" << endl;
    
}

void generate_from_inner4star(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_4starregions,
                          const vector<BaseRegion> &outer_3regions_with_edge,
                          const vector<BaseRegion> &outer_4regions_with_edge,
                          const vector<BaseRegion> &outer_3regions_without_edge,
                              const vector<BaseRegion> &outer_4regions_without_edge,
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
    cout << "Done with inner 4star-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
}

void generate_from_inner5(map<vector<int>,BaseRegion> &signature_minimal,
                             const vector<BaseRegion> &inner_5regions,
                             const vector<BaseRegion> &outer_3regions_with_edge,
                             const vector<BaseRegion> &outer_4regions_with_edge,
                             const vector<BaseRegion> &outer_3regions_without_edge,
                          const vector<BaseRegion> &outer_4regions_without_edge,
                          int upper_left_size,
                          int upper_right_size
                             ) {
    
    cout << "Starting from inner 5-regions. Outer: " << upper_left_size << "-"<< upper_right_size << endl;
    
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
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    for (int down_edges = 1; down_edges <= 0b11; down_edges++) {
                        
                        int max_between_edge_up = upper_left_size == 3 && upper_right_size == 3 ? 2 : 0;
                        for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                            Region R2(R);
                            
                            if (between_edge_up == 1) {
                                R2.addEdge(b, inner_c);
                            }
                            if(between_edge_up == 2) {
                                R2.addEdge(c, inner_b);
                            }
                            
                            if ((down_edges & 0b10) != 0) {
                                R2.addEdge(inner_e, e);
                            }
                            if ((down_edges & 0b01) != 0) {
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
    cout << "Done with inner non-empty 5-regions. Outer: 3-4" << endl;
    
}

void generate_from_empty_inner6(map<vector<int>,BaseRegion> &signature_minimal,
                          const vector<BaseRegion> &inner_6regions,
                          const vector<BaseRegion> &outer_general_3regions_with_edge,
                          const vector<BaseRegion> &outer_general_4regions_with_edge,
                          const vector<BaseRegion> &outer_general_3regions_without_edge,
                                const vector<BaseRegion> &outer_general_4regions_without_edge,
                                const vector<BaseRegion> &non_dom_outer_3regions_with_edge,
                                const vector<BaseRegion> &non_dom_outer_4regions_with_edge,
                                const vector<BaseRegion> &non_dom_outer_3regions_without_edge,
                                const vector<BaseRegion> &non_dom_outer_4regions_without_edge,
                          int upper_left_size,
                          int upper_right_size,
                          int lower_left_size,
                          int lower_right_size
                          ) {
    
    cout << "Starting generate_from_empty_inner6. Outer: " << upper_left_size << "-"<< upper_right_size<<"-"<< lower_left_size<< "-"<< lower_right_size << endl;
    cout << "outer_general_3regions_with_edge.size()=" << outer_general_3regions_with_edge.size() << endl;
    cout << "outer_general_4regions_with_edge.size()=" << outer_general_4regions_with_edge.size() << endl;
    cout << "outer_general_3regions_without_edge.size()=" << outer_general_3regions_without_edge.size() << endl;
    cout << "outer_general_4regions_without_edge.size()=" << outer_general_4regions_without_edge.size() << endl;
    cout << "non_dom_outer_3regions_with_edge.size()=" << non_dom_outer_3regions_with_edge.size() << endl;
    cout << "non_dom_outer_4regions_with_edge.size()=" << non_dom_outer_4regions_with_edge.size() << endl;
    cout << "non_dom_outer_3regions_without_edge.size()=" << non_dom_outer_3regions_without_edge.size() << endl;
    cout << "non_dom_outer_4regions_without_edge.size()=" << non_dom_outer_4regions_without_edge.size() << endl;
    
    int current = 0;
    unsigned long mmax = inner_6regions.size();
    
    cout << "Number of iterations: " << mmax << endl;
    
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
            
            // Choose which outer region might be dominator
            for (int dominator = 0; dominator <= 3; dominator++) {
                
                vector<BaseRegion> upper_left = choose_outer_regions(upper_left_size, inner.isAdjacent(a, b),
                                                                     dominator == 0 ? outer_general_3regions_with_edge: non_dom_outer_3regions_with_edge,
                                                                     dominator == 0 ? outer_general_3regions_without_edge: non_dom_outer_3regions_without_edge,
                                                                     dominator == 0 ? outer_general_4regions_with_edge : non_dom_outer_4regions_with_edge,
                                                                     dominator == 0 ? outer_general_4regions_without_edge: non_dom_outer_4regions_without_edge);
                
                vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d),
                                                                      dominator == 1 ? outer_general_3regions_with_edge: non_dom_outer_3regions_with_edge,
                                                                      dominator == 1 ? outer_general_3regions_without_edge: non_dom_outer_3regions_without_edge,
                                                                      dominator == 1 ? outer_general_4regions_with_edge : non_dom_outer_4regions_with_edge,
                                                                      dominator == 1 ? outer_general_4regions_without_edge: non_dom_outer_4regions_without_edge);
                
                vector<BaseRegion> lower_left = choose_outer_regions(lower_left_size, inner.isAdjacent(a, f),
                                                                     dominator == 2 ? outer_general_3regions_with_edge: non_dom_outer_3regions_with_edge,
                                                                     dominator == 2 ? outer_general_3regions_without_edge: non_dom_outer_3regions_without_edge,
                                                                     dominator == 2 ? outer_general_4regions_with_edge : non_dom_outer_4regions_with_edge,
                                                                     dominator == 2 ? outer_general_4regions_without_edge: non_dom_outer_4regions_without_edge);
                
                vector<BaseRegion> lower_right = choose_outer_regions(lower_right_size, inner.isAdjacent(d, e),
                                                                      dominator == 3 ? outer_general_3regions_with_edge: non_dom_outer_3regions_with_edge,
                                                                      dominator == 3 ? outer_general_3regions_without_edge: non_dom_outer_3regions_without_edge,
                                                                      dominator == 3 ? outer_general_4regions_with_edge : non_dom_outer_4regions_with_edge,
                                                                      dominator == 3 ? outer_general_4regions_without_edge: non_dom_outer_4regions_without_edge);
                
                for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                    for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                        for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                            for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                                
//                                unsigned long itss = upper_left.size() * upper_right.size() * lower_right.size() * lower_left.size();
//                                
//                                cout << "Thread " << tid << ": Going to do " << upper_left.size() << "*"<< upper_right.size() << "*"<< lower_right.size() << "*"<< lower_left.size() << "="<< itss << " iterations." << endl;
                                
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
            
            
            
            priv_current++;
#pragma omp critical
                {
                    current+=1;
                    std::cout << "Thread " << tid << ": Done with iteration " << current << " of " << mmax << std::endl;
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
    
    cout << "Starting generate_from_inner6. Outer: " << upper_left_size << "-"<< upper_right_size<<"-"<< lower_left_size<< "-"<< lower_right_size << endl;
    
    int current = 0;
    unsigned long mmax = inner_6regions.size();
    
    cout << "Number of iterations: " << mmax << endl;
    
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
            
            unsigned long itss = upper_left.size() * upper_right.size() * lower_right.size() * lower_left.size();
            
            cout << "Thread " << tid << ": Going to do " << itss << " iterations" << endl;
            
            unsigned long done_its = 0;
            
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
                            done_its++;
                            if (done_its % 10000 == 0) {
                                cout << "____________Thread " << tid << "done " << done_its << " of " << itss << " iterations" << endl;
                            }
                        }
                    }
                }
            }
            
            priv_current++;
            if(priv_current%1 == 0) {
#pragma omp critical
                {
                    current+=1;
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
                                  const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                         ) {
    
    if(inner_4starregions.empty() || inner_4regions.empty() || inner_5regions.empty() || inner_6regions.empty() || inner_2regions.empty() || inner_3regions.empty()
       || outer_non_dom_3regions_with_edge.empty() || outer_non_dom_4regions_with_edge.empty() || outer_non_dom_3regions_without_edge.empty() || outer_non_dom_4regions_without_edge.empty() ){
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
    
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, inner_5regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4(signature_minimal, inner_4regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4star(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4star(signature_minimal, inner_4starregions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner3(signature_minimal, inner_3regions, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner2(signature_minimal, inner_2regions);
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
                                        const vector<BaseRegion> &outer_non_dom_3regions_with_edge,
                                        const vector<BaseRegion> &outer_non_dom_4regions_with_edge,
                                        const vector<BaseRegion> &outer_non_dom_3regions_without_edge,
                                        const vector<BaseRegion> &outer_non_dom_4regions_without_edge
                                  ) {
    cout << "Starting generate_6regions_from_empty_inner" << endl;
    
    if(empty_inner_4starregions.empty() || empty_inner_4regions.empty() || empty_inner_5regions.empty() || empty_inner_6regions.empty() || empty_inner_2regions.empty() || empty_inner_3regions.empty()
       || outer_general_3regions_with_edge.empty() || outer_general_4regions_with_edge.empty() | outer_general_3regions_without_edge.empty() || outer_general_4regions_without_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int num = 0;
//    generate_from_empty_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 4, 3);
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 4, 3);
    cout << "Checkpoint " << num++ << endl;
//    generate_from_empty_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, outer_non_dom_3regions_with_edge, outer_non_dom_4regions_with_edge, outer_non_dom_3regions_without_edge, outer_non_dom_4regions_without_edge, 3, 4, 3,4);
    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 4);
    cout << "Checkpoint " << num++ << endl;
//    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4, 3, 3);
//    cout << "Checkpoint " << num++ << endl;
//    generate_from_inner6(signature_minimal, empty_inner_6regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3, 3, 3);
//    cout << "Checkpoint " << num++ << endl;
    
    // TODO: Make empty outers
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner5(signature_minimal, empty_inner_5regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4(signature_minimal, empty_inner_4regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner4star(signature_minimal, empty_inner_4starregions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 4);
    cout << "Checkpoint " << num++ << endl;
    generate_from_inner4star(signature_minimal, empty_inner_4starregions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge, 3, 3);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner3(signature_minimal, empty_inner_3regions, outer_general_3regions_with_edge, outer_general_4regions_with_edge, outer_general_3regions_without_edge, outer_general_4regions_without_edge);
    cout << "Checkpoint " << num++ << endl;
    
    generate_from_inner2(signature_minimal, empty_inner_2regions);
    cout << "Checkpoint " << num++ << endl;
    
}

void generate_6regions_with_no_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                     const vector<BaseRegion> &regions_3hat_with_edges,
                                     const vector<BaseRegion> &regions_4hat_with_edges,
                                     const vector<BaseRegion> &regions_5hat_with_edges,
                                     const vector<BaseRegion> &regions_6hat_with_edges
                                     ) {
    cout << "Starting generate_6regions_with_no_inner" << endl;
    
    if (regions_3hat_with_edges.empty() || regions_4hat_with_edges.empty() || regions_5hat_with_edges.empty() || regions_6hat_with_edges.empty()) {
        cout << "needed regions empty!" << endl;
        exit(1);
    }
    
    Region R(6,a,d);
    
    cout << "c-e edge" << endl;
    
    int current = 0;
    unsigned long mmax = regions_5hat_with_edges.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < regions_5hat_with_edges.size(); i++) {
            for (int j = 0; j < regions_3hat_with_edges.size(); j++) {
                Region R2(R);
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, d);
                R2.addLabelToNode(4, e);
                R2.addLabelToNode(5, f);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion left5 = regions_5hat_with_edges[i];
                left5.addLabelToNode(0, a);
                left5.addLabelToNode(1, b);
                left5.addLabelToNode(2, c);
                left5.addLabelToNode(4, d);
                left5.addLabelToNode(5, e);
                toGlue.push_back(&left5);
                
                BaseRegion right3 = regions_3hat_with_edges[j];
                right3.addLabelToNode(3, a);
                right3.addLabelToNode(4, b);
                right3.addLabelToNode(2, c);
                toGlue.push_back(&right3);
                
                R2.glue(toGlue);
                
                store_sign(R2, priv_signature_minimal);
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
    
    cout << "b-e edge" << endl;
    current = 0;
    mmax = regions_4hat_with_edges.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < regions_4hat_with_edges.size(); i++) {
            for (int j = 0; j < regions_4hat_with_edges.size(); j++) {
                Region R2(R);
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, d);
                R2.addLabelToNode(4, e);
                R2.addLabelToNode(5, f);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion left4 = regions_4hat_with_edges[i];
                left4.addLabelToNode(0, a);
                left4.addLabelToNode(1, b);
                left4.addLabelToNode(4, c);
                left4.addLabelToNode(5, d);
                toGlue.push_back(&left4);
                
                BaseRegion right4 = regions_4hat_with_edges[j];
                right4.addLabelToNode(3, a);
                right4.addLabelToNode(4, b);
                right4.addLabelToNode(1, c);
                right4.addLabelToNode(2, d);
                toGlue.push_back(&right4);
                
                R2.glue(toGlue);
                
                store_sign(R2, priv_signature_minimal);
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
    
    cout << "b-e node" << endl;
    current = 0;
    mmax = regions_5hat_with_edges.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < regions_5hat_with_edges.size(); i++) {
            for (int j = 0; j < regions_5hat_with_edges.size(); j++) {
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
                
                BaseRegion left5 = regions_5hat_with_edges[i];
                left5.addLabelToNode(0, a);
                left5.addLabelToNode(1, b);
                left5.addLabelToNode(6, c);
                left5.addLabelToNode(4, d);
                left5.addLabelToNode(5, e);
                toGlue.push_back(&left5);
                
                BaseRegion right5 = regions_5hat_with_edges[j];
                right5.addLabelToNode(3, a);
                right5.addLabelToNode(4, b);
                right5.addLabelToNode(6, c);
                right5.addLabelToNode(1, d);
                right5.addLabelToNode(2, e);
                toGlue.push_back(&right5);
                
                R2.glue(toGlue);
                
                
                store_sign_if_valid(R2, priv_signature_minimal);
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
    
    cout << "c-e node" << endl;
    current = 0;
    mmax = regions_6hat_with_edges.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        int nthreads = NUM_THREADS;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < regions_6hat_with_edges.size(); i++) {
            for (int j = 0; j < regions_4hat_with_edges.size(); j++) {
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
                
                BaseRegion left6 = regions_6hat_with_edges[i];
                left6.addLabelToNode(0, a);
                left6.addLabelToNode(1, b);
                left6.addLabelToNode(2, c);
                left6.addLabelToNode(6, d);
                left6.addLabelToNode(4, e);
                left6.addLabelToNode(5, f);
                toGlue.push_back(&left6);
                
                BaseRegion right4 = regions_4hat_with_edges[j];
                right4.addLabelToNode(3, a);
                right4.addLabelToNode(4, b);
                right4.addLabelToNode(5, c);
                right4.addLabelToNode(2, d);
                toGlue.push_back(&right4);
                
                R2.glue(toGlue);
                
                store_sign_if_valid(R2, priv_signature_minimal);
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
    
    cout << "Done generate_6regions_with_no_inner" << endl;
}

void generate_6regions(map<vector<int>,BaseRegion> &signature_minimal,
                       const vector<BaseRegion> &inner_2regions,
                       const vector<BaseRegion> &inner_3regions,
                       const vector<BaseRegion> &inner_4regions,
                       const vector<BaseRegion> &inner_4starregions,
                       const vector<BaseRegion> &inner_5regions,
                       const vector<BaseRegion> &inner_6regions,
                       const vector<BaseRegion> &empty_inner_2regions,
                       const vector<BaseRegion> &empty_inner_3regions,
                       const vector<BaseRegion> &empty_inner_4regions,
                       const vector<BaseRegion> &empty_inner_4starregions,
                       const vector<BaseRegion> &empty_inner_5regions,
                       const vector<BaseRegion> &empty_inner_6regions,
                       const vector<BaseRegion> &regions_3hat_with_edges,
                       const vector<BaseRegion> &regions_4hat_with_edges,
                       const vector<BaseRegion> &regions_5hat_with_edges,
                       const vector<BaseRegion> &regions_6hat_with_edges,
                       const vector<BaseRegion> &regions_3hat_without_ac_edge,
                       const vector<BaseRegion> &regions_4hat_without_ad_edge,
                       const vector<BaseRegion> &non_dom_regions_3hat_with_edges,
                       const vector<BaseRegion> &non_dom_regions_4hat_with_edges,
                       const vector<BaseRegion> &non_dom_regions_3hat_without_ac_edge,
                       const vector<BaseRegion> &non_dom_regions_4hat_without_ad_edge
                       ) {
    
    cout << "starting generate_6regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_2regions.empty() || inner_3regions.empty() || inner_4regions.empty() || inner_4starregions.empty() || inner_5regions.empty() || inner_6regions.empty()
       || empty_inner_2regions.empty() || empty_inner_3regions.empty() || empty_inner_4regions.empty() || empty_inner_4starregions.empty() || empty_inner_5regions.empty() || empty_inner_6regions.empty()
       || regions_3hat_with_edges.empty() || regions_4hat_with_edges.empty() || regions_3hat_without_ac_edge.empty() || regions_4hat_without_ad_edge.empty()
       || non_dom_regions_3hat_with_edges.empty() || non_dom_regions_4hat_with_edges.empty() || non_dom_regions_3hat_without_ac_edge.empty() || non_dom_regions_4hat_without_ad_edge.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    generate_6regions_with_no_inner(signature_minimal, regions_3hat_with_edges, regions_4hat_with_edges, regions_5hat_with_edges, regions_6hat_with_edges);
    generate_6regions_from_empty_inner(signature_minimal, empty_inner_2regions, empty_inner_3regions, empty_inner_4regions, empty_inner_4starregions, empty_inner_5regions, empty_inner_6regions, regions_3hat_with_edges, regions_4hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_without_ad_edge, non_dom_regions_3hat_with_edges, non_dom_regions_4hat_with_edges, non_dom_regions_3hat_without_ac_edge, non_dom_regions_4hat_without_ad_edge);
    generate_6regions_from_nonempty_inner(signature_minimal, inner_2regions, inner_3regions, inner_4regions, inner_4starregions, inner_5regions, inner_6regions, non_dom_regions_3hat_with_edges, non_dom_regions_4hat_with_edges, non_dom_regions_3hat_without_ac_edge, non_dom_regions_4hat_without_ad_edge);
    
    // Symmetries
    cout << "Finding symmetries"<< endl;
    
    // Flip around vertical
    cout << "Around vertical" << endl;
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        BaseRegion sym(6);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, d);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, c);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, b);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, a);
        sym.addLabelToNode(4, e); reg.addLabelToNode(4, f);
        sym.addLabelToNode(5, f); reg.addLabelToNode(5, e);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }
    
    // Flip around horisontal
    cout << "Around horistontal" << endl;
    regs.clear();
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        BaseRegion sym(6);
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
    
    cout << "Done generate_6regions" << endl;
    print_map(signature_minimal);
}

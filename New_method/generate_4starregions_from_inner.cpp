//
//  generate_4starregions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_4starregions_from_inner.hpp"
#include "parallization.h"
#include "generate_from_inner.hpp"

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

void generate_4starregions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
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
                                  const vector<BaseRegion> &regions_3_with_edges,
                                  const vector<BaseRegion> &regions_3_without_ac_edge,
                                  bool with_ad_edge
                                  ){
    cout << "Starting 4*-regions from inner" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_2regions.empty() || inner_3regions.empty() || inner_4regions.empty() || inner_4starregions.empty() || inner_5regions.empty() || inner_6regions.empty() || regions_3hat_with_edges.empty() ||  regions_3hat_without_ac_edge.empty() || regions_4hat_with_edges.empty() || regions_3_with_edges.empty() || regions_3_without_ac_edge.empty() || regions_4hat_without_ad_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    Region R(4,a,d);
    if (!with_ad_edge) {
        R.removeEdge(a, d);
    }
    
    cout << "a-c edge" << endl;
    vector<BaseRegion> rights = choose_outer_regions(with_ad_edge, regions_3_with_edges, regions_3_without_ac_edge);
    for (vector<BaseRegion>::const_iterator it_left = regions_3hat_with_edges.begin(); it_left != regions_3hat_with_edges.end(); it_left++){
        for (vector<BaseRegion>::const_iterator it_right = rights.begin(); it_right != rights.end(); it_right++){
            
            Region R2(R);
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(4, d);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left = *it_left;
            left.addLabelToNode(0, a);
            left.addLabelToNode(1, b);
            left.addLabelToNode(2, c);
            toGlue.push_back(&left);
            
            BaseRegion right = *it_right;
            right.addLabelToNode(3, a);
            right.addLabelToNode(2, b);
            right.addLabelToNode(0, c);
            toGlue.push_back(&right);
            
            R2.glue(toGlue);
            
            store_sign(R2, signature_minimal);
        }
    }
    
    cout << "inner 3-region" << endl;
    for (vector<BaseRegion>::const_iterator it_inner = inner_3regions.begin(); it_inner != inner_3regions.end(); it_inner++){
        BaseRegion inner = *it_inner;
        
        // check if compatible with edge
        if (inner.isAdjacent(a, c) != with_ad_edge) {
            continue;
        }
        
        for (int up_edges = 1; up_edges <= 0b11; up_edges++) {
            Region R2(R);
            int node = R2.addNode();
            
            if ((up_edges & 0b10) != 0) {
                R2.addEdge(b, node);
            }
            if ((up_edges & 0b01) != 0) {
                R2.addEdge(c, node);
            }
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, node);
            R2.addLabelToNode(2, d);
            
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            R2.glue(&inner);
            
            store_sign(R2, signature_minimal);
        }
    }
    
    for (int upper_right_size = 3; upper_right_size <= 4; upper_right_size++) {
        cout << "Inner 4*region with 3-" << upper_right_size << " outer" << endl;
        int current = 0;
        unsigned long mmax = inner_6regions.size();
        
#pragma omp parallel
        {
            map<vector<int>,BaseRegion> priv_signature_minimal;
            int priv_current = 0;
            int tid = THREAD_ID;
            int nthreads = NUM_THREADS;
            
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            
            BaseRegion inner = inner_4starregions[i];
            // check if compatible with edge
            if (inner.isAdjacent(a, d) != with_ad_edge) {
                continue;
            }
            
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R2(R);
            
            int inner_b = R2.addNode();
            int inner_c = R2.addNode();
            
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, inner_b);
            R2.addLabelToNode(2, inner_c);
            R2.addLabelToNode(3, d);
            
            R2.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), regions_3hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_with_edges, regions_4hat_without_ad_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    int max_between_edge_up = upper_right_size == 3 ? 2 : 0;
                    for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
                        Region R3(R2);
                        
                        if (between_edge_up == 1) {
                            R3.addEdge(b, inner_c);
                        }
                        if(between_edge_up == 2) {
                            R3.addEdge(c, inner_b);
                        }
                        
                        R3.addLabelToNode(0, a);
                        R3.addLabelToNode(1, b);
                        R3.addLabelToNode(2, c);
                        R3.addLabelToNode(3, d);
                        R3.addLabelToNode(4, inner_b);
                        R3.addLabelToNode(5, inner_c);
                        
                        vector<BaseRegion*> toGlue;
                        
                        BaseRegion upper_left = *it_upper_left;
                        upper_left.addLabelToNode(0, a);
                        upper_left.addLabelToNode(1, b);
                        upper_left.addLabelToNode(4, c);
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
                        
                        R3.glue(toGlue);
                        
                        store_sign(R3, priv_signature_minimal);
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
            
        }// parallel over
    }
    
    cout << "Done with 4*-regions" << endl;
    print_map(signature_minimal);
    
}

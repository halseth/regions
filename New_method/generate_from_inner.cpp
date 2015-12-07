//
//  generate_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 05/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

//#include <omp.h>

#include "generate_from_inner.hpp"

void generate_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                         vector<BaseRegion> &inner_2regions,
                         vector<BaseRegion> &inner_3regions,
                         vector<BaseRegion> &inner_4regions,
                         vector<BaseRegion> &inner_4starregions,
                         vector<BaseRegion> &inner_5regions,
                         vector<BaseRegion> &inner_6regions,
                         vector<BaseRegion> &outer_non_dom_3regions,
                         vector<BaseRegion> &outer_non_dom_4regions
                         ) {
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_4starregions.empty() || inner_4regions.empty() || inner_5regions.empty() || inner_6regions.empty() || inner_2regions.empty() || inner_3regions.empty()
       || outer_non_dom_3regions.empty() || outer_non_dom_4regions.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    
    cout << "Starting inner non-empty 6-regions. Outer: 3-4-4-3" << endl;
    
    int current = 0;
    int mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        // Inner 6-regions. This is a WIP. Outer regions not considered
#pragma omp for nowait
        for (int i = 0; i < inner_6regions.size(); i++) {
            for (int inner_boundary_edges = 0; inner_boundary_edges <= 0b111111; inner_boundary_edges++) {
                
                BaseRegion inner = inner_6regions[i];
                inner.removeEdge(a, b);
                inner.removeEdge(b, c);
                inner.removeEdge(c, d);
                inner.removeEdge(d, e);
                inner.removeEdge(e, f);
                inner.removeEdge(f, a);
                
                if ( (inner_boundary_edges & (0b100000)) != 0) {
                    inner.addEdge(a, b);
                }
                if ( (inner_boundary_edges & (0b010000)) != 0) {
                    inner.addEdge(b, c);
                }
                if ( (inner_boundary_edges & (0b001000)) != 0) {
                    inner.addEdge(c, d);
                }
                if ( (inner_boundary_edges & (0b000100)) != 0) {
                    inner.addEdge(d, e);
                }
                if ( (inner_boundary_edges & (0b000010)) != 0) {
                    inner.addEdge(e, f);
                }
                if ( (inner_boundary_edges & (0b000001)) != 0) {
                    inner.addEdge(f, a);
                }
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
                
                if (!R.isValid()) {
                    continue;
                }
                
                for (vector<BaseRegion>::const_iterator it_upper_left = outer_non_dom_3regions.begin(); it_upper_left != outer_non_dom_3regions.end(); it_upper_left++) {
                    for (vector<BaseRegion>::const_iterator it_upper_right = outer_non_dom_4regions.begin(); it_upper_right != outer_non_dom_4regions.end(); it_upper_right++) {
                        for (vector<BaseRegion>::const_iterator it_lower_left = outer_non_dom_4regions.begin(); it_lower_left != outer_non_dom_4regions.end(); it_lower_left++) {
                            for (vector<BaseRegion>::const_iterator it_lower_right = outer_non_dom_3regions.begin(); it_lower_right != outer_non_dom_3regions.end(); it_lower_right++) {
                                
                                Region R2(R);
                                if (!R2.getLabelToNode().empty() || !R2.getNodeToLabels().empty()) {
                                    cout << "labels not emoty!" << endl;
                                    exit(1);
                                }
                                
                                R2.addEdge(inner_b, b);
                                R2.addEdge(inner_c, b);
                                R2.addEdge(inner_e, e);
                                R2.addEdge(inner_f, e);
                                
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
                                upper_left.removeEdge(a, c);
                                upper_left.addLabelToNode(0, a);
                                upper_left.addLabelToNode(1, b);
                                upper_left.addLabelToNode(6, c);
                                toGlue.push_back(&upper_left);
                                
                                BaseRegion upper_right = *it_upper_right;
                                upper_right.removeEdge(a, d);
                                upper_right.addLabelToNode(3, a);
                                upper_right.addLabelToNode(2, b);
                                upper_right.addLabelToNode(1, c);
                                upper_right.addLabelToNode(7, d);
                                toGlue.push_back(&upper_right);
                                
                                BaseRegion lower_left = *it_lower_left;
                                lower_left.removeEdge(a, d);
                                lower_left.addLabelToNode(0, a);
                                lower_left.addLabelToNode(5, b);
                                lower_left.addLabelToNode(4, c);
                                lower_left.addLabelToNode(9, d);
                                toGlue.push_back(&lower_left);
                                
                                BaseRegion lower_right = *it_lower_right;
                                lower_right.removeEdge(a, c);
                                lower_right.addLabelToNode(3, a);
                                lower_right.addLabelToNode(4, b);
                                lower_right.addLabelToNode(8, c);
                                toGlue.push_back(&lower_right);
                                
                                R2.glue(toGlue);
                                
                                store_sign_if_valid(R2, priv_signature_minimal);
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
    cout << "Done with inner non-empty 6-regions. Outer: 3-4-4-3" << endl;

    
    cout << "Starting inner 2-regions" << endl;
    current = 0;
    mmax = inner_2regions.size();
    
    #pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
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
    cout << "Starting inner 3-regions" << endl;
    
    current = 0;
    mmax = inner_3regions.size();
    
    #pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        // Inner 3-regions. Outer regions will be empty
        #pragma omp for nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            for (int inner_boundary_edges = 0; inner_boundary_edges <= 0b111; inner_boundary_edges++) {
                for (int edges_up = 0; edges_up <= 0b11; edges_up++) {
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
                    
                    store_sign_if_valid(R, priv_signature_minimal);
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
    
    cout << "Starting inner 4-regions" << endl;
    
    current = 0;
    mmax = inner_4regions.size();
    
    #pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int tid = 0;//omp_get_thread_num();
        int nthreads = 1;//omp_get_num_threads();
        cout << "Thread " << tid << " / " << nthreads << " starting" << endl;
        
        // Inner 4-regions. Outer regions will be empty
        #pragma omp for nowait
        for (int i = 0; i < inner_4regions.size(); i++) {
            for (int inner_boundary_edges = 0; inner_boundary_edges <= 0b1111; inner_boundary_edges++) {
                for (int edges_up = 0; edges_up <= 0b11; edges_up++) {
                    for (int edges_down = 0; edges_down <= 0b11; edges_down++) {
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
                        
                        store_sign_if_valid(R, priv_signature_minimal);
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

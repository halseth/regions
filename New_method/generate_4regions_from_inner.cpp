//
//  generate_4regions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_4regions_from_inner.hpp"
#include "parallization.h"


#include "choose_regions.hpp"
#include <stdlib.h>

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

void generate_4regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                  const vector<BaseRegion> &inner_2regions,
                                  const vector<BaseRegion> &inner_3regions,
                                  const vector<BaseRegion> &inner_4regions,
                                  const vector<BaseRegion> &inner_4starregions,
                                  const vector<BaseRegion> &inner_5regions,
                                  const vector<BaseRegion> &inner_6regions,
                                  const vector<BaseRegion> &regions_3hat_with_edges,
                                  const vector<BaseRegion> &regions_3hat_without_ac_edge,
                                  const vector<BaseRegion> &regions_4hat_with_edges
                                  ){
    
    
    cout << "Starting 4-regions from inner" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_2regions.empty() || inner_3regions.empty() || inner_4regions.empty() || inner_4starregions.empty() || inner_5regions.empty() || inner_6regions.empty() || regions_3hat_with_edges.empty() ||  regions_3hat_without_ac_edge.empty() || regions_4hat_with_edges.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    
    cout << "b-d edge" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_3hat_with_edges.begin(); it_left != regions_3hat_with_edges.end(); it_left++){
        for (vector<BaseRegion>::const_iterator it_right = regions_3hat_with_edges.begin(); it_right != regions_3hat_with_edges.end(); it_right++){
            
            Region R(4, a,c);
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, b);
            R.addLabelToNode(2, c);
            R.addLabelToNode(3, d);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left = *it_left;
            left.addLabelToNode(0, a);
            left.addLabelToNode(1, b);
            left.addLabelToNode(3, c);
            toGlue.push_back(&left);
            
            BaseRegion right = *it_right;
            right.addLabelToNode(2, a);
            right.addLabelToNode(1, b);
            right.addLabelToNode(3, c);
            toGlue.push_back(&right);
            
            R.glue(toGlue);
            
            if (!R.isAdjacent(b, d)) {
                cout << "b-d not adj" ;
                exit(1);
            }
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    cout << "b-d node" << endl;
    
    for (vector<BaseRegion>::const_iterator it_left = regions_4hat_with_edges.begin(); it_left != regions_4hat_with_edges.end(); it_left++){
        for (vector<BaseRegion>::const_iterator it_right = regions_4hat_with_edges.begin(); it_right != regions_4hat_with_edges.end(); it_right++){
            
            Region R2(4, a,c);
            int node = R2.addNode();
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, b);
            R2.addLabelToNode(2, c);
            R2.addLabelToNode(3, d);
            R2.addLabelToNode(4, node);
            
            vector<BaseRegion*> toGlue;
            
            BaseRegion left = *it_left;
            left.addLabelToNode(0, a);
            left.addLabelToNode(1, b);
            left.addLabelToNode(4, c);
            left.addLabelToNode(3, d);
            toGlue.push_back(&left);
            
            BaseRegion right = *it_right;
            right.addLabelToNode(2, a);
            right.addLabelToNode(1, b);
            right.addLabelToNode(4, c);
            right.addLabelToNode(3, d);
            toGlue.push_back(&right);
            
            R2.glue(toGlue);
            
            // Check if node is adjacent to an endpoint
            if (!R2.isAdjacent(a, node) && !R2.isAdjacent(c, node)) {
                continue;
            }
            
            store_sign(R2, signature_minimal);
        }
    }
    
    cout << "Starting inner 6-regions" << endl;
    
    int current = 0;
    unsigned long mmax = inner_6regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_6regions.size(); i++){
            BaseRegion inner = inner_6regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            inner.addLabelToNode(5, f);
            
            Region R(4,a,c);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            int inner_f = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, c);
            R.addLabelToNode(4, inner_e);
            R.addLabelToNode(5, inner_f);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(c, d), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> lower_right = choose_outer_regions(inner.isAdjacent(d, e), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> lower_left = choose_outer_regions(inner.isAdjacent(a, f), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    for (vector<BaseRegion>::const_iterator it_lower_left = lower_left.begin(); it_lower_left != lower_left.end(); it_lower_left++) {
                        for (vector<BaseRegion>::const_iterator it_lower_right = lower_right.begin(); it_lower_right != lower_right.end(); it_lower_right++) {
                            
                            Region R2(R);
                            
                            R2.addLabelToNode(0, a);
                            R2.addLabelToNode(1, b);
                            R2.addLabelToNode(2, c);
                            R2.addLabelToNode(3, d);
                            R2.addLabelToNode(4, inner_b);
                            R2.addLabelToNode(5, inner_c);
                            R2.addLabelToNode(6, inner_e);
                            R2.addLabelToNode(7, inner_f);
                            
                            vector<BaseRegion*> toGlue;
                            
                            BaseRegion upper_left = *it_upper_left;
                            upper_left.addLabelToNode(0, a);
                            upper_left.addLabelToNode(1, b);
                            upper_left.addLabelToNode(4, c);
                            toGlue.push_back(&upper_left);
                            
                            BaseRegion upper_right = *it_upper_right;
                            upper_right.addLabelToNode(2, a);
                            upper_right.addLabelToNode(1, b);
                            upper_right.addLabelToNode(5, c);
                            toGlue.push_back(&upper_right);
                            
                            BaseRegion lower_left = *it_lower_left;
                            lower_left.addLabelToNode(0, a);
                            lower_left.addLabelToNode(3, b);
                            lower_left.addLabelToNode(7, c);
                            toGlue.push_back(&lower_left);
                            
                            BaseRegion lower_right = *it_lower_right;
                            lower_right.addLabelToNode(2, a);
                            lower_right.addLabelToNode(3, b);
                            lower_right.addLabelToNode(6, c);
                            toGlue.push_back(&lower_right);
                            
                            R2.glue(toGlue);
                            
                            if (R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)) {
                                cout << "R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)" << endl;
                                exit(1);
                            }
                            
                            if (R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)) {
                                cout << "R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)" << endl;
                                exit(1);
                            }
                            
                            if (R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)) {
                                cout << "R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)" << endl;
                                exit(1);
                            }
                            
                            if (R2.isAdjacent(c, inner_e) != inner.isAdjacent(d, e)) {
                                cout << "R2.isAdjacent(c, inner_e) != inner.isAdjacent(d, e)" << endl;
                                exit(1);
                            }
                            
                            if (R2.isAdjacent(inner_e, inner_f) != inner.isAdjacent(e, f)) {
                                cout << "R2.isAdjacent(inner_e, inner_f) != inner.isAdjacent(e, f)" << endl;
                                exit(1);
                            }
                            
                            if (R2.isAdjacent(inner_f, a) != inner.isAdjacent(f, a)) {
                                cout << "R2.isAdjacent(inner_f, a) != inner.isAdjacent(f, a)" << endl;
                                exit(1);
                            }
                            
                            if (!R2.isValid()) {
                                cout << "inner:";
                                inner.printRegion();
                                cout << "upLeft:";
                                upper_left.printRegion();
                                cout << "upRight:";
                                upper_right.printRegion();
                                cout << "lowLeft:";
                                lower_left.printRegion();
                                cout << "lowRight:";
                                lower_right.printRegion();
                                
                                cout << "final:";
                                R2.printRegion();
                            }
                            
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
        
    }// parallel over
    
    
    cout << "inner 5-regions" << endl;
    current = 0;
    mmax = inner_5regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_5regions.size(); i++){
            BaseRegion inner = inner_5regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            inner.addLabelToNode(4, e);
            
            Region R(4,a,c);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            int inner_e = R.addNode();
            
            R.addEdge(inner_e, d);
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, c);
            R.addLabelToNode(4, inner_e);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(c, d), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, inner_b);
                    R2.addLabelToNode(5, inner_c);
                    R2.addLabelToNode(6, inner_e);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper_left = *it_upper_left;
                    upper_left.addLabelToNode(0, a);
                    upper_left.addLabelToNode(1, b);
                    upper_left.addLabelToNode(4, c);
                    toGlue.push_back(&upper_left);
                    
                    BaseRegion upper_right = *it_upper_right;
                    upper_right.addLabelToNode(2, a);
                    upper_right.addLabelToNode(1, b);
                    upper_right.addLabelToNode(5, c);
                    toGlue.push_back(&upper_right);
                    
                    R2.glue(toGlue);
                    
                    if (R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)) {
                        cout << "R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)) {
                        cout << "R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)) {
                        cout << "R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(c, inner_e) != inner.isAdjacent(d, e)) {
                        cout << "R2.isAdjacent(c, inner_e) != inner.isAdjacent(d, e)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(inner_e, a) != inner.isAdjacent(e, a)) {
                        cout << "R2.isAdjacent(inner_e, a) != inner.isAdjacent(e, a)" << endl;
                        exit(1);
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
    
    
    cout << "inner 4-regions" << endl;
    current = 0;
    mmax = inner_4regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4regions.size(); i++){
            BaseRegion inner = inner_4regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(4,a,c);
            
            int inner_b = R.addNode();
            int inner_d = R.addNode();
            R.addEdge(inner_b, b);
            R.addEdge(inner_d, d);
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, c);
            R.addLabelToNode(3, inner_d);
            
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
    
    
    cout << "inner 4*-regions" << endl;
    current = 0;
    mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++){
            BaseRegion inner = inner_4starregions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            Region R(4,a,c);
            
            int inner_b = R.addNode();
            int inner_c = R.addNode();
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, inner_c);
            R.addLabelToNode(3, c);
            
            R.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(c, d), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    Region R2(R);
                    
                    R2.addLabelToNode(0, a);
                    R2.addLabelToNode(1, b);
                    R2.addLabelToNode(2, c);
                    R2.addLabelToNode(3, d);
                    R2.addLabelToNode(4, inner_b);
                    R2.addLabelToNode(5, inner_c);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper_left = *it_upper_left;
                    upper_left.addLabelToNode(0, a);
                    upper_left.addLabelToNode(1, b);
                    upper_left.addLabelToNode(4, c);
                    toGlue.push_back(&upper_left);
                    
                    BaseRegion upper_right = *it_upper_right;
                    upper_right.addLabelToNode(2, a);
                    upper_right.addLabelToNode(1, b);
                    upper_right.addLabelToNode(5, c);
                    toGlue.push_back(&upper_right);
                    
                    R2.glue(toGlue);
                    
                    if (R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)) {
                        cout << "R2.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)) {
                        cout << "R2.isAdjacent(inner_b, inner_c) != inner.isAdjacent(b, c)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)) {
                        cout << "R2.isAdjacent(inner_c, c) != inner.isAdjacent(c, d)" << endl;
                        exit(1);
                    }
                    
                    if (R2.isAdjacent(a, c) != inner.isAdjacent(a, d)) {
                        cout << "R2.isAdjacent(a, c) != inner.isAdjacent(a, d)" << endl;
                        exit(1);
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
    
    cout << "inner 3-regions" << endl;
    current = 0;
    mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_3regions.size(); i++){
            BaseRegion inner = inner_3regions[i];
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            Region R(4,a,c);
            
            int inner_b = R.addNode();
            R.addEdge(inner_b, b);
            
            
            R.addLabelToNode(0, a);
            R.addLabelToNode(1, inner_b);
            R.addLabelToNode(2, c);
            
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

    cout << "inner 2-regions" << endl;
    for (int i = 0; i < inner_2regions.size(); i++){
        BaseRegion inner = inner_2regions[i];
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        
        Region R(4,a,c);
        
        R.addLabelToNode(0, a);
        R.addLabelToNode(1, c);
        
        R.glue(&inner);
        
        store_sign(R, signature_minimal);
    }
    
    // Symmetries
    cout << "Finding symmetries"<< endl;
    
    // Flip around vertical
    cout << "Around vertical" << endl;
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        Region sym(4,a,c);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, c);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, b);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, a);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, d);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }
    
    // Flip around horisontal
    cout << "Around horisontal" << endl;
    regs.clear();
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        Region sym(4,a,c);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, a);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, d);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, c);
        sym.addLabelToNode(3, d); reg.addLabelToNode(3, b);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }

    
    cout << "done with 4-regions" << endl;
    print_map(signature_minimal);
    
}

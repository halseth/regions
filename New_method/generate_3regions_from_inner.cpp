//
//  generate_3regions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_3regions_from_inner.hpp"
#include "parallization.h"
#include "choose_regions.hpp"
const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;

void generate_3regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                        const vector<BaseRegion> &inner_2regions,
                                        const vector<BaseRegion> &inner_3regions,
                                        const vector<BaseRegion> &inner_4starregions,
                                        const vector<BaseRegion> &regions_3hat_with_edges,
                                        const vector<BaseRegion> &regions_3hat_without_ac_edge
                                        ){
    cout << "Start generate 3-regions from inner" <<endl;
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(inner_2regions.empty() || inner_3regions.empty() || inner_4starregions.empty() || regions_3hat_with_edges.empty() ||  regions_3hat_without_ac_edge.empty() ){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    Region R(3, a,c);
    
    cout << "Starting with inner 4*-regions" << endl;
    int current = 0;
    unsigned long mmax = inner_4starregions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_4starregions.size(); i++) {
            BaseRegion inner = inner_4starregions[i];
            
            //Ignore if not consistent with edge
//            if (inner.isAdjacent(a, d) != with_edge) {
//                continue;
//            }
            
            Region R2(R);
            
            int inner_b = R2.addNode();
            int inner_c = R2.addNode();
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, inner_b);
            R2.addLabelToNode(2, inner_c);
            R2.addLabelToNode(3, c);
            
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            inner.addLabelToNode(3, d);
            
            R2.glue(&inner);
            
            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(d, c), regions_3hat_with_edges, regions_3hat_without_ac_edge);
            
            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                    
                    Region R3(R2);
                    R3.addLabelToNode(0, a);
                    R3.addLabelToNode(1, b);
                    R3.addLabelToNode(2, c);
                    R3.addLabelToNode(3, inner_b);
                    R3.addLabelToNode(4, inner_c);
                    
                    vector<BaseRegion*> toGlue;
                    
                    BaseRegion upper_left = *it_upper_left;
                    upper_left.addLabelToNode(0, a);
                    upper_left.addLabelToNode(1, b);
                    upper_left.addLabelToNode(3, c);
                    toGlue.push_back(&upper_left);
                    
                    BaseRegion upper_right = *it_upper_right;
                    upper_right.addLabelToNode(2, a);
                    upper_right.addLabelToNode(1, b);
                    upper_right.addLabelToNode(4, c);
                    toGlue.push_back(&upper_right);
                    
                    R3.glue(toGlue);
                    
//                    if (R3.isAdjacent(a, c) != with_edge) {
//                        cout << "R3.isAdjacent(a, c) != with_edge" << endl;
//                        exit(1);
//                    }
                    
                    if (!R3.isAdjacent(inner_b, b)) {
                        cout << "b-inner_b not adj" << endl;
                        exit(1);
                    }
                    
                    if (!R3.isAdjacent(inner_c, b)) {
                        cout << "b-inner_c not adj" << endl;
                        exit(1);
                    }
                    
                    if (R3.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)) {
                        cout << "R3.isAdjacent(a, inner_b) != inner.isAdjacent(a, b)" << endl;
                        exit(1);
                    }
                    
                    if (R3.isAdjacent(c, inner_c) != inner.isAdjacent(c, d)) {
                        cout << "R3.isAdjacent(c, inner_c) != inner.isAdjacent(c, d)" << endl;
                        exit(1);
                    }
                    
                    if (!R3.isValid()) {
                        cout << "R3-not valid"<< endl;
                        R3.printRegion();
                        cout << "inenr:" << endl;
                        inner.printRegion();
                        cout << "lef:" << endl;
                        upper_left.printRegion();
                        cout << "right:" << endl;
                        upper_right.printRegion();
                        exit(1);
                    }
                    
                    store_sign(R3, priv_signature_minimal);
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
    
    
    cout << "Starting with inner 3-regions" << endl;
    current = 0;
    mmax = inner_3regions.size();
    
#pragma omp parallel
    {
        map<vector<int>,BaseRegion> priv_signature_minimal;
        int priv_current = 0;
        int tid = THREAD_ID;
        
#pragma omp for schedule(dynamic) nowait
        for (int i = 0; i < inner_3regions.size(); i++) {
            BaseRegion inner = inner_3regions[i];
            
            //Ignore if not consistent with edge
//            if (inner.isAdjacent(a, c) != with_edge) {
//                continue;
//            }
            
            Region R2(R);
            
            int inner_b = R2.addNode();
            
            R2.addEdge(inner_b, b);
            
            R2.addLabelToNode(0, a);
            R2.addLabelToNode(1, inner_b);
            R2.addLabelToNode(2, c);
            
            inner.addLabelToNode(0, a);
            inner.addLabelToNode(1, b);
            inner.addLabelToNode(2, c);
            
            R2.glue(&inner);
            
//            if (R2.isAdjacent(a, c) != with_edge) {
//                cout << "R2.isAdjacent(a, c) != with_edge" << endl;
//                exit(1);
//            }
            
            store_sign(R2, priv_signature_minimal);
            
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
    
    cout << "Starting with inner 2-regions" << endl;
    for (vector<BaseRegion>::const_iterator it_inner2 = inner_2regions.begin(); it_inner2 != inner_2regions.end(); it_inner2++) {
        BaseRegion inner = *it_inner2;
        
        //Ignore if not consistent with edge
//        if (inner.isAdjacent(a, b) != with_edge) {
//            continue;
//        }
        
        Region R2(R);
        
        R2.addLabelToNode(0, a);
        R2.addLabelToNode(1, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        
        R2.glue(&inner);
        
//        if (R2.isAdjacent(a, c) != with_edge) {
//            cout << "R2.isAdjacent(a, c) != with_edge" << endl;
//            exit(1);
//        }
        
        store_sign(R2, signature_minimal);
    }
    
    // Symmetries
    cout << "Finding symmetries"<< endl;
    vector<BaseRegion> regs;
    for(map<vector<int>,BaseRegion >::const_iterator it = signature_minimal.begin(); it != signature_minimal.end(); it++){
        regs.push_back(it->second);
    }
    
    for (int i = 0; i < regs.size(); i++) {
        
        Region sym(3,a,c);
        for (int j = 0; j < sym.getSize(); j++) {
            sym.removeEdge(j, (j+1)%sym.getSize());
        }
        BaseRegion reg = regs[i];
        sym.addLabelToNode(0, a); reg.addLabelToNode(0, c);
        sym.addLabelToNode(1, b); reg.addLabelToNode(1, b);
        sym.addLabelToNode(2, c); reg.addLabelToNode(2, a);
        
        sym.glue(&reg);
        
        store_sign(sym, signature_minimal);
    }
    
    cout << "Done with 3-regions" << endl;
    print_map(signature_minimal);
}
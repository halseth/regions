//
//  generate_3regions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 19/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_3regions_from_inner.hpp"
#include "generate_from_inner.hpp"
const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;

void generate_3regions_from_inner(map<vector<int>,BaseRegion> &signature_minimal,
                                        const vector<BaseRegion> &inner_2regions,
                                        const vector<BaseRegion> &inner_3regions,
                                        const vector<BaseRegion> &inner_4starregions,
                                        const vector<BaseRegion> &outer_general_3regions_with_edge,
                                        const vector<BaseRegion> &outer_general_3regions_without_edge,
                                  bool with_edge
                                        ){
    
    cout << "Starting with inner 4*-regions" << endl;
    for (vector<BaseRegion>::const_iterator it_4star = inner_4starregions.begin(); it_4star != inner_4starregions.end(); it_4star++) {
        BaseRegion inner = *it_4star;
        //Ignore if not consistent with edge
        if (inner.isAdjacent(a, d) != with_edge) {
            continue;
        }
        
        Region R(3, a,c);
        if (!with_edge) {
            R.removeEdge(a, c);
        }
        
        int inner_b = R.addNode();
        int inner_c = R.addNode();
        
        R.addEdge(inner_b, b);
        R.addEdge(inner_c, b);
        
        R.addLabelToNode(0, a);
        R.addLabelToNode(1, inner_b);
        R.addLabelToNode(2, inner_c);
        R.addLabelToNode(3, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        inner.addLabelToNode(2, c);
        inner.addLabelToNode(3, d);
        
        R.glue(&inner);
        
        if (!R.isValid()) {
            continue;
        }
        
        
        vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), outer_general_3regions_with_edge, outer_general_3regions_without_edge);
        vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(d, c), outer_general_3regions_with_edge, outer_general_3regions_without_edge);
        
        for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
            for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                
                BaseRegion R2(R);
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, inner_b);
                R2.addLabelToNode(4, inner_c);
                
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
                
                R2.glue(toGlue);
                
                store_sign(R2, signature_minimal);
            }
        }
        
    }
    
    cout << "Starting with inner 3-regions" << endl;
    for (vector<BaseRegion>::const_iterator it_inner3 = inner_3regions.begin(); it_inner3 != inner_3regions.end(); it_inner3++) {
        BaseRegion inner = *it_inner3;
        
        //Ignore if not consistent with edge
        if (inner.isAdjacent(a, c) != with_edge) {
            continue;
        }
        
        Region R(3, a,c);
        if (!with_edge) {
            R.removeEdge(a, c);
        }
        
        int inner_b = R.addNode();
        
        R.addEdge(inner_b, b);
        
        R.addLabelToNode(0, a);
        R.addLabelToNode(1, inner_b);
        R.addLabelToNode(2, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        inner.addLabelToNode(2, c);
        
        R.glue(&inner);
        
        if (!R.isValid()) {
            continue;
        }
        
        vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), outer_general_3regions_with_edge, outer_general_3regions_without_edge);
        vector<BaseRegion> upper_right = choose_outer_regions(inner.isAdjacent(b, c), outer_general_3regions_with_edge, outer_general_3regions_without_edge);
        
        for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
            for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
                
                BaseRegion R2(R);
                R2.addLabelToNode(0, a);
                R2.addLabelToNode(1, b);
                R2.addLabelToNode(2, c);
                R2.addLabelToNode(3, inner_b);
                
                vector<BaseRegion*> toGlue;
                
                BaseRegion upper_left = *it_upper_left;
                upper_left.addLabelToNode(0, a);
                upper_left.addLabelToNode(1, b);
                upper_left.addLabelToNode(3, c);
                toGlue.push_back(&upper_left);
                
                BaseRegion upper_right = *it_upper_right;
                upper_right.addLabelToNode(2, a);
                upper_right.addLabelToNode(1, b);
                upper_right.addLabelToNode(3, c);
                toGlue.push_back(&upper_right);
                
                R2.glue(toGlue);
                
                store_sign(R2, signature_minimal);
            }
        }
    }
    
    cout << "Starting with inner 2-regions" << endl;
    for (vector<BaseRegion>::const_iterator it_inner2 = inner_2regions.begin(); it_inner2 != inner_2regions.end(); it_inner2++) {
        BaseRegion inner = *it_inner2;
        
        //Ignore if not consistent with edge
        if (inner.isAdjacent(a, b) != with_edge) {
            continue;
        }
        
        Region R(3, a,c);
        if (!with_edge) {
            R.removeEdge(a, c);
        }
        
        R.addLabelToNode(0, a);
        R.addLabelToNode(1, c);
        
        inner.addLabelToNode(0, a);
        inner.addLabelToNode(1, b);
        
        R.glue(&inner);
        
        if (!R.isValid()) {
            continue;
        }
        
        store_sign(R, signature_minimal);
    }
}
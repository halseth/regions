//
//  generate_5regions_from_inner.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include "generate_5regions_from_inner.hpp"
#include "generate_from_inner.hpp"

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

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
        for (int j = 0; j < regions_3.size(); j++) {
            BaseRegion reg4 = regions_4[i];
            BaseRegion reg3 = regions_3[i];
            
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
            
            reg3.addLabelToNode(3, a);
            reg3.addLabelToNode(2, b);
            reg3.addLabelToNode(1, b);
            toGlue.push_back(&reg3);
            
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
            BaseRegion reg4 = regions_4[i];
            BaseRegion reg3 = regions_3[i];
            
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
            reg3.addLabelToNode(4, b);
            toGlue.push_back(&reg3);
            
            R.glue(toGlue);
            
            if (!R.isAdjacent(c, e)) {
                cout << "c-e not adj";
                exit(1);
            }
            
            store_sign(R, signature_minimal);
        }
    }
    
//    cout << "inner 6-region" << endl;
//    for (int upper_right_size = 3; upper_right_size <= 4; upper_right_size++) {
//        cout << "Inner 6-region with 3-" << upper_right_size << " outer" << endl;
//        for (int i = 0; i < inner_6regions.size(); i++) {
//            
//            BaseRegion inner = inner_6regions[i];
//            
//            inner.addLabelToNode(0, a);
//            inner.addLabelToNode(1, b);
//            inner.addLabelToNode(2, c);
//            inner.addLabelToNode(3, d);
//            inner.addLabelToNode(4, e);
//            inner.addLabelToNode(5, f);
//            
//            Region R(5,a,d);
//            
//            int inner_b = R.addNode();
//            int inner_c = R.addNode();
//            int inner_e = R.addNode();
//            int inner_f = R.addNode();
//            
//            
//            R.addLabelToNode(0, a);
//            R.addLabelToNode(1, inner_b);
//            R.addLabelToNode(2, inner_c);
//            R.addLabelToNode(3, d);
//            R.addLabelToNode(4, inner_e);
//            R.addLabelToNode(5, inner_f);
//            
//            R.glue(&inner);
//            
//            vector<BaseRegion> upper_left = choose_outer_regions(inner.isAdjacent(a, b), regions_3hat_with_edges, regions_3hat_without_ac_edge);
//            vector<BaseRegion> upper_right = choose_outer_regions(upper_right_size, inner.isAdjacent(c, d), regions_3hat_with_edges, regions_3hat_without_ac_edge, regions_4hat_with_edges, regions_4hat_without_ad_edge);
//            
//            for (vector<BaseRegion>::const_iterator it_upper_left = upper_left.begin(); it_upper_left != upper_left.end(); it_upper_left++) {
//                for (vector<BaseRegion>::const_iterator it_upper_right = upper_right.begin(); it_upper_right != upper_right.end(); it_upper_right++) {
//                    
//                    int max_between_edge_up = upper_right_size == 3 ? 2 : 0;
//                    for (int between_edge_up = 0; between_edge_up <= max_between_edge_up; between_edge_up++) {
//                        Region R2(R);
//                        
//                        if (between_edge_up == 1) {
//                            R2.addEdge(b, inner_c);
//                        }
//                        if(between_edge_up == 2) {
//                            R2.addEdge(c, inner_b);
//                        }
//                        
//                        R2.addLabelToNode(0, a);
//                        R2.addLabelToNode(1, b);
//                        R2.addLabelToNode(2, c);
//                        R2.addLabelToNode(3, d);
//                        R2.addLabelToNode(4, inner_b);
//                        R2.addLabelToNode(5, inner_c);
//                        
////                        vector<BaseRegion*> toGlue;
//                        
//                        BaseRegion upper_left = *it_upper_left;
//                        upper_left.addLabelToNode(0, a);
//                        upper_left.addLabelToNode(1, b);
//                        upper_left.addLabelToNode(4, c);
//                        toGlue.push_back(&upper_left);
//                        
//                        BaseRegion upper_right = *it_upper_right;
//                        if (upper_right_size == 3) {
//                            upper_right.addLabelToNode(3, a);
//                            upper_right.addLabelToNode(2, b);
//                            upper_right.addLabelToNode(5, c);
//                        } else {
//                            upper_right.addLabelToNode(3, a);
//                            upper_right.addLabelToNode(2, b);
//                            upper_right.addLabelToNode(1, c);
//                            upper_right.addLabelToNode(5, d);
//                        }
//                        toGlue.push_back(&upper_right);
//                        
//                        R3.glue(toGlue);
//                        
//                        store_sign(R3, signature_minimal);
//                    }
//                    
//                }
//            }
//        }
//    }

}
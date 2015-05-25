//
//  5hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 25/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//
#include <iostream>
#include "5hat_regions.h"
#include "store_sign.h"

void generate_5hat_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_5hat_a, std::map<std::vector<int>,BaseRegion> &regions_4hat_a,std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_3hat){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    
    for (int s_empty = 0; s_empty <= 1; s_empty++) {
        if(s_empty){
            /*{ // a-c edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat;
                for (it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); it_4hat++) {
                    HatRegion R(5,v);
                    R.addEdge(a, c);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, c);
                    R.addLabelToNode(3, d);
                    
                    BaseRegion R_4hat = it_4hat->second;
                    R_4hat.clearLabels();
                    R_4hat.addLabelToNode(0, v);
                    R_4hat.addLabelToNode(1, a);
                    R_4hat.addLabelToNode(2, b);
                    R_4hat.addLabelToNode(3, c);
                    
                    R.glue(R_4hat);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
            
            { // a-d edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat;
                for (it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); it_3hat++) {
                    HatRegion R(5,v);
                    R.addEdge(a, d);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, d);
                    
                    BaseRegion R_3hat = it_3hat->second;
                    R_3hat.clearLabels();
                    R_3hat.addLabelToNode(0, v);
                    R_3hat.addLabelToNode(1, a);
                    R_3hat.addLabelToNode(2, b);
                    
                    R.glue(R_3hat);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
            
            { // v-b edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat;
                for (it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); it_3hat++) {
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat;
                    for (it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); it_4hat++) {
                        HatRegion R(5,v);
                        R.addEdge(v, b);
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        
                        std::vector<BaseRegion> toGLue;
                        
                        BaseRegion R_3hat = it_3hat->second;
                        R_3hat.clearLabels();
                        R_3hat.addLabelToNode(0, v);
                        R_3hat.addLabelToNode(1, a);
                        R_3hat.addLabelToNode(2, b);
                        toGLue.push_back(R_3hat);
                        
                        BaseRegion R_4hat = it_4hat->second;
                        R_4hat.clearLabels();
                        R_4hat.addLabelToNode(0, v);
                        R_4hat.addLabelToNode(2, a);
                        R_4hat.addLabelToNode(3, b);
                        R_4hat.addLabelToNode(4, c);
                        toGLue.push_back(R_4hat);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                    }
                    
                }
            }*/
            
            for (int va_nodes = 0; va_nodes <= 1; va_nodes++) {
                for (int vb_nodes = 0; vb_nodes <= 2; vb_nodes++) {
                    for (int vc_nodes = 0; vc_nodes <= 2; vc_nodes++) {
                        for (int vd_nodes = 0; vd_nodes <= 1; vd_nodes++) {
                            int max_vb_a_edge = vb_nodes > 0 ? 1 : 0;
                            for(int vb_a_edge = 0; vb_a_edge <= max_vb_a_edge; vb_a_edge++){
                                int max_vb_c_edge = vb_nodes > 0 ? 1 : 0;
                                for(int vb_c_edge = 0; vb_c_edge <= max_vb_c_edge; vb_c_edge++){
                                    int max_vb_d_edge = vb_nodes > 0 && vc_nodes == 0 ? 1 : 0;
                                    for(int vb_d_edge = 0; vb_d_edge <= max_vb_d_edge; vb_d_edge++){
                                        int max_vc_d_edge = vc_nodes > 0 ? 1 : 0;
                                        for(int vc_d_edge = 0; vc_d_edge <= max_vc_d_edge; vc_d_edge++){
                                            int max_vc_b_edge = vc_nodes >= 0 && !vb_c_edge ? 1 : 0;
                                            for(int vc_b_edge = 0; vc_b_edge <= max_vc_b_edge; vc_b_edge++){
                                                int max_vc_a_edge = vc_nodes > 0 && vb_nodes == 0 ? 1 : 0;
                                                for(int vc_a_edge = 0; vc_a_edge <= max_vc_a_edge; vc_a_edge++){
                                                    
                                                    int max_va_d_edge = va_nodes > 0 && vb_nodes == 0 && vc_nodes == 0 ? 1 : 0;
                                                    for(int va_d_edge = 0; va_d_edge <= max_va_d_edge; va_d_edge++){
                                                        int max_va_c_edge = va_nodes > 0 && vb_nodes == 0 ? 1 : 0;
                                                        for(int va_c_edge = 0; va_c_edge <= max_va_c_edge; va_c_edge++){
                                                            
                                                            int max_vd_a_edge = vd_nodes > 0 && vc_nodes == 0 && vb_nodes == 0 && !va_c_edge && !va_d_edge ? 1 : 0;
                                                            for(int vd_a_edge = 0; vd_a_edge <= max_vd_a_edge; vd_a_edge++){
                                                                int max_vd_b_edge = vd_nodes > 0 && vc_nodes == 0 && !va_c_edge && !va_d_edge ? 1 : 0;
                                                                for(int vd_b_edge = 0; vd_b_edge <= max_vd_b_edge; vd_b_edge++){
                                                                    HatRegion R(5,v);
                                                                    
                                                                    int va = -1;
                                                                    for (int i = 0; i < va_nodes; i++) {
                                                                        va = R.addNode();
                                                                    }
                                                                    
                                                                    int vb1 = -1;
                                                                    int vb2 = -1;
                                                                    for (int i = 0; i < vb_nodes; i++) {
                                                                        int vb = R.addNode();
                                                                        if(vb1 == -1) vb1 = vb;
                                                                        vb2 = vb;
                                                                    }
                                                                    
                                                                    int vc1 = -1;
                                                                    int vc2 = -1;
                                                                    for (int i = 0; i < vc_nodes; i++) {
                                                                        int vc = R.addNode();
                                                                        if(vc1 == -1) vc1 = vc;
                                                                        vc2 = vc;
                                                                    }
                                                                    
                                                                    int vd = -1;
                                                                    for (int i = 0; i < vd_nodes; i++) {
                                                                        vd = R.addNode();
                                                                    }
                                                                    
                                                                    if (vb_a_edge) {
                                                                        R.addEdge(vb1, a);
                                                                    }
                                                                    
                                                                    if (vb_c_edge) {
                                                                        R.addEdge(vb2, c);
                                                                    }
                                                                    
                                                                    if (vb_d_edge) {
                                                                        R.addEdge(vb2, d);
                                                                    }
                                                                    
                                                                    if (vc_a_edge) {
                                                                        R.addEdge(vc1, a);
                                                                    }
                                                                    
                                                                    if (vc_b_edge) {
                                                                        R.addEdge(vc1, b);
                                                                    }
                                                                    
                                                                    if (vc_d_edge) {
                                                                        R.addEdge(vc2, d);
                                                                    }
                                                                    
                                                                    if (va_d_edge) {
                                                                        R.addEdge(va, d);
                                                                    }
                                                                    
                                                                    if (va_c_edge) {
                                                                        R.addEdge(va, c);
                                                                    }
                                                                    
                                                                    if (vd_a_edge) {
                                                                        R.addEdge(vd, a);
                                                                    }
                                                                    
                                                                    if (vd_b_edge) {
                                                                        R.addEdge(vd, b);
                                                                    }
                                                                    
                                                                    counter++;
                                                                    store_sign(R, signature_minimal);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
          /*  std::map<std::vector<int>,BaseRegion>::iterator it_4hat_a;
            for (it_4hat_a = regions_4hat_a.begin(); it_4hat_a != regions_4hat_a.end(); it_4hat_a++) {
                std::map<std::vector<int>,BaseRegion>::iterator it_5hat_a;
                for (it_5hat_a = regions_5hat_a.begin(); it_5hat_a != regions_5hat_a.end(); it_5hat_a++) {
                    HatRegion R(5, v);
                    int s = R.addNode();
                    R.addEdge(v, s);
                    R.addEdge(s, b);
                    
                    BaseRegion R_4hat_a = it_4hat_a->second;
                    BaseRegion R_5hat_a = it_5hat_a->second;
                    std::vector<BaseRegion> toGLue;
                    
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, b);
                    R.addLabelToNode(3, c);
                    R.addLabelToNode(4, d);
                    R.addLabelToNode(5, s);
                    
                    R_4hat_a.addLabelToNode(0, v);
                    R_4hat_a.addLabelToNode(5, a);
                    R_4hat_a.addLabelToNode(2, b);
                    R_4hat_a.addLabelToNode(1, c);
                    toGLue.push_back(R_4hat_a);
                    
                    R_5hat_a.addLabelToNode(0, v);
                    R_5hat_a.addLabelToNode(5, a);
                    R_5hat_a.addLabelToNode(2, b);
                    R_5hat_a.addLabelToNode(3, c);
                    R_5hat_a.addLabelToNode(4, d);
                    toGLue.push_back(R_5hat_a);
                    
                    R.glue(toGLue);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }*/
            
        }
    }
    
    std::cout << "done with 5hat_regions. Total regions checked: " << counter << std::endl;
}

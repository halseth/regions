//
//  6hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "6hat_regions.h"
#include "store_sign.h"
#include <iostream>

void generate_6hat_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_5hat, std::map<std::vector<int>,BaseRegion> &regions_4hat_a,std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_3hat, std::map<std::vector<int>,BaseRegion> &regions_3hat_a, std::map<std::vector<int>,BaseRegion> &regions_6hat_a, std::map<std::vector<int>,BaseRegion> &regions_5hat_a){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 4;
    
    for (int s_empty = 0; s_empty <= 1; s_empty++) {
        if(s_empty){
            
            { // a-d edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat;
                for (it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); it_4hat++) {
                    HatRegion R(6,v);
                    R.addEdge(a, d);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, d);
                    R.addLabelToNode(3, e);
                    
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
            
            { // a-e edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat;
                for (it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); it_3hat++) {
                    HatRegion R(6,v);
                    R.addEdge(a, e);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, e);
                    
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
            
            { // b-d edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat;
                for (it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); it_5hat++) {
                    HatRegion R(6,v);
                    R.addEdge(b, d);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, b);
                    R.addLabelToNode(3, d);
                    R.addLabelToNode(4, e);
                    
                    BaseRegion R_5hat = it_5hat->second;
                    R_5hat.clearLabels();
                    R_5hat.addLabelToNode(0, v);
                    R_5hat.addLabelToNode(1, a);
                    R_5hat.addLabelToNode(2, b);
                    R_5hat.addLabelToNode(3, c);
                    R_5hat.addLabelToNode(4, d);
                    
                    R.glue(R_5hat);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
            
            { // a-c edge
                std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat;
                for (it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); it_5hat++) {
                    HatRegion R(6,v);
                    R.addEdge(a, c);
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, a);
                    R.addLabelToNode(2, c);
                    R.addLabelToNode(3, d);
                    R.addLabelToNode(4, e);
                    
                    BaseRegion R_5hat = it_5hat->second;
                    R_5hat.clearLabels();
                    R_5hat.addLabelToNode(0, v);
                    R_5hat.addLabelToNode(1, a);
                    R_5hat.addLabelToNode(2, b);
                    R_5hat.addLabelToNode(3, c);
                    R_5hat.addLabelToNode(4, d);
                    
                    R.glue(R_5hat);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
            
            { // v-b edge
                long loc_total = regions_5hat.size() * regions_3hat.size();
                long loc_counter = 0;
                std::map<std::vector<int>,BaseRegion>::const_iterator it_3hat;
                for (it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); it_3hat++) {
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat;
                    for (it_5hat = regions_5hat.begin(); it_5hat != regions_5hat.end(); it_5hat++) {
                        HatRegion R(6,v);
                        R.addEdge(v, b);
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        R.addLabelToNode(5, e);
                        
                        std::vector<BaseRegion> toGLue;
                        
                        BaseRegion R_3hat = it_3hat->second;
                        R_3hat.clearLabels();
                        R_3hat.addLabelToNode(0, v);
                        R_3hat.addLabelToNode(1, a);
                        R_3hat.addLabelToNode(2, b);
                        toGLue.push_back(R_3hat);
                        
                        BaseRegion R_5hat = it_5hat->second;
                        R_5hat.clearLabels();
                        R_5hat.addLabelToNode(0, v);
                        R_5hat.addLabelToNode(2, a);
                        R_5hat.addLabelToNode(3, b);
                        R_5hat.addLabelToNode(4, c);
                        R_5hat.addLabelToNode(5, d);
                        toGLue.push_back(R_5hat);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                        loc_counter++;
                        std::cout << "v-b edge: checked " << loc_counter << " of " << loc_total << std::endl;
                    }
                    
                }
            }
            
            { // v-c edge
                long loc_total = regions_4hat.size() * regions_4hat.size();
                long loc_counter = 0;
                std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat1;
                for (it_4hat1 = regions_4hat.begin(); it_4hat1 != regions_4hat.end(); it_4hat1++) {
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat2;
                    for (it_4hat2 = regions_4hat.begin(); it_4hat2 != regions_4hat.end(); it_4hat2++) {
                        HatRegion R(6,v);
                        R.addEdge(v, c);
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        R.addLabelToNode(5, e);
                        
                        std::vector<BaseRegion> toGLue;
                        
                        BaseRegion R_4hat1 = it_4hat1->second;
                        R_4hat1.clearLabels();
                        R_4hat1.addLabelToNode(0, v);
                        R_4hat1.addLabelToNode(1, a);
                        R_4hat1.addLabelToNode(2, b);
                        R_4hat1.addLabelToNode(3, c);
                        toGLue.push_back(R_4hat1);
                        
                        BaseRegion R_4hat2 = it_4hat2->second;
                        R_4hat2.clearLabels();
                        R_4hat2.addLabelToNode(0, v);
                        R_4hat2.addLabelToNode(3, a);
                        R_4hat2.addLabelToNode(4, b);
                        R_4hat2.addLabelToNode(5, c);
                        toGLue.push_back(R_4hat2);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                        loc_counter++;
                        std::cout << "v-c edge: checked " << loc_counter << " of " << loc_total << std::endl;
                    }
                    
                }
            }
            
            { // at least one vc-node
                long loc_total = regions_5hat.size() * regions_5hat.size();
                long loc_counter = 0;
                std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat1;
                for(it_5hat1 = regions_5hat.begin(); it_5hat1 != regions_5hat.end(); ++it_5hat1){
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat2;
                    for(it_5hat2 = regions_5hat.begin(); it_5hat2 != regions_5hat.end(); ++it_5hat2){
                        HatRegion R(6, v);
                        int vc = R.addNode();
                        R.addEdge(v, vc);
                        R.addEdge(vc, c);
                        
                        BaseRegion R_5hat1 = it_5hat1->second;
                        BaseRegion R_5hat2 = it_5hat2->second;
                        std::vector<BaseRegion> toGLue;
                        
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        R.addLabelToNode(5, e);
                        R.addLabelToNode(6, vc);
                        
                        R_5hat1.addLabelToNode(0, v);
                        R_5hat1.addLabelToNode(6, a);
                        R_5hat1.addLabelToNode(3, b);
                        R_5hat1.addLabelToNode(2, c);
                        R_5hat1.addLabelToNode(1, d);
                        toGLue.push_back(R_5hat1);
                        
                        R_5hat2.addLabelToNode(0, v);
                        R_5hat2.addLabelToNode(6, a);
                        R_5hat2.addLabelToNode(3, b);
                        R_5hat2.addLabelToNode(4, c);
                        R_5hat2.addLabelToNode(5, d);
                        toGLue.push_back(R_5hat2);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                        loc_counter++;
                        std::cout << "vc-node: checked " << loc_counter << " of " << loc_total << std::endl;
                    }
                }
            }
            
            // No vc-nodes
            
            for (int va_nodes = 0; va_nodes <= 2; va_nodes++) {
                for (int vb_nodes = 0; vb_nodes <= 4; vb_nodes++) {
                    for (int vd_nodes = 0; vd_nodes <= 4; vd_nodes++) {
                        for (int ve_nodes = 0; ve_nodes <= 2; ve_nodes++) {
                            
                            int max_va_b_edge = va_nodes > 0 ? 1 : 0;
                            for(int va_b_edge = 0; va_b_edge <= max_va_b_edge; va_b_edge++){
                                int max_va_d_edge = va_nodes > 0 && vb_nodes == 0 ? 1 : 0;
                                for(int va_d_edge = 0; va_d_edge <= max_va_d_edge; va_d_edge++){
                                    int max_va_e_edge = va_nodes > 0 && vb_nodes == 0 && vd_nodes == 0 ? 1 : 0;
                                    for(int va_e_edge = 0; va_e_edge <= max_va_e_edge; va_e_edge++){
                                        
                                        int max_vb_a_edge = vb_nodes > 0 && !va_b_edge ? 1 : 0;
                                        for(int vb_a_edge = 0; vb_a_edge <= max_vb_a_edge; vb_a_edge++){
                                            int max_vb_d_edge = vb_nodes > 0 ? 1 : 0;
                                            for(int vb_d_edge = 0; vb_d_edge <= max_vb_d_edge; vb_d_edge++){
                                                int max_vb_e_edge = vb_nodes > 0 && vd_nodes == 0? 1 : 0;
                                                for(int vb_e_edge = 0; vb_e_edge <= max_vb_e_edge; vb_e_edge++){
                                                                    
                                                    int max_vd_a_edge = vd_nodes > 0 && vb_nodes == 0 && !va_b_edge && !va_d_edge ? 1 : 0;
                                                    for(int vd_a_edge = 0; vd_a_edge <= max_vd_a_edge; vd_a_edge++){
                                                        int max_vd_b_edge = vd_nodes > 0 && !va_d_edge && !vb_d_edge ? 1 : 0;
                                                        for(int vd_b_edge = 0; vd_b_edge <= max_vd_b_edge; vd_b_edge++){
                                                                  int max_vd_e_edge = vd_nodes > 0 ? 1 : 0;
                                                            for(int vd_e_edge = 0; vd_e_edge <= max_vd_e_edge; vd_e_edge++){
                                                              
                                                                int max_ve_a_edge = ve_nodes > 0 && vb_nodes == 0 && vd_nodes == 0 && !va_b_edge && !va_d_edge && !va_e_edge ? 1 : 0;
                                                                for(int ve_a_edge = 0; ve_a_edge <= max_ve_a_edge; ve_a_edge++){
                                                                    int max_ve_b_edge = ve_nodes > 0 && vd_nodes == 0 && !va_d_edge && !va_e_edge && !vb_d_edge && !vb_e_edge ? 1 : 0;
                                                                    for(int ve_b_edge = 0; ve_b_edge <= max_ve_b_edge; ve_b_edge++){
                                                                        int max_ve_d_edge = ve_nodes > 0 && !va_e_edge && !vb_e_edge && !vd_e_edge ? 1 : 0;
                                                                        for(int ve_d_edge = 0; ve_d_edge <= max_ve_d_edge; ve_d_edge++){
                                                                            HatRegion R(6,v);
                                                                            std::cout << "new region. va=" << va_nodes << ". vb=" << vb_nodes << ". vd="<<vd_nodes << ". ve=" <<ve_nodes << std::endl;
                                                                            int va = -1;
                                                                            for (int i = 0; i < va_nodes; i++) {
                                                                                va = R.addNode();
                                                                                R.addEdge(v, va);
                                                                                R.addEdge(va, a);
                                                                            }
                                                                          
                                                                            int vb1 = -1;
                                                                            int vb2 = -1;
                                                                            for (int i = 0; i < vb_nodes; i++) {
                                                                                int vb = R.addNode();
                                                                                if(vb1 == -1) vb1 = vb;
                                                                                vb2 = vb;
                                                                                R.addEdge(v, vb);
                                                                                R.addEdge(vb, b);
                                                                            }
                                                                          
                                                                            int vd1 = -1;
                                                                            int vd2 = -1;
                                                                            for (int i = 0; i < vd_nodes; i++) {
                                                                                int vd = R.addNode();
                                                                                if(vd1 == -1) vd1 = vd;
                                                                                vd2 = vd;
                                                                                R.addEdge(v, vd);
                                                                                R.addEdge(vd, d);
                                                                            }
                                                                          
                                                                            int ve = -1;
                                                                            for (int i = 0; i < ve_nodes; i++) {
                                                                                ve = R.addNode();
                                                                                R.addEdge(v, ve);
                                                                                R.addEdge(ve, e);
                                                                            }
                                                                          
                                                                            if (va_b_edge) {
                                                                                R.addEdge(va, b);
//                                                                                std::cout << "adding va-b" << std::endl;
                                                                            }
                                                                          
                                                                            if (va_d_edge) {
                                                                                R.addEdge(va, d);
//                                                                                std::cout << "adding va-d" << std::endl;
                                                                            }
                                                                          
                                                                            if (va_e_edge) {
                                                                                R.addEdge(va, e);
//                                                                                std::cout << "adding va-e" << std::endl;
                                                                            }
                                                                          
                                                                            if (vb_a_edge) {
                                                                                R.addEdge(vb1, a);
//                                                                                std::cout << "adding vb-a" << std::endl;
                                                                            }
                                                                          
                                                                            if (vb_d_edge) {
                                                                                R.addEdge(vb2, d);
//                                                                                std::cout << "adding vb-d" << std::endl;
                                                                            }
                                                                          
                                                                            if (vb_e_edge) {
                                                                                R.addEdge(vb2, e);
//                                                                                std::cout << "adding vb-e" << std::endl;
                                                                            }
                                                                          
                                                                            if (vd_a_edge) {
                                                                                R.addEdge(vd1, a);
//                                                                                std::cout << "adding vd-a" << std::endl;
                                                                            }
                                                                          
                                                                            if (vd_b_edge) {
                                                                                R.addEdge(vd1, b);
//                                                                                std::cout << "adding vd-b" << std::endl;
                                                                            }
                                                                          
                                                                            if (vd_e_edge) {
                                                                                R.addEdge(vd2, e);
//                                                                                std::cout << "adding vd-e" << std::endl;
                                                                            }
                                                                          
                                                                            if (ve_a_edge) {
                                                                                R.addEdge(ve, a);
//                                                                                std::cout << "adding ve-a" << std::endl;
                                                                            }
                                                                          
                                                                            if (ve_b_edge) {
                                                                                R.addEdge(ve, b);
//                                                                                std::cout << "adding ve-b" << std::endl;
                                                                            }
                                                                          
                                                                            if (ve_d_edge) {
                                                                                R.addEdge(ve, d);
//                                                                                std::cout << "adding ve-d" << std::endl;
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
                }
            }
        } else {// S > 0
            
            { // s connected to b
                long loc_total = regions_4hat_a.size() * regions_6hat_a.size();
                long loc_counter = 0;
                std::map<std::vector<int>,BaseRegion>::const_iterator it_4hat_a;
                for(it_4hat_a = regions_4hat_a.begin(); it_4hat_a != regions_4hat_a.end(); ++it_4hat_a){
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_6hat_a;
                    for(it_6hat_a = regions_6hat_a.begin(); it_6hat_a != regions_6hat_a.end(); ++it_6hat_a){
                        HatRegion R(6, v);
                        int s = R.addNode();
                        R.addEdge(v, s);
                        R.addEdge(s, b);
                        
                        BaseRegion R_4hat_a = it_4hat_a->second;
                        BaseRegion R_6hat_a = it_6hat_a->second;
                        std::vector<BaseRegion> toGLue;
                        
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        R.addLabelToNode(5, e);
                        R.addLabelToNode(6, s);
                        
                        R_4hat_a.addLabelToNode(0, v);
                        R_4hat_a.addLabelToNode(6, a);
                        R_4hat_a.addLabelToNode(2, b);
                        R_4hat_a.addLabelToNode(1, c);
                        toGLue.push_back(R_4hat_a);
                        
                        R_6hat_a.addLabelToNode(0, v);
                        R_6hat_a.addLabelToNode(6, a);
                        R_6hat_a.addLabelToNode(2, b);
                        R_6hat_a.addLabelToNode(3, c);
                        R_6hat_a.addLabelToNode(4, d);
                        R_6hat_a.addLabelToNode(5, e);
                        toGLue.push_back(R_6hat_a);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                        loc_counter++;
                        std::cout << "s to b: checked " << loc_counter << " of " << loc_total << std::endl;
                    }
                }
            }
            
            { // s connected to c
                long loc_total = regions_5hat_a.size() * regions_5hat_a.size();
                long loc_counter = 0;
                std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat_a1;
                for(it_5hat_a1 = regions_5hat_a.begin(); it_5hat_a1 != regions_5hat_a.end(); ++it_5hat_a1){
                    std::map<std::vector<int>,BaseRegion>::const_iterator it_5hat_a2;
                    for(it_5hat_a2 = regions_5hat_a.begin(); it_5hat_a2 != regions_5hat_a.end(); ++it_5hat_a2){
                        HatRegion R(6, v);
                        int s = R.addNode();
                        R.addEdge(v, s);
                        R.addEdge(s, c);
                        
                        BaseRegion R_5hat_a1 = it_5hat_a1->second;
                        BaseRegion R_5hat_a2 = it_5hat_a2->second;
                        std::vector<BaseRegion> toGLue;
                        
                        R.addLabelToNode(0, v);
                        R.addLabelToNode(1, a);
                        R.addLabelToNode(2, b);
                        R.addLabelToNode(3, c);
                        R.addLabelToNode(4, d);
                        R.addLabelToNode(5, e);
                        R.addLabelToNode(6, s);
                        
                        R_5hat_a1.addLabelToNode(0, v);
                        R_5hat_a1.addLabelToNode(6, a);
                        R_5hat_a1.addLabelToNode(3, b);
                        R_5hat_a1.addLabelToNode(2, c);
                        R_5hat_a1.addLabelToNode(1, d);
                        toGLue.push_back(R_5hat_a1);
                        
                        R_5hat_a2.addLabelToNode(0, v);
                        R_5hat_a2.addLabelToNode(6, a);
                        R_5hat_a2.addLabelToNode(3, b);
                        R_5hat_a2.addLabelToNode(4, c);
                        R_5hat_a2.addLabelToNode(5, d);
                        toGLue.push_back(R_5hat_a2);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                        loc_counter++;
                        std::cout << "s to c: checked " << loc_counter << " of " << loc_total << std::endl;
                    }
                }
            }
            
        }
    }
    
    std::cout << "done with 6hat_regions. Total regions checked: " << counter << std::endl;
}
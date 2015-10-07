//
//  5hat_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 25/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//
#include <iostream>
using namespace std;

#include "5hat_regions.h"
#include "store_sign.h"

void generate_5hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<vector<int>,BaseRegion> &regions_3hat, std::map<vector<int>,BaseRegion> &regions_4hat, std::map<vector<int>,BaseRegion> &regions_4hat_b, std::map<vector<int>,BaseRegion> &regions_5hat_b){
    cout << "in generate_5hat_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat.empty() || regions_4hat_b.empty() || regions_5hat_b.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    
    // S any size
    
    // a-c edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
            HatRegion R(5, a);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_3hat = it_3hat->second;
            R_3hat.addLabelToNode(a, 0);
            R_3hat.addLabelToNode(b, 1);
            R_3hat.addLabelToNode(c, 2);
            toGlue.push_back(&R_3hat);
            
            BaseRegion R_4hat = it_4hat->second;
            R_4hat.addLabelToNode(a, 0);
            R_4hat.addLabelToNode(c, 1);
            R_4hat.addLabelToNode(d, 2);
            R_4hat.addLabelToNode(e, 3);
            toGlue.push_back(&R_4hat);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    // b-d edge
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
        HatRegion R(5, a);
        R.addEdge(b, d);
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_4hat = it_4hat->second;
        R_4hat.addLabelToNode(a, 0);
        R_4hat.addLabelToNode(b, 1);
        R_4hat.addLabelToNode(d, 2);
        R_4hat.addLabelToNode(e, 3);
        toGlue.push_back(&R_4hat);
        
        R.glue(toGlue);
        
        store_sign(R, signature_minimal);
        
    }
    
    // b-e edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        HatRegion R(5, a);
        R.addEdge(b, e);
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        R.addLabelToNode(e, e);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat = it_3hat->second;
        R_3hat.addLabelToNode(a, 0);
        R_3hat.addLabelToNode(b, 1);
        R_3hat.addLabelToNode(e, 2);
        toGlue.push_back(&R_3hat);
        
        R.glue(toGlue);
        
        store_sign(R, signature_minimal);
        
    }
    
    // c-e node
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        for (map<vector<int>,BaseRegion>::const_iterator it_4hat = regions_4hat.begin(); it_4hat != regions_4hat.end(); ++it_4hat) {
            for (int edge_node_d = 0; edge_node_d <= 1; edge_node_d++) {
                HatRegion R(5, a);
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(c, node);
                R.addEdge(e, node);
                
                if(edge_node_d){
                    R.addEdge(node, d);
                }
                
                R.addLabelToNode(a, a);
                R.addLabelToNode(b, b);
                R.addLabelToNode(c, c);
                R.addLabelToNode(d, d);
                R.addLabelToNode(e, e);
                R.addLabelToNode(node, node);
                
                std::vector<BaseRegion*> toGlue;
                
                BaseRegion R_3hat = it_3hat->second;
                R_3hat.addLabelToNode(a, 0);
                R_3hat.addLabelToNode(node, 1);
                R_3hat.addLabelToNode(e, 2);
                toGlue.push_back(&R_3hat);
                
                BaseRegion R_4hat = it_4hat->second;
                R_4hat.addLabelToNode(a, 0);
                R_4hat.addLabelToNode(b, 1);
                R_4hat.addLabelToNode(c, 2);
                R_4hat.addLabelToNode(node, 3);
                toGlue.push_back(&R_4hat);
                
                R.glue(toGlue);
                
                store_sign(R, signature_minimal);
                
            }
            
        }
    }
    
    // b-e node
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_1 = regions_3hat.begin(); it_3hat_1 != regions_3hat.end(); ++it_3hat_1) {
        for (map<vector<int>,BaseRegion>::const_iterator it_3hat_2 = regions_3hat.begin(); it_3hat_2 != regions_3hat.end(); ++it_3hat_2) {
            for (int edge_node_d = 0; edge_node_d <= 1; edge_node_d++) {
                HatRegion R(5, a);
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(b, node);
                R.addEdge(e, node);
                
                if(edge_node_d){
                    R.addEdge(node, d);
                }
                
                R.addLabelToNode(a, a);
                R.addLabelToNode(b, b);
                R.addLabelToNode(c, c);
                R.addLabelToNode(d, d);
                R.addLabelToNode(e, e);
                R.addLabelToNode(node, node);
                
                std::vector<BaseRegion*> toGlue;
                
                BaseRegion R_3hat_1 = it_3hat_1->second;
                R_3hat_1.addLabelToNode(a, 0);
                R_3hat_1.addLabelToNode(b, 1);
                R_3hat_1.addLabelToNode(node, 2);
                toGlue.push_back(&R_3hat_1);
                
                BaseRegion R_3hat_2 = it_3hat_2->second;
                R_3hat_2.addLabelToNode(a, 0);
                R_3hat_2.addLabelToNode(node, 1);
                R_3hat_2.addLabelToNode(e, 2);
                toGlue.push_back(&R_3hat_2);
                
                R.glue(toGlue);
                
                store_sign(R, signature_minimal);
            }
            
            
        }
    }
    
    // |S| = 0
    for (int dangling_n3 = 0; dangling_n3 <= 1; dangling_n3++) {
        for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
            for (int deg2_a_e = 0; deg2_a_e <= 1; deg2_a_e++) {
                
                for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                    for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                        
                        for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
                            for (int deg3_a_d_e = 0; deg3_a_d_e <= 1; deg3_a_d_e++) {
                                
                                
                                for (int deg3_a_c_d = 0; deg3_a_c_d <= 1; deg3_a_c_d++) {
                                    
                                    HatRegion R(5,a);
                                    
                                    for (int i = 0; i < dangling_n3; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_b; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, b);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_e; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, e);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_c; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, c);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_b_c; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, b);
                                        R.addEdge(node, c);
                                    }
                                    
                                    for (int i = 0; i < deg2_a_d; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, d);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_d_e; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, d);
                                        R.addEdge(node, e);
                                    }
                                    
                                    for (int i = 0; i < deg3_a_c_d; i++) {
                                        int node = R.addNode();
                                        R.addEdge(node, a);
                                        R.addEdge(node, c);
                                        R.addEdge(node, d);
                                    }
                                    
                                    store_sign(R, signature_minimal);
                                    
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    // |S| > 0, s connected to c or d (symmetric), or a is as good
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b = regions_4hat_b.begin(); it_4hat_b != regions_4hat_b.end(); ++it_4hat_b) {
        for (map<vector<int>,BaseRegion>::const_iterator it_5hat_b = regions_5hat_b.begin(); it_5hat_b != regions_5hat_b.end(); ++it_5hat_b) {
            HatRegion R(5, a);
            int s = R.addNode();
            R.addEdge(a, s);
            R.addEdge(c, s);
            
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(e, e);
            R.addLabelToNode(s, s);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_4hat_b = it_4hat_b->second;
            R_4hat_b.addLabelToNode(s, 0);
            R_4hat_b.addLabelToNode(a, 1);
            R_4hat_b.addLabelToNode(b, 2);
            R_4hat_b.addLabelToNode(c, 3);
            toGlue.push_back(&R_4hat_b);
            
            BaseRegion R_5hat_b = it_5hat_b->second;
            R_5hat_b.addLabelToNode(a, 0);
            R_5hat_b.addLabelToNode(s, 1);
            R_5hat_b.addLabelToNode(c, 2);
            R_5hat_b.addLabelToNode(d, 3);
            R_5hat_b.addLabelToNode(e, 4);
            toGlue.push_back(&R_5hat_b);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    cout << "done with 4hat_regions." << endl;
}

void old_generate_5hat_regions(std::map<std::vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_5hat_a, std::map<std::vector<int>,BaseRegion> &regions_4hat_a,std::map<std::vector<int>,BaseRegion> &regions_4hat, std::map<std::vector<int>,BaseRegion> &regions_3hat){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    
    for (int s_empty = 0; s_empty <= 1; s_empty++) {
        if(s_empty){
            { // a-c edge
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
                    
                    R.glue(&R_4hat);
                    
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
                    
                    R.glue(&R_3hat);
                    
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
                        
                        std::vector<BaseRegion*> toGLue;
                        
                        BaseRegion R_3hat = it_3hat->second;
                        R_3hat.clearLabels();
                        R_3hat.addLabelToNode(0, v);
                        R_3hat.addLabelToNode(1, a);
                        R_3hat.addLabelToNode(2, b);
                        toGLue.push_back(&R_3hat);
                        
                        BaseRegion R_4hat = it_4hat->second;
                        R_4hat.clearLabels();
                        R_4hat.addLabelToNode(0, v);
                        R_4hat.addLabelToNode(2, a);
                        R_4hat.addLabelToNode(3, b);
                        R_4hat.addLabelToNode(4, c);
                        toGLue.push_back(&R_4hat);
                        
                        R.glue(toGLue);
                        
                        counter++;
                        store_sign(R, signature_minimal);
                    }
                    
                }
            }
            
            // No cross edge
            for (int va_nodes = 0; va_nodes <= 2; va_nodes++) {
                for (int vb_nodes = 0; vb_nodes <= 4; vb_nodes++) {
                    for (int vc_nodes = 0; vc_nodes <= 4; vc_nodes++) {
                        for (int vd_nodes = 0; vd_nodes <= 2; vd_nodes++) {
                            int max_vb_a_edge = vb_nodes > 0 ? 1 : 0;
                            for(int vb_a_edge = 0; vb_a_edge <= max_vb_a_edge; vb_a_edge++){
                                int max_vb_c_edge = vb_nodes > 0 ? 1 : 0;
                                for(int vb_c_edge = 0; vb_c_edge <= max_vb_c_edge; vb_c_edge++){
                                    int max_vb_d_edge = vb_nodes > 0 && vc_nodes == 0 ? 1 : 0;
                                    for(int vb_d_edge = 0; vb_d_edge <= max_vb_d_edge; vb_d_edge++){
                                        int max_vc_d_edge = vc_nodes > 0 ? 1 : 0;
                                        for(int vc_d_edge = 0; vc_d_edge <= max_vc_d_edge; vc_d_edge++){
                                            int max_vc_b_edge = vc_nodes > 0 && !vb_c_edge ? 1 : 0;
                                            for(int vc_b_edge = 0; vc_b_edge <= max_vc_b_edge; vc_b_edge++){
                                                int max_vc_a_edge = vc_nodes > 0 && vb_nodes == 0 ? 1 : 0;
                                                for(int vc_a_edge = 0; vc_a_edge <= max_vc_a_edge; vc_a_edge++){
                                                    
                                                    int max_va_d_edge = va_nodes > 0 && vb_nodes == 0 && vc_nodes == 0 ? 1 : 0;
                                                    for(int va_d_edge = 0; va_d_edge <= max_va_d_edge; va_d_edge++){
                                                        int max_va_c_edge = va_nodes > 0 && vb_nodes == 0 && !vc_b_edge &&!vc_a_edge ? 1 : 0;
                                                        for(int va_c_edge = 0; va_c_edge <= max_va_c_edge; va_c_edge++){
                                                            
                                                            int max_vd_a_edge = vd_nodes > 0 && vc_nodes == 0 && vb_nodes == 0 && !va_c_edge && !va_d_edge ? 1 : 0;
                                                            for(int vd_a_edge = 0; vd_a_edge <= max_vd_a_edge; vd_a_edge++){
                                                                int max_vd_b_edge = vd_nodes > 0 && vc_nodes == 0 && !va_c_edge && !va_d_edge && !vb_d_edge && !vb_c_edge ? 1 : 0;
                                                                for(int vd_b_edge = 0; vd_b_edge <= max_vd_b_edge; vd_b_edge++){
                                                                    
                                                                    for (int deg1 = 0; deg1 <= 1; deg1++) {                                                                        
                                                                        HatRegion R(5,v);
                                                                        
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
                                                                        
                                                                        int vc1 = -1;
                                                                        int vc2 = -1;
                                                                        for (int i = 0; i < vc_nodes; i++) {
                                                                            int vc = R.addNode();
                                                                            if(vc1 == -1) vc1 = vc;
                                                                            vc2 = vc;
                                                                            R.addEdge(v, vc);
                                                                            R.addEdge(vc, c);
                                                                        }
                                                                        
                                                                        int vd = -1;
                                                                        for (int i = 0; i < vd_nodes; i++) {
                                                                            vd = R.addNode();
                                                                            R.addEdge(v, vd);
                                                                            R.addEdge(vd, d);
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
                                                                        
                                                                        if (deg1) {
                                                                            int node = R.addNode();
                                                                            R.addEdge(node, v);
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
        } else {
            std::map<std::vector<int>,BaseRegion>::iterator it_4hat_a;
            for (it_4hat_a = regions_4hat_a.begin(); it_4hat_a != regions_4hat_a.end(); it_4hat_a++) {
                std::map<std::vector<int>,BaseRegion>::iterator it_5hat_a;
                for (it_5hat_a = regions_5hat_a.begin(); it_5hat_a != regions_5hat_a.end(); it_5hat_a++) {
                    HatRegion R(5, v);
                    int s = R.addNode();
                    R.addEdge(v, s);
                    R.addEdge(s, b);
                    
                    BaseRegion R_4hat_a = it_4hat_a->second;
                    BaseRegion R_5hat_a = it_5hat_a->second;
                    std::vector<BaseRegion*> toGLue;
                    
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
                    toGLue.push_back(&R_4hat_a);
                    
                    R_5hat_a.addLabelToNode(0, v);
                    R_5hat_a.addLabelToNode(5, a);
                    R_5hat_a.addLabelToNode(2, b);
                    R_5hat_a.addLabelToNode(3, c);
                    R_5hat_a.addLabelToNode(4, d);
                    toGLue.push_back(&R_5hat_a);
                    
                    R.glue(toGLue);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
            
        }
    }
    
    std::cout << "done with 5hat_regions. Total regions checked: " << counter << std::endl;
}

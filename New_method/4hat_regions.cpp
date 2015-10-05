#include <vector>
#include <iostream>
using namespace std;

#include "store_sign.h"
#include "HatRegion.h"
#include "4hat_regions.h"

// FINDS TOO FEW
void generate_4hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            for(int deg2_v_a = 0; deg2_v_a <= 1; deg2_v_a++){
                for(int deg2_v_c = 0; deg2_v_c <= 1; deg2_v_c++){
                    for(int deg3_v_a_b = 0; deg3_v_a_b <= 1; deg3_v_a_b++){
                        for(int deg3_v_b_c = 0; deg3_v_b_c <= 1; deg3_v_b_c++){
                            for(int deg2_v_b = 0; deg2_v_b <= 2; deg2_v_b++){
                                int max_deg3_v_a_c = deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg2_v_b > 0 ? 0 : 1;
                                for(int deg3_v_a_c = 0; deg3_v_a_c <= max_deg3_v_a_c; deg3_v_a_c++){
                                    int max_deg4 = deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg2_v_b > 0 ||deg3_v_a_c > 0 ? 0 : 1;
                                    for(int deg4 = 0; deg4 <= max_deg4; deg4++){
                                        
                                        int max_v_b_edge = deg3_v_a_c > 0 || deg4 > 0 ? 0 : 1;
                                        for(int v_b_edge = 0; v_b_edge <= max_v_b_edge; v_b_edge++){
                                            
                                            int max_a_c_edge = deg2_v_b > 0 || deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg4 > 0 || v_b_edge > 0 ? 0 : 1;
                                            for(int a_c_edge = 0; a_c_edge <= max_a_c_edge; a_c_edge++){
                                                
                                                HatRegion R(4, v);
                                                for (int i = 0; i < deg2_v_a; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                }
                                                for (int i = 0; i < deg2_v_c; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, c);
                                                }
                                                for (int i = 0; i < deg3_v_a_b; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, b);
                                                }
                                                for (int i = 0; i < deg3_v_b_c; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, b);
                                                    R.addEdge(node, c);
                                                }
                                                
                                                for (int i = 0; i < deg2_v_b; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, b);
                                                }
                                                
                                                for(int i = 0; i < deg3_v_a_c; i++){
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, c);
                                                }
                                                for (int i = 0; i < deg4; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, b);
                                                    R.addEdge(node, c);
                                                }
                                                
                                                if(v_b_edge){
                                                    R.addEdge(v, b);
                                                }
                                                if(a_c_edge){
                                                    R.addEdge(a, c);
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
        } else if (s_size == 1){
            for(int over = 0; over <= 1; over++){
                for(int under = 0; under <= 1; under++){
                    int start_over_edges = over == 0 ? 0b00 : 0b01;
                    int end_over_edges = over == 0 ? 0b00 : 0b11;
                    for(int over_edges = start_over_edges; over_edges <= end_over_edges; over_edges++){
                        int start_under_edges = under == 0 ? 0b00 : 0b01;
                        int end_under_edges = under == 0 ? 0b00 : 0b11;
                        for(int under_edges = start_under_edges; under_edges <= end_under_edges; under_edges++){
                            int start_s_up_edge = 0;
                            int end_s_up_edge = (over_edges & 0b01) == 0 ? 1 : 0;
                            for (int s_up_edge = start_s_up_edge; s_up_edge <= end_s_up_edge; s_up_edge++) {
                                int start_s_down_edge = 0;
                                int end_s_down_edge = (under_edges & 0b01) == 0 ? 1 : 0;
                                for (int s_down_edge = start_s_down_edge; s_down_edge <= end_s_down_edge; s_down_edge++) {
                                    
                                    for(int deg2 = 0; deg2 <= 1; deg2++){
                                        HatRegion R(4, v);
                                        
                                        int s = R.addNode();
                                        R.addEdge(s, v);
                                        R.addEdge(s, b);
                                        
                                        for(int i = 0; i < over; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(s, u);
                                            if( (over_edges & 0b10) != 0 ){
                                                R.addEdge(u, a);
                                            }
                                            if( (over_edges & 0b01) != 0 ){
                                                R.addEdge(u, b);
                                            }
                                        }
                                        
                                        for(int i = 0; i < under; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(s, u);
                                            if( (under_edges & 0b10) != 0 ){
                                                R.addEdge(u, c);
                                            }
                                            if( (under_edges & 0b01) != 0 ){
                                                R.addEdge(u, b);
                                            }
                                        }
                                        
                                        if(s_up_edge){
                                            R.addEdge(s, a);
                                        }
                                        if(s_down_edge){
                                            R.addEdge(s, c);
                                        
                                        }
                                        
                                        if(deg2){
                                            int node = R.addNode();
                                            R.addEdge(node, s);
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
        } else if (s_size == 2){
            for(int deg3 = 0; deg3 <= 1; deg3++){
                for(int va_node = 0; va_node <= 2; va_node++){
                    HatRegion R(4, v);
                    int s1 = R.addNode();
                    int s2 = R.addNode();
                    R.addEdge(v, s1);
                    R.addEdge(v, s2);
                    R.addEdge(b, s1);
                    R.addEdge(b, s2);
                    R.addEdge(s1, s2);
                    if(deg3){
                        int node = R.addNode();
                        R.addEdge(node, v);
                        R.addEdge(node, s1);
                        R.addEdge(node, s2);
                    }
                    for (int i = 0; i < va_node; i++) {
                        int va = R.addNode();
                        R.addEdge(v, va);
                        R.addEdge(va, a);
                    }
                    counter++;
                    store_sign(R, signature_minimal);
                }
                
            }
            
        }
    }
    
    cout << "done with 4hat_regions. Total regions checked: " << counter << endl;
}

void generate_4hat_regions_new(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_4hat_a){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            
            for(int deg2_v_a = 0; deg2_v_a <= 1; deg2_v_a++){
                for(int deg2_v_c = 0; deg2_v_c <= 1; deg2_v_c++){
                    for(int deg3_v_a_b = 0; deg3_v_a_b <= 1; deg3_v_a_b++){
                        for(int deg3_v_b_c = 0; deg3_v_b_c <= 1; deg3_v_b_c++){
                            for(int deg2_v_b = 0; deg2_v_b <= 2; deg2_v_b++){
                                int max_deg3_v_a_c = deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg2_v_b > 0 ? 0 : 1;
                                for(int deg3_v_a_c = 0; deg3_v_a_c <= max_deg3_v_a_c; deg3_v_a_c++){
                                    int max_deg4 = deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg2_v_b > 0 ||deg3_v_a_c > 0 ? 0 : 1;
                                    for(int deg4 = 0; deg4 <= max_deg4; deg4++){
                                        
                                        int max_v_b_edge = deg3_v_a_c > 0 || deg4 > 0 ? 0 : 1;
                                        for(int v_b_edge = 0; v_b_edge <= max_v_b_edge; v_b_edge++){
                                            
                                            int max_a_c_edge = deg2_v_b > 0 || deg3_v_a_b > 0 || deg3_v_b_c > 0 || deg4 > 0 || v_b_edge > 0 ? 0 : 1;
                                            for(int a_c_edge = 0; a_c_edge <= max_a_c_edge; a_c_edge++){
                                                
                                                for (int deg1 = 0; deg1 <= 1; deg1++) {
                                                    HatRegion R(4, v);
                                                    for (int i = 0; i < deg2_v_a; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, a);
                                                    }
                                                    for (int i = 0; i < deg2_v_c; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, c);
                                                    }
                                                    for (int i = 0; i < deg3_v_a_b; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, a);
                                                        R.addEdge(node, b);
                                                    }
                                                    for (int i = 0; i < deg3_v_b_c; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, b);
                                                        R.addEdge(node, c);
                                                    }
                                                    
                                                    for (int i = 0; i < deg2_v_b; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, b);
                                                    }
                                                    
                                                    for(int i = 0; i < deg3_v_a_c; i++){
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, a);
                                                        R.addEdge(node, c);
                                                    }
                                                    for (int i = 0; i < deg4; i++) {
                                                        int node = R.addNode();
                                                        R.addEdge(node, v);
                                                        R.addEdge(node, a);
                                                        R.addEdge(node, b);
                                                        R.addEdge(node, c);
                                                    }
                                                    
                                                    if(v_b_edge){
                                                        R.addEdge(v, b);
                                                    }
                                                    if(a_c_edge){
                                                        R.addEdge(a, c);
                                                    }
                                                    
                                                    if(deg1){
                                                        int node = R.addNode();
                                                        R.addEdge(v, node);
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
        } else if (s_size == 1){
            
            for (std::map<std::vector<int>,BaseRegion>::const_iterator it_4a_over = regions_4hat_a.begin(); it_4a_over != regions_4hat_a.end(); it_4a_over++) {
                for (std::map<std::vector<int>,BaseRegion>::const_iterator it_4a_under = regions_4hat_a.begin(); it_4a_under != regions_4hat_a.end(); it_4a_under++) {
                    HatRegion R(4, v);
                    int s = R.addNode();
                    R.addEdge(v, s);
                    R.addEdge(b, s);
                    
                    BaseRegion over = it_4a_over->second;
                    BaseRegion under = it_4a_under->second;
                    over.addLabelToNode(0, v);
                    over.addLabelToNode(1, a);
                    over.addLabelToNode(2, b);
                    over.addLabelToNode(3, c);
                    
                    under.addLabelToNode(0, v);
                    under.addLabelToNode(1, a);
                    under.addLabelToNode(2, b);
                    under.addLabelToNode(4, c);
                    
                    R.addLabelToNode(0, v);
                    R.addLabelToNode(1, s);
                    R.addLabelToNode(2, b);
                    R.addLabelToNode(3, a);
                    R.addLabelToNode(4, c);
                    
                    R.glue(over);
                    R.glue(under);
                    
                    counter++;
                    store_sign(R, signature_minimal);
                    
                }
            }
        } else if (s_size == 2){
            for(int deg3 = 0; deg3 <= 1; deg3++){
                for(int va_node = 0; va_node <= 2; va_node++){
                    HatRegion R(4, v);
                    int s1 = R.addNode();
                    int s2 = R.addNode();
                    R.addEdge(v, s1);
                    R.addEdge(v, s2);
                    R.addEdge(b, s1);
                    R.addEdge(b, s2);
                    R.addEdge(s1, s2);
                    if(deg3){
                        int node = R.addNode();
                        R.addEdge(node, v);
                        R.addEdge(node, s1);
                        R.addEdge(node, s2);
                    }
                    for (int i = 0; i < va_node; i++) {
                        int va = R.addNode();
                        R.addEdge(v, va);
                        R.addEdge(va, a);
                    }
                    counter++;
                    int before = signature_minimal.size();
                    store_sign(R, signature_minimal);
                    if (signature_minimal.size() > before) {
                        R.printRegion();
                         exit(0);
                    } // TODO: This caso should be unecessary
                }
                
            }
            
        }
    }
    
    cout << "done with 4hat_regions. Total regions checked: " << counter << endl;
}
#include <iostream>
#include <vector>
using namespace std;

#include "HatABCRegion.h"
#include "store_sign.h"
#include "4hat_ab_regions.h"


// THIS GENERATES TOO FEW!!
void generate_4hat_ab_regions(std::map<vector<int>, BaseRegion> &signature_minimal){
    cout << "in generate_4hat_ab_regions" << endl;
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 3;
    int c = 2;
    
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(a);
    boundaryDominators.push_back(c); // TODO: Change b and c
    
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            for(int node_va = 0; node_va <= 1; node_va++){
                for(int node_vac = 0; node_vac <= 1; node_vac++){
                    int max_node_vacb = node_vac > 0 ? 0:1;
                    for(int node_vacb = 0; node_vacb <= max_node_vacb; node_vacb++){
                        int max_node_vc = node_vacb > 0 ? 0 : 2;
                        for(int node_vc = 0; node_vc <= max_node_vc; node_vc++){
                            int max_node_vbc = node_vacb > 0 ? 0 : 1;
                            for(int node_vbc = 0; node_vbc <= max_node_vbc; node_vbc++){
                                int max_edge_vc = node_vacb > 0 ? 0: 1;
                                for(int edge_vc = 0; edge_vc <= max_edge_vc; edge_vc++){
                                    int max_edge_ab = node_vac > 0 || node_vc > 0 || node_vbc > 0 || node_vacb > 0 || edge_vc > 0 ? 0 : 1;
                                    for(int edge_ab = 0; edge_ab <= max_edge_ab; edge_ab++){
                                        HatABCRegion R(4, v, boundaryDominators);
                                        
                                        if(node_va){
                                            int node = R.addNode();
                                            R.addEdge(v, node);
                                            R.addEdge(node, a);
                                        }
                                        if(node_vac){
                                            int node = R.addNode();
                                            R.addEdge(v, node);
                                            R.addEdge(node, a);
                                            R.addEdge(node, c);
                                        }
                                        if(node_vacb){
                                            int node = R.addNode();
                                            R.addEdge(v, node);
                                            R.addEdge(node, a);
                                            R.addEdge(node, c);
                                            R.addEdge(node, b);
                                        }
                                        
                                        for(int i = 0; i < node_vc; i++){
                                            int node = R.addNode();
                                            R.addEdge(v, node);
                                            R.addEdge(node, c);
                                        }
                                        if(node_vbc){
                                            int node = R.addNode();
                                            R.addEdge(v, node);
                                            R.addEdge(node, b);
                                            R.addEdge(node, c);
                                        }
                                        if(edge_vc){
                                            R.addEdge(v, c);
                                        }
                                        if(edge_ab){
                                            R.addEdge(a, b);
                                        }
                                        
                                        counter++;
                                        int before = signature_minimal.size();
                                        store_sign(R, signature_minimal);
                                        if (signature_minimal.size() > before) {
                                            R.printRegion();
                                           // exit(0);
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
                        int end_under_edge = under == 0 ? 0 : 1;
                        for(int under_edge = 0; under_edge <= end_under_edge; under_edge++){
                            int start_s_up_edge = 0;
                            int end_s_up_edge = (over_edges & 0b01) == 0 ? 1 : 0;
                            for (int s_up_edge = start_s_up_edge; s_up_edge <= end_s_up_edge; s_up_edge++) {
                                int start_s_down_edge = 0;
                                int end_s_down_edge = under == 0 ? 1 : 0;
                                for (int s_down_edge = start_s_down_edge; s_down_edge <= end_s_down_edge; s_down_edge++) {
                                    
                                    int max_edge_vc = (s_down_edge || under_edge != 0) && (s_up_edge || (over_edges & 0b10) != 0) ? 0 : 1;
                                    for(int edge_vc = 0; edge_vc <= max_edge_vc; edge_vc++){
                                        HatABCRegion R(4, v, boundaryDominators);
                                        
                                        int s = R.addNode();
                                        R.addEdge(s, v);
                                        R.addEdge(s, c);
                                        
                                        for(int i = 0; i < over; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(s, u);
                                            if( (over_edges & 0b10) != 0 ){
                                                R.addEdge(u, a);
                                            }
                                            if( (over_edges & 0b01) != 0 ){
                                                R.addEdge(u, c);
                                            }
                                        }
                                        
                                        for(int i = 0; i < under; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(c, u);
                                            R.addEdge(s, u);
                                            if( under_edge  ){
                                                R.addEdge(u, b);
                                            }
                                        }
                                        
                                        if(s_up_edge){
                                            R.addEdge(s, a);
                                        }
                                        if(s_down_edge){
                                            R.addEdge(s, b);
                                            
                                        }
                                        
                                        if(edge_vc){
                                            R.addEdge(v, c);
                                        }
                                        
                                        counter++;
                                        int before = signature_minimal.size();
                                        store_sign(R, signature_minimal);
                                        if (signature_minimal.size() > before) {
                                            R.printRegion();
                                            // exit(0);
                                        }
                                    }
                                    
                                    
                                }
                            }
                        }
                    }
                }
            }
        } else if (s_size == 2){
            for(int s_up_edge = 0; s_up_edge <= 1; s_up_edge++){
                for(int s_down_edge = 0; s_down_edge <= 1; s_down_edge++){
                    HatABCRegion R(4, v, boundaryDominators);
                    int s1 = R.addNode();
                    int s2 = R.addNode();
                    R.addEdge(v, s1);
                    R.addEdge(v, s2);
                    R.addEdge(c, s1);
                    R.addEdge(c, s2);
                    R.addEdge(s1, s2);
                    if(s_up_edge){
                        R.addEdge(s1, a);
                    }
                    if(s_down_edge){
                        R.addEdge(s2, b);
                    }
                    
                    counter++;
                    int before = signature_minimal.size();
                    store_sign(R, signature_minimal);
                    if (signature_minimal.size() > before) {
                        R.printRegion();
                        // exit(0);
                    }
                }
            }
        }
    }
    
    cout << "done with 4ab_regions. Total regions checked: " << counter << endl;
}

void generate_4hat_ab_regions_new(std::map<vector<int>, BaseRegion> &signature_minimal, std::map<std::vector<int>,BaseRegion> &regions_4hat_a, std::map<std::vector<int>,BaseRegion> &regions_4hat_b){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    
    for (std::map<std::vector<int>,BaseRegion>::const_iterator it_4a = regions_4hat_a.begin(); it_4a != regions_4hat_a.end(); it_4a++) {
        counter++;
        BaseRegion R = it_4a->second;
        store_sign(R, signature_minimal);
    }
    
    for (std::map<std::vector<int>,BaseRegion>::const_iterator it_4b = regions_4hat_b.begin(); it_4b != regions_4hat_b.end(); it_4b++) {
        counter++;
        BaseRegion R = it_4b->second;
        store_sign(R, signature_minimal);
    }
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(a);
    boundaryDominators.push_back(b);
    
    for (int s = 0; s <= 1; s++) {
        for (int mid = 0; mid <= 1; mid++) {
            for (int down_edge = 0; down_edge <= 1; down_edge++) {
                int max_vb_edge = s && down_edge ? 0 : 1;
                for (int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++) {
                    HatABCRegion R(4, v, boundaryDominators);
                    int node_va = R.addNode();
                    R.addEdge(v, node_va);
                    R.addEdge(a, node_va);
                    
                    int node_vb = R.addNode();
                    R.addEdge(v, node_vb);
                    R.addEdge(b, node_vb);
                    
                    int node = -1;
                    if (mid) {
                        node = R.addNode();
                        R.addEdge(v, node);
                        R.addEdge(a, node);
                        R.addEdge(b, node);
                    }
                    
                    if (s) {
                        if (mid) {
                            R.addEdge(node, node_va);
                            R.addEdge(node, node_vb);
                        } else {
                            R.addEdge(node_va, node_vb);
                        }
                    }
                    
                    if (down_edge) {
                        R.addEdge(node_vb, c);
                    }
                    
                    if (vb_edge) {
                        R.addEdge(v, b);
                    }
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
        }
    }
    

    cout << "done with 4ab_regions. Total regions checked: " << counter << endl;
}
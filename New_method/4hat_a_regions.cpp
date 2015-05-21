#include <iostream>
#include <vector>
using namespace std;

#include "HatARegion.h"
#include "store_sign.h"
#include "4hat_a_regions.h"

void generate_4hat_a_regions(std::map<vector<int>, BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 3;
    int c = 2;
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
                                        HatARegion R(4, v, a, c);
                                        
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
                                        store_sign(R, signature_minimal);
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
                                        HatARegion R(4, v, a, c);
                                        
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
                                        store_sign(R, signature_minimal);
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
                    HatARegion R(4, v, a, c);
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
                    store_sign(R, signature_minimal);
                }
            }
        }
    }
    
    cout << "done with 4a_regions. Total regions checked: " << counter << endl;
}
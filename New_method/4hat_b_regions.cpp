#include <vector>
#include <iostream>
using namespace std;

#include "HatABCRegion.h"
#include "store_sign.h"
#include "4hat_b_regions.h"

void generate_4hat_b_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    int c = 3;
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(b);
    
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            for(int nodes_vb = 0; nodes_vb <= 4; nodes_vb++){
                int max_edges = nodes_vb == 0 ? 0b00: 0b11;
                for(int edges = 0b00; edges <= max_edges; edges++){
                    int max_ab_edge = nodes_vb > 0 ? 0 : 1;
                    for(int ac_edge = 0; ac_edge <= max_ab_edge; ac_edge++){
                        int max_vb_edge = (nodes_vb <= 1 && edges == 0b11) || ac_edge ? 0 : 1;
                        for(int vb_edge = 0; vb_edge <= max_vb_edge; vb_edge++){
                            HatABCRegion R(4, v, boundaryDominators);
                            
                            for(int i = 0; i < nodes_vb; i++){
                                int node = R.addNode();
                                R.addEdge(v, node);
                                R.addEdge(b, node);
                                if(i == 0 && (edges & 0b10) != 0){
                                    R.addEdge(node, a);
                                }
                                if(i == nodes_vb-1 && (edges & 0b01) != 0){
                                    R.addEdge(node, c);
                                }
                            }
                            
                            if(ac_edge){
                                R.addEdge(a, c);
                            }
                            if(vb_edge){
                                R.addEdge(v, b);
                            }
                            
                            counter++;
                            store_sign(R, signature_minimal);
                        }
                    }
                }
            }
        } else if (s_size == 1){
            for(int over = 0; over <= 1; over++){
                for(int under = 0; under <= 1; under++){
                    int end_over_edge = over == 0 ? 0 : 1;
                    for(int over_edge = 0; over_edge <= end_over_edge; over_edge++){
                        int end_under_edge = under == 0 ? 0 : 1;
                        for(int under_edge = 0; under_edge <= end_under_edge; under_edge++){
                            int start_s_up_edge = 0;
                            int end_s_up_edge = over == 0 ? 1 : 0;
                            for (int s_up_edge = start_s_up_edge; s_up_edge <= end_s_up_edge; s_up_edge++) {
                                int start_s_down_edge = 0;
                                int end_s_down_edge = under == 0 ? 1 : 0;
                                for (int s_down_edge = start_s_down_edge; s_down_edge <= end_s_down_edge; s_down_edge++) {
                                    
                                    int max_edge_vb = (s_down_edge || under_edge != 0) && (s_up_edge || over_edge != 0) ? 0 : 1;
                                    for(int edge_vb = 0; edge_vb <= max_edge_vb; edge_vb++){
                                        HatABCRegion R(4, v, boundaryDominators);
                                        
                                        int s = R.addNode();
                                        R.addEdge(s, v);
                                        R.addEdge(s, b);
                                        
                                        for(int i = 0; i < over; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(b, u);
                                            R.addEdge(s, u);
                                            if( over_edge ){
                                                R.addEdge(u, a);
                                            }
                                        }
                                        
                                        for(int i = 0; i < under; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(b, u);
                                            R.addEdge(s, u);
                                            if( under_edge  ){
                                                R.addEdge(u, c);
                                            }
                                        }
                                        
                                        if(s_up_edge){
                                            R.addEdge(s, a);
                                        }
                                        if(s_down_edge){
                                            R.addEdge(s, c);
                                            
                                        }
                                        
                                        if(edge_vb){
                                            R.addEdge(v, b);
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
                    HatABCRegion R(4, v, boundaryDominators);
                    
                    int s1 = R.addNode();
                    int s2 = R.addNode();
                    R.addEdge(v, s1);
                    R.addEdge(v, s2);
                    R.addEdge(b, s1);
                    R.addEdge(b, s2);
                    R.addEdge(s1, s2);
                    if(s_up_edge){
                        R.addEdge(s1, a);
                    }
                    if(s_down_edge){
                        R.addEdge(s2, c);
                    }
                    
                    counter++;
                    store_sign(R, signature_minimal);
                }
            }
        }
    }
    
    cout << "done with 4b_regions. Total regions checked: " << counter << endl;
}
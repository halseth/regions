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
    int b = 3;
    int c = 2;
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(c); // TODO: Should be b
    
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            for(int nodes_vc = 0; nodes_vc <= 4; nodes_vc++){
                int max_edges = nodes_vc == 0 ? 0b00: 0b11;
                for(int edges = 0b00; edges <= max_edges; edges++){
                    int max_ab_edge = nodes_vc > 0 ? 0 : 1;
                    for(int ab_edge = 0; ab_edge <= max_ab_edge; ab_edge++){
                        int max_vc_edge = edges == 0b11 || ab_edge ? 0 : 1;
                        for(int vc_edge = 0; vc_edge <= max_vc_edge; vc_edge++){
                            HatABCRegion R(4, v, boundaryDominators);
                            
                            for(int i = 0; i < nodes_vc; i++){
                                int node = R.addNode();
                                R.addEdge(v, node);
                                R.addEdge(c, node);
                                if(i == 0 && (edges & 0b10) != 0){
                                    R.addEdge(node, a);
                                }
                                if(i == nodes_vc-1 && (edges & 0b01) != 0){
                                    R.addEdge(node, b);
                                }
                            }
                            
                            if(ab_edge){
                                R.addEdge(a, b);
                            }
                            if(vc_edge){
                                R.addEdge(v, c);
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
                                    
                                    int max_edge_vc = (s_down_edge || under_edge != 0) && (s_up_edge || over_edge != 0) ? 0 : 1;
                                    for(int edge_vc = 0; edge_vc <= max_edge_vc; edge_vc++){
                                        HatABCRegion R(4, v, boundaryDominators);
                                        
                                        int s = R.addNode();
                                        R.addEdge(s, v);
                                        R.addEdge(s, c);
                                        
                                        for(int i = 0; i < over; i++){
                                            int u = R.addNode();
                                            R.addEdge(v, u);
                                            R.addEdge(c, u);
                                            R.addEdge(s, u);
                                            if( over_edge ){
                                                R.addEdge(u, a);
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
                    store_sign(R, signature_minimal);
                }
            }
        }
    }
    
    cout << "done with 4b_regions. Total regions checked: " << counter << endl;
}
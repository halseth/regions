#include "SmallRegion.h"
#include <vector>
using namespace std;

extern void store_sign(SmallRegion &R, std::map<vector<int>,SmallRegion > &signature_minimal);

void generate4regions(std::map<vector<int>,SmallRegion > &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 3;
    int c = 2;
    for(int s_size = 0; s_size <= 2; s_size++){
        if (s_size == 0) {
            for(int deg2_v_a = 0; deg2_v_a <= 1; deg2_v_a++){
                for(int deg2_v_b = 0; deg2_v_b <= 1; deg2_v_b++){
                    for(int deg3_v_a_c = 0; deg3_v_a_c <= 1; deg3_v_a_c++){
                        for(int deg3_v_b_c = 0; deg3_v_b_c <= 1; deg3_v_b_c++){
                            for(int deg2_v_c = 0; deg2_v_c <= 2; deg2_v_c++){
                                int max_deg3_v_a_b = deg3_v_a_c > 0 || deg3_v_b_c > 0 || deg2_v_c > 0 ? 0 : 1;
                                for(int deg3_v_a_b = 0; deg3_v_a_b <= max_deg3_v_a_b; deg3_v_a_b++){
                                    int max_deg4 = deg3_v_a_c > 0 || deg3_v_b_c > 0 || deg2_v_c > 0 ||deg3_v_a_b > 0 ? 0 : 1;
                                    for(int deg4 = 0; deg4 <= max_deg4; deg4++){
                                        
                                        int max_v_c_edge = deg3_v_a_b > 0 || deg4 > 0 ? 0 : 1;
                                        for(int v_c_edge = 0; v_c_edge <= max_v_c_edge; v_c_edge++){
                                            
                                            int max_a_b_edge = deg2_v_c > 0 || deg3_v_a_c > 0 || deg3_v_b_c > 0 || deg4 > 0 || v_c_edge > 0 ? 0 : 1;
                                            for(int a_b_edge = 0; a_b_edge <= max_a_b_edge; a_b_edge++){
                                                
                                                SmallRegion R(4,c,counter++);
                                                for (int i = 0; i < deg2_v_a; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                }
                                                for (int i = 0; i < deg2_v_b; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, b);
                                                }
                                                for (int i = 0; i < deg3_v_a_c; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, c);
                                                }
                                                for (int i = 0; i < deg3_v_b_c; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, b);
                                                    R.addEdge(node, c);
                                                }
                                                
                                                for (int i = 0; i < deg2_v_c; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, c);
                                                }
                                                
                                                for(int i = 0; i < deg3_v_a_b; i++){
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, b);
                                                }
                                                for (int i = 0; i < deg4; i++) {
                                                    int node = R.addNode();
                                                    R.addEdge(node, v);
                                                    R.addEdge(node, a);
                                                    R.addEdge(node, b);
                                                    R.addEdge(node, c);
                                                }
                                                
                                                if(v_c_edge){
                                                    R.addEdge(v, c);
                                                }
                                                if(a_b_edge){
                                                    R.addEdge(a, b);
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
                                        SmallRegion R(4,c,counter++);
                                        
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
                                            R.addEdge(s, u);
                                            if( (under_edges & 0b10) != 0 ){
                                                R.addEdge(u, b);
                                            }
                                            if( (under_edges & 0b01) != 0 ){
                                                R.addEdge(u, c);
                                            }
                                        }
                                        
                                        if(s_up_edge){
                                            R.addEdge(s, a);
                                        }
                                        if(s_down_edge){
                                            R.addEdge(s, b);
                                        
                                        }
                                        
                                        if(deg2){
                                            int node = R.addNode();
                                            R.addEdge(node, s);
                                            R.addEdge(node, v);
                                        }
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
                SmallRegion R(4,c,counter++);
                int s1 = R.addNode();
                int s2 = R.addNode();
                R.addEdge(v, s1);
                R.addEdge(v, s2);
                R.addEdge(c, s1);
                R.addEdge(c, s2);
                R.addEdge(s1, s2);
                if(deg3){
                    int node = R.addNode();
                    R.addEdge(node, v);
                    R.addEdge(node, s1);
                    R.addEdge(node, s2);
                }
                store_sign(R, signature_minimal);
            }
            
        }
    }
    
    cout << "done with 4regions. Total regions checked: " << counter << endl;
}
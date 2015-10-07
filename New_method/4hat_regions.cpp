#include <vector>
#include <iostream>
using namespace std;

#include "store_sign.h"
#include "HatRegion.h"
#include "4hat_regions.h"

void generate_4hat_regions(std::map<vector<int>,BaseRegion> &signature_minimal, std::map<vector<int>,BaseRegion> &regions_3hat, std::map<vector<int>,BaseRegion> &regions_4hat_b){
    cout << "in generate_4hat_regions" << endl;
    
    if(!signature_minimal.empty()){
        cerr << "signminimal not empty";
        exit(1);
    }
    
    if(regions_3hat.empty() || regions_4hat_b.empty()){
        cerr << "needed regions empty" << endl;
        exit(1);
    }
    
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    // S any size
    
    // a-c edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_1 = regions_3hat.begin(); it_3hat_1 != regions_3hat.end(); ++it_3hat_1) {
        for (map<vector<int>,BaseRegion>::const_iterator it_3hat_2 = regions_3hat.begin(); it_3hat_2 != regions_3hat.end(); ++it_3hat_2) {
            HatRegion R(4, a);
            R.addEdge(a, c);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_3hat_1 = it_3hat_1->second;
            R_3hat_1.addLabelToNode(a, 0);
            R_3hat_1.addLabelToNode(b, 1);
            R_3hat_1.addLabelToNode(c, 2);
            toGlue.push_back(&R_3hat_1);
            
            BaseRegion R_3hat_2 = it_3hat_2->second;
            R_3hat_2.addLabelToNode(a, 0);
            R_3hat_2.addLabelToNode(c, 1);
            R_3hat_2.addLabelToNode(d, 2);
            toGlue.push_back(&R_3hat_2);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    // b-d edge
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat = regions_3hat.begin(); it_3hat != regions_3hat.end(); ++it_3hat) {
        HatRegion R(4, a);
        R.addEdge(b, d);
        R.addLabelToNode(a, a);
        R.addLabelToNode(b, b);
        R.addLabelToNode(c, c);
        R.addLabelToNode(d, d);
        
        std::vector<BaseRegion*> toGlue;
        
        BaseRegion R_3hat = it_3hat->second;
        R_3hat.addLabelToNode(a, 0);
        R_3hat.addLabelToNode(b, 1);
        R_3hat.addLabelToNode(d, 2);
        toGlue.push_back(&R_3hat);
        
        R.glue(toGlue);
        
        store_sign(R, signature_minimal);
    }
    
    // b-d node
    for (map<vector<int>,BaseRegion>::const_iterator it_3hat_1 = regions_3hat.begin(); it_3hat_1 != regions_3hat.end(); ++it_3hat_1) {
        for (map<vector<int>,BaseRegion>::const_iterator it_3hat_2 = regions_3hat.begin(); it_3hat_2 != regions_3hat.end(); ++it_3hat_2) {
            HatRegion R(4, a);
            int node = R.addNode();
            R.addEdge(b, node);
            R.addEdge(node, d);
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
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
            R_3hat_2.addLabelToNode(d, 2);
            toGlue.push_back(&R_3hat_2);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    // |S| = 0
    for (int dangling_n3 = 0; dangling_n3 <= 1; dangling_n3++) {
        for (int deg2_a_b = 0; deg2_a_b <= 1; deg2_a_b++) {
            for (int deg2_a_d = 0; deg2_a_d <= 1; deg2_a_d++) {
                
                for (int deg2_a_c = 0; deg2_a_c <= 1; deg2_a_c++) {
                    for (int deg3_a_b_c = 0; deg3_a_b_c <= 1; deg3_a_b_c++) {
                        for (int deg3_a_c_d = 0; deg3_a_c_d <= 1; deg3_a_c_d++) {
                            
                            HatRegion R(4,a);
                            
                            for (int i = 0; i < dangling_n3; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                            }
                            
                            for (int i = 0; i < deg2_a_b; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                                R.addEdge(node, b);
                            }
                            
                            for (int i = 0; i < deg2_a_d; i++) {
                                int node = R.addNode();
                                R.addEdge(node, a);
                                R.addEdge(node, d);
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
    
    // |S| > 0, s connected to c, or a is as good
    for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b_1 = regions_4hat_b.begin(); it_4hat_b_1 != regions_4hat_b.end(); ++it_4hat_b_1) {
        for (map<vector<int>,BaseRegion>::const_iterator it_4hat_b_2 = regions_4hat_b.begin(); it_4hat_b_2 != regions_4hat_b.end(); ++it_4hat_b_2) {
            HatRegion R(4, a);
            int s = R.addNode();
            R.addEdge(a, s);
            R.addEdge(c, s);
            
            R.addLabelToNode(a, a);
            R.addLabelToNode(b, b);
            R.addLabelToNode(c, c);
            R.addLabelToNode(d, d);
            R.addLabelToNode(s, s);
            
            std::vector<BaseRegion*> toGlue;
            
            BaseRegion R_4hat_b_1 = it_4hat_b_1->second;
            R_4hat_b_1.addLabelToNode(s, 0);
            R_4hat_b_1.addLabelToNode(a, 1);
            R_4hat_b_1.addLabelToNode(b, 2);
            R_4hat_b_1.addLabelToNode(c, 3);
            toGlue.push_back(&R_4hat_b_1);
            
            BaseRegion R_4hat_b_2 = it_4hat_b_2->second;
            R_4hat_b_2.addLabelToNode(a, 0);
            R_4hat_b_2.addLabelToNode(s, 1);
            R_4hat_b_2.addLabelToNode(c, 2);
            R_4hat_b_2.addLabelToNode(d, 3);
            toGlue.push_back(&R_4hat_b_2);
            
            R.glue(toGlue);
            
            store_sign(R, signature_minimal);
            
        }
    }
    
    cout << "done with 4hat_regions." << endl;
}
#include <vector>
#include <iostream>
using namespace std;

#include "store_sign.h"
#include "HatABCRegion.h"
#include "3hat_ab_regions.h"

void generate_3hat_ab_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int v = 0;
    int a = 1;
    int b = 2;
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(a);
    boundaryDominators.push_back(b);
    
    for (int deg2_v_a = 0; deg2_v_a <= 1; deg2_v_a++) {
        for(int deg2_v_b = 0; deg2_v_b <= 1; deg2_v_b++){
            for (int deg_3 = 0; deg_3 <= 1; deg_3++) {
                HatABCRegion R(3, v, boundaryDominators);
                if(deg2_v_a){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, a);
                }
                if(deg2_v_b){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, b);
                }
                if(deg_3){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, a);
                    R.addEdge(c, b);
                }
                store_sign(R, signature_minimal);
            }
        }
    }
    
    cout << "done with 3ab_regions" << endl;
}
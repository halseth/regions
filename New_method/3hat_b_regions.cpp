#include <vector>
#include <iostream>
using namespace std;

#include "InnerHatABCRegion.hpp"
#include "store_sign.h"
#include "3hat_b_regions.h"

void generate_3hat_b_regions(std::map<vector<int>,BaseRegion> &signature_minimal){

    int a = 0;
    int b = 1;
    int c = 2;
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(b);
   
    for(int deg2 = 0; deg2 <= 1; deg2++){
        for(int deg3 = 0; deg3 <= 1; deg3++){
            InnerHatABCRegion R(3, a, boundaryDominators);
            if(deg2){
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(node, b);
            }
            if(deg3){
                int node = R.addNode();
                R.addEdge(a, node);
                R.addEdge(b, node);
                R.addEdge(c, node);
            }
            //store_sign(R, signature_minimal);
//            inner_region_store_sign(R, signature_minimal);
        }
    }
    
    cout << "done with 3b_regions" << endl;
}
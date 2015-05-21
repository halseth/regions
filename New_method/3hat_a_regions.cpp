#include <vector>
#include <iostream>
using namespace std;

#include "HatABCRegion.h"
#include "store_sign.h"
#include "3hat_a_regions.h"

void generate_3hat_a_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int v = 0;
    int a = 1;
    int b = 2;
    
    
    std::vector<int> boundaryDominators;
    boundaryDominators.push_back(a);
   
    for(int deg2 = 0; deg2 <= 1; deg2++){
        for(int deg3 = 0; deg3 <= 1; deg3++){
            HatABCRegion R(3, v, boundaryDominators);
            if(deg2){
                int c = R.addNode();
                R.addEdge(c, v);
                R.addEdge(c, a);
            }
            if(deg3){
                int c = R.addNode();
                R.addEdge(c, v);
                R.addEdge(c, a);
                R.addEdge(c, b);
            }
            store_sign(R, signature_minimal);
        }
    }
    
    cout << "done with 3a_regions" << endl;
}
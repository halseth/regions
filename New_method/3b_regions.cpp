#include <vector>
#include <iostream>
using namespace std;

#include "HatBRegion.h"
#include "store_sign.h"

void generate_3b_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    int v = 0;
    int a = 1;
    int b = 2;
   
    for(int deg2 = 0; deg2 <= 1; deg2++){
        for(int deg3 = 0; deg3 <= 1; deg3++){
            HatBRegion R(3, v, a);
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
    
    cout << "done with 3b_regions" << endl;
}
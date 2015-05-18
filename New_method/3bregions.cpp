#include "SmallRegion.h"
#include <vector>
using namespace std;

extern void store_sign(SmallRegion &R, std::map<vector<int>,SmallRegion > &signature_minimal);

void generate3bregions(std::map<vector<int>,SmallRegion > &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
   
    for(int deg2 = 0; deg2 <= 1; deg2++){
        for(int deg3 = 0; deg3 <= 1; deg3++){
            SmallRegion R(3,v,counter++);
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
    
    cout << "done with 3aregions" << endl;
}
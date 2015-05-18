#include "SmallRegion.h"
#include <vector>
using namespace std;

extern void store_sign(SmallRegion &R, std::map<vector<int>,SmallRegion > &signature_minimal);

void generateEmptyregions(std::map<vector<int>,SmallRegion > &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    
    SmallRegion R(2,1,0);
    
    store_sign(R, signature_minimal);
    
    cout << "done with empty regions" << endl;
}
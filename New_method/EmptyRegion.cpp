#include <vector>
#include <iostream>
using namespace std;

#include "BaseRegion.h"
#include "store_sign.h"
#include "EmptyRegion.h"

void generate_Empty_regions(std::map<vector<int>,BaseRegion> &signature_minimal){
    BaseRegion R(2);
    store_sign(R, signature_minimal);
    cout << "done with empty regions" << endl;
}
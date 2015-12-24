#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdlib.h>
#include "store_sign.h"
using namespace std;

void print_map(const std::map<vector<int>,BaseRegion > &map){
	std::map<vector<int>,BaseRegion >::const_iterator it;
    int big = 0;
	for(it = map.begin(); it != map.end(); it++){
		int small = it->second.getSize();
        if(small > big) big = small;
	}
    cout << "Biggest: " << big << endl;
}

void store_sign(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal){
    
    // Check if it is valid for it's subclass type
	if(!R.isValid()){
        cout << "not valid!" << endl;
#ifndef TEST
        R.printRegion();
		exit(0);
#endif
		return;
	}
    
    store_sign_if_valid(R, signature_minimal);
}


void store_sign_if_valid(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal){
    
    // Check if it is valid for it's subclass type
    if(!R.isValid()){
        return;
    }
    
    vector<int> sign;
    R.getSignature(sign);
    if(signature_minimal.count(sign) == 0 )
    {
        //cout << "Saving new signature because (signature_minimal.count(sign) == 0)" << endl;
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else if( signature_minimal.at(sign).getSize() > R.getSize() )
    {
        //cout << "Saving new signature because signature_minimal.at(sign).size() =" << signature_minimal.at(sign).size() << " and R.size()=" << R.size() << endl;
        signature_minimal.erase(sign);
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else
    {
        return;
    }
    
    cout << endl << endl << "Current found signatures ("<< signature_minimal.size() << ")." << endl;
//    print_map(signature_minimal);
}

bool contains_sign(std::map<std::vector<int>,BaseRegion> &regions, BaseRegion &region){
    vector<int> sign;
    region.getSignature(sign);
    if(regions.count(sign) == 0 )
    {
        return false;
    }
    return true;
}
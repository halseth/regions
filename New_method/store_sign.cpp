#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdlib.h>
#include "store_sign.h"
using namespace std;

int biggest = 0;


void print_map(const std::map<vector<int>,BaseRegion > &map){
	std::map<vector<int>,BaseRegion >::const_iterator it;
    int big = 0;
	for(it = map.begin(); it != map.end(); it++){
		
//		cout << "Sign: ";
//		for(int i = 0; i < it->first.size(); i++){
//			cout << it->first[i] << " ";
//		}
		int small = it->second.getSize();
        if(small > big) big = small;
//		cout << " Smallest: " << small << endl;
	}
    cout << "Biggest: " << big << endl;
}

// Flips dangling N3 vertices outside region by removing them
void flip_n3(BaseRegion &R){
    
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

void inner_region_store_sign(InnerRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal){
    
    // All possible subsets of boundary edges
    int boundary_size = R.getBoundarySize();
    
    int max_edges = (1 << boundary_size) - 1;
    for (int edges = 0; edges <= max_edges; edges++) {
        InnerRegion R2 = R;
        for(int i = 0; i < R2.getBoundarySize(); i++){
            if ((edges & (1 << i)) != 0) {
                R2.addEdge(i, (i+1)%R2.getBoundarySize());
            }
        }
        store_sign(R2, signature_minimal);
    }
}

void store_sign_if_valid(BaseRegion &R, std::map<std::vector<int>,BaseRegion> &signature_minimal){
    
    // Check if it is valid for it's subclass type
    if(!R.isValid()){
        return;
    }
    
    vector<int> sign;
    R.getSignature2(sign);
    if(signature_minimal.count(sign) == 0 )
    {
        //cout << "Saving new signature because (signature_minimal.count(sign) == 0)" << endl;
        if(R.getSize() > biggest) biggest = R.getSize();
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else if( signature_minimal.at(sign).getSize() > R.getSize() )
    {
        //cout << "Saving new signature because signature_minimal.at(sign).size() =" << signature_minimal.at(sign).size() << " and R.size()=" << R.size() << endl;
        if(R.getSize() > biggest) biggest = R.getSize();
        signature_minimal.erase(sign);
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else
    {
        return;
    }
    
    cout << endl << endl << "Current found signatures ("<< signature_minimal.size() << "). Biggest=" << biggest << endl;
    print_map(signature_minimal);
    
    cout << endl;
}

bool contains_sign(std::map<std::vector<int>,BaseRegion> &regions, BaseRegion &region){
    vector<int> sign;
    region.getSignature2(sign);
    if(regions.count(sign) == 0 )
    {
        return false;
    }
    return true;
}
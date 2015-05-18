#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include "SmallRegion.h"
#include <vector>
using namespace std;


void print_map(std::map<vector<int>,SmallRegion > *map){
	std::map<vector<int>,SmallRegion >::iterator it;
	for(it = map->begin(); it != map->end(); it++){
		
		cout << "Sign: ";
		for(int i = 0; i < it->first.size(); i++){
			cout << it->first[i] << " ";
		}
		int small = it->second.size();
		cout << " Smallest: " << small << endl;
	}
}

void store_sign(SmallRegion &R, std::map<vector<int>,SmallRegion > &signature_minimal){
	if(!R.isValid()){
        cout << "not valid!" << endl;
		exit(0);
		return;
	}
	
	vector<int> sign;			
	R.getSignature(sign);
	if(signature_minimal.count(sign) == 0 )
	{
		//cout << "Saving new signature because (signature_minimal.count(sign) == 0)" << endl;
		signature_minimal.insert(pair<vector<int>, SmallRegion>(sign, R));
	} 
	else if(signature_minimal.at(sign).size() > R.size())
	{
		//cout << "Saving new signature because signature_minimal.at(sign).size() =" << signature_minimal.at(sign).size() << " and R.size()=" << R.size() << endl;
		signature_minimal.erase(sign);
		signature_minimal.insert(pair<vector<int>, SmallRegion>(sign, R));
	}
	else 
	{
		return;
	}
	
	cout << endl << endl << "Current found signatures ("<< signature_minimal.size() << "):"<< endl;
	print_map(&signature_minimal);
	cout << endl;
}
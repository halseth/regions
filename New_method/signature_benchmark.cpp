//
//  signature_benchmark.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 09/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#include <sys/time.h>
#include <iostream>
#include <map>
using namespace std;

#include "signature_benchmark.hpp"
#include "enumerate_inner.hpp"
#include "store_sign.h"
#include "store_region_map.h"

void benchmark() {
    
    std::vector<BaseRegion> inner_regions;
    load_region_vector(inner_regions, "inner_4regions.txt");
    
    
    map<vector<int>, BaseRegion> signatures;
    
    timeval time;
    gettimeofday(&time, NULL);
    long startmillis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    
    for(int i = 0; i < inner_regions.size(); i++){
        BaseRegion R = inner_regions[i];
//        store_sign_if_valid(R, signatures);
    }
    gettimeofday(&time, NULL);
    long endmillis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    long elapsed1 = endmillis - startmillis;
    int num = signatures.size();
    signatures.clear();
    
    gettimeofday(&time, NULL);
    startmillis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    
    
    for(int i = 0; i < inner_regions.size(); i++){
        BaseRegion R = inner_regions[i];
//        store_sign_if_valid3(R, signatures);
    }
    gettimeofday(&time, NULL);
    endmillis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    long elapsed2 = endmillis - startmillis;
    int num2 = signatures.size();
    
    
    cout <<"Old build Elapsed: " << elapsed1 << " ms. Num signs: " << num << endl;
    cout <<"New build Elapsed: " << elapsed2 << " ms. Num signs: " << num2 << endl;
}

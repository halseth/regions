//
//  store_region_map.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "store_region_map.h"
#include "store_sign.h"

void store_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename){
    std::ofstream file;
    file.open(filename.c_str());
    
    if (!file.is_open()) {
        std::cerr << "ERROR opening file " << filename << std::endl;
        exit(0);
    } else {
        std::map<std::vector<int>,BaseRegion>::iterator it;
        for(it = map.begin(); it != map.end(); ++it){
            std::string str_rep = it->second.toString();
            file << str_rep << std::endl;
        }
        file.close();
        std::cout << "Done storing to file " << filename << std::endl;
    }
    
}

std::vector<BaseRegion> toVector(std::map<std::vector<int>,BaseRegion> &map){
    std::vector<BaseRegion> vec;
    std::map<std::vector<int>,BaseRegion>::iterator it;
    for(it = map.begin(); it != map.end(); ++it){
        vec.push_back(it->second);
    }
    return vec;
}

void store_region_vector(std::vector<BaseRegion> vec, std::string filename){
    std::ofstream file;
    file.open(filename.c_str());
    
    if (!file.is_open()) {
        std::cerr << "ERROR opening file " << filename << std::endl;
        exit(0);
    } else {
        std::vector<BaseRegion>::iterator it;
        for(it = vec.begin(); it != vec.end(); ++it){
            std::string str_rep = it->toString();
            file << str_rep << std::endl;
        }
        file.close();
        std::cout << "Done storing to file " << filename << std::endl;
    }
}


void load_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename){
    std::cout << "loading map from file " << filename << std::endl;
    std::ifstream file;
    file.open(filename.c_str());
    map.clear();
    
    if (!file.is_open()) {
        std::cerr << "ERROR opening file " << filename << std::endl;
        exit(1);
    } else {
        std::string line;
        int ll = 0;
        while (getline(file, line)) {
            //std::cout << "line; " << line << std::endl;
            BaseRegion R(line);
            store_sign(R, map);
            ll++;
            if(ll%100 == 0) std::cout << "done with line " << ll << std::endl;
        }
        std::cout << "Done loading from file " << filename << std::endl;
    }
}

void load_region_vector(std::vector<BaseRegion> &vec, std::string filename){
    std::cout << "loading vector from file " << filename << std::endl;
    std::ifstream file;
    file.open(filename.c_str());
    vec.clear();
    
    if (!file.is_open()) {
        std::cerr << "ERROR opening file " << filename << std::endl;
        exit(1);
    } else {
        std::string line;
        int ll = 0;
        while (getline(file, line)) {
            //std::cout << "line; " << line << std::endl;
            BaseRegion R(line);
            vec.push_back(R);
            ll++;
            if(ll%100 == 0) std::cout << "done with line " << ll << std::endl;
        }
        std::cout << "Done loading from file " << filename << std::endl;
    }
}
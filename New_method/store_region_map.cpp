//
//  store_region_map.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 26/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <fstream>
#include <iostream>
#include "store_region_map.h"
#include "store_sign.h"

void store_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename){
    std::ofstream file;
    file.open(filename);
    
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


void load_region_map(std::map<std::vector<int>,BaseRegion> &map, std::string filename){
    std::cout << "loading map from file " << filename << std::endl;
    std::ifstream file;
    file.open(filename);
    map.clear();
    
    if (!file.is_open()) {
        std::cerr << "ERROR opening file " << filename << std::endl;
    } else {
        std::string line;
        while (getline(file, line)) {
            //std::cout << "line; " << line << std::endl;
            BaseRegion R(line);
            store_sign(R, map);
        }
        std::cout << "Done loading from file " << filename << std::endl;
    }
}
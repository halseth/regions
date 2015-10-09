//
//  main.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 07/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

#include "BaseRegion.h"

#include "3hat_b_regions.h"
#include "3_regions.hpp"
#include "3hat_regions.h"
#include "4hat_b_regions.h"
#include "4hat_regions.h"
#include "4star_regions.hpp"
#include "4_regions.hpp"
#include "5hat_b_regions.h"
#include "5hat_regions.h"
#include "5_regions.hpp"
#include "6hat_b_regions.h"
#include "6hat_regions.h"
#include "6_regions.hpp"

#include "store_region_map.h"
#include "store_sign.h"

#define FILENAME_3HAT_B "regions_3hat_b.txt"
map<vector<int>, BaseRegion> regions_3hat_b;

#define OLD_FILENAME_3HAT_B "old_regions_3hat_b.txt"
map<vector<int>, BaseRegion> old_regions_3hat_b;

#define FILENAME_3HAT "regions_3hat.txt"
map<vector<int>, BaseRegion> regions_3hat;

#define OLD_FILENAME_3HAT "old_regions_3hat.txt"
map<vector<int>, BaseRegion> old_regions_3hat;

#define FILENAME_3 "regions_3.txt"
map<vector<int>, BaseRegion> regions_3;

#define FILENAME_4HAT_B "regions_4hat_b.txt"
map<vector<int>, BaseRegion> regions_4hat_b;
#define OLD_FILENAME_4HAT_B "old_regions_4hat_b.txt"
map<vector<int>, BaseRegion> old_regions_4hat_b;


#define FILENAME_4HAT_AB "regions_4hat_ab.txt"
map<vector<int>, BaseRegion> regions_4hat_ab;

#define OLD_FILENAME_4HAT "old_regions_4hat.txt"
map<vector<int>, BaseRegion> old_regions_4hat;

#define FILENAME_4HAT "regions_4hat.txt"
map<vector<int>, BaseRegion> regions_4hat;

#define FILENAME_4star "regions_4star.txt"
map<vector<int>, BaseRegion> regions_4star;
#define FILENAME_4 "regions_4.txt"
map<vector<int>, BaseRegion> regions_4;

#define OLD_FILENAME_5HAT_B "old_regions_5hat_b.txt"
map<vector<int>, BaseRegion> old_regions_5hat_b;

#define FILENAME_5HAT_B "regions_5hat_b.txt"
map<vector<int>, BaseRegion> regions_5hat_b;


#define OLD_FILENAME_5HAT "old_regions_5hat.txt"
map<vector<int>, BaseRegion> old_regions_5hat;
#define FILENAME_5HAT "regions_5hat.txt"
map<vector<int>, BaseRegion> regions_5hat;
#define FILENAME_5 "regions_5.txt"
map<vector<int>, BaseRegion> regions_5;

#define OLD_FILENAME_6HAT_B "old_regions_6hat_b.txt"
map<vector<int>, BaseRegion> old_regions_6hat_b;
#define FILENAME_6HAT_B "regions_6hat_b.txt"
map<vector<int>, BaseRegion> regions_6hat_b;


#define OLD_FILENAME_6HAT "old_regions_6hat.txt"
map<vector<int>, BaseRegion> old_regions_6hat;
#define FILENAME_6HAT "regions_6hat.txt"
map<vector<int>, BaseRegion> regions_6hat;

#define FILENAME_6 "regions_6.txt"
map<vector<int>, BaseRegion> regions_6;

 
int main(){
    
    bool load_old_files = false;
    bool load_from_file = true;
    bool save_to_file = true;
    
    if (load_old_files) load_region_map(old_regions_3hat_b, OLD_FILENAME_3HAT_B);
    if (load_from_file) load_region_map(regions_3hat_b, FILENAME_3HAT_B);
    if(regions_3hat_b.empty()){
        generate_3hat_b_regions(regions_3hat_b);
        if (save_to_file) store_region_map(regions_3hat_b, FILENAME_3HAT_B);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_3hat_b.begin() ; it != old_regions_3hat_b.end(); it++){
        BaseRegion old = it->second;
       
        if (!contains_sign(regions_3hat_b, old)) {
            cout << "old had more" << endl;
            exit(1);
        }
    }
    
    if (load_old_files) load_region_map(old_regions_3hat, OLD_FILENAME_3HAT);
    if (load_from_file) load_region_map(regions_3hat, FILENAME_3HAT);
    if (regions_3hat.empty()) {
        generate_3hat_regions(regions_3hat);
        if (save_to_file) store_region_map(regions_3hat, FILENAME_3HAT);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_3hat.begin() ; it != old_regions_3hat.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_3hat, old)) {
            cout << "old had more" << endl;
            exit(1);
        }
    }

    if (load_old_files) load_region_map(old_regions_4hat_b, OLD_FILENAME_4HAT_B);
    if (load_from_file) load_region_map(regions_4hat_b, FILENAME_4HAT_B);
    if (regions_4hat_b.empty()) {
        generate_4hat_b_regions(regions_4hat_b, regions_3hat_b);
        if (save_to_file) store_region_map(regions_4hat_b, FILENAME_4HAT_B);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_4hat_b.begin() ; it != old_regions_4hat_b.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_4hat_b, old)) {
            cout << "old 4hat had more" << endl;
            old.printRegion();
            exit(1);
        }
    }
    
    if (load_old_files) load_region_map(old_regions_4hat, OLD_FILENAME_4HAT);
    if (load_from_file) load_region_map(regions_4hat, FILENAME_4HAT);
    if (regions_4hat.empty()) {
        generate_4hat_regions(regions_4hat, regions_3hat, regions_4hat_b);
        //generate_4hat_regions_new(regions_4hat, regions_4hat_a);
        if (save_to_file) store_region_map(regions_4hat, FILENAME_4HAT);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_4hat.begin() ; it != old_regions_4hat.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_4hat, old)) {
            cout << "old 4hat had more" << endl;
            old.printRegion();
            exit(1);
        }
    }

    if (load_old_files) load_region_map(old_regions_5hat_b, OLD_FILENAME_5HAT_B);
    if (load_from_file) load_region_map(regions_5hat_b, FILENAME_5HAT_B);
    if (regions_5hat_b.empty()) {
        generate_5hat_b_regions(regions_5hat_b, regions_3hat_b, regions_4hat_b);
        if (save_to_file) store_region_map(regions_5hat_b, FILENAME_5HAT_B);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_5hat_b.begin() ; it != old_regions_5hat_b.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_5hat_b, old)) {
            cout << "old 5hat_b had more" << endl;
            old.printRegion();
            exit(1);
        }
    }

    if (load_old_files) load_region_map(old_regions_5hat, OLD_FILENAME_5HAT);
    if (load_from_file) load_region_map(regions_5hat, FILENAME_5HAT);
    if (regions_5hat.empty()) {
        generate_5hat_regions(regions_5hat, regions_3hat, regions_4hat, regions_4hat_b, regions_5hat_b);
        if (save_to_file) store_region_map(regions_5hat, FILENAME_5HAT);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_5hat.begin() ; it != old_regions_5hat.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_5hat, old)) {
            cout << "old 5hat had more" << endl;
            old.printRegion();
            exit(1);
        }
    }

    if (load_old_files) load_region_map(old_regions_6hat_b, OLD_FILENAME_6HAT_B);
    if (load_from_file) load_region_map(regions_6hat_b, FILENAME_6HAT_B);
    if (regions_6hat_b.empty()) {
        generate_6hat_b_regions(regions_6hat_b, regions_3hat_b, regions_4hat_b, regions_5hat_b);
        if (save_to_file) store_region_map(regions_6hat_b, FILENAME_6HAT_B);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_6hat_b.begin() ; it != old_regions_6hat_b.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_6hat_b, old)) {
            cout << "old 6hat_b had more" << endl;
            old.printRegion();
            exit(1);
        }
    }

    if (load_old_files) load_region_map(old_regions_6hat, OLD_FILENAME_6HAT);
    if (load_from_file) load_region_map(regions_6hat, FILENAME_6HAT);
    if (regions_6hat.empty()) {
        generate_6hat_regions(regions_6hat, regions_3hat, regions_4hat, regions_4hat_b, regions_5hat_b, regions_5hat, regions_6hat_b);
        if (save_to_file) store_region_map(regions_6hat, FILENAME_6HAT);
    }
    
    for(std::map<vector<int>, BaseRegion>::iterator it = old_regions_6hat.begin() ; it != old_regions_6hat.end(); it++){
        BaseRegion old = it->second;
        
        if (!contains_sign(regions_6hat, old)) {
            cout << "old 6hat_b had more" << endl;
            old.printRegion();
            exit(1);
        }
    }

    if (load_from_file) load_region_map(regions_3, FILENAME_3);
    if (regions_3.empty()) {
        generate_3_regions(regions_3, regions_3hat, regions_4hat, regions_5hat);
        if (save_to_file) store_region_map(regions_3, FILENAME_3);
    }

    if (load_from_file) load_region_map(regions_4star, FILENAME_4star);
    if (regions_4star.empty()) {
        generate_4star_regions(regions_4star, regions_3hat, regions_3, regions_4hat, regions_6hat);
        if (save_to_file) store_region_map(regions_4star, FILENAME_4star);
    }

    if (load_from_file) load_region_map(regions_4, FILENAME_4);
    if (regions_4.empty()) {
        generate_4_regions(regions_4, regions_3hat, regions_3, regions_4hat, regions_5hat);
        if (save_to_file) store_region_map(regions_4, FILENAME_4);
    }

    if (load_from_file) load_region_map(regions_5, FILENAME_5);
    if (regions_5.empty()) {
        generate_5_regions(regions_5, regions_3hat, regions_3, regions_4hat, regions_4star, regions_4, regions_5hat, regions_6hat);
        if (save_to_file) store_region_map(regions_5, FILENAME_5);
    }

    if (load_from_file) load_region_map(regions_6, FILENAME_6);
    if (regions_6.empty()) {
        generate_6_regions(regions_6, regions_3hat, regions_4hat, regions_4star, regions_5, regions_5hat, regions_6hat);
        if (save_to_file) store_region_map(regions_6, FILENAME_6);
    }
    
    //cout << "#3a=" << signature_minimal_3aregions.size() << " #3b=" << signature_minimal_3bregions.size() << " #3=" << signature_minimal_3regions.size() << " #4a=" << signature_minimal_4aregions.size() << " #4b=" << signature_minimal_4bregions.size() << " #4=" << signature_minimal_4regions.size() << " #empty=" << empty_region.size()<< endl;
    
    /*
    int id = 0;
    for(std::map<vector<int>, BaseRegion>::iterator it = signature_minimal_3hat_a_regions.begin() ; it != signature_minimal_3hat_a_regions.end(); it++){
        id++;
        ofstream file;
        stringstream ss;
        ss << "4region_" << id << ".dot";
        string filename = ss.str();
        std::cout << "filename: " << filename << std::endl;
        file.open(filename);
        
        if(!file.is_open()){
            std::cout << "ERROR opening file "<< std::endl;
        }
        else {
            //file << it->second.getDotFormat();
        }
        file.close();
    }
    
    cout << "Finding 6regions with empty mid" << endl;*/
    /*
    
    for (int RegA = Empty; RegA <= Type4A; RegA++) {
        int startB = Empty;
        int maxB = RegA >= Type3A ? Type3B : Type4A;
        for(int RegB = startB; RegB <= maxB; RegB++){
            
            for (int RegC = Empty; RegC <= Type4A; RegC++) {
                int startD = Empty;
                int maxD = RegC >= Type3A ? Type3B : Type4A;
                for(int RegD = startD; RegD <= maxD; RegD++){
                    
                    int start_AB_together = 0;
                    int max_AB_together = (RegA == Type3B && (RegB == Type3B || RegB == Type4A)) || (RegA == Type4A && (RegB == Type3B)) ? 1 : 0;
                    for(int AB_together = start_AB_together; AB_together <= max_AB_together; AB_together++){
                        
                        int start_CD_together = 0;
                        int max_CD_together = (RegC == Type3B && (RegD == Type3B || RegD == Type4A)) || (RegC == Type4A && (RegD == Type3B)) ? 1 : 0;
                        
                        for (int CD_together = start_CD_together; CD_together <= max_CD_together; CD_together++) {
                            cout << "have region A=" << type_to_string(RegA) << ", B=" << type_to_string(RegB)<< ", C=" << type_to_string(RegC)<< ", D=" << type_to_string(RegD) << endl;
                            
                            map<vector<int>,SmallRegion >  RegAmap = set_regionmap((RegionType)RegA);
                            map<vector<int>,SmallRegion >  RegBmap = set_regionmap((RegionType)RegB);
                            map<vector<int>,SmallRegion >  RegCmap = set_regionmap((RegionType)RegC);
                            map<vector<int>,SmallRegion >  RegDmap = set_regionmap((RegionType)RegD);
                            
                            for(map<vector<int>,SmallRegion >::iterator itA = RegAmap.begin(); itA != RegAmap.end(); itA++){
                                for(map<vector<int>,SmallRegion >::iterator itB = RegBmap.begin(); itB != RegBmap.end(); itB++){
                                    for(map<vector<int>,SmallRegion >::iterator itC = RegCmap.begin(); itC != RegCmap.end(); itC++){
                                        for(map<vector<int>,SmallRegion >::iterator itD = RegDmap.begin(); itD != RegDmap.end(); itD++){
                                            
                                            // create boundaried 6-region and glue on the small regions
                                            
                                            BoundariedRegion bigRegion = BoundariedRegion(6, 3, counter++);
                                            vector<BoundariedRegion> toGlue;
                                            
                                            for(int i = 0; i < 6; i++){
                                                bigRegion.addLabel(i, i);
                                            }
                                            
                                            int node6 = -1;
                                            if(RegA == Type3B){
                                                node6 = bigRegion.addNode();
                                                bigRegion.addEdge(node6, 0);
                                                bigRegion.addEdge(node6, 1);
                                                bigRegion.addLabel(node6, 6);
                                                
                                                BoundariedRegion bA(3,0,0);
                                                itA->second.copy(bA);
                                                
                                            }
                                            if(RegA == Type4A){
                                                node6 = bigRegion.addNode();
                                                bigRegion.addEdge(node6, 0);
                                                bigRegion.addEdge(node6, 2);
                                                bigRegion.addLabel(node6, 6);
                                            }
                                            
                                            int node7 = -1;
                                            if(RegB == Type3B){
                                                if (AB_together) {
                                                    node7 = node6;
                                                } else {
                                                    node7 = bigRegion.addNode();
                                                }
                                                
                                                bigRegion.addEdge(node7, 3);
                                                bigRegion.addEdge(node7, 2);
                                                bigRegion.addLabel(node7, 7);
                                            }
                                            if(RegB == Type4A){
                                                if (AB_together) {
                                                    node7 = node6;
                                                } else {
                                                    node7 = bigRegion.addNode();
                                                }
                                                bigRegion.addEdge(node7, 3);
                                                bigRegion.addEdge(node7, 1);
                                                bigRegion.addLabel(node7, 7);
                                            }
                                            
                                            BoundariedRegion bA;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    */
    cout << "main done" << endl;
    return 0;
}

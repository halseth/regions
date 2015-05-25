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

#include "EmptyRegion.h"
#include "3hat_a_regions.h"
#include "3hat_ab_regions.h"
#include "4hat_ab_regions.h"
#include "4hat_b_regions.h"
#include "4hat_regions.h"
#include "4hat_a_regions.h"
#include "5hat_a_regions.h"
#include "5hat_regions.h"


enum RegionType {
    Empty,
    Type3B,
    Type3A,
    Type4A
};

map<vector<int>, BaseRegion> empty_region;
map<vector<int>, BaseRegion> signature_minimal_4hat_a_regions;
map<vector<int>, BaseRegion> signature_minimal_4hat_ab_regions;
map<vector<int>, BaseRegion> signature_minimal_4hat_b_regions;
map<vector<int>, BaseRegion> signature_minimal_4hat_regions;
map<vector<int>, BaseRegion> signature_minimal_3hat_a_regions;
map<vector<int>, BaseRegion> signature_minimal_3hat_ab_regions;
map<vector<int>, BaseRegion> signature_minimal_3hat_regions;
map<vector<int>, BaseRegion> signature_minimal_5hat_a_regions;
map<vector<int>, BaseRegion> signature_minimal_5hat_regions;

string type_to_string(int a){
    switch (a) {
        case 0:
            return "empty";
            break;
            
        case 1:
            return "3B";
            break;
            
        case 2:
            return "3A";
            break;
            
        case 3:
            return "4A";
            break;
            
        case 4:
            return "4B";
            break;
            
        default:
            return "unknown";
            break;
    }
}

/*

map<vector<int>, BaseRegion > set_regionmap(RegionType t){
    switch (t) {
        case Empty:
            return empty_region;
            break;
        case Type3B:
            return signature_minimal_3hat_b_regions;
            break;
        case Type3A:
            return signature_minimal_3hat_a_regions;
            break;
        case Type4A:
            return signature_minimal_4hat_a_regions;
            break;
        default:
            cerr << "should not happen" << endl;
            exit(0);
            break;
    }
}*/

 
int main(){
    
    //generate_3hat_a_regions(signature_minimal_3hat_a_regions);
    generate_3hat_ab_regions(signature_minimal_3hat_ab_regions);
    //generate_3regions(signature_minimal_3hat_regions); // == 3hat_ab
    generate_4hat_a_regions(signature_minimal_4hat_a_regions);
    //generate_4hat_ab_regions(signature_minimal_4hat_ab_regions);
    //generate_4hat_b_regions(signature_minimal_4hat_b_regions);
    generate_4hat_regions(signature_minimal_4hat_regions);
    //generate_Empty_regions(empty_region);
    generate_5hat_a_regions(signature_minimal_5hat_a_regions);
    generate_5hat_regions(signature_minimal_5hat_regions, signature_minimal_5hat_a_regions, signature_minimal_4hat_a_regions, signature_minimal_4hat_regions, signature_minimal_3hat_ab_regions);
 
    //cout << "#3a=" << signature_minimal_3aregions.size() << " #3b=" << signature_minimal_3bregions.size() << " #3=" << signature_minimal_3regions.size() << " #4a=" << signature_minimal_4aregions.size() << " #4b=" << signature_minimal_4bregions.size() << " #4=" << signature_minimal_4regions.size() << " #empty=" << empty_region.size()<< endl;
    
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
    
    cout << "Finding 6regions with empty mid" << endl;
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

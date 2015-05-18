//
//  BaseRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <lemon/planarity.h>
#include <lemon/connectivity.h>
#include "BaseRegion.h"
#include "subsets.hpp"

BaseRegion::BaseRegion(int boundarySize){
    num_internal_nodes = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        std::vector<bool> t;
        for(int j = 0; j < MAX_SIZE; j++){
            t.push_back(false);
        }
        adj.push_back(t);
    }
    for(int i = 0; i < boundarySize; i++){
        Boundary.push_back(i);
    }
    
    for(int i = 0; i < Boundary.size(); i++){
        this->addEdge( Boundary[i], Boundary[(i+1)%Boundary.size()] );
    }
}

int BaseRegion::addNode(){
    return Boundary.size() + num_internal_nodes++;
}

void BaseRegion::addEdge(int from, int to){
    adj[from][to] = true;
    adj[to][from] = true;
}

int BaseRegion::getSize(){
    return Boundary.size() + num_internal_nodes;
}

bool BaseRegion::isAdjacent(int a, int b){
    return adj[a][b];
}

bool BaseRegion::isValid(){
    // The region must be planar and connected
    // TODO: connectivity
    
    lemon::ListGraph g;
    std::vector<lemon::ListGraph::Node> gnodes;
    
    for(int i = 0; i < getSize(); i++){
        gnodes.push_back(g.addNode());
    }
    
    for(int node = 0; node < getSize(); node++){
        for(int i = node+1; i < adj[node].size(); i++){
            if(adj[node][i]){
                g.addEdge(gnodes[node], gnodes[i]);
            }
        }
    }
    
    bool valid = true;
    
    // It must be connected
    if (!connected(g)) {
        valid = false;
    }
   
    // It must be planar with all internal vertices drawn on the inside
    lemon::ListGraph::Node gadget = g.addNode();
    for(int i = 0; i < Boundary.size(); i++){
        g.addEdge(gadget, g.nodeFromId(Boundary[i]));
    }
    
    if(!checkPlanarity(g)){
        valid = false;
    }
    
    return valid;
}


int BaseRegion::getBoundarySize(){
    return Boundary.size();
}

// Calculates the signature zeta(X,S) of a region
int BaseRegion::signature(std::vector<int> X, std::vector<int> S){
    
    //Helper array to calculate indexes of vertices
    int xs[this->getSize()];
    for(int i = 0; i < this->getSize(); i++){
        xs[i] = 0;
    }
    for(int i = 0; i < X.size(); i++){
        xs[X[i]] = 1;
    }
    int item = 0;
    for(int i = 0; i < this->getSize(); i++){
        if(xs[i] == 0){
            xs[item++] = i;
        }
    }
    
    int best = this->getSize();
    // Try all possible dominating sets and check if they are good
    int x_size = X.size();
    
    // Size of set in addition to X is max 2 (we can always pick v and w)
    for(int k = 0; k <= 2; k++){
        std::vector<std::vector<int> > d_subsets;
        gen_subsets(this->getSize()-1-x_size, k, d_subsets);
        for(int i = 0; i < d_subsets.size(); i++){
            std::vector<int> D;
            for(int j = 0; j < X.size();j++){
                D.push_back(X[j]);
            }
            std::vector<int> additional = d_subsets[i];
            for(int j = 0; j < additional.size(); j++){
                int a = additional[j];
                D.push_back(xs[a]);
            }
            
            bool valid = true;
            
            bool dominated[this->getSize()];
            for(int j = 0; j < this->getSize(); j++){
                dominated[j] = false;
            }
            for(int j = 0; j < D.size(); j++){
                int d = D[j];
                dominated[d] = true;
            }
            
            
            //Check if X is part of D
            for(int j = 0; j < X.size(); j++){
                int x = X[j];
                valid &= dominated[x];
            }
            
            if(!valid){
                std::cerr << "ERROR in signature calculation!. X not part of D." << std::endl;
                exit(0);
            }
            
            // Check if it is a dominating set of V(R)\S
            for(int j = 0; j < S.size(); j++){
                int s = S[j];
                dominated[s] = true;
            }
            for(int j = 0; j < D.size(); j++){
                int d = D[j];
                for(int l = 0; l < adj[d].size(); l++){
                    if(adj[d][l]) dominated[l] = true;
                }
            }
            
            for(int v = 0; v < this->getSize(); v++){
                valid &= dominated[v];
            }
            
            //Check if valid and smallest possible
            if(valid && D.size() < best){
                best = D.size();
            } 
            
        }
    }
   /* std::cout << "For x=";
    for(int i = 0; i<X.size(); i++){
        std::cout << X[i] << " ";
    }
    std::cout << "and s=";
    for(int i = 0; i<S.size(); i++){
        std::cout << S[i] << " ";
    }
    std::cout << "we return " << (best - X.size()) << std::endl;
    */
    return best - X.size();
}

void BaseRegion::getSignature(std::vector<int> &signature){
    signature.clear();
    
    for(int s_set = 0; s_set <= std::pow(2,Boundary.size())-1; s_set++){
        for(int x_set = 0; x_set <= std::pow(2, Boundary.size())-1; x_set++){
            if((s_set & x_set) != 0) continue; // overlaps
            
            std::vector<int> X;
            std::vector<int> S;
            
            for(int i = 0; i < Boundary.size(); i++){
                if(s_set & (1 << i)) S.push_back(i);
                if(x_set & (1 << i)) X.push_back(i);
            }
            
            signature.push_back(this->signature(X, S));
        }
    }
}


bool BaseRegion::isEqual(const BaseRegion &b){
    bool equal = true;
    equal &= this->Boundary == b.Boundary;
    equal &= this->num_internal_nodes == b.num_internal_nodes;
    equal &= this->adj == b.adj;
    return equal;
}


void BaseRegion::addLabelToNode(int label, int node){
    labelToNode[label] = node;
    nodeToLabels[node].insert(label);
}

void BaseRegion::clearLabels(){
    labelToNode.clear();
    nodeToLabels.clear();
}

void BaseRegion::glue(const std::vector<BaseRegion> regions){
    for(std::vector<BaseRegion>::const_iterator it = regions.begin(); it != regions.end(); it++){
        
        BaseRegion region = (BaseRegion) *it;
        
        //Find largest used label
        int label = 0;
        for(std::map<int, int>::const_iterator it = labelToNode.begin(); it != labelToNode.end(); it++){
            if(it->first >= label){
                label = it->first + 1;
            }
        }
        
        for(std::map<int, int>::const_iterator it = region.labelToNode.begin(); it != region.labelToNode.end(); it++){
            if(it->first >= label){
                label = it->first + 1;
            }
        }
        
        // Nodes not having a label in the region to glue on, or not having a matching label in the target graph, are added to the graph and given a temporary label
        std::map<int, int> newNodeToLabel;
        for (int i = 0; i < region.getSize(); i++) {
            if(region.nodeToLabels.count(i) == 0) {
                newNodeToLabel[i] = label++;
            } else {
                bool foundMatchingLabel = false;
                for(std::set<int>::const_iterator it = region.nodeToLabels[i].begin(); it != region.nodeToLabels[i].end(); it++){
                    if(this->labelToNode.count(*it) != 0){
                        foundMatchingLabel = true;
                    }
                }
                if(!foundMatchingLabel){
                    newNodeToLabel[i] = label++;
                }
            }
        }
    }
}
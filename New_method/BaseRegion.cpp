//
//  BaseRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include <lemon/planarity.h>
#include <lemon/connectivity.h>
#include <fstream>
#include "BaseRegion.h"
#include "subsets.hpp"

BaseRegion::BaseRegion(int boundarySize){
    init(boundarySize);
}


BaseRegion::BaseRegion(std::string string_rep){
    std::stringstream ss;
    ss << string_rep;
    
    int boundary_size;
    ss >> boundary_size;
   // std::cout << "found boundary size " << boundary_size << std::endl;
    
    init(boundary_size);
    
    int internal_nodes;
    ss >> internal_nodes;
   // std::cout << "internal nodes is " << internal_nodes << std::endl;
    for(int i = 0; i < internal_nodes; i++){
        this->addNode();
    }
    int from, to;
    while (ss >> from && ss >> to) {
        this->addEdge(from, to);
       // std::cout << "found edge (" << from << ", " << to << ")" << std::endl;
    }
}

void BaseRegion::init(int boundarySize){
    std::vector<std::vector<bool> > adjacent;
    num_internal_nodes = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        std::vector<bool> t;
        for(int j = 0; j < MAX_SIZE; j++){
            t.push_back(false);
        }
        adjacent.push_back(t);
    }
    this->adj = adjacent;
    for(int i = 0; i < boundarySize; i++){
        Boundary.push_back(i);
    }
    
    for(int i = 0; i < Boundary.size(); i++){
        this->addEdge( Boundary[i], Boundary[(i+1)%Boundary.size()] );
    }
}

std::string BaseRegion::toString(){
    std::stringstream ss;
    ss << this->getBoundarySize() << " ";
    ss << this->num_internal_nodes << " ";
    
    for(int i = 0; i < this->getSize(); i++){
        for(int j = i+1; j < this->getSize(); j++){
            if(this->isAdjacent(i, j)){
                ss << i << " ";
                ss << j << " ";
            }
        }
    }
    return ss.str();
}

int BaseRegion::addNode(){
    return Boundary.size() + num_internal_nodes++;
}

void BaseRegion::addEdge(int from, int to){
    if (from == to) {
        return;
    }
    //std::cout << "adding edge " << from << " to " << to << std::endl;
//    if (adj[from][to] || adj[to][from]) {
//        std::cout << "edge " << from << " to " << to << " already exists. Error?" << std::endl;
//        exit(0);
//    }
    adj[from][to] = true;
    adj[to][from] = true;
}

int BaseRegion::getSize() const{
    return Boundary.size() + num_internal_nodes;
}

bool BaseRegion::isAdjacent(int a, int b){
    return adj[a][b];
}

bool BaseRegion::isValid(){
    // The region must be planar and connected
    
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
        std::cout << "Not connected" << std::endl;
        valid = false;
#ifndef TEST
        printRegion();
        exit(0);
#endif
    }
   
    // It must be planar with all internal vertices drawn on the inside
    lemon::ListGraph::Node gadget = g.addNode();
    for(int i = 0; i < Boundary.size(); i++){
        g.addEdge(gadget, g.nodeFromId(Boundary[i]));
    }
    
    if(!checkPlanarity(g)){
        std::cout << "Not planar" << std::endl;
        valid = false;
#ifndef TEST
        printRegion();
        exit(0);
#endif
    }
    
    return valid;
}


int BaseRegion::getBoundarySize() const{
    return Boundary.size();
}

// Calculates the signature zeta(X,S) of a region
// TODO: Most likely wrong
int BaseRegion::signature(std::vector<int> X, std::vector<int> S){
    
    //Helper array to calculate indexes of vertices
    int xs[this->getSize()];
    for(int i = 0; i < this->getSize(); i++){
        xs[i] = 0;
    }
    
    // Set indices in X to 1
    for(int i = 0; i < X.size(); i++){
        xs[X[i]] = 1;
    }
    
    // The first elements in the array will point to the elements not in X
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
    }*/
//    std::cout << "we return " << (best - X.size()) << "for X=";
//    for (int i = 0; i < X.size(); i++) {
//        std::cout << X[i] << " ";
//    }
//    std::cout << "S=";
//    for (int i = 0; i < S.size(); i++) {
//        std::cout << S[i] << " ";
//    }
//    std::cout << std::endl;
    return best - X.size();
}

int BaseRegion::signature2(std::vector<int> X, std::vector<int> S){
    
    //Helper array to calculate indexes of vertices
    int xs[this->getBoundarySize()];
    for(int i = 0; i < this->getBoundarySize(); i++){
        xs[i] = 0;
    }
    for(int i = 0; i < X.size(); i++){
        xs[X[i]] = 1;
    }
    int item = 0;
    for(int i = 0; i < this->getBoundarySize(); i++){
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
//        std::cout << "k=" << k << std::endl;
        // Pick boundary nodes
        gen_subsets(this->getBoundarySize()-1-x_size, k, d_subsets);
        for(int i = 0; i < d_subsets.size(); i++){
            std::vector<int> D;
            for(int j = 0; j < X.size();j++){
                D.push_back(X[j]);
            }
            std::vector<int> additional = d_subsets[i];
//            std::cout << "Additional :";
            for(int j = 0; j < additional.size(); j++){
                int a = additional[j];
//                std::cout << " " << a;
                D.push_back(xs[a]);
            }
//            std::cout << std::endl;
            
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
            
            std::vector<int> not_dominated;
            for(int v = 0; v < this->getSize(); v++){
                valid &= dominated[v];
                if(!dominated[v]){
                    not_dominated.push_back(v);
                }
            }
            
            if (!valid) {
                // Try to pick one extra internal vertex to make it valid
                for(int internal = getBoundarySize(); internal < getSize(); internal++){
                    bool fix_domination = true;
                    for(int v = 0; v < not_dominated.size(); v++){
                        if (not_dominated[v] == internal) {
                            continue;
                        }
                        fix_domination &= isAdjacent(not_dominated[v], internal);
                    }
                    // Found vertex to fix domination, add to D
                    if (fix_domination) {
//                        std::cout << "Fixed" << std::endl;
                        D.push_back(internal);
                        valid = true;
                        break;
                    }
                }
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
     */
    
//    std::cout << "we return " << (best - X.size()) << "for X=";
//    for (int i = 0; i < X.size(); i++) {
//        std::cout << X[i] << " ";
//    }
//    std::cout << "S=";
//    for (int i = 0; i < S.size(); i++) {
//        std::cout << S[i] << " ";
//    }
//    std::cout << std::endl;
    return best - X.size();
}

void BaseRegion::getSignature(std::vector<int> &signature){
    signature.clear();
//    std::cout << "Sign1" << std::endl;
    
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

void BaseRegion::getSignature2(std::vector<int> &signature){
    signature.clear();
//    std::cout << "Sign2" << std::endl;
    for(int s_set = 0; s_set <= std::pow(2,Boundary.size())-1; s_set++){
        for(int x_set = 0; x_set <= std::pow(2, Boundary.size())-1; x_set++){
            if((s_set & x_set) != 0) continue; // overlaps
            
            std::vector<int> X;
            std::vector<int> S;
            
            for(int i = 0; i < Boundary.size(); i++){
                if(s_set & (1 << i)) S.push_back(i);
                if(x_set & (1 << i)) X.push_back(i);
            }
            
            signature.push_back(this->signature2(X, S));
        }
    }
}

void BaseRegion::printRegion(){
    std::cout << "Num nodes: " << getSize() << std::endl;
    for(int i = 0; i < getSize(); i++){
        for(int j = i+1; j < getSize(); j++){
            if (isAdjacent(i, j)) {
                std::cout << "Edge from " << i << " to " << j << std::endl;
            }
        }
    }
}

void BaseRegion::test(){
    std::cout << "I am baseclass" << std::endl;
}


bool BaseRegion::isEqual(const BaseRegion &b) const{
    bool equal = true;
    equal &= this->Boundary == b.Boundary;
    if (!equal) {
        std::cout << "Boundary not equal" << std::endl;
    }
    equal &= this->num_internal_nodes == b.num_internal_nodes;
    if (!equal) {
        std::cout << "Internal nodes not equal" << std::endl;
    }
    equal &= this->adj == b.adj;
    if (!equal) {
        std::cout << "Edges not equal" << std::endl;
    }
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

void BaseRegion::glue(BaseRegion* region){
    
    using namespace std;
    
    //Find smallest free label
    int free_label = 0;
    for(std::map<int, int>::const_iterator map_it = labelToNode.begin(); map_it != labelToNode.end(); map_it++){
        if(map_it->first >= free_label){
            free_label = map_it->first + 1;
        }
    }
    
    for(std::map<int, int>::const_iterator map_it = region->labelToNode.begin(); map_it != region->labelToNode.end(); map_it++){
        if(map_it->first >= free_label){
            free_label = map_it->first + 1;
        }
    }
    
    // Nodes not having a label in the region to glue on, or not having a matching label in the target graph, are added to the graph and given a temporary label
    
    // Store these for later
    std::map<int, std::set<int> > temporaryNodeToLabels = this->nodeToLabels;
    std::map<int, int> temporaryLabelToNode = this->labelToNode;
    
    // Give all nodes in the graph to glue labels
    for (int i = 0; i < region->getSize(); i++) {
        
        // Not having a label
        if(region->nodeToLabels.count(i) == 0 || region->nodeToLabels[i].size() == 0) {
            std::set<int> labels;
            labels.insert(free_label);
            region->nodeToLabels[i] = labels;
            region->labelToNode[free_label] = i;
            free_label++;
        }
    }
        
    // Update labels in target graph to be consistent with glue graph. Add necessary nodes to target
    for (std::map<int, std::set<int> >::const_iterator map_it = region->nodeToLabels.begin(); map_it != region->nodeToLabels.end(); map_it++) {
        int node = map_it->first;
        std::set<int> labelSet = map_it->second;
        
        // If none of the node's labels exist in target, add a new node
        bool exist = false;
        int nodeNum = -1;
        for(std::set<int>::const_iterator set_it = labelSet.begin(); set_it != labelSet.end(); set_it++){
            if (this->labelToNode.count(*set_it) > 0) {
                exist = true;
                nodeNum = this->labelToNode[*set_it];
            }
        }
        
            // Add new node and give it all the labels
        if(!exist){
            nodeNum = this->addNode();
        }
        
        // Add missing labels
        for(std::set<int>::const_iterator set_it = region->nodeToLabels[node].begin(); set_it != region->nodeToLabels[node].end(); set_it++){
            this->addLabelToNode(*set_it, nodeNum);
        }
    }
        
        
    // Add edges
    for (int i = 0; i < region->getSize(); i++) {
        for(int j = i+1; j < region->getSize(); j++){
            if(region->isAdjacent(i, j)){
                // Find these two nodes in the target
                int label1 = *(region->nodeToLabels[i].begin());
                int node1 = this->labelToNode[label1];
                
                int label2 = *(region->nodeToLabels[j].begin());
                int node2 = this->labelToNode[label2];
                    
                //Add the edge between them
                this->addEdge(node1, node2);
            }
        }
    }
    this->labelToNode = temporaryLabelToNode;
    this->nodeToLabels = temporaryNodeToLabels;
}

void BaseRegion::glue(const std::vector<BaseRegion*> regions){
    for (std::vector<BaseRegion*>::const_iterator it = regions.begin(); it != regions.end(); it++) {
        BaseRegion* r = *it;
        glue(r);
    }
}

std::map<int, int> BaseRegion::getLabelToNode(){
    return labelToNode;
}

std::map<int, std::set<int> > BaseRegion::getNodeToLabels(){
    return nodeToLabels;
}

BaseRegion::BaseRegion(const BaseRegion &obj)
{
    //std::cout << "copy constructor" << std::endl;
    init(obj.getBoundarySize());
    this->adj = obj.adj;
    this->num_internal_nodes = obj.num_internal_nodes;
    
    // Do not copy labels
//    // Deep copy of labels
//    
//    for(std::map<int, int>::const_iterator map_it = obj.labelToNode.begin(); map_it != obj.labelToNode.end(); map_it++){
//        this->labelToNode[map_it->first] = map_it->second;
//    }
//    
//    for (std::map<int, std::set<int> >::const_iterator map_it = obj.nodeToLabels.begin(); map_it != obj.nodeToLabels.end(); map_it++) {
//        std::set<int> labels;
//        std::set<int> labelSet = map_it->second;
//        for(std::set<int>::const_iterator set_it = labelSet.begin(); set_it != labelSet.end(); set_it++){
//            labels.insert(*set_it);
//        }
//        this->nodeToLabels[map_it->first] = labels;
//    }
}

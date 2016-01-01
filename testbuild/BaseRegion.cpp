//
//  BaseRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//


#include <lemon/planarity.h>
#include <lemon/connectivity.h>
#include <stdlib.h>
#include <fstream>
#include "BaseRegion.h"

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
    
    // Remove all edges implicitly added
    for (int i = 0; i < boundary_size; i++) {
        removeEdge(i, (i+1)%boundary_size);
    }
    
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

void BaseRegion::removeEdge(int from, int to){
    adj[from][to] = false;
    adj[to][from] = false;
}

int BaseRegion::getSize() const{
    return Boundary.size() + num_internal_nodes;
}

bool BaseRegion::isAdjacent(int a, int b){
    return adj[a][b];
}

bool BaseRegion::isValid(){
    // The region must be planar and connected
    
    bool valid = true;
    
    // It must be connected
    if (!isConnected()) {
        //std::cout << "Not connected" << std::endl;
        valid = false;
#ifndef TEST
        //printRegion();
        //exit(0);
#endif
    }
    
    if(!isPlanar()){
        //std::cout << "Not planar" << std::endl;
        valid = false;
#ifndef TEST
       // printRegion();
       // exit(0);
#endif
    }
    
    return valid;
}

bool BaseRegion::isConnected(){
    // Check connectivity
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
    
    // It must be connected
    return connected(g);
}

bool BaseRegion::isPlanar(){
//    std::cout << "check planar" << std::endl;
    // The region must be planar when all boundary edges are there
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
    
    // Add boundary edges if not already added
    for(int node = 0; node < getBoundarySize(); node++){
        int neighbor = (node+1) % getBoundarySize();
        if (!isAdjacent(node, neighbor)) {
            g.addEdge(gnodes[node], gnodes[neighbor]);
        }
    }
    
    // It must be planar with all internal vertices drawn on the inside
    lemon::ListGraph::Node gadget = g.addNode();
    for(int i = 0; i < Boundary.size(); i++){
        g.addEdge(gadget, g.nodeFromId(Boundary[i]));
    }
    
//    std::cout << "done building" << std::endl;
    return checkPlanarity(g);
}



int BaseRegion::getBoundarySize() const{
    return Boundary.size();
}

// Check if the set D dominates region \ S
bool BaseRegion::dominates(std::vector<int> D, std::vector<int> S) {
    
    bool dominated[this->getSize()];
    for(int j = 0; j < this->getSize(); j++){
        dominated[j] = false;
    }
    for(int j = 0; j < D.size(); j++){
        int d = D[j];
        dominated[d] = true;
    }
    
    // Check if it is a dominating set of V(R)\S
    for(int j = 0; j < S.size(); j++){
        int s = S[j];
        dominated[s] = true;
    }
    
    for(int j = 0; j < D.size(); j++){
        int d = D[j];
        for(int l = 0; l < this->getSize(); l++){
            if(adj[d][l]) dominated[l] = true;
        }
    }
    
    bool valid = true;
    for(int v = 0; v < this->getSize(); v++){
        valid &= dominated[v];
    }
    
    return valid;
}

// Calculates the signature zeta(X,S) of a region
// Optimized signature function. NB: only valid if {u,v} dominates the whole regions (included boundary)
int BaseRegion::signature(std::vector<int> X, std::vector<int> S){
    
    // Check if X already dominates region
    if(dominates(X, S)) {
        // Don't need any additional nodes
        return 0;
    }
    
    // Try picking one vertex in addition to X
    for (int i = 0; i < this->getSize(); i++) {
        std::vector<int> dominators(X);
        dominators.push_back(i);
        
        if (dominates(dominators, S)) {
            // Enough with one extra
            return 1;
        }
    }
    
    // If not we can always just pick u and v. NB: If we get this far we know that u or v cannot already be in X
    return 2;
}

void BaseRegion::getSignature(std::vector<int> &signature){
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
            
            signature.push_back(this->signature(X, S));
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
    if (node > getSize()) {
        std::cout << "Tried to add label " << label << " to node " << node << " but size of region is " << getSize() << std::endl;
        exit(1);
    }
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

// Calculates the signature zeta(X,S) of a region where {u,v} not necessarily dominates the whole region (included boundary)
int BaseRegion::generalSignature(std::vector<int> X, std::vector<int> S){
    
    // Check if X already dominates region
    if(dominates(X, S)) {
        // Don't need any additional nodes
        return 0;
    }
    
    // Try picking subsets of size k in addition
    int n = getSize();
    for (int k = 1; k <= n; k++) {
        
        // Gosper's hack: http://stackoverflow.com/questions/15932237/iterating-over-all-subsets-of-a-given-size
        int c = (1<<k)-1;
        while (c < (1<<n)) {
            
            std::vector<int> dominators(X);
            
            for (int i = 0; i < n; i++) {
                if(c & (1 << i)) dominators.push_back(i);
            }
            
            if (dominates(dominators, S)) {
                return k;
            }
            
            int a = c&-c, b = c+a;
            c = (c^b)/4/a|b;
        }
    }

    return n;
}

void BaseRegion::getGeneralSignature(std::vector<int> &signature){
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
            
            signature.push_back(this->generalSignature(X, S));
        }
    }
}

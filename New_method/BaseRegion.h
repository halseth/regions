//
//  BaseRegion.h
//  New_method
//
//  Created by Johan Torås Halseth on 14/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef __New_method__BaseRegion__
#define __New_method__BaseRegion__

#include <vector>
#include <map>
#include <set>

#define MAX_SIZE 32

class BaseRegion {
private:
    std::vector<int> Boundary;
    int num_internal_nodes;
    std::vector<std::vector<bool> > adj;
    std::map<int, int> labelToNode;
    std::map<int, std::set<int> > nodeToLabels;
    
    // Private methods
    int signature(std::vector<int> X, std::vector<int> S);
    
public:
    BaseRegion(int boundarySize);
    virtual bool isValid();
    int getSize() const;
    int addNode();
    void addEdge(int from, int to);
    bool isAdjacent(int a, int b);
    void getSignature(std::vector<int> &signature);
    int getBoundarySize();
    
    void printRegion();
    
    bool isEqual(const BaseRegion &b);
    
    void addLabelToNode(int label, int node);
    void clearLabels();
    
    void glue(BaseRegion &region);
    void glue(const std::vector<BaseRegion> regions);
    std::map<int, int> getLabelToNode();
    std::map<int, std::set<int> > getNodeToLabels();
    
    virtual void test();
    
};


#endif /* defined(__New_method__BaseRegion__) */

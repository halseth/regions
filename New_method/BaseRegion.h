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
#include <string>

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
    int signature2(std::vector<int> X, std::vector<int> S);
    void init(int boundarySize);
    
public:
    BaseRegion(int boundarySize);
    BaseRegion(std::string filename);
    std::string toString();
    
    // Operator overloading
    bool operator==(const BaseRegion& b) const {return isEqual(b);};
    
    virtual bool isValid();
    int getSize() const;
    int addNode();
    void addEdge(int from, int to);
    bool isAdjacent(int a, int b);
    void getSignature(std::vector<int> &signature);
    void getSignature2(std::vector<int> &signature);
    int getBoundarySize();
    
    void printRegion();
    
    bool isEqual(const BaseRegion &b) const;
    
    void addLabelToNode(int label, int node);
    void clearLabels();
    
    void glue(BaseRegion &region);
    void glue(const std::vector<BaseRegion> regions);
    std::map<int, int> getLabelToNode();
    std::map<int, std::set<int> > getNodeToLabels();
    
    virtual void test();
    
};


#endif /* defined(__New_method__BaseRegion__) */

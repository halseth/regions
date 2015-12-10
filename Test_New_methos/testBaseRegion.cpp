//
//  testBaseRegion.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 15/05/15.
//  Copyright (c) 2015 Johan Torås Halseth. All rights reserved.
//

#include "catch.hpp"
#include <iostream>
#include "BaseRegion.h"
using namespace std;

TEST_CASE( "Testin BaseRegion", "[BaseRegion]" ) {
    BaseRegion b(3);
    REQUIRE( b.getSize() == 3 );
    
    REQUIRE( b.isValid());
    
    // must be connected
    int node = b.addNode();
    REQUIRE( !b.isValid());
    
    b.addEdge(0, node);
    REQUIRE( b.isValid());
    
    // Check two regions having the same signature
    BaseRegion b1(6);
    
    int node1 = b1.addNode();
    int node2 = b1.addNode();
    b1.addEdge(0, node1);
    b1.addEdge(node1, 1);
    b1.addEdge(0, node2);
    b1.addEdge(node2, node1);
    
    BaseRegion b2(6);
    int node3 = b2.addNode();
    b2.addEdge(0, node3);
    b2.addEdge(node3, 1);
    int node4 = b2.addNode();
    b2.addEdge(0, node4);
    
    
    std::vector<int> sig1, sig2;
    b1.getSignature(sig1);
    b2.getSignature(sig2);
    
    REQUIRE(sig1 == sig2);
    
}

TEST_CASE( "Testing Reduction Rules", "[BaseRegion]" ) {
    BaseRegion b1(6);
    
    int node1 = b1.addNode();
    int node2 = b1.addNode();
    b1.addEdge(0, node1);
    b1.addEdge(node1, 3);
    b1.addEdge(0, node2);
    b1.addEdge(node2, 3);
    
    BaseRegion b2(6);
    for(int i = 0; i < 6; i++){
        int node = b2.addNode();
        b2.addEdge(0, node);
        b2.addEdge(node, 3);
    }
    
    std::vector<int> sig1, sig2;
    b1.getSignature(sig1);
    b2.getSignature(sig2);
    
    REQUIRE(sig1 == sig2);
    
}

TEST_CASE( "Testing equality", "[BaseRegion]" ) {
    BaseRegion b1(6);
    int node1 = b1.addNode();
    b1.addEdge(0, node1);
    
    BaseRegion b2(6);
    int node2 = b2.addNode();
    b2.addEdge(0, node2);
    
    REQUIRE( b1.isEqual(b2));
}

TEST_CASE( "Testing gluing", "[BaseRegion]" ) {
    BaseRegion r1(5);
    r1.addLabelToNode(1, 0);
    r1.addLabelToNode(2, 1);
    r1.addLabelToNode(3, 2);
    
    BaseRegion b1(4);
    b1.addLabelToNode(1, 0);
    b1.addLabelToNode(2, 1);
    b1.addLabelToNode(3, 2);
    
    std::vector<BaseRegion> regions;
    regions.push_back(b1);
    
    r1.glue(&b1);
   // std::cout << "r is:" << std::endl;
  //  r.printRegion();
    
    BaseRegion shouldEqual(5);
    int node = shouldEqual.addNode();
    shouldEqual.addEdge(0, node);
    shouldEqual.addEdge(2, node);
    
   // std::cout << "Should be:" << std::endl;
   // shouldEqual.printRegion();
    
    REQUIRE( r1.isEqual(shouldEqual));
    
    BaseRegion r2(3);
    r2.addLabelToNode(1, 0);
    r2.addLabelToNode(2, 0);
    
    BaseRegion b2(3);
    b2.addLabelToNode(1, 0);
    b2.addLabelToNode(2, 2);
    
    r2.glue(&b2);
    
    BaseRegion shouldEqual2(3);
    node = shouldEqual2.addNode();
    shouldEqual2.addEdge(node, 0);
    
    REQUIRE( r2.isEqual(shouldEqual2));
    
    REQUIRE( r2.getLabelToNode().size() == 2);
    REQUIRE( r2.getNodeToLabels().size() == 1);
    
}

TEST_CASE( "Testing multiple gluing", "[BaseRegion]" ) {
    BaseRegion r(3);
    r.addLabelToNode(1, 0);
    r.addLabelToNode(2, 1);
    
    std::vector<BaseRegion*> toGlue;
    
    BaseRegion b1(2);
    b1.addLabelToNode(1, 0);
    b1.addLabelToNode(2, 1);
    toGlue.push_back(&b1);
    
    BaseRegion b2(2);
    b2.addLabelToNode(1, 0);
    b2.addLabelToNode(2, 1);
    toGlue.push_back(&b2);
    
    r.glue(toGlue);
    
    BaseRegion shouldEqual(3);
    
    REQUIRE( r.isEqual(shouldEqual));
    REQUIRE(r == shouldEqual);
    
    BaseRegion r2(3);
    r2.addLabelToNode(1, 0);
    r2.addLabelToNode(2, 1);
    
    toGlue.clear();
    
    BaseRegion b3(2);
    b3.addLabelToNode(1, 0);
    toGlue.push_back(&b3);
    
    BaseRegion b4(2);
    b4.addLabelToNode(2, 1);
    toGlue.push_back(&b4);
    
    r2.glue(toGlue);
    
    BaseRegion shouldEqual2(3);
    int node = shouldEqual2.addNode();
    shouldEqual2.addEdge(0, node);
    node = shouldEqual2.addNode();
    shouldEqual2.addEdge(node, 1);
    
    REQUIRE( r2.isEqual(shouldEqual2));
}

TEST_CASE( "Testing multiple complex gluing", "[BaseRegion]" ) {
    BaseRegion r(6);
    for (int i = 0; i < 6; i++) {
        r.addLabelToNode(i, i);
    }
    int node = r.addNode();
    r.addLabelToNode(6, node);
    r.addLabelToNode(7, node);
    for (int i = 0; i < 4; i++) {
        r.addEdge(node, i);
    }
    
    std::vector<BaseRegion*> toGlue;
    BaseRegion b1(3);
    node = b1.addNode();
    for (int i = 0; i < 3; i++) {
        b1.addEdge(node, i);
    }
    b1.addLabelToNode(0, 0);
    b1.addLabelToNode(1, 1);
    b1.addLabelToNode(6, 2);
    toGlue.push_back(&b1);

    BaseRegion b2(3);
    for (int i = 0; i < 3; i++) {
        node = b2.addNode();
        b2.addEdge(node, i);
        b2.addEdge(node, (i+1)%3);
    }
    b2.addLabelToNode(2, 0);
    b2.addLabelToNode(3, 1);
    b2.addLabelToNode(7, 2);
    toGlue.push_back(&b2);
    
    r.glue(toGlue);
    
    BaseRegion shouldEqual(6);
    for (int i = 0; i < 6; i++) {
        shouldEqual.addLabelToNode(i, i);
    }
    node = shouldEqual.addNode();
    for (int i = 0; i < 4; i++) {
        shouldEqual.addEdge(node, i);
    }
    
    node = shouldEqual.addNode();
    shouldEqual.addEdge(node, 0);
    shouldEqual.addEdge(node, 1);
    shouldEqual.addEdge(node, 6);
    
    node = shouldEqual.addNode();
    shouldEqual.addEdge(node, 2);
    shouldEqual.addEdge(node, 3);
    
    node = shouldEqual.addNode();
    shouldEqual.addEdge(node, 3);
    shouldEqual.addEdge(node, 6);
    
    node = shouldEqual.addNode();
    shouldEqual.addEdge(node, 6);
    shouldEqual.addEdge(node, 2);
    
    REQUIRE( r.isEqual(shouldEqual));
    
}

TEST_CASE( "Testing multiple complex gluing2", "[BaseRegion]" ) {
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    
    BaseRegion R(4);
    int s = R.addNode();
    R.addEdge(a, s);
    
    int e = R.addNode();
    R.addEdge(e, c);
    R.addEdge(s, e);
    R.addLabelToNode(a, a);
    R.addLabelToNode(b, b);
    R.addLabelToNode(c, c);
    R.addLabelToNode(d, d);
    R.addLabelToNode(s, s);
    R.addLabelToNode(e, e);
    
    std::vector<BaseRegion*> toGLue;
    
    BaseRegion R1(5);
    R1.addEdge(0, 2);
    R1.addEdge(0, 3);
    R1.addLabelToNode(s, 0);
    R1.addLabelToNode(a, 1);
    R1.addLabelToNode(b, 2);
    R1.addLabelToNode(c, 3);
    R1.addLabelToNode(e, 4);
    toGLue.push_back(&R1);
    
    BaseRegion R2(5);
    R2.addEdge(0, 2);
    R2.addEdge(0, 3);
    R2.addLabelToNode(s, 0);
    R2.addLabelToNode(e, 1);
    R2.addLabelToNode(c, 2);
    R2.addLabelToNode(d, 3);
    R2.addLabelToNode(a, 4);
    toGLue.push_back(&R2);
    
    R.glue(toGLue);
    
    REQUIRE( R.isValid());
    
}

TEST_CASE( "Testing multiple complex gluing3", "[BaseRegion]" ) {
    int a = 0;
    int b = 1;
    int c = 2;
    
    BaseRegion R(3);
    
    // We have at least on node in S
    int s = R.addNode();
    R.addEdge(a, s);
    
    int node = R.addNode();
    R.addEdge(s, node);
    R.addEdge(c, node);
    
    R.addLabelToNode(a, a);
    R.addLabelToNode(b, b);
    R.addLabelToNode(c, c);
    R.addLabelToNode(s, s);
    R.addLabelToNode(node, node);
    
    BaseRegion R_5hat(5);
    R_5hat.addEdge(0, 2);
    R_5hat.addEdge(0, 3);
    REQUIRE( R_5hat.isValid());
    
    BaseRegion R_4hat(4);
    R_4hat.addEdge(1, 3);
    REQUIRE( R_4hat.isValid());
    
    std::vector<BaseRegion*> toGLue;
    
    R_5hat.addLabelToNode(s, 0);
    R_5hat.addLabelToNode(a, 1);
    R_5hat.addLabelToNode(b, 2);
    R_5hat.addLabelToNode(c, 3);
    R_5hat.addLabelToNode(node, 4);
    toGLue.push_back(&R_5hat);
    
    R_4hat.addLabelToNode(s, 0);
    R_4hat.addLabelToNode(node, 1);
    R_4hat.addLabelToNode(c, 2);
    R_4hat.addLabelToNode(a, 3);
    toGLue.push_back(&R_4hat);
    
//    cout << "before glue label to node: " << endl;
//    for(std::map<int, int>::const_iterator map_it = R.labelToNode.begin(); map_it != R.labelToNode.end(); map_it++){
//        cout << map_it->first << ":" << map_it->second << endl;
//    }
//    
//    cout << "before glue node to label: " << endl;
//    for (std::map<int, std::set<int> >::const_iterator map_it = R.nodeToLabels.begin(); map_it != R.nodeToLabels.end(); map_it++) {
//        int node = map_it->first;
//        cout << "node: " << node << "  ";
//        std::set<int> labelSet = map_it->second;
//        for(std::set<int>::const_iterator set_it = labelSet.begin(); set_it != labelSet.end(); set_it++){
//            cout << *set_it;
//        }
//        cout << endl;
//    }
    
    R.glue(toGLue);
//    cout << "after glue label to node: " << endl;
//    for(std::map<int, int>::const_iterator map_it = R.labelToNode.begin(); map_it != R.labelToNode.end(); map_it++){
//        cout << map_it->first << ":" << map_it->second << endl;
//    }
//    
//    cout << "after glue node to label: " << endl;
//    for (std::map<int, std::set<int> >::const_iterator map_it = R.nodeToLabels.begin(); map_it != R.nodeToLabels.end(); map_it++) {
//        int node = map_it->first;
//        cout << "node: " << node << "  ";
//        std::set<int> labelSet = map_it->second;
//        for(std::set<int>::const_iterator set_it = labelSet.begin(); set_it != labelSet.end(); set_it++){
//            cout << *set_it;
//        }
//        cout << endl;
//    }
    
    std::cout << "5hat:" << std::endl;
    R_5hat.printRegion();
    std::cout << "4hat:" << std::endl;
    R_4hat.printRegion();
    std::cout << "glued:" << std::endl;
    R.printRegion();
    std::cout << "done print" << std::endl;
    
    REQUIRE( R.isValid());
    std::cout << "done method" << std::endl;
    
}

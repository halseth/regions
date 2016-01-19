//
//  generate_basic_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#include "generate_basic_regions.hpp"

#include "TaggedRegion.hpp"


const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;

const int BIG = 0;
const int LEFT = 1;
const int RIGHT = 2;

void generate_basic_regions(map<vector<int>, BaseRegion> &sign_minimal) {
    
    cout << "big region" << endl;
    
    for (int up_left_deg2 = 0; up_left_deg2 <= 1; up_left_deg2++) {
        for (int down_left_deg2 = 0; down_left_deg2 <= 1; down_left_deg2++) {
            for (int left_deg3 = 0; left_deg3 <= 1; left_deg3++) {
                for (int left_edge = 0; left_edge <= 1; left_edge++) {
                    for (int up_right_deg2 = 0; up_right_deg2 <= 1; up_right_deg2++) {
                        for (int down_right_deg2 = 0; down_right_deg2 <= 1; down_right_deg2++) {
                            for (int right_deg3 = 0; right_deg3 <= 1; right_deg3++) {
                                for (int right_edge = 0; right_edge <= 1; right_edge++) {
                                    TaggedRegion basic(6,a,d,BIG);
                                    
                                    if (up_left_deg2) {
                                        int node = basic.addNode();
                                        basic.addEdge(a, node);
                                        basic.addEdge(b, node);
                                    }
                                    
                                    if (down_left_deg2) {
                                        int node = basic.addNode();
                                        basic.addEdge(a, node);
                                        basic.addEdge(f, node);
                                    }
                                    
                                    if (left_deg3) {
                                        int node = basic.addNode();
                                        basic.addEdge(a, node);
                                        basic.addEdge(b, node);
                                        basic.addEdge(f, node);
                                    }
                                    
                                    if (left_edge) {
                                        basic.addEdge(b, f);
                                    }
                                    
                                    if (up_right_deg2) {
                                        int node = basic.addNode();
                                        basic.addEdge(d, node);
                                        basic.addEdge(c, node);
                                    }
                                    
                                    if (down_right_deg2) {
                                        int node = basic.addNode();
                                        basic.addEdge(d, node);
                                        basic.addEdge(e, node);
                                    }
                                    
                                    if (right_deg3) {
                                        int node = basic.addNode();
                                        basic.addEdge(d, node);
                                        basic.addEdge(c, node);
                                        basic.addEdge(e, node);
                                    }
                                    
                                    if (right_edge) {
                                        basic.addEdge(c, e);
                                    }
                                    
                                    store_sign(basic, sign_minimal);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << "left region" << endl;
    
    for (int up_left_deg2 = 0; up_left_deg2 <= 1; up_left_deg2++) {
        for (int down_left_deg2 = 0; down_left_deg2 <= 1; down_left_deg2++) {
            for (int left_deg3 = 0; left_deg3 <= 1; left_deg3++) {
                for (int left_edge = 0; left_edge <= 1; left_edge++) {
                    TaggedRegion basic(5,a,d, LEFT);
                    
                    for (int i = 0; i < basic.getSize(); i++) {
                        basic.removeEdge(i, (i+1)%basic.getSize());
                    }
                    
                    basic.addEdge(a, b);
                    basic.addEdge(b, c);
                    basic.addEdge(c, d);
                    basic.addEdge(c, e);
                    basic.addEdge(e, a);
                    
                    if (up_left_deg2) {
                        int node = basic.addNode();
                        basic.addEdge(a, node);
                        basic.addEdge(b, node);
                    }
                    
                    if (down_left_deg2) {
                        int node = basic.addNode();
                        basic.addEdge(a, node);
                        basic.addEdge(e, node);
                    }
                    
                    if (left_deg3) {
                        int node = basic.addNode();
                        basic.addEdge(a, node);
                        basic.addEdge(b, node);
                        basic.addEdge(e, node);
                    }
                    
                    if (left_edge) {
                        basic.addEdge(b, e);
                    }
                    
                    store_sign(basic, sign_minimal);
                }
            }
        }
    }
    
    for (int up_right_deg2 = 0; up_right_deg2 <= 1; up_right_deg2++) {
        for (int down_right_deg2 = 0; down_right_deg2 <= 1; down_right_deg2++) {
            for (int right_deg3 = 0; right_deg3 <= 1; right_deg3++) {
                for (int right_edge = 0; right_edge <= 1; right_edge++) {
                    TaggedRegion basic(5,a,d, RIGHT);
                    
                    for (int i = 0; i < basic.getSize(); i++) {
                        basic.removeEdge(i, (i+1)%basic.getSize());
                    }
                    
                    basic.addEdge(a, b);
                    basic.addEdge(b, c);
                    basic.addEdge(c, d);
                    basic.addEdge(d, e);
                    basic.addEdge(e, b);
                    
                    if (up_right_deg2) {
                        int node = basic.addNode();
                        basic.addEdge(d, node);
                        basic.addEdge(c, node);
                    }
                    
                    if (down_right_deg2) {
                        int node = basic.addNode();
                        basic.addEdge(d, node);
                        basic.addEdge(e, node);
                    }
                    
                    if (right_deg3) {
                        int node = basic.addNode();
                        basic.addEdge(d, node);
                        basic.addEdge(c, node);
                        basic.addEdge(e, node);
                    }
                    
                    if (right_edge) {
                        basic.addEdge(c, e);
                    }
                    
                    store_sign(basic, sign_minimal);
                }
            }
        }
    }

    cout << "done basics" << endl;
    print_map(sign_minimal);
}

void save_new(BaseRegion &R, map<vector<int>,BaseRegion> &signature_minimal, map<vector<int>,BaseRegion> &new_regs) {
    if(!R.isValid()){
        cout << "not valid!" << endl;
        R.printRegion();
        exit(0);
    }
    
    vector<int> sign;
    R.getSignature(sign);
    if(signature_minimal.count(sign) == 0 )
    {
        //cout << "Saving new signature because (signature_minimal.count(sign) == 0)" << endl;
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
        new_regs.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else if( signature_minimal.at(sign).getSize() > R.getSize() )
    {
        //cout << "Saving new signature because signature_minimal.at(sign).size() =" << signature_minimal.at(sign).size() << " and R.size()=" << R.size() << endl;
        signature_minimal.erase(sign);
        signature_minimal.insert(pair<vector<int>, BaseRegion>(sign, R));
        new_regs.erase(sign);
        new_regs.insert(pair<vector<int>, BaseRegion>(sign, R));
    }
    else
    {
        return;
    }
    
}

void build_from_basic_regions(map<vector<int>, BaseRegion> &sign_minimal, const map<vector<int>, BaseRegion> &basic_regions) {
    map<vector<int>,BaseRegion> new_regs;
    
    for (map<vector<int>, BaseRegion>::const_iterator it = basic_regions.begin(); it != basic_regions.end(); it++) {
        BaseRegion R = it->second;
        save_new(R, sign_minimal, new_regs);
    }
    
    while (!new_regs.empty()) {
        cout << "starting while. new_regs.size()=" << new_regs.size() << endl;
        
        map<vector<int>, BaseRegion> temp_new_regs;
        
        int iteration = 0;
        for (map<vector<int>, BaseRegion>::const_iterator it = new_regs.begin(); it != new_regs.end(); it++) {
            cout << "iteration " << iteration++ << " of " << new_regs.size() << endl;
            
            for (map<vector<int>, BaseRegion>::const_iterator it_basic = basic_regions.begin(); it_basic != basic_regions.end(); it_basic++) {
                BaseRegion upper = it->second;
                BaseRegion lower = it_basic->second;
                
                int upperType = BIG;
                
                if (upper.getBoundarySize() < 6) {
                    if (!upper.isAdjacent(a, e)) {
                        upperType = RIGHT;
                    } else if(!upper.isAdjacent(d, e)) {
                        upperType = LEFT;
                    } else {
                        cout << "err0";
                        exit(0);
                    }
                }
                
                int lowerType = BIG;
                if (lower.getBoundarySize() < 6) {
                    if (!lower.isAdjacent(a, e)) {
                        lowerType = RIGHT;
                    } else if(!lower.isAdjacent(d, e)) {
                        lowerType = LEFT;
                    } else {
                        cout << "err0";
                        exit(0);
                    }
                }
                
                if (upperType == RIGHT) {
                    
                    if (lowerType == BIG) {
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        outer.addLabelToNode(6, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(6, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(1, b);
                        lower.addLabelToNode(6, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        lower.addLabelToNode(5, f);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                    } else if (lowerType == LEFT) {
                        
                        vector<BaseRegion*> toGlue;
                        Region outer(6,a,d);
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(4, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(1, b);
                        lower.addLabelToNode(4, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(5, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                    } else if (lowerType == RIGHT) {
                        
                        vector<BaseRegion*> toGlue;
                        TaggedRegion outer(5,a,d, RIGHT);
                        
                        for (int i = 0; i < outer.getSize(); i++) {
                            outer.removeEdge(i, (i+1)%outer.getSize());
                        }
                        
                        outer.addEdge(a, b);
                        outer.addEdge(b, c);
                        outer.addEdge(c, d);
                        outer.addEdge(d, e);
                        outer.addEdge(e, b);
                        
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(5, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(1, b);
                        lower.addLabelToNode(5, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                        
                    } else {
                        cout << "err1";
                        exit(0);
                    }
                } else if(upperType == LEFT) {
                    if (lowerType == BIG) {
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        outer.addLabelToNode(6, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(6, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(6, b);
                        lower.addLabelToNode(2, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        lower.addLabelToNode(5, f);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                    } else if (lowerType == LEFT) {
                        
                        vector<BaseRegion*> toGlue;
                        TaggedRegion outer(5,a,d, LEFT);
                        
                        for (int i = 0; i < outer.getSize(); i++) {
                            outer.removeEdge(i, (i+1)%outer.getSize());
                        }
                        
                        outer.addEdge(a, b);
                        outer.addEdge(b, c);
                        outer.addEdge(c, d);
                        outer.addEdge(c, e);
                        outer.addEdge(e, a);
                        
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(5, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(5, b);
                        lower.addLabelToNode(2, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);

                    } else if (lowerType == RIGHT) {
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(5, e);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(5, b);
                        lower.addLabelToNode(2, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                        
                    } else {
                        cout << "err1";
                        exit(0);
                    }
                } else if (upperType == BIG) {
                    if (lowerType == RIGHT) {
                        
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        outer.addLabelToNode(6, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(6, e);
                        upper.addLabelToNode(5, f);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(5, b);
                        lower.addLabelToNode(6, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                    } else if(lowerType == LEFT) {
                        
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        int node = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        outer.addLabelToNode(6, node);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(4, e);
                        upper.addLabelToNode(6, f);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(6, b);
                        lower.addLabelToNode(4, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(5, e);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                        
                    } else if (lowerType == BIG) {
                        
                        
                        vector<BaseRegion*> toGlue;
                        
                        Region outer(6,a,d);
                        int node6 = outer.addNode();
                        int node7 = outer.addNode();
                        
                        outer.addLabelToNode(0, a);
                        outer.addLabelToNode(1, b);
                        outer.addLabelToNode(2, c);
                        outer.addLabelToNode(3, d);
                        outer.addLabelToNode(4, e);
                        outer.addLabelToNode(5, f);
                        outer.addLabelToNode(6, node6);
                        outer.addLabelToNode(7, node7);
                        
                        upper.addLabelToNode(0, a);
                        upper.addLabelToNode(1, b);
                        upper.addLabelToNode(2, c);
                        upper.addLabelToNode(3, d);
                        upper.addLabelToNode(7, e);
                        upper.addLabelToNode(6, f);
                        toGlue.push_back(&upper);
                        
                        lower.addLabelToNode(0, a);
                        lower.addLabelToNode(6, b);
                        lower.addLabelToNode(7, c);
                        lower.addLabelToNode(3, d);
                        lower.addLabelToNode(4, e);
                        lower.addLabelToNode(5, f);
                        toGlue.push_back(&lower);
                        
                        outer.glue(toGlue);
                        
                        save_new(outer, sign_minimal, temp_new_regs);
                        
                    } else {
                        cout << "err1";
                        exit(0);
                    }
                } else {
                    cout << "err2";
                    exit(0);
                }
                
            }
        }
        
        new_regs.clear();
        
        for (map<vector<int>, BaseRegion>::const_iterator it = temp_new_regs.begin(); it != temp_new_regs.end(); it++) {
            new_regs.insert(pair<vector<int>, BaseRegion>(it->first, it->second));
        }
        
    }
    
    cout << "building done" << endl;
    print_map(sign_minimal);
    
}


//
//  choose_regions.cpp
//  New_method
//
//  Created by Johan Torås Halseth on 18/01/16.
//  Copyright © 2016 Johan Torås Halseth. All rights reserved.
//

#include "choose_regions.hpp"

vector<BaseRegion> choose_outer_regions(int size, bool edge,
                                        const vector<BaseRegion> &outer_3regions_with_edge,
                                        const vector<BaseRegion> &outer_3regions_without_edge,
                                        const vector<BaseRegion> &outer_4regions_with_edge,
                                        const vector<BaseRegion> &outer_4regions_without_edge
                                        ){
    if (size == 3) {
        if (edge) return outer_3regions_with_edge;
        else return outer_3regions_without_edge;
    } else if (size == 4) {
        if (edge) return outer_4regions_with_edge;
        else return outer_4regions_without_edge;
    } else {
        cout << "Ivalid size: " << size << endl;
        exit(1);
    }
}

vector<BaseRegion> choose_outer_regions(bool edge,
                                        const vector<BaseRegion> &regions_with_edge,
                                        const vector<BaseRegion> &regions_without_edge
                                        ){
    if (edge) return regions_with_edge;
    else return regions_without_edge;
}

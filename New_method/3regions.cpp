#include "SmallRegion.h"
#include <vector>
using namespace std;

extern void store_sign(SmallRegion &R, std::map<vector<int>,SmallRegion > &signature_minimal);

void generate3regions(std::map<vector<int>,SmallRegion > &signature_minimal){
    int counter = 0;
    int v = 0;
    int a = 1;
    int b = 2;
    
    for (int deg2_v_a = 0; deg2_v_a <= 1; deg2_v_a++) {
        for(int deg2_v_b = 0; deg2_v_b <= 1; deg2_v_b++){
            for (int deg_3 = 0; deg_3 <= 1; deg_3++) {
                SmallRegion R(3,v,counter++);
                if(deg2_v_a){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, a);
                }
                if(deg2_v_b){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, b);
                }
                if(deg_3){
                    int c = R.addNode();
                    R.addEdge(c, v);
                    R.addEdge(c, a);
                    R.addEdge(c, b);
                }
                store_sign(R, signature_minimal);
            }
        }
    }
    
    cout << "done with 3regions" << endl;
}
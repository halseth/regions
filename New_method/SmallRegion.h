#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/planarity.h>
#include <lemon/dim2.h>
#include <lemon/core.h>

extern void gen_subsets(int n, int k, std::vector<std::vector<int> > &subsets);
#define MAX_SIZE 32

class SmallRegion{
	
private:
	std::vector<int> C;
	int endpoint1;
	int endpoint2;
	int boundary_nodes;
	int internal_nodes;
	std::vector<std::vector<bool> > adj;
	int region_id;
	
    // Calculates the signature zeta(X,S) of a region
    int signature(std::vector<int> X, std::vector<int> S){
		//Helper array to calculate indexes of vertices
		int xs[this->size()];
		for(int i = 0; i < this->size(); i++){
			xs[i] = 0;
		}
		for(int i = 0; i < X.size(); i++){
			xs[X[i]] = 1;
		}
		int item = 0;
		for(int i = 0; i < this->size(); i++){
			if(xs[i] == 0){
				xs[item++] = i;
			}
		}		
		
        int best = this->size();
        // Try all possible dominating sets and check if they are good
		int x_size = X.size();
		
		// Size of set in addition to X is max 2 (we can always pick v and w)
        for(int k = 0; k <= 2; k++){
			std::vector<std::vector<int> > d_subsets;
			gen_subsets(this->size()-1-x_size, k, d_subsets);
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

                bool dominated[this->size()];
				for(int j = 0; j < this->size(); j++){
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

                for(int v = 0; v < this->size(); v++){
                    valid &= dominated[v];
                }

                //Check if valid and smallest possible
                if(valid && D.size() < best){
                    best = D.size();
                } 

            }
        }
        return best - X.size();
    }
	
public:
	
	int getEndpoint1(){ return endpoint1;}
	int getEndpoint2(){ return endpoint2;}
	
	SmallRegion(int boundary_size, int endpoint2_num, int id){
		region_id = id;
		endpoint1 = 0;
		endpoint2 = endpoint2_num;
		boundary_nodes = boundary_size;
		internal_nodes = 0;
		for(int i = 0; i < MAX_SIZE; i++){
			std::vector<bool> t;
			for(int j = 0; j < MAX_SIZE; j++){
				t.push_back(false);
			}
			adj.push_back(t);
		}
		for(int i = 0; i < boundary_size; i++){
			C.push_back(i);
		}
		
		for(int i = 0; i < C.size(); i++){
			adj[ C[i] ][ C[(i+1)%C.size()] ] = true;
			adj[ C[(i+1)%C.size()] ][ C[i] ] = true;
		}
	}
	
	int addNode(){
		if(boundary_nodes + internal_nodes >= MAX_SIZE){
			std::cout << "Adding node nr " << boundary_nodes + internal_nodes << ". MAX_SIZE=" << MAX_SIZE << ". Exiting." << std::endl;
			exit(0);
		}
   // std::cout << " returning node " << boundary_nodes + internal_nodes << std::endl;
		return boundary_nodes + internal_nodes++;
	}
	
	void addEdge(int from, int to){
    //if((from == 3 && to == 4) || (from == 4 && to == 3)){
      //std::cout << "-------------------------- connected " << from << " to " << to << std::endl;
      //}
		adj[from][to] = true;
		adj[to][from] = true;
	}
	
	int size(){
		return boundary_nodes + internal_nodes;
	}
	
	bool isAdjacent(int a, int b){
		return adj[a][b];
	}
	
	bool isValid(){
		// The endpoints must dominate the whole region
		using namespace lemon;
		using namespace std;
		
		ListGraph g;
		std::vector<ListGraph::Node> gnodes;
		
		for(int i = 0; i < size(); i++){
			gnodes.push_back(g.addNode());
		}
		
		for(int node = 0; node < size(); node++){
			for(int i = node+1; i < adj[node].size(); i++){
				if(adj[node][i]){
					g.addEdge(gnodes[node], gnodes[i]);
				}
			}
		}
	
		int n = countNodes(g);
		int l = countEdges(g);
		bool valid = true;
		bool* dominated  = new bool[n]();
	
		dominated[endpoint1] = true;
		for (ListGraph::OutArcIt arcIt(g, g.nodeFromId(endpoint1)); arcIt != INVALID; ++arcIt) {

		    ListGraph::Arc arc(arcIt);
		    ListGraph::Node oppositeNode( g.oppositeNode(g.nodeFromId(endpoint1), arc) );
			//cout << "Found neighbor to " << g.id(endpoint1) << ": " << g.id(oppositeNode) << endl;
			dominated[g.id(oppositeNode)] = true;
		}
	
		dominated[endpoint2] = true;
	
		for(int i = 0; i < n; i++){
			if(!dominated[i]){
				valid = false;
				cout << "Found vertex not dominated: " << i << endl;
			} 
		}
				
		// It must be planar with all internal vertices drawn on the inside
		ListGraph::Node gadget = g.addNode();
		for(int i = 0; i < C.size(); i++){
			g.addEdge(gadget, g.nodeFromId(C[i]));
		}
	
		if(!checkPlanarity(g)){
			cout << "Not planar!" << endl;
			valid = false;
		}
		else {
			//cout << "Planar!" << endl;
		
		}
	
	
		// Reduction rules?
		delete[] dominated;
		return valid;
	}
	
	void getSignature(std::vector<int> &signature){
		signature.clear();
		signature.push_back(this->boundary_nodes);
		
		for(int s_set = 0; s_set <= std::pow(2,C.size())-1; s_set++){
			for(int x_set = 0; x_set <= std::pow(2, C.size())-1; x_set++){
				if((s_set & x_set) != 0) continue; // overlaps
				
				std::vector<int> X;
				std::vector<int> S;
				
				for(int i = 0; i < C.size(); i++){
					if(s_set & (1 << i)) S.push_back(i);
					if(x_set & (1 << i)) X.push_back(i);
				}
				/*std::cout << "X: ";
				for(int i = 0; i < X.size(); i++){
					std::cout << X[i] << " ";
				}	
				std::cout << " S: ";
				for(int i = 0; i < S.size(); i++){
					std::cout << S[i] << " ";
				}
				std::cout << std::endl;*/
				
				signature.push_back(this->signature(X, S));
			}
		}
		/*		
			std::vector<std::vector<int> > S_sets;
			gen_subsets(C.size()-1, s_size, S_sets);
			
			for(int x_size = 0; x_size <= C.size(); x_size++){
				std::vector<std::vector<int> > X_sets;
				gen_subsets(C.size()-1, x_size, X_sets);
				
				for(int i = 0; i < S_sets.size(); i++){
					for(int j = 0; j < X_sets.size(); j++){
						signature.push_back(this->signature(X_sets[j], S_sets[i]));
					}
				}
				
			}
		}*/
	}
	
	void draw_region(std::string filename){


		using namespace lemon;
		using namespace std;
		
		ListGraph g;
		std::vector<ListGraph::Node> gnodes;
		for(int i = 0; i < size(); i++){
			gnodes.push_back(g.addNode());
		}
		
		for(int node = 0; node < size(); node++){
			for(int i = node+1; i < adj[node].size(); i++){
				if(adj[node][i]){
					g.addEdge(gnodes[node], gnodes[i]);
				}
			}
		}
		
		PlanarEmbedding<ListGraph> embedding(g);
		embedding.run();

		PlanarDrawing<ListGraph> drawing(g);
		drawing.run(embedding.embeddingMap());
		const PlanarDrawing<ListGraph>::PointMap * points = &drawing.coords();
		int n = countNodes(g);
		int m = countEdges(g);
	
		ofstream file;
		std::cout << "filename: " << filename << std::endl;
		file.open(filename);
	
		if(!file.is_open()){
			std::cout << "ERROR opening file "<< std::endl;
		}
	
		vector<int> x;
		vector<int> y;
	
		for(int i = 0; i < n; i++){
			//cout << "node " << i << ":"<< endl;
			lemon::dim2::Point<int> p = (*points)[g.nodeFromId(i)];
			x.push_back(p.x);
			y.push_back(p.y);
			if(i == endpoint1 || i == endpoint2){
				file << "end ";
			} else if(i < boundary_nodes){
				file << "bound ";
			}
			file << p.x << " " << p.y << std::endl;
		}
		for(ListGraph::ArcIt e(g); e!=lemon::INVALID; ++e){
			file << x[g.id(g.source(e))] << " " << y[g.id(g.source(e))] << " "
				<< x[g.id(g.target(e))] << " " << y[g.id(g.target(e))] << std::endl;
		}
		
		file.close();
		
	}
	
	void copy(SmallRegion &ret){
		ret.C = std::vector<int>(this->C.begin(), this->C.end());
		ret.internal_nodes = this->internal_nodes;
		ret.boundary_nodes = this->boundary_nodes;
		ret.endpoint1 = this->endpoint1;
		ret.endpoint2 = this->endpoint2;
		for(int i = 0; i < MAX_SIZE; i++){
			for(int j = 0; j < MAX_SIZE; j++){
				ret.adj[i][j] = this->adj[i][j];
			}
		}
	}
	
	int getId(){
		return region_id;
	}
	
	std::string signatureString(){
		std::stringstream ss;
		std::vector<int> signature;
	
		getSignature(signature);
	
		for(int i = 0; i < signature.size(); i++){
			ss << signature[i] << " ";
		}
		return ss.str();
	}
    
    std::string getDotFormat(){
        std::stringstream ss;
        ss << "graph g {" << std::endl;
        for(int i = 0; i < size(); i++) {
            for(int j = i+1; j < size(); j++){
                if(adj[i][j]) ss << i << " -- " << j << ";" << std::endl;
            }
        }
        ss << "}" << std::endl;
        return ss.str();
    }
};
#include <vector>
#include <iostream>

void subsets2(int n, int current_int, int rem, std::vector<int> &current_set,
                                 std::vector<std::vector<int> > &subsets) {

        if(rem == 0){ // subset complete
            subsets.push_back(current_set);
			//std::cout << "Subset complete"<< std::endl;
            return;
        } else{
        	//std::cout << "Remainding: " << rem << std::endl;
        }


        if (current_int > n){
            // uncomplete subset
			//std::cout << " not complete subset " << std::endl;
            return;
        }  else {
        	//std::cout << "current: " << current_int << std::endl;
        }


        // current is in
        std::vector<int> clone(current_set.begin(), current_set.end());
        clone.push_back(current_int);
        subsets2(n, current_int+1, rem - 1, clone, subsets);

        //first is not in
        subsets2(n, current_int+1, rem, current_set, subsets);

 }

/* Creates all subsets of size k from the integers 0..n */
void gen_subsets(int n, int k, std::vector<std::vector<int> > &subsets){
		std::vector<int> empty;
        subsets2(n, 0, k, empty, subsets);
}

/*
int main(){
	std::vector<std::vector<int> > subsets;
	gen_subsets(6,1, subsets);
	std::cout << "# subsets: " << subsets.size() << std::endl;
	for(int i = 0; i < subsets.size(); i++){
		std::cout << "Subset: ";
		for(int j = 0; j < subsets[i].size(); ++j){
			std::cout << subsets[i][j] << " ";
		}
		std::cout << std::endl;
	}
}*/


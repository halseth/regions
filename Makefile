parallel:
	g++ -o multi_threaded -fopenmp -DPARALLEL New_method/*.cpp
		 
single:
	g++ -o single_threaded -fopenmp New_method/*.cpp
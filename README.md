# Signature minimal region enumerator
Enumerates a signature minimal detached region for every signature, as described in my Master's thesis.

* Should be run on a parallel computer, as it is heavily parallelized, and takes about 4 days on a semi-powerful 72 core computer
* Requires the graph library Lemon (https://lemon.cs.elte.hu/trac/lemon) to compile. Make sure it is in GCC/G++'s include path
* For parallel build it requires OpenMP, which is included with GCC. Tested on GCC 4.7.

#Compile:
For parallel build: 
```
make parallel
```
For single-threaded build:
```
make single
```

#Output:
If you don't want to use your days waiting for the program to finish running, the graphs it generates on a run is found in the folder 
`generated_output/`. This contains lists of graphs on the format `b i v1 v2 v3 v4 ...`, where `b` is the boundary size of the region, `i` is the number of internal vertices, and the following are pairs of vertices having an edge between them. Note that vertices `0,1,...,b-1` are the boundary vertices
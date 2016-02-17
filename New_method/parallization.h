//
//  parallization.h
//  New_method
//
//  Created by Johan Torås Halseth on 29/12/15.
//  Copyright © 2015 Johan Torås Halseth. All rights reserved.
//

#ifndef parallization_h
#define parallization_h

// with OMP
#ifdef PARALLEL
#include <omp.h>
#define THREAD_ID omp_get_thread_num()
#define NUM_THREADS omp_get_num_threads()
#elif
// without OMP
#define THREAD_ID 0
#define NUM_THREADS 1
#endif


#endif /* parallization_h */

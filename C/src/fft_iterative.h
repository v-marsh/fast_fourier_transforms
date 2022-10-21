#ifndef FFT_ITERATIVE
#define FFT_ITERATIVE

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <math.h>
    #include "tools.h"


    struct complexarr
    {
        int len;
        double *re;
        double *im;
    };


    /**
     * @brief standard allocator for complex arrays
     * 
     * @param n_elements number of elements in array
     * @return struct complexarr* the allocated complex array. NOTE: free
     * memory after use with freecompelxarr
     */
    struct complexarr *alloccomplexarr(int n_elements);


    /**
     * @brief standard destructor for a complexarr object
     * 
     * @param arr complex array object to be deallocated 
     */
    void freecomplexarr(struct complexarr **arr);


    /**
     * @brief Compute powers for of a root of unity  
     * 
     * @param n_root the root of to compute powers for
     * @param maxpower maximum power to compute
     * @return complexarr * a complex array with real and complex values
     * computed for powers ranging from [0, maxpower) for the n_root'th 
     * root of unity. NOTE: release memory after use with _freerootsofunity
     */
    struct complexarr *_getrootsofunity(int n_root, int maxpower);


    /**
     * @brief standard destructor for _getrootsofunity
     * 
     * @param roots roots to be freed
     */
    void _freerootsofunity(struct complexarr **roots);


    void gentleman_sande_butterfly(struct complexarr *arr, struct complexarr *roots,
        int subprobsize, int n_subproblems);


    /**
     * @brief Compute the DFT using the decimation in frequency fast fourier
     * transform in place. This will repeatedly perform the Gentleman-Sande
     * butterfly on elements that differ by the ith bit for in decreasing
     * order. 
     * 
     * @param arr complex input array of real and imaginary values
     * @param len the length of the array
     */
    void fft_iterative_ordered(struct complexarr **arr);

#endif
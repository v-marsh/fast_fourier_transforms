#ifndef FFT_ITERATIVE
#define FFT_ITERATIVE

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <math.h>
    #include "omp.h"
    #include "tools.h"


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
#ifndef FFT_THREADED
#define FFT_THREADED

    #include <stdlib.h>
    #include <stdio.h>
    #include "tools.h"

    void fft_threaded(struct complexarr **arr);


    void gentleman_sande_butterfly_threaded(struct complexarr *arr,
        struct complexarr *roots, int subprobsize, int n_subproblems,
        int halfsize);

#endif
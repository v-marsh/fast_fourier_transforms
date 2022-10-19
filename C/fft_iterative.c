#include "fft_iterative.h"
#define PI_VALUE 3.141592653589793238


struct rootsofunity *_getrootsofunity(int nth_root, int maxpower)
{
    // Total number of powers to calculate (including 0)
    struct rootsofunity *roots = (struct rootsofunity*)malloc(sizeof(struct rootsofunity));
    roots->re = (double*)malloc(maxpower * sizeof(double));
    roots->im = (double*)malloc(maxpower * sizeof(double));
    // Determine real and imaginary roots of unity
    double arg;
    for (int i = 0; i < maxpower; i++){
        arg = 2 * PI_VALUE * i / nth_root;
        roots->im[i] = sin(-arg);
        roots->re[i] = cos(arg);
    }
    return roots;
}


void freerootsofunity(struct rootsofunity **roots)
{
    // Free allocated memory and set hanging pointers to NULL
    free((*roots)->im);
    (*roots)->im = NULL;
    free((*roots)->re);
    (*roots)->re = NULL;
    free(*roots);
    *roots = NULL;
}

void fft_iterative_compute_ordered(double **arr, int len)
{
    // 
}
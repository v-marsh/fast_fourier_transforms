#include <fft_iterative.h>


struct rootsofunity *_getrootsofunity(int nth_root, int maxpower)
{
    // Total number of powers to calculate
    int n = maxpower + 1;
    struct rootsofunity *roots = (struct rootsofunity*)malloc(sizeof(struct rootsofunity));
    roots->im = malloc(n * sizeof(double));
    roots->re = malloc(n * sizeof(double));
        
}

void 

void fft_iterative_compute_ordered(double **arr, int len)
{

}
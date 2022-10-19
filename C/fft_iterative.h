#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct rootsofunity
{
    double *re;
    double *im;
};

/**
 * @brief Compute the DFT using the decimation in frequency fast fourier
 * transform in place. This will repeatedly perform the Gentleman-Sande
 * butterfly on elements that differ by the ith bit for in decreasing
 * order 
 * 
 * @param arr (2, n) input array of real and imaginary values
 * @param len the length of the array
 */
void fft_iterative_compute_ordered(double **arr, int len);

/**
 * @brief Compute the first n powers for of a root of unity from 0 to n 
 * 
 * @param n_root the root of unity
 * @param maxpower the maximum (includsive) power
 * @return double** (2, maxpower) real and complex values for the first
 * maxpower powers for the n_root root of unity. NOTE: remember to 
 * release memory after use
 */
struct rootsofunity *_getrootsofunity(int n_root, int maxpower);

/**
 * @brief Standard destructor for a rootsofunity object
 * 
 * @param roots object to be destoyed
 */
void freerootsofunity(struct rootsofunity *roots);
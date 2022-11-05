#include "fft_iterative.h"


void gentleman_sande_butterfly(struct complexarr *arr, struct complexarr *roots,
    int subprobsize, int n_subproblems)
{
    int halfsize = (int) subprobsize / 2;
    for (int k = 0; k < n_subproblems; k++){
        int start = k * subprobsize;
        int end = start + halfsize;
        int root_pow = 0;
        struct complexnum temp;
        int ioff;
        // NOTE: THE PROBLEM IS WITH THE COMPLEX MULTIPLICATION IN SECOND HALF
        for (int i = start; i < end; i++){
            ioff = i + halfsize;
            temp.re = arr->val[i].re - arr->val[ioff].re;
            temp.im = arr->val[i].im - arr->val[ioff].im;
            arr->val[i].re += arr->val[ioff].re;
            arr->val[i].im += arr->val[ioff].im;
            arr->val[ioff].re = temp.re * roots->val[root_pow].re - temp.im * roots->val[root_pow].im;
            arr->val[ioff].im = temp.re * roots->val[root_pow].im + temp.im * roots->val[root_pow].re;
            root_pow += n_subproblems;            
        } 
    }
}


void fft_iterative_ordered(struct complexarr **arr)
{
    // Test that the input array length is equal to 2^n for some integer
    // n
    double pow_of_2 = log2((double) (*arr)->len);
    unsigned int pow_of_2_int = (unsigned int) pow_of_2;
    double epsilon = 1e-8;
    if (comparedouble(pow_of_2, pow_of_2_int, epsilon) == false)
    {
        perror("Error: input array length much be equal to 2^n");
        exit(EXIT_FAILURE);
    }
    // Create lookup table for roots of unity
    int root_n = (*arr)->len;
    int maxpower = (int) (*arr)->len / 2; 
    struct complexarr *roots = _getrootsofunity(root_n, maxpower);
    /* Compute Gentleman-Sande butterfly on all elements that differ on
    the ith bit starting with the leading bit */
    int n_subproblems = 1;
    int subprobsize = (*arr)->len;
    int halfsize = subprobsize / 2;
    while (subprobsize > 1){
        gentleman_sande_butterfly(*arr, roots, subprobsize, n_subproblems);
        subprobsize = halfsize;
        halfsize = (int) subprobsize / 2;
        n_subproblems *= 2;
    }
    struct complexarr *newarr = alloccomplexarr((*arr)->len);
    unsigned int nbits = pow_of_2_int;
    for (unsigned int i = 0; i < (*arr)->len; i++){
        newarr->val[bitreverse(i, nbits)].re = (*arr)->val[i].re;
        newarr->val[bitreverse(i, nbits)].im = (*arr)->val[i].im;
    }
    struct complexarr *arrtmp = *arr;
    *arr = newarr;
    newarr = NULL;
    _freerootsofunity(&arrtmp);
}
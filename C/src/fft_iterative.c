#include "fft_iterative.h"


struct complexarr *alloccomplexarr(int n_elements)
{
    struct complexarr *roots = (struct complexarr*)malloc(sizeof(struct complexarr));
    roots->len = n_elements;
    roots->re = (double*)calloc(n_elements, sizeof(double));
    roots->im = (double*)calloc(n_elements, sizeof(double));
    return roots;
}


void freecomplexarr(struct complexarr **roots)
{
    // Free allocated memory and set hanging pointers to NULL
    free((*roots)->im);
    (*roots)->im = NULL;
    free((*roots)->re);
    (*roots)->re = NULL;
    free(*roots);
    *roots = NULL;
}


struct complexarr *_getrootsofunity(int nth_root, int maxpower)
{
    // Total number of powers to calculate (including 0)
    struct complexarr *roots = alloccomplexarr(maxpower);
    // Determine real and imaginary roots of unity
    double arg;
    for (int i = 0; i < maxpower; i++){
        arg = 2 * M_PI * i / nth_root;
        roots->im[i] = sin(-arg);
        roots->re[i] = cos(arg);
    }
    return roots;
}


void _freerootsofunity(struct complexarr **roots)
{
    freecomplexarr(roots);
}



void gentleman_sande_butterfly(struct complexarr *arr, struct complexarr *roots,
    int subprobsize, int n_subproblems)
{
    int halfsize = (int) subprobsize / 2;
    for (int k = 0; k < n_subproblems; k++){
        int start = k * subprobsize;
        int end = start + halfsize;
        int root_pow = 0;
        struct complexarr *temp = alloccomplexarr(2);
        // NOTE: THE PROBLEM IS WITH THE COMPLEX MULTIPLICATION IN SECOND HALF
        for (int i = start; i < end; i++){
            temp->re[0] = arr->re[i];
            temp->re[1] = arr->re[i + halfsize];
            temp->im[0] = arr->im[i];
            temp->im[1] = arr->im[i + halfsize];
            arr->re[i] = temp->re[0] + temp->re[1];
            arr->im[i] = temp->im[0] + temp->im[1];
            arr->re[i + halfsize] = (temp->re[0] - temp->re[1]) * roots->re[root_pow];
            arr->re[i + halfsize] -= (temp->im[0] - temp->im[1]) * roots->im[root_pow];
            arr->im[i + halfsize] = (temp->re[0] - temp->re[1]) * roots->im[root_pow];
            arr->im[i + halfsize] += (temp->im[0] - temp->im[1]) * roots->re[root_pow];
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
        fprintf(stderr, "Error: input array length much be equal to 2^n\n");
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
    struct complexarr *temparr = alloccomplexarr((*arr)->len);
    unsigned int nbits = pow_of_2_int;
    for (unsigned int i = 0; i < (*arr)->len; i++){
        temparr->re[bitreverse(i, nbits)] = (*arr)->re[i];
        temparr->im[bitreverse(i, nbits)] = (*arr)->im[i];
    }
    for (unsigned int i = 0; i < (*arr)->len; i++){
        (*arr)->re[i] = temparr->re[i];
        (*arr)->im[i] = temparr->im[i];
    }
    _freerootsofunity(&temparr);
}
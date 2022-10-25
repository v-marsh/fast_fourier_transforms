#include "fft_threaded.h"

void fft_threaded(struct complexarr **arr)
{
    // Test that the input array length is equal to 2^n for some integer
    // n
    unsigned int pow_of_2;
    {
        double pow_of_2_temp = log2((double) (*arr)->len);
        pow_of_2 = (unsigned int) pow_of_2_temp;
        double epsilon = 1e-8;
        if (comparedouble(pow_of_2_temp, pow_of_2, epsilon) == false){
            perror("Error: input array length much be equal to 2^n");
            exit(EXIT_FAILURE);
        }
    }
    // Create lookup table for roots of unity
    unsigned int halflen =  (unsigned int) (*arr)->len / 2; 
    struct complexarr *roots = _getrootsofunity((*arr)->len, halflen);
    // initiate variables required for nested parallel loops
    unsigned int n_subproblems = 1;
    unsigned int subprobsize = (*arr)->len;
    unsigned int halfsize = (unsigned int) subprobsize / 2;
    while (subprobsize > 1){
        gentleman_sande_butterfly_threaded(*arr, roots, subprobsize, n_subproblems, halfsize);
        subprobsize = halfsize;
        halfsize = (int) subprobsize / 2;
        n_subproblems *= 2;
    }
    struct complexarr *newarr = alloccomplexarr((*arr)->len);
    unsigned int i;
    #pragma omp parallel private(i) shared(arr, newarr)
    {
        #pragma omp for schedule(auto)
        for (i = 0; i < (*arr)->len; i++){
            newarr->re[bitreverse(i, pow_of_2)] = (*arr)->re[i];
            newarr->im[bitreverse(i, pow_of_2)] = (*arr)->im[i];
        }
    }
    struct complexarr *arrtmp = *arr;
    *arr = newarr;
    newarr = NULL;
    _freerootsofunity(&arrtmp);
}


void gentleman_sande_butterfly_threaded(struct complexarr *arr,
    struct complexarr *roots, int subprobsize, int n_subproblems,
    int halfsize)
    {
        unsigned int i, j, start, end, root_pow, id, id2;
        double tempre, tempim;
        #pragma omp parallel private(i, j, start, end, root_pow, id, id2, tempre, tempim) shared(arr, roots)
        {
            #pragma omp for schedule(auto)
            for (i = 0; i < n_subproblems; i++){
                for (j = 0; j < halfsize; j++){
                    start = i * subprobsize;
                    id = start + j;
                    id2 = id + halfsize;
                    root_pow = j * n_subproblems;
                    tempre = arr->re[id] - arr->re[id2];
                    tempim = arr->im[id] - arr->im[id2];
                    arr->re[id] += arr->re[id2];
                    arr->im[id] += arr->im[id2];
                    arr->re[id2] = tempre * roots->re[root_pow] - tempim * roots->im[root_pow];
                    arr->im[id2] = tempre * roots->im[root_pow] + tempim * roots->re[root_pow];
                } 
            }
        }
        
    }
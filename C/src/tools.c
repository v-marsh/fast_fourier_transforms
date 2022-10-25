#include "tools.h"


bool comparedouble(double val1, double val2, double epsilon)
{
    double diff = val1 - val2;
    if (diff > epsilon || -diff > epsilon) return false;
    else return true;    
}


unsigned int bitreverse(unsigned int val, unsigned int nbits)
{
    unsigned int count = nbits - 1;
    unsigned int reversed = val;
    val >>= 1;
     while(val){
        reversed <<= 1;
        reversed |= val & 1;
        val >>= 1;
        count--;
    }
    reversed <<= count;
    unsigned int used_bits = (MAXUINT >> (UINTBITS - nbits));
    reversed &= used_bits;
    return reversed;
}

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

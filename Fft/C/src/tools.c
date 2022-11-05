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
    roots->val = (struct complexnum*)calloc(n_elements, sizeof(struct complexnum));
    return roots;
}


void freecomplexarr(struct complexarr **roots)
{
    // Free allocated memory and set hanging pointers to NULL
    free((*roots)->val);
    (*roots)->val = NULL;
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
        roots->val[i].im = -sin(arg);
        roots->val[i].re = cos(arg);
    }
    return roots;
}


void _freerootsofunity(struct complexarr **roots)
{
    freecomplexarr(roots);
}


int check_pow_of_2(unsigned int value, double epsilon)
{
    double pow_of_2 = log2((double) value);
    unsigned int pow_of_2_int = (unsigned int) pow_of_2;
    if (comparedouble(pow_of_2, pow_of_2_int, epsilon) == false){
        pow_of_2_int = -1;
    }
    return pow_of_2_int;
}


unsigned int get_complement(unsigned int value, unsigned int bitnum, unsigned int maxbits)
{
    unsigned int out, mask, bits_in_value, bits_to_shift;
    bits_in_value = sizeof(value) * BITSPERBYTE;
    bits_to_shift = bits_in_value - maxbits;
    mask = pow(2, bitnum + 1);
    mask <<= bits_to_shift;
    value <<= bits_to_shift;
    out = value & mask;
    out >>= bits_to_shift;
    return out;
}
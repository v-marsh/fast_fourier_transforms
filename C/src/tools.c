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
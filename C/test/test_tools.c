#include <stdbool.h>
#include <math.h>
#include "tools.h"


int main(int argc, char ** argv)
{
    /* Check that when val1 and val2 are compard they comparedouble
    returns 1 (true) for them. Check that when val1 and val3 are 
    compared they comparedouble returns 0 (false) for them. */
    double val1 = sin(M_PI);
    double val2 = sin(0);
    double val3 = 1;
    double epsilon = 1e-8;
    if (comparedouble(val1, val2, epsilon) != true) return -1;
    if (comparedouble(val1, val3, epsilon) != false) return -1;
    
    /* Test bitreverse
    Check outputs against hand calculated values from 0 to 7*/
    unsigned int bitreversed_vals_true[] = {0, 4, 2, 6, 1, 5, 3, 7};
    unsigned int bitreversed_vals[8];
    for (unsigned int i = 0; i < 8; i++){
        bitreversed_vals[i] = bitreverse(i, 3);
        if (bitreversed_vals[i] != bitreversed_vals_true[i]) return -1;
    }    
    return 0;
}
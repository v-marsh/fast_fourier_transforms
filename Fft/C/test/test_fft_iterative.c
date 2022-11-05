#include <math.h>
#include <stdbool.h>
#include "fft_iterative.h"
#include "tools.h"


int main(int argc, char ** argv)
{
    int length = 16;
    struct complexarr *array = alloccomplexarr(length);
    for (int i = 0; i < length + 1; i++){
        array->val[i].re = i;
    }
    fft_iterative_ordered(&array);
    double fft_re_true[] = {120.0, -7.999999999999999, -8.0,
    -7.999999999999999, -8.0, -8.0, -8.0, -8.0, -8.0,
    -7.999999999999999, -8.0, -7.999999999999999, -8.0, -8.0, -8.0,
    -8.0};
    for (int i = 0; i < length; i++){
        if (comparedouble(array->val[i].re, fft_re_true[i], 1e-4) != true) return -1;
    }
    return 0;
}
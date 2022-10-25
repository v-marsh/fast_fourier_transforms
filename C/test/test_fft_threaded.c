#include "fft_threaded.h"
#include "tools.h"

int main(int argc, char **argv)
{
    int length = 16;
    struct complexarr *array = alloccomplexarr(length);
    for (int i = 0; i < length + 1; i++){
        array->re[i] = i;
    }
    fft_threaded(&array);
    double fft_re_true[] = {120.0, -7.999999999999999, -8.0,
    -7.999999999999999, -8.0, -8.0, -8.0, -8.0, -8.0,
    -7.999999999999999, -8.0, -7.999999999999999, -8.0, -8.0, -8.0,
    -8.0};
    for (int i = 0; i < length; i++){
        if (comparedouble(array->re[i], fft_re_true[i], 1e-4) != true) return -1;
    }
    return 0;
}
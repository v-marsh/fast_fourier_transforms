#include "fft_iterative.h"

int main(int argc, char **argv)
{
    /* Check that _getcomplexarr returns a roots of unity object with
    the correct values for the two powers of the first root of unity */
    struct complexarr *roots = _getrootsofunity(2, 2);
    double re_true[] = {1, -1};
    double im_true[] = {-0, -0};
    double epsilon = 1e-8;
    // Check values differ by less than epsilon
    for (int i = 0; i < 2; i++){
        double re_diff = re_true[i] - roots->re[i];
        double im_diff =  im_true[i] - roots->im[i];
        if (re_diff > epsilon || -re_diff > epsilon) return -1;
        if (im_diff > epsilon || -im_diff > epsilon) return -1;
    }
    /* Check that _freerootsofunity frees all memeory allocated by
    _getrootsofunity and set all previously allocated pointers to NULL*/
    _freerootsofunity(&roots);
    if (roots != NULL) return -1;
    return 0;
}
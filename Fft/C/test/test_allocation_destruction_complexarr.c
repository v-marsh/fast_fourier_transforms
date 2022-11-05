#include "fft_iterative.h"

int main(int argc, char **argv)
{
    // Check that complexarr is properly allocated with correct len
    int elements = 20;
    struct complexarr *arr = alloccomplexarr(elements);
    if (arr->len != elements) return -1;
    // Check that freecomplexarr properly frees as complexarr object and
    // assigns the hanging pointer to NULL
    freecomplexarr(&arr);
    if (arr != NULL) return -1;
    return 0;
}
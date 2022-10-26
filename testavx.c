#include <immintrin.h>
#include <stdio.h>

int main()
{
    double a = 1.0;
    double b = 2.0;
    __m128d val; (__m128) a, b;

    printf("%f", val[0]);
    return 0;
}
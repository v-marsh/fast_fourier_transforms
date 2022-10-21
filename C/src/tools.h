#ifndef TOOLS
#define TOOLS

    #include <math.h>
    #include <stdbool.h>
    #define MAXUINT 4294967295
    #define UINTBITS 32

    /**
     * @brief compares two double to determine if they are within epsilon of
     * each other
     * 
     * @param val1 first value to compare 
     * @param val2 second value to compare
     * @param epsilon maximum accepted difference between first and second 
     * value
     * @return true if the first and second values are within epsilon of 
     * eachother, false if the first and second values are not within epsilon of
     * eachother 
     */
    bool comparedouble(double val1, double val2, double epsilon);


    unsigned int bitreverse(unsigned int val, unsigned int count);

#endif
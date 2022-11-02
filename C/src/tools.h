#ifndef TOOLS
#define TOOLS

    #include  <stdlib.h>
    #include <stdbool.h>
    #include <math.h>
    
    #define MAXUINT 4294967295
    #define UINTBITS 32
    #define BITSPERBYTE 4

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

    /**
     * @brief calculate the bitreversed value of a number to a given 
     * number of bits
     * 
     * @param val the value to bitreverse
     * @param count the number of bits used to represent value
     * @return unsigned int the bitreversed value
     */
    unsigned int bitreverse(unsigned int val, unsigned int count);

    struct complexnum
    {
        double re;
        double im;
    };

    
    struct complexarr
    {
        unsigned int len;
        struct complexnum *val;
    };


    /**
     * @brief standard allocator for complex arrays
     * 
     * @param n_elements number of elements in array
     * @return struct complexarr* the allocated complex array. NOTE: free
     * memory after use with freecompelxarr
     */
    struct complexarr *alloccomplexarr(int n_elements);


    /**
     * @brief standard destructor for a complexarr object
     * 
     * @param arr complex array object to be deallocated 
     */
    void freecomplexarr(struct complexarr **arr);
    
    
    /**
     * @brief Compute powers for of a root of unity  
     * 
     * @param n_root the root of to compute powers for
     * @param maxpower maximum power to compute
     * @return complexarr * a complex array with real and complex values
     * computed for powers ranging from [0, maxpower) for the n_root'th 
     * root of unity. NOTE: release memory after use with _freerootsofunity
     */
    struct complexarr *_getrootsofunity(int n_root, int maxpower);


    /**
     * @brief standard destructor for _getrootsofunity
     * 
     * @param roots roots to be freed
     */
    void _freerootsofunity(struct complexarr **roots);


    /**
     * @brief Check if input value is a power of two up to a given 
     * epsilon.
     * 
     * @param value the number to check
     * @param epsilon the maxium allowed deviation from a power of two
     * @return unsigned int log2 of input if within epsilon of a power 
     * of two, otherwise -1.
     */
    int check_pow_of_2(unsigned int value, double epsilon);


    /**
     * @brief Determine the number that differs from value only on the 
     * bitnum^th bit.
     * 
     * @param value number to determine compliment for
     * @param bitnum index that compliment should differ on (0 inclusive)
     * @param maxbits number of bits used to represent value
     * @return unsigned int the compliment of value that differs on the
     * bitnum^th bit.
     */
    unsigned int find_complement(unsigned int value, unsigned int bitnum, unsigned int maxbits);


#endif
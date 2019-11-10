#ifndef MPN_H
#define MPN_H

class MPN
{
public:
    static int set_str(int*dest,char*str,const int& str_len);

    /** Add x[0:size-1] and y, and write the size least
     * significant words of the result to dest.
     * Return carry, either 0 or 1.
     * All values are unsigned.
     * This is basically the same as gmp's mpn_add_1. */
    static int add_1(int *dest,int*x,const int&size,const int&y);

    /** Multiply x[0:len-1] by y, and write the len least
     * significant words of the product to dest[0:len-1].
     * Return the most significant word of the product.
     * All values are treated as if they were unsigned
     * (i.e. masked with 0xffffffffL).
     * OK if dest==x (not sure if this is guaranteed for mpn_mul_1).
     * This function is basically the same as gmp's mpn_mul_1.
     */
    static int mul_1(int*dest,int*x,const int&len,const int&y);
};

#endif // MPN_H

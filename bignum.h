#ifndef BIGNUM_H
#define BIGNUM_H

class BigInteger
{
private:
    int ival;
    int *words;

    int bitLength=-1;
    int signnum;

    BigInteger(const int& val);

//    const static int minFixNum=-128;
//    const static int maxFixNum=127;
    static BigInteger ZERO;
    static BigInteger ONE;

    static BigInteger valueOf(const char*s);
    static BigInteger valueOf(char* digits,const int& byte_len,const bool &negative);

    /** Make a canonicalized BigInteger from an array of words.
    * The array may be reused (without copying). */
    static BigInteger make(int* words,const int&len);

    /** Calculate how many words are significant in words[0:len-1].
    * Returns the least value x such that x>0 && words[0:x-1]==words[0:len-1],
    * when words is viewed as a 2's complement integer.*/
    static int wordsNeeded(const int*words,const int&len);
public:
    ~BigInteger();
    BigInteger operator=(const BigInteger&val);
    BigInteger(const char* val);

    /** Return a (possibly-shared) BigInteger with a given long value. */
    static BigInteger valueOf(const long& val);

    /** Set dest[0:len-1] to the negation of src[0:len-1].
    * Return true if overflow (i.e. if src is -2**(32*len-1)).
    * Ok for src==dest. */
    static bool negate(int *dest,int* src,const int&len);

};

#endif // BIGNUM_H

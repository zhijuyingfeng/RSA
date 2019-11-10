#ifndef BIGNUM_H
#define BIGNUM_H

class BigInteger
{
private:
	int ival;
	int *words;

//	int bitLength = -1;
//	int signnum;

	BigInteger(const int& val);
    BigInteger canonicalize();
    bool isZero();
    bool isOne();
    bool isNegative()const;

    /** Add a BigInteger and an int, yielding a new BigInteger. */
    static BigInteger add(const BigInteger&x,const int&y);

    /** Set this to the sum of x and y.
     * OK if x==this. */
    void setAdd(const BigInteger &x,const int& y);

    /** Destructively set the value of this to a long. */
    void set(const long&y);

    /** Destructively set the value of this to the given words.
     * The words array is reused, not copied. */
    void set(const int*words,const int& len);

    /** Destructively set this to the negative of x.
    * It is OK if x==this.*/
    void setNegative(const BigInteger& x);

    /** Destructively negate this. */
    void setNegative();

	//    const static int minFixNum=-128;
	//    const static int maxFixNum=127;
	static BigInteger ZERO;
	static BigInteger ONE;

    /** Add two ints, yielding a BigInteger. */
    static BigInteger add(const int&x,const int& y);

	static BigInteger valueOf(const char*s);
	static BigInteger valueOf(char* digits, const int& byte_len, const bool &negative);

	/** Make a canonicalized BigInteger from an array of words.
	* The array may be reused (without copying). */
	static BigInteger make(int* words, const int&len);

    /** Add two BigIntegers, yielding their sum as another BigInteger. */
    static BigInteger add(BigInteger x,BigInteger y,const int&k);

	/** Calculate how many words are significant in words[0:len-1].
	* Returns the least value x such that x>0 && words[0:x-1]==words[0:len-1],
	* when words is viewed as a 2's complement integer.*/
	static int wordsNeeded(const int*words, const int&len);

    static BigInteger neg(const BigInteger& x);
    static BigInteger times(const BigInteger& x,int y);
    static BigInteger times(const BigInteger&x,const BigInteger& y);
public:
	~BigInteger();
	BigInteger(const BigInteger&val);
	BigInteger operator=(const BigInteger&val);
	BigInteger(const char* val);

    /** Return a (possibly-shared) BigInteger with a given long long value. */
    static BigInteger valueOf(const long long& val);

	/** Set dest[0:len-1] to the negation of src[0:len-1].
	* Return true if overflow (i.e. if src is -2**(32*len-1)).
	* Ok for src==dest. */
	static bool negate(int *dest, int* src, const int&len);

    BigInteger add(const BigInteger&val);
    BigInteger subtract(const BigInteger& val);
    BigInteger multiply(const BigInteger&val);

    void Show();
};

#endif // BIGNUM_H

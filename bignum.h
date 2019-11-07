#ifndef BIGNUM_H
#define BIGNUM_H

class BigNum
{
    int len;
    char* data;
public:
    BigNum();
    BigNum(const BigNum& val);

    //Copy constructor,then shift left sl(times 10^sl).
    BigNum(const BigNum& val,const int&sl);
    ~BigNum();
    BigNum(const int&len);

    //Translates the decimal string representation of a BigInteger into a BigNum.
    BigNum(const char* val);

    //Translates a integer into a BigNum.
    BigNum(const long&val);

    //Translates a integer into a BigNum,then shift left sl(times 10^sl).
    BigNum(const long&val,const int&sl);

    //Returns a BigNum whose value is (this + val).
    BigNum add(const BigNum&val)const;
    BigNum add(const int&val)const;

    //Returns a BigNum whose value is (this - val).
    BigNum subtract(const BigNum&val)const;

    //Returns a BigNum whose value is (this * val).
    BigNum multiply(const BigNum& val)const;
    BigNum multiply(const int& val)const;

    //Returns a BigNum whose value is (this / val).
    BigNum divide(const BigNum&val);

    //Returns a BigNum whose value is (this mod m).
    BigNum mod(const BigNum&m)const;

    void show()const;

    bool operator<(const BigNum&val)const;
    bool operator>(const BigNum&val)const;
    BigNum operator=(const BigNum&val);
    BigNum operator+(const BigNum&val)const;
    BigNum operator-(const BigNum&val)const;
    BigNum operator*(const BigNum&val)const;
    BigNum operator*(const int&val)const;
    BigNum operator%(const BigNum&val)const;
};

#endif // BIGNUM_H

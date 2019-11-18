#ifndef RSA_H
#define RSA_H

#include "bigint.h"

class RSA
{
    BigInteger p,q,n,lambda_n,d,e;
public:
    RSA(const BigInteger&P,const BigInteger&Q,const BigInteger&E);
    BigInteger encrypt(const BigInteger&m);
    BigInteger decrypt(const BigInteger&c);
};

#endif // RSA_H

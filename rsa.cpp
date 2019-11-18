#include "rsa.h"

RSA::RSA(const BigInteger&P,const BigInteger&Q,const BigInteger&E)
{
    this->p=P;
    this->q=Q;
    this->e=E;

    this->n=this->p.multiply(this->q);
    BigInteger p_1=this->p.subtract(BigInteger::ONE);
    BigInteger q_1=this->q.subtract(BigInteger::ONE);
    BigInteger gcd=p_1.gcd(q_1);

    this->lambda_n=p_1.divide(gcd).multiply(q_1);
    this->d=this->e.modInverse(this->lambda_n);
}

BigInteger RSA::encrypt(const BigInteger &m)
{
    return m.modPow(this->e,this->n);
}

BigInteger RSA::decrypt(const BigInteger &c)
{
    return c.modPow(this->d,this->n);
}

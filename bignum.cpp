#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "bignum.h"
#include "mpn.h"

BigInteger::BigInteger(const char* val)
{
    BigInteger result=valueOf(val);
    this->ival=result.ival;
    this->words=new int[this->ival];
    memcpy(this->words,result.words,sizeof(int)*static_cast<size_t>(this->ival));
}

BigInteger BigInteger::valueOf(const char*s)
{
    int len=static_cast<int>(strlen(s));
    if(len<=15)
    {
        return valueOf(atol(s));
    }

    int i;
    char digit;
    bool negative;
    char* bytes;

    /*
     * TODO
     * need to handle s is NULL here
    */

    char ch=s[0];
    if(ch=='-')
    {
        negative=true;
        i=1;
        bytes=new char[len-1];
    }
    else
    {
        negative=false;
        i=0;
        bytes=new char[len];
    }
    int byte_len=0;
    for(;i<len;i++)
    {
        ch=s[i];
        digit=s[i]-'0';
        bytes[byte_len++]=digit;
    }
    BigInteger ans=valueOf(bytes,byte_len,negative);
    delete []bytes;
    return ans;
}

BigInteger BigInteger::valueOf(char *digits, const int &byte_len, const bool &negative)
{
    int chars_per_word=9;
    int *words=new int[byte_len/chars_per_word+1];
    int size=MPN::set_str(words,digits,byte_len);
    if(!size)
        return ZERO;
    if(words[size-1]<0)
        words[size++]=0;
    if(negative)
        negate(words,words,size);
    BigInteger ans=make(words,size);
    delete [] words;
    return ans;
}

BigInteger::BigInteger(const int&val)
{
    this->ival=val;
    this->words=nullptr;
}

BigInteger BigInteger::ZERO(0);
BigInteger BigInteger::ONE(1);

BigInteger::~BigInteger()
{
    delete [] words;
}

bool BigInteger::negate(int *dest, int *src, const int &len)
{
    long carry=1;
    bool negative=src[len-1]<0;
    for(int i=0;i<len;i++)
    {
        carry+=(static_cast<long>(~src[i])&0xFFFFFFFFL);
        dest[i]=static_cast<int>(carry);
        carry>>=32;
    }
    return (negative&&dest[len-1]<0);
}

BigInteger BigInteger::make(int *words, const int &len)
{
    if(words==nullptr)
        return valueOf(len);
    int Len=BigInteger::wordsNeeded(words,len);
    if(Len<=1)
        return !Len?ZERO:valueOf(words[0]);
    BigInteger num(0);
    num.ival=Len;
    num.words=new int[Len];
    memcpy(num.words,words,sizeof(int)*static_cast<size_t>(Len));
    return num;
}

int BigInteger::wordsNeeded(const int *words, const int &len)
{
    int i=len;
    if(i>0)
    {
        int word=words[--i];
        if(word==-1)
        {
            while(i>0&&(word=words[i-1])<0)
            {
                i--;
                if(word!=-1)
                    break;
            }
        }
        else
        {
            while(word==0&&i>0&&(word=words[i-1])>=0)
                i--;
        }
    }
    return i+1;
}

BigInteger BigInteger::operator=(const BigInteger &val)
{
    this->ival=val.ival;
    delete [] this->words;
    if(val.words==nullptr)
    {
        this->words=nullptr;
    }
    else
    {
        this->words=new int[this->ival];
        memcpy(this->words,val.words,sizeof(int)*static_cast<size_t>(this->ival));
    }
    return *this;
}

BigInteger BigInteger::valueOf(const long &val)
{
    int i=static_cast<int>(val);
    if(static_cast<long>(i)==val)
        return BigInteger(i);
    BigInteger result(0);
    result.ival=2;
    result.words=new int[2];
    result.words[0]=i;
    result.words[1]=static_cast<int>(val>>32);
    return result;
}

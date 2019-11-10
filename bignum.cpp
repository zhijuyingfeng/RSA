#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "bignum.h"
#include "mpn.h"

BigInteger::BigInteger(const char* val)
{
	BigInteger result = valueOf(val);
	this->ival = result.ival;
    if(result.words==nullptr)
        this->words=nullptr;
    else
    {
        this->words = new int[this->ival];
        memcpy(this->words, result.words, sizeof(int)*static_cast<size_t>(this->ival));
    }
}

BigInteger BigInteger::valueOf(const char*s)
{
    if(s==nullptr)
        return ZERO;

	int len = static_cast<int>(strlen(s));
	if (len <= 15)
	{
        return valueOf(atoll(s));
	}

	int i;
	char digit;
	bool negative;
	char* bytes;

	char ch = s[0];
	if (ch == '-')
	{
		negative = true;
		i = 1;
		bytes = new char[len - 1];
	}
	else
	{
		negative = false;
		i = 0;
		bytes = new char[len];
	}
	int byte_len = 0;
	for (; i<len; i++)
	{
		ch = s[i];
		digit = s[i] - '0';
		bytes[byte_len++] = digit;
	}
	BigInteger ans = valueOf(bytes, byte_len, negative);
	delete[]bytes;
	return ans;
}

BigInteger BigInteger::valueOf(char *digits, const int &byte_len, const bool &negative)
{
	int chars_per_word = 9;
	int *words = new int[byte_len / chars_per_word + 1];
	int size = MPN::set_str(words, digits, byte_len);
	if (!size)
		return ZERO;
	if (words[size - 1]<0)
		words[size++] = 0;
	if (negative)
		negate(words, words, size);
	BigInteger ans = make(words, size);
	delete[] words;
	return ans;
}

BigInteger::BigInteger(const int&val)
{
	this->ival = val;
	this->words = nullptr;
}

BigInteger BigInteger::ZERO(0);
BigInteger BigInteger::ONE(1);

BigInteger::~BigInteger()
{
	delete[] words;
}

bool BigInteger::negate(int *dest, int *src, const int &len)
{
    long long carry = 1;
	bool negative = src[len - 1]<0;
	for (int i = 0; i<len; i++)
	{
        carry += (static_cast<long long>(~src[i]) & 0xFFFFFFFFL);
		dest[i] = static_cast<int>(carry);
		carry >>= 32;
	}
	return (negative&&dest[len - 1]<0);
}

BigInteger BigInteger::make(int *words, const int &len)
{
	if (words == nullptr)
		return valueOf(len);
	int Len = BigInteger::wordsNeeded(words, len);
	if (Len <= 1)
		return !Len ? ZERO : valueOf(words[0]);
	BigInteger num(0);
	num.ival = Len;
	num.words = new int[Len];
	memcpy(num.words, words, sizeof(int)*static_cast<size_t>(Len));
	return num;
}

int BigInteger::wordsNeeded(const int *words, const int &len)
{
	int i = len;
	if (i>0)
	{
		int word = words[--i];
		if (word == -1)
		{
			while (i>0 && (word = words[i - 1])<0)
			{
				i--;
				if (word != -1)
					break;
			}
		}
		else
		{
			while (word == 0 && i>0 && (word = words[i - 1]) >= 0)
				i--;
		}
	}
	return i + 1;
}

BigInteger BigInteger::operator=(const BigInteger &val)
{
	this->ival = val.ival;
	delete[] this->words;
	if (val.words == nullptr)
	{
		this->words = nullptr;
	}
	else
	{
		this->words = new int[this->ival];
		memcpy(this->words, val.words, sizeof(int)*static_cast<size_t>(this->ival));
	}
	return *this;
}

BigInteger BigInteger::valueOf(const long long &val)
{
	int i = static_cast<int>(val);
    if (static_cast<long long>(i) == val)
		return BigInteger(i);
	BigInteger result(0);
	result.ival = 2;
	result.words = new int[2];
	result.words[0] = i;
	result.words[1] = static_cast<int>(val >> 32);
	return result;
}

BigInteger::BigInteger(const BigInteger&val)
{
	this->ival = val.ival;
    if (val.words == nullptr)
	{
		this->words = nullptr;
	}
	else
	{
		this->words = new int[this->ival];
		memcpy(this->words, val.words, sizeof(int)*static_cast<size_t>(this->ival));
	}
}

BigInteger BigInteger::canonicalize()
{
    if(this->words!=nullptr&&
            (this->ival=this->wordsNeeded(this->words,this->ival))<=1)
    {
        if(this->ival==1)
            this->ival=this->words[0];
        delete [] this->words;
        this->words=nullptr;
    }
    return *this;
}

bool BigInteger::isOne()
{
    return this->ival==1&&this->words==nullptr;
}

bool BigInteger::isZero()
{
    return this->ival==0&&this->words==nullptr;
}

BigInteger BigInteger::add(const int &x, const int &y)
{
    return valueOf(static_cast<long long>(x)+static_cast<long long>(y));
}

void BigInteger::set(const int *words, const int &len)
{
    this->ival=len;
    delete [] this->words;
    this->words=new int[len];
    memcpy(this->words,words,sizeof(int)*static_cast<size_t>(len));
}

BigInteger BigInteger::add(const BigInteger &x, const int &y)
{
    if(x.words==nullptr)
        return BigInteger::add(x.ival,y);
    BigInteger result(ZERO);
    result.setAdd(x,y);
    return result.canonicalize();
}

void BigInteger::setAdd(const BigInteger &x, const int &y)
{
    if(x.words==nullptr)
    {
        set(static_cast<long long>(x.ival)+static_cast<long long>(y));
        return;
    }
    int len=x.ival;
    delete [] this->words;
    this->words=new int[len+1];
    long long carry=y;
    for(int i=0;i<len;i++)
    {
        carry+=static_cast<long long>(x.words[i])&0xFFFFFFFFL;
        words[i]=static_cast<int>(carry);
        carry>>=32;
    }
    if(x.words[len-1]<0)
        carry--;
    this->words[len]=static_cast<int>(carry);
    this->ival=this->wordsNeeded(words,len+1);
}

void BigInteger::set(const long &y)
{
    int i=static_cast<int>(y);
    if(y==static_cast<long long>(i))
    {
        this->ival=i;
        delete [] this->words;
        this->words=nullptr;
    }
    else
    {
        delete [] this->words;
        this->words=new int[2];
        this->ival=2;
        this->words[0]=i;
        this->words[1]=static_cast<int>(y>>32);
    }
}

BigInteger BigInteger::add(const BigInteger &val)
{
    return BigInteger::add(*this,val,1);
}

BigInteger BigInteger::neg(const BigInteger &x)
{
    int MIN_VALUE=static_cast<int>(0x80000000);
    if(x.words==nullptr&&x.ival!=MIN_VALUE)
        return valueOf(-x.ival);
    BigInteger result=ZERO;
    result.setNegative(x);
    return result.canonicalize();
}

void BigInteger::setNegative(const BigInteger &x)
{
    int len=x.ival;
    int MIN_VALUE=static_cast<int>(0x80000000);
    if(x.words==nullptr)
    {
        if(x.ival==MIN_VALUE)
            this->set(-static_cast<long long>(len));
        else
            this->set(-len);
        return;
    }
    delete []this->words;
    this->words=new int[len+1];
    if(negate(words,x.words,len))
        words[len++]=0;
    this->ival=len;
}

BigInteger BigInteger::add(BigInteger x, BigInteger y, const int &k)
{
    if(x.words==nullptr&&y.words==nullptr)
    {
        long long temp=static_cast<long long>(k)*static_cast<long long>(x.ival);
        temp*=static_cast<long long>(y.ival);
        return valueOf(temp);
    }
    if(k!=1)
    {
        if(-1==k)
        {
            y=BigInteger::neg(y);
        }
        else
            y=BigInteger::times(y,valueOf(k));
    }
    if(x.words==nullptr)
        return BigInteger::add(y,x.ival);
    else if(y.words==nullptr)
        return BigInteger::add(x,y.ival);

    //Both are big
    if(y.ival>x.ival)
    {
        //swap so that x is longer than y
        BigInteger temp=x;
        x=y;
        y=temp;
    }
    BigInteger result(0);
    result.words=new int[x.ival+1];
    int i=y.ival;
    long long carry=MPN::add_n(result.words,x.words,y.words,i);
    long long y_ext=y.words[i - 1] < 0 ? 0xffffffffL : 0;
    for(;i<x.ival;i++)
    {
        carry+=(static_cast<long long>(x.words[i])&0xFFFFFFFFL)+y_ext;
        result.words[i]=static_cast<int>(carry);
        unsigned long long temp=static_cast<unsigned long long>(carry);
        temp>>=32;
        carry=static_cast<long long>(temp);
    }
    if(x.words[i-1]<0)
        y_ext--;
    result.words[i]=static_cast<int>(carry+y_ext);
    result.ival=i+1;
    return result.canonicalize();
}

BigInteger BigInteger::subtract(const BigInteger &val)
{
    return this->add(*this,val,-1);
}

BigInteger BigInteger::times(const BigInteger &x, const BigInteger &y)
{
    if(y.words==nullptr)
        return times(x,y.ival);
    else if(x.words==nullptr)
        return times(y,x.ival);

    bool negative=false;
    int *xwords=new int[x.ival];
    int *ywords=new int[y.ival];
    int xlen=x.ival,ylen=y.ival;
    if(x.isNegative())
    {
        negative=true;
        negate(xwords,x.words,xlen);
    }
    else
    {
        negative=false;
        memcpy(xwords,x.words,sizeof(int)*static_cast<size_t>(x.ival));
    }
    if(y.isNegative())
    {
        negative=!negative;
        negate(ywords,y.words,ylen);
    }
    else
    {
        memcpy(ywords,y.words,sizeof(int)*static_cast<size_t>(y.ival));
    }

    //swap if x is shorter than y
    if(xlen<ylen)
    {
        int* twords=xwords;
        xwords=ywords;
        ywords=twords;
        int tlen=xlen;
        xlen=ylen;
        ylen=tlen;
    }

    BigInteger result=ZERO;
    result.words=new int[xlen+ylen];
    MPN::mul(result.words,xwords,xlen,ywords,ylen);
    result.ival=xlen+ylen;
    if(negative)
        result.setNegative();

    delete [] xwords;
    delete [] ywords;
    return result.canonicalize();
}

bool BigInteger::isNegative() const
{
    return (this->words==nullptr?this->ival:this->words[this->ival-1])<0;
}

void BigInteger::setNegative()
{
    this->setNegative(*this);
}

BigInteger BigInteger::times(const BigInteger &x, int y)
{
    if(y==0)
        return ZERO;
    else if(1==y)
        return x;
    else if(x.words==nullptr)
        return valueOf(static_cast<long long>(x.ival)*static_cast<long long>(y));
    int *xwords=new int[x.ival];
    memcpy(xwords,x.words,sizeof(int)*static_cast<size_t>(x.ival));
    int xlen=x.ival;
    bool negative;
    BigInteger result=ZERO;
    result.words=new int[xlen+1];

    if(xwords[xlen-1]<0)
    {
        negative=true;
        negate(result.words,xwords,xlen);
        delete [] xwords;
        xwords=new int[xlen+1];
        memcpy(xwords,result.words,sizeof(int)*static_cast<size_t>(xlen+1));
    }
    else
    {
        negative=false;
    }

    if(y<0)
    {
        negative=!negative;
        y=-y;
    }
    result.words[xlen]=MPN::mul_1(result.words,xwords,xlen,y);
    result.ival=xlen+1;
    if(negative)
        result.setNegative();
    delete [] xwords;
    return result.canonicalize();
}

void BigInteger::Show()
{
    if(this->words==nullptr)
        printf("%d\n",this->ival);
    else
    {
        for(int i=this->ival-1;i>=0;i--)
        {
            printf("%08X\t",this->words[i]);
        }
        printf("\n");
    }
}


BigInteger BigInteger::multiply(const BigInteger &val)
{
    return times(*this,val);
}

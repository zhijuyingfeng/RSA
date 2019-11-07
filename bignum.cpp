#include <cstdio>
#include <cstring>
#include "bignum.h"

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

BigNum::BigNum()
{
//    this->data=new char[8];
//    memset(this->data,0,sizeof(char)<<3);
    this->len=0;
    this->data=nullptr;
}

BigNum::~BigNum()
{
    delete [] this->data;
}

BigNum::BigNum(const long&val)
{
    char temp[30]={0};
    sprintf(temp,"%ld",val);
    this->len=static_cast<int>(strlen(temp));
    this->data=new char[this->len];
    memset(this->data,0,sizeof(char)*static_cast<size_t>(this->len));
    for(int i=0;i<this->len;i++)
    {
        this->data[i]=temp[this->len-i-1]-'0';
    }
}

BigNum::BigNum(const char* val)
{
    this->len=static_cast<int>(strlen(val));
    for(int i=0;i<this->len;i++)
    {
        this->data[i]=val[this->len-i-1]-'0';
    }
}

BigNum BigNum::add(const BigNum &val)const
{
    BigNum ans(max(val.len,this->len)+1);
    ans.len=0;
    char carry=0;
    int min=min(val.len,this->len);

    int i;
    for(i=0;i<min;i++)
    {
        ans.data[i]=this->data[i]+val.data[i]+carry;
        carry=ans.data[i]>=10?1:0;
        if(carry)
            ans.data[i]-=10;
        ans.len++;
    }

    for(;i<val.len;i++)
    {
        ans.data[i]=val.data[i]+carry;
        carry=ans.data[i]>=10?1:0;
        if(carry)
            ans.data[i]-=10;
        ans.len++;
    }

    for(;i<this->len;i++)
    {
        ans.data[i]=this->data[i]+carry;
        carry=ans.data[i]>=10?1:0;
        if(carry)
            ans.data[i]-=10;
        ans.len++;
    }
    if(carry)
        ans.data[ans.len++]=carry;
    return ans;
}

BigNum::BigNum(const BigNum&val)
{
    this->len=val.len;
    this->data=new char[this->len];
    memcpy(this->data,val.data,sizeof(char)*static_cast<unsigned>(this->len));
}

BigNum BigNum::operator=(const BigNum &val)
{
    delete [] this->data;
    this->len=val.len;
    this->data=new char[this->len];
    memcpy(this->data,val.data,sizeof(char)*static_cast<unsigned>(this->len));
    return *this;
}

void BigNum::show()const
{
    for(int i=0;i<this->len;i++)
        printf("%d",this->data[this->len-i-1]);
    printf("\n");
}

BigNum::BigNum(const int &len)
{
    this->len=len;
    this->data=new char[len];
    memset(this->data,0,sizeof(char)*static_cast<size_t>(len));
}

BigNum BigNum::operator+(const BigNum &val) const
{
    return this->add(val);
}

BigNum BigNum::multiply(const int &val) const
{
    BigNum ans;
    for(int i=0;i<this->len;i++)
    {
        long temp=val*this->data[i];
        ans=ans.add(BigNum(temp,i));
    }
    return ans;
}

BigNum::BigNum(const long&val,const int&sl)
{
    char temp[30]={0};
    sprintf(temp,"%ld",val);
    this->len=static_cast<int>(strlen(temp))+sl;
    this->data=new char[this->len];
    memset(this->data,0,sizeof(char)*static_cast<size_t>(this->len));
    for(int i=sl;i<this->len;i++)
    {
        this->data[i]=temp[this->len-i-1]-'0';
    }
}

BigNum BigNum::operator*(const int &val) const
{
    return this->multiply(val);
}

BigNum BigNum::multiply(const BigNum &val) const
{
    BigNum ans;
    for(int i=0;i<val.len;i++)
    {
        BigNum temp=this->multiply(val.data[i]);
        ans=ans.add(BigNum(temp,i));
    }
    return ans;
}


BigNum::BigNum(const BigNum& val,const int&sl)
{
    this->len=val.len+sl;
    this->data=new char[this->len];
    memset(this->data,0,sizeof (char)*static_cast<size_t>(sl));
    memcpy(this->data+sl,val.data,sizeof(char)*static_cast<size_t>(val.len));
}

BigNum BigNum::divide(const BigNum &val)
{
    if(val.len==0)
        return BigNum();
    int diff=this->len-val.len;
    BigNum tab[10];
    for(int i=0;i<10;i++)
    {
        tab[i]=val*i;
    }

    BigNum resi,ans;
    delete [] resi.data;
    resi.len=val.len;
    resi.data=new char[resi.len];
    memset(resi.data,0,sizeof(char)*static_cast<size_t>(resi.len));
    memcpy(resi.data,this->data+diff,sizeof(char)*static_cast<size_t>(val.len));

    char *res=new char[diff+1];
    memset(res,0,sizeof(char)*static_cast<size_t>(diff+1));

    int count;
    for(int i=diff;i>=0;i--)
    {
        count=0;
        while(tab[count]<resi)count++;
        if(tab[count]>resi)count--;
        resi=(resi-tab[count])*10;
        if(diff)
            resi=resi+this->data[i-1];
        res[i]=static_cast<char>(count);
    }

    ans.len=diff+1;
    if(!res[diff])
        ans.len--;
    ans.data=new char[ans.len];
    memset(ans.data,0,sizeof (char)*static_cast<size_t>(ans.len));
    memcpy(ans.data,res,sizeof(char)*static_cast<size_t>(ans.len));
    delete [] res;
    return ans;
}

BigNum BigNum::add(const int &val) const
{
    return this->add(BigNum(val));
}

BigNum BigNum::subtract(const BigNum &val) const
{
    char*temp=new char[this->len];
    memset(temp,0,sizeof (char)*static_cast<size_t>(this->len));
    char carry=0;
    for(int i=0;i<this->len;i++)
    {
        temp[i]=this->data[i]-carry;
        if(i<val.len)
            temp[i]-=val.data[i];
        if(temp[i]<0)
        {
            temp[i]+=10;
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    BigNum ans;
    int i=this->len-1;
    while(i&&!temp[i])
    {
        i--;
    }
    ans.len=i+1;
    ans.data=new char[ans.len];
    memset(ans.data,0,sizeof (char)*static_cast<size_t>(ans.len));
    memcpy(ans.data,temp,sizeof(char)*static_cast<size_t>(ans.len));
    delete [] temp;
    return ans;
}

bool BigNum::operator<(const BigNum &val) const
{
    if(this->len<val.len)
        return true;
    else if(this->len>val.len)
        return false;
    for(int i=this->len-1;i>=0;i--)
    {
        if(this->data[i]<val.data[i])
            return true;
        else if(this->data[i]>val.data[i])
            return false;
    }
    return false;
}

bool BigNum::operator>(const BigNum &val) const
{
    return !this->operator<(val);
}

BigNum BigNum::operator-(const BigNum &val) const
{
    return this->subtract(val);
}

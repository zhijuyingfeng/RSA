#include "mpn.h"

int MPN::add_1(int *dest, int *x, const int &size, const int &y)
{
    long carry=static_cast<long>(y)&0xFFFFFFFFL;
    for(int i=0;i<size;i++)
    {
        carry+=static_cast<long>(x[i])&0xFFFFFFFFL;
        dest[i]=static_cast<int>(carry);
        carry>>=32;
    }
    return static_cast<int>(carry);
}

int MPN::mul_1(int *dest, int *x, const int &len, const int &y)
{
    long yword=static_cast<long>(y)&0xFFFFFFFFL;
    long carry=0;
    for(int i=0;i<len;i++)
    {
        carry+=(static_cast<long>(x[i])&0xFFFFFFFFL)*yword;
        dest[i]=static_cast<int>(carry);
        carry>>=32;
    }
    return static_cast<int>(carry);
}

int MPN::set_str(int *dest, char *str, const int &str_len)
{
    int size=0,str_pos=0,base=10;
    int indigits_per_limb=9;
    while(str_pos<str_len)
    {
        int chunk=str_len-str_pos;
        if(chunk>indigits_per_limb)
            chunk=indigits_per_limb;
        int res_digit=str[str_pos++];
        int big_base=base;

        while(--chunk>0)
        {
            res_digit=res_digit*base+str[str_pos++];
            big_base*=base;
        }

        int cy_limb;
        if(!size)
            cy_limb=res_digit;
        else
        {
            cy_limb=mul_1(dest,dest,size,big_base);
            cy_limb+=add_1(dest,dest,size,res_digit);
        }
        if(cy_limb)
            dest[size++]=cy_limb;
    }
    return size;
}

#include <iostream>
#include "bignum.h"
#include <cstdlib>
using namespace std;

const long NextPrime=16303069;
const char p[]="473775733099111458095976402892151243213040090086618881"
               "031224856589919883111175432182210784004484707192524499"
               "542529027682867198116142629463026716198471009819494687"
               "419717246926437103127982384979803193954685843127713049"
               "424082085738653899178130804288754453401240826773288925"
               "74545183253774970952621120608285211907";
const char q[]="179763108085962807080093919657307409975718428269269435"
               "318693176520197803112687952722248946497029842707955098"
               "616584161059182132899857985791259621959619387353664424"
               "449358830496413557281341725462360322134010042282012642"
               "274593164792155394683891626920676409771537318196968561"
               "566914528483955014073455660937229038263";

long power(long a,long e,long n)
{
    if(!e)
        return 1%n;
    if(1==e)
        return a%n;
    long temp=power(a,e>>1,n);
    temp*=temp;
    temp%=n;
    if(e&1)
        return (temp*a)%n;
    return temp;
}

int main()
{
    for(int i=0;i<100;i++)
    {
        long a=rand()%1000,e=rand()%10000,n=rand()%1000;
        BigNum bg1(static_cast<long>(a)),bg2(static_cast<long>(e)),bgn(static_cast<long>(n));
        long ans1=power(a,e,n);
        BigNum ans2=bg1.powerMod(e,n);
        if(ans1!=ans2.toLong())
        {
            printf("%d\t%d\t%d\n",a,e,n);
            printf("%d\t%d\n",ans1,ans2.toLong());
        }
    }
	return 0;
}

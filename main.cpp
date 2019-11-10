#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "bignum.h"
#include "mpn.h"
#include "SHA1.h"
using namespace std;

//temp=(p-3)*(q-3)*3/4
//PK=SK^(temp-1)
const char p_string[] =  "473775733099111458095976402892151243213040090086618881"
                         "031224856589919883111175432182210784004484707192524499"
                         "542529027682867198116142629463026716198471009819494687"
                         "419717246926437103127982384979803193954685843127713049"
                         "424082085738653899178130804288754453401240826773288925"
                         "74545183253774970952621120608285211907";
const char q_string[] =  "179763108085962807080093919657307409975718428269269435"
                         "318693176520197803112687952722248946497029842707955098"
                         "616584161059182132899857985791259621959619387353664424"
                         "449358830496413557281341725462360322134010042282012642"
                         "274593164792155394683891626920676409771537318196968561"
                         "566914528483955014073455660937229038263";

//static const BigNum PK=SK.powerMod((p-3)*(q-3)*3/4-1,phi_n);

/*
1657638504213882438612915678406897850953771977370767973388101092333569881287258488509212557998784730580049101760347534298806565841062311630059922070026166286332428419339820296006220687116294992148942312822844093313409286176749416399242782263350591360704308206429921405011294641011979175751598446203645185965743503742905643318236399907630783004132454014479796501973248311464515422287590903500456569467614775245698691098134433920112088720497870313969409957141055025352822532164149333775229903313437681069433083250413406187496669691271354077157846897433215011358483874741923356675695266865372804229680571394794561748649

*/

void RSA_encrypt();

int main()
{
    BigInteger p("12345678901234567890");
    BigInteger p2=p.multiply(p);
    p2.Show();

//    int x[]={0x6B8B4567,0x327B23C6,0x643C9869};
//    int y[]={0x66334873,0x74B0DC51,0x19495CFF};
//    int *dest=new int[6];
//    MPN::mul(dest,x,3,y,3);
//    for(int i=0;i<6;i++)
//        printf("%d\t",dest[i]);
//    printf("\n");
//    delete [] dest;
    return 0;
}

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "bigint.h"
#include "rsa.h"
#include "oaep.h"
#include "SHA1.h"
using namespace std;

int main()
{
    const char p_string[] = "473775733099111458095976402892151243213040090086618881"
                            "031224856589919883111175432182210784004484707192524499"
                            "542529027682867198116142629463026716198471009819494687"
                            "419717246926437103127982384979803193954685843127713049"
                            "424082085738653899178130804288754453401240826773288925"
                            "74545183253774970952621120608285211907";
    const char q_string[] = "179763108085962807080093919657307409975718428269269435"
                            "318693176520197803112687952722248946497029842707955098"
                            "616584161059182132899857985791259621959619387353664424"
                            "449358830496413557281341725462360322134010042282012642"
                            "274593164792155394683891626920676409771537318196968561"
                            "566914528483955014073455660937229038263";
    //学号为16303067，下一个素数为16303069
    const char e_string[]="16303069";
    const char m[]="Sun Yat-sen University";

    char oaep_en[256];
    char oaep_de[128];
    int32_t oaep_en_data[64],rsa_de_data[64];
    char oaep_en_data_2[256];

    BigInteger p(p_string),q(q_string),e(e_string);
    RSA rsa(p,q,e);

    printf("Plaintext: \t%s\n\n",m);
    clock_t t=clock();
    OAEP::encrypt(m,oaep_en);
    memcpy(oaep_en_data,oaep_en,sizeof(oaep_en));

    printf("After OAEP encryption:\n");
    for(int32_t i=0;i<64;i++)
        printf("%08X",oaep_en_data[i]);
    t=clock()-t;
    printf("\nTime elapsed:\t%lfms\n\n",1000.0*t/CLOCKS_PER_SEC);
    t=clock();

    BigInteger rsa_m(oaep_en_data,64);
    BigInteger rsa_en=rsa.encrypt(rsa_m);
    printf("After RSA encryption:\n");
    rsa_en.show();
    t=clock()-t;
    printf("Time elapsed:\t%lfms\n\n",1000.0*t/CLOCKS_PER_SEC);
    t=clock();

    BigInteger rsa_de=rsa.decrypt(rsa_en);
    printf("After RSA decryption:\n");
    rsa_de.show();
    t=clock()-t;
    printf("Time elapsed:\t%lfms\n\n",1000.0*t/CLOCKS_PER_SEC);
    t=clock();

    rsa_de.getWords(rsa_de_data);

    memcpy(oaep_en_data_2,rsa_de_data,sizeof(rsa_de_data));
    OAEP::decrypt(oaep_en_data_2,oaep_de);
    printf("After OAEP decryption:\n");
    printf("%s\n",oaep_de);
    t=clock()-t;
    printf("Time elapsed:\t%lfms\n\n",1000.0*t/CLOCKS_PER_SEC);

    return 0;
}

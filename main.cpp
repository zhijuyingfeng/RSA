#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "bigint.h"
#include "rsa.h"
#include "mpn.h"
#include "SHA1.h"
#include "oaep.h"
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
const static int32_t OAEP_PADDED_LENGTH=256;

int main()
{
    const char m[]="SUN Yat-sen University";
    BigInteger p(p_string),q(q_string),e("16303069");
    RSA rsa(p,q,e);

    char oaep_c[OAEP_PADDED_LENGTH];
    char oeap_decrypted[OAEP_PADDED_LENGTH];
    int32_t data[OAEP_PADDED_LENGTH>>2];
    OAEP::encrypt(m,oaep_c);
    memcpy(data,oaep_c,sizeof(data));

    BigInteger rsa_m(data,OAEP_PADDED_LENGTH>>2);
    BigInteger rsa_encrypted=rsa.encrypt(rsa_m);
    BigInteger rsa_decrypted=rsa.decrypt(rsa_encrypted);

    memset(data,0,sizeof(data));
    rsa_decrypted.getWords(data);
    memcpy(oaep_c,data,sizeof(data));
    OAEP::decrypt(oaep_c,oeap_decrypted);
    return 0;
}

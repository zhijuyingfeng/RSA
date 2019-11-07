#include <iostream>
#include "bignum.h"
using namespace std;

int main()
{
    BigNum bg1(2911896L),bg2(18297L),bg3=bg1.divide(bg2);
    bg3.show();
    return 0;
}

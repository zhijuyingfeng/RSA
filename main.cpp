#include <iostream>
#include "bignum.h"
#include <cstdlib>
using namespace std;

int main()
{
	for (int i = 0; i < 100000; i++)
	{
		long a = rand(), b = rand();
		BigNum bg1(a), bg2(b);
		BigNum bg3 = bg1.multiply(bg2).divide(bg2);
		long ans = bg3.toLong();
		if (b&&ans != a )
			printf("%ld\t%ld\n", a, b);
	}

	//BigNum bg1(20920L), bg2(0L), bg3 = bg1.divide( bg2);
	//printf("%ld\n", bg3.toLong());
	//bg3.show();
	return 0;
}

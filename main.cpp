#include <iostream>
#include "bignum.h"
#include <cstdlib>
using namespace std;

int main()
{
	for (int i = 0; i < 10000; i++)
	{
		long a = rand(), b = rand();
		BigNum bg1(a), bg2(b);
		BigNum bg3 = bg1.divide(bg2);
		long ans = bg3.toLong();
		if (ans != a / b)
			printf("%ld\t%ld\n", a, b);
	}

	//BigNum bg1(21375L), bg2(1425L), bg3 = bg1.divide( bg2);
	//printf("%ld\n", bg3.toLong());
	//bg3.show();
	return 0;
}

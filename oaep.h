#ifndef OAEP_H
#define OAEP_H

#include <cstdint>
#include "SHA1.h"

class OAEP
{
	const static int32_t byteNumber = 128;
	const static int32_t SHA1Length = 20;
public:
	static void SHA1( char*m, char* res);
	static void encrypt(const char*m, char* res);
	static void decrypt(const char*c, char*res);
};

#endif // OAEP_H

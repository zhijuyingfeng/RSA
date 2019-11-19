#ifndef OAEP_H
#define OAEP_H

#include <cstdint>
#include "SHA1.h"

class OAEP
{
public:
	static void SHA1( char*m, char* res);
	static void encrypt(const char*m, char* res);
	static void decrypt(const char*c, char*res);
};

#endif // OAEP_H

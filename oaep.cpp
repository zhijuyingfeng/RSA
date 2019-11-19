#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "oaep.h"

static const int32_t byteNumber = 128;
static const int32_t SHA1Length = 20;

void OAEP::SHA1( char *m, char *res)
{
	memset(res, 0, sizeof(char)*byteNumber);
	char sha1[SHA1Length+1];
    for (int32_t i = 0; i<6; i++)
	{
		if(!i)
			SHA(m, sha1,byteNumber);
		else
			SHA(sha1, sha1, SHA1Length);

        memcpy(res + 8 + SHA1Length * i, sha1, sizeof(char)*SHA1Length);
	}
}

void OAEP::encrypt(const char *m, char *res)
{
	srand(0);
	char r[byteNumber];
	for (int32_t i = 0; i<(byteNumber >> 2); i++)
	{
		//int32_t temp = rand();
		int32_t temp = 0;
		memcpy(r + (i << 2), &temp, sizeof(int32_t));
	}
	char x[byteNumber] = { 0 };
	char G[byteNumber];
	char H[byteNumber];
	char y1[byteNumber];
	char y2[byteNumber];

	int32_t len = static_cast<int32_t>(strlen(m));
	if (len<byteNumber)
	{
		memcpy(x + (byteNumber - len), m, sizeof(char)*static_cast<uint32_t>(len));
		SHA1(r, G);
		for (int32_t i = 0; i<byteNumber; i++)
			y1[i] = x[i] ^ G[i];
		SHA1(y1, H);
		for (int32_t i = 0; i<byteNumber; i++)
			y2[i] = r[i] ^ H[i];
		memcpy(res, y1, sizeof(char)*byteNumber);
		memcpy(res + byteNumber, y2, sizeof(char)*byteNumber);
	}
	else
	{
		memset(res, 0, sizeof(char)*(byteNumber << 1));
	}
}

void OAEP::decrypt(const char *c, char *res)
{
	char x1[byteNumber], x2[byteNumber];
	char G[byteNumber], H[byteNumber];
	char r[byteNumber];
    memset(res,0,sizeof(char)*byteNumber);
	memcpy(x1, c, sizeof(char)*byteNumber);
	memcpy(x2, c + byteNumber, sizeof(char)*byteNumber);
	SHA1(x1, H);
	for (int32_t i = 0; i<byteNumber; i++)
		r[i] = x2[i] ^ H[i];
	SHA1(r, G);

    int32_t count=0;
    char ch;
	for (int32_t i = 0; i<byteNumber; i++)
    {
        ch=G[i]^x1[i];
        if(ch)
            res[count++]=ch;
    }
}

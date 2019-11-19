#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "SHA1.h"
using namespace std;

const unsigned K[4] = { 0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6 };
const unsigned MAX_LENGTH = 128;

static char* str;
static unsigned char *last;
static uint64_t length;
static unsigned remain;
static unsigned int H[5];

void init( char* s)
{
	H[0] = 0x67452301;
	H[1] = 0xEFCDAB89;
	H[2] = 0x98BADCFE;
	H[3] = 0x10325476;
	H[4] = 0xC3D2E1F0;
	str = s;
	last = new unsigned char[MAX_LENGTH];
	memset(last, 0, sizeof(char)*MAX_LENGTH);
	//length = strlen(str);
	remain = (length & 0x3F);
	memcpy(last, str + length - remain, sizeof(char)*remain);
	length <<= 3;
	SHAPad();
}

void destroy()
{
	delete[]last;
}

void SHAPad()
{
	unsigned d = ((447 - ((length << 55) >> 55)));
	d <<= 23;
	d >>= 23;
	unsigned temp = ((d + 1) >> 3);
	memset(last + remain, 0, sizeof(char)*temp);
	last[remain] = 0x80;
	remain += temp;
    uint64_t big = swap_uint64(length);
    memcpy(last + remain, &big, sizeof(int64_t));
    remain += sizeof(int64_t);
	remain <<= 3;
}

unsigned ROTL(const unsigned &x, const unsigned& s)
{
	return (x << s) | (x >> (32 - s));
}

void MainLoop(const unsigned char* Mi)
{
	unsigned A, B, C, D, E;
	unsigned W[80];
	memcpy(W, Mi, sizeof(char) << 6);
	for (int i = 0; i < 16; i++)
		W[i] = swap_uint32(W[i]);
	for (int i = 16; i<80; i++)
		W[i] = ROTL(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
	A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];
	for (int i = 0; i<80; i++)
	{
		unsigned temp = ROTL(A, 5) + E + W[i] + K[i / 20];
		switch (i / 20)
		{
		case 0:temp += f0(B, C, D); break;
		case 1:temp += f1(B, C, D); break;
		case 2:temp += f2(B, C, D); break;
		case 3:temp += f3(B, C, D); break;
		default:
			printf("Error loop\n");
		}
		E = D; D = C;
		C = ROTL(B, 30);
		B = A; A = temp;
	}
	H[0] += A; H[1] += B;
	H[2] += C; H[3] += D;
	H[4] += E;
}

unsigned f0(const unsigned &B, const unsigned &C, const unsigned &D)
{
	return (B&C) | ((~B)&D);
}

unsigned f1(const unsigned &B, const unsigned &C, const unsigned &D)
{
	return B ^ C^D;
}

unsigned f2(const unsigned &B, const unsigned &C, const unsigned &D)
{
	return (B&C) | (B&D) | (C&D);
}

unsigned f3(const unsigned &B, const unsigned &C, const unsigned &D)
{
	return B ^ C^D;
}

void SHA( char* s, char *res,const int& len)
{
    length = static_cast<uint64_t>(len);
	init(s);

    int64_t n = static_cast<int64_t>((length >> 9));
	unsigned char temp[64];
    for (int64_t i = 0; i<n; i++)
	{
		memcpy(temp, str + (i << 6), sizeof(char) << 6);
		MainLoop(temp);
	}
	n = (remain >> 9);
	for (int i = 0; i<n; i++)
	{
		memcpy(temp, last + (1 << 6)*i, sizeof(char) << 6);
		MainLoop(temp);
	}

	//    ShowHash();
	memcpy(res, H, sizeof(int) * 5);
	//for (int i = 0; i<5; i++)
	//{
	//	sprintf(res + (i << 3), "%08X", H[i]);
	//}
	destroy();
}

uint64_t swap_uint64(const uint64_t& x)
{
    uint64_t val = x;
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

void ShowHash()
{
	for (int i = 0; i<5; i++)
	{
		printf("%08X", H[i]);
	}
	printf("\n");
}

unsigned swap_uint32(const unsigned &x)
{
	unsigned a = x;
	a = ((a&(0x0000FFFF)) << 16) | ((a&(0xFFFF0000)) >> 16);
	a = ((a&(0x00FF00FF)) << 8) | ((a&(0xFF00FF00)) >> 8);
	return a;
}

#ifndef SHA1_H
#define SHA1_H
#include <cstdint>

void init( char* s);
void destroy();
void SHAPad();
unsigned f0(const unsigned &B, const unsigned &C, const unsigned &D);
unsigned f1(const unsigned &B, const unsigned &C, const unsigned &D);
unsigned f2(const unsigned &B, const unsigned &C, const unsigned &D);
unsigned f3(const unsigned &B, const unsigned &C, const unsigned &D);
void Long2Bin(const unsigned long&x);
void Int2Bin(const unsigned&x);
void ShowIntBin(const unsigned& x);
void ShowLongBin(const unsigned long&x);
void MainLoop(const unsigned char* Mi);
void SHA( char* s, char* res,const int&len);
void ShowHash();
unsigned ROTL(const unsigned &x, const unsigned& s);
uint64_t swap_uint64(const uint64_t& x);
unsigned swap_uint32(const unsigned &x);
#endif // SHA1_H

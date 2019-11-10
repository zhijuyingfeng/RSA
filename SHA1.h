#ifndef SHA1_H
#define SHA1_H
void init(char* s);
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
void SHA(char* s, char* res);
void ShowHash();
unsigned ROTL(const unsigned &x, const unsigned& s);
unsigned long long swap_uint64(const unsigned long long& x);
unsigned swap_uint32(const unsigned &x);
#endif // SHA1_H

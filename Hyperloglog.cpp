#include<iostream>
#include<vector>
#include<cmath>

typedef unsigned long long ull;

using namespace std;

//tal vez usar u_int32
int M = 5;

//se necesita solo 6 bits por bucket
vector<uint8_t> sketch(M);

//p: bits mas significativos
//b: bits menos significativos

for(string kmer : stream){
  ull h_kmer = hash<string>{}(kmer);

  int log_m = (int)ceil(log2(M));

  unsigned char p = (h_kmer >> (64 - log_m))
  ull b = (h_kmer << log_m) >> log_m;

  uint8_t first_one_bit = __builtin_ctz(b) + 1;
  sketch[p] = max(sketch[p], first_one_bit)
}

int mean = reduce(sketch.begin(), sketch.end())/M;
float count = pow(2, mean) * 0.78;


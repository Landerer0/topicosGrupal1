#include "Hyperloglog.hpp"

Hyperloglog::Hyperloglog(unsigned int M){
  this->M = M;
  sketch.assign(M, 0);
}

Hyperloglog::~Hyperloglog(){ 
}

float Hyperloglog::alpha_m(){
  float phi = 0.7213/(1 + (1.079/M));
  return phi;
}

void Hyperloglog::update_sketch(string kmer){
  //p: bits mas significativos
  //b: bits menos significativos
  ull h_kmer = std::hash<std::string>{}(kmer);

  int log_m = (int)ceil(log2(M));

  uc p = (h_kmer >> (64 - log_m));
  ull b = (h_kmer << log_m) >> log_m;

  uc first_one_bit = __builtin_ctzll(b);
  sketch[p] = max(sketch[p], first_one_bit);
}

uc Hyperloglog::bucket_value(unsigned int i){
  return sketch[i];
}

ull Hyperloglog::estimate(/* Stream S */){
  vector<string> S;
  for(string kmer : S)
    update_sketch(kmer);
  float Z = 0;
  for(uc bucket : sketch) Z += 1/pow(2,(int)bucket);//no estoy seguro si castear a int
  float E = this->M * this->M * Z * alpha_m(); //dudas acerca del tipo de dato
  return (ull)E; //ull truncara?
}

void Hyperloglog::union_sk(Hyperloglog hll){
  for(int i = 0; i < M; i++)
    sketch[i] = max(sketch[i], hll.bucket_value(i));
}


#include "Hyperloglog.hpp"
#include <cstring>

Hyperloglog::Hyperloglog(unsigned int M){
  this->M = M;
  sketch.assign(M, 0);
  bucketMutex.assign(M,new std::mutex);
  log_m = (int)ceil(log2(M));
  two_32 = 4294967296.0;
}

Hyperloglog::~Hyperloglog(){ 
}

double Hyperloglog::alpha_m(){
  double phi = 0.7213/(1 + (1.079/M));
  return phi;
}

void Hyperloglog::update(string &kmer){
  ull h_kmer = hash<string>{}(kmer);
  uc p = (h_kmer >> (64 - log_m));
  ull b = h_kmer << log_m;
  uc first_one_bit = __builtin_clzll(b) + 1;
  bucketMutex.at(p)->lock();
  sketch[p] = max(sketch[p], first_one_bit);
  bucketMutex.at(p)->unlock();
}

uc Hyperloglog::bucket_value(unsigned int i){
  return sketch[i];
}

ull Hyperloglog::estimate(){
  double Z = 0.0;
  unsigned int V = 0;

  for(uc bucket : sketch){
    Z += 1.0/(1 << (int)bucket);
    if((int)bucket == 0) V++;
  }

  //cerr << Z << endl;

  double E = (this->M * this->M * alpha_m())/Z;
  if(E <= 2.5 * this->M){
    if(V != 0) E = this->M * log2(this->M/V);
  }
  else if(E > ((1.0/30.0) * two_32)){
   E = -1 * two_32 * log(1.0 - (E/two_32));
  }
  return (ull)E; 
}

void Hyperloglog::merge(Hyperloglog &hll){
  for(int i = 0; i < M; i++)
    sketch[i] = max(sketch[i], hll.bucket_value(i));
}

ull Hyperloglog::intersection(Hyperloglog &hll){
    Hyperloglog copy(M);
    memcpy(&copy,this,sizeof(Hyperloglog));
    ull est1 = copy.estimate();
    ull est2 = hll.estimate();
    copy.merge(hll);
    return est1 + est2 - copy.estimate();

}

ull Hyperloglog::jaccard(Hyperloglog &hll){
    Hyperloglog copy(M);
    memcpy(&copy,this,sizeof(Hyperloglog));
    ull inter = copy.intersection(hll);
    copy.merge(hll);
    ull un = copy.estimate();
    return inter/un;
}

ull Hyperloglog::setDifference(Hyperloglog &hll){
    Hyperloglog copy(M);
    memcpy(&copy,this,sizeof(Hyperloglog));
    ull inter = copy.intersection(hll);
    return copy.estimate() - inter;
}

ull Hyperloglog::symmetricDifference(Hyperloglog &hll){
    Hyperloglog copy(M);
    memcpy(&copy,this,sizeof(Hyperloglog));
    ull est1 = copy.estimate();
    ull est2 = hll.estimate();
    ull inter = copy.intersection(hll);
    return est1 + est2 - 2 * inter;
}


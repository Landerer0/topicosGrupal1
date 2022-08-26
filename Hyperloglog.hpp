#include<iostream>
#include<vector>
#include<cmath>

typedef unsigned long long ull;
typedef unsigned char uc;

using namespace std;

class Hyperloglog{
  private:
    vector<uc> sketch; //6 bits por bucket
    unsigned int M;
    void update_sketch(string kmer);
    float alpha_m(); //factor de correcion
  public:
    Hyperloglog(unsigned int M);
    ~Hyperloglog();
    uc bucket_value(unsigned int i);
    ull estimate(vector<string> stream); 
    void union_sk(Hyperloglog hll); //el objeto donde se llama el metodo union se utiliza para almacenar la union entre ambos sketches
};

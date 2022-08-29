#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <unordered_set>

#include "kmer.hpp"
#include "pcsa.hpp"
#include "Hyperloglog.hpp"

using namespace std;

const unsigned int Buckets = 16;
const unsigned int k = 32; //tamaño del kmer

void pruebaCaracter(char caracter, Kmer &kmer, PCSA &pcsa){
    kmer.pushBack(caracter);
    cout << kmer.genoma() << endl;
    pcsa.update(kmer.genoma());
    pcsa.showSketch();
    unsigned long long estimacion = pcsa.estimate();
    cerr << "estimacion: " << estimacion << endl;
}

template <typename T> T readStream(unordered_set<string> &gt, ifstream &file, unsigned int size){
    T estimator(size);
 //Archivo -> vector de kmers
    for(string line; getline(file, line);){
      line.erase(std::remove(line.begin(), line.end(), 'N'), line.end());
      for(int i = 0; i <= line.size() - k; i++){
        string aux = line.substr(i,k);  
        gt.insert(aux);
        estimator.update(aux);
        //cout<<aux<<endl;
      }
    }
  return estimator;
}
// Importante: hash<string> usa 8 bytes

int main(int argc, char *argv[]) {

    ifstream file(argv[1]); //el archivo se entrega como argumento
    unordered_set<string> gt; //ground truth de la cardinalidad real

    if(argc < 3){
      Hyperloglog hll = readStream<Hyperloglog>(gt, file, Buckets);
      cout<<"Estimacion HLL: "<<hll.estimate()<<endl;
      PCSA pcsa = readStream<PCSA>(gt, file, Buckets);
      cout<<"Estimacion PCSA: "<<pcsa.estimate()<<endl;
    }
    else if(strcmp(argv[2],"hll") == 0){ 
      Hyperloglog hll = readStream<Hyperloglog>(gt, file, Buckets);
      cout<<"Estimacion HLL: "<<hll.estimate()<<endl;
    }
    else if(strcmp(argv[2],"pcsa") == 0){
      PCSA pcsa = readStream<PCSA>(gt, file, Buckets);
      cout<<"Estimacion PCSA: "<<pcsa.estimate()<<endl;
    }

    
    cout<<"Cardinalidad real: "<<gt.size()<<endl;
    
    /*
    else{
      PCSA pcsa(Buckets);
      pcsa.showSketch();
      unsigned long long estimacion = pcsa.estimate();
      cerr << "estimacion: " << estimacion << endl;

      string s = "Lucas";
      Kmer kmer("ATTACG");
      cout << kmer.genoma() << endl;
      pcsa.update(kmer.genoma());
      pcsa.showSketch();
      estimacion = pcsa.estimate();
      cerr << "estimacion: " << estimacion << endl;

      pruebaCaracter('G', kmer, pcsa);
      pruebaCaracter('C', kmer, pcsa);
      pruebaCaracter('T', kmer, pcsa);
      pruebaCaracter('A', kmer, pcsa);
      pruebaCaracter('C', kmer, pcsa);
    }
    */
    
    // Kmer kmer("ATTACG");
    // cout << kmer.genoma() << endl;
    // string s = "Lucas";
    // kmer.pushBack('G');
    // cout << kmer.genoma() << endl;
    // kmer.pushBack('T');
    // cout << kmer.genoma() << endl;
    // cout << "String: " << s << endl;
    // cout << "Hash: " << hash<string>{}(s) << '\n';
    // cout << sizeof(hash<string>{}(s)) << endl;

    return 0;
}

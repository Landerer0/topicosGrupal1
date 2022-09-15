#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <cstring>
#include <chrono>
#include "pcsa.hpp"
#include "Hyperloglog.hpp"

using namespace std;
using namespace std::chrono;

const unsigned int Buckets = 16;
const unsigned int k = 31; //tamaño del kmer

const int numThreads = 5; // 80-31 = 49, 49%7=0 division exacta

void lectura(Hyperloglog &hll, PCSA &pcsa, ifstream &file){
  int linea = 0;
  ull progreso = 0;

  for(string line; getline(file, line);){

    // Tipo barra de progreso
    progreso++;
    if(progreso%100000==0) cout << progreso << endl;

    for(int i = 0; i <= line.size() - k; i++){
      string aux = line.substr(i,k);  
      hll.update(aux);
      pcsa.update(aux);
    }
  }

  return;
}

template <typename T> T readStream(unordered_set<string> &gt, ifstream &file, unsigned int size){
    T estimator(size);
    int linea = 0; 
    ull progreso = 0;

    for(string line; getline(file, line);){

      // Tipo barra de progreso
      progreso++;
      if(progreso%100000==0) cout << progreso << endl;

      for(int i = 0; i <= line.size() - k; i++){
        string aux = line.substr(i,k);  
        estimator.update(aux);
      }
    }
  return estimator;
}

// Importante: hash<string> usa 8 bytes
int main(int argc, char *argv[]) {

    ifstream file(argv[1]); //el archivo se entrega como argumento
    unordered_set<string> gt; //ground truth de la cardinalidad real

    auto start = high_resolution_clock::now();
    if(argc < 3){
      Hyperloglog hll(Buckets);
      PCSA pcsa(Buckets);
      lectura(hll,pcsa,file);
      
      cout << "Estimacion HLL: "  << hll.estimate()  << endl;
      cout << "Estimacion PCSA: " << pcsa.estimate() << endl;
    }
    else if(strcmp(argv[2],"hll") == 0){ 
      Hyperloglog hll = readStream<Hyperloglog>(gt, file, Buckets);
      cout<<"Estimacion HLL: "<<hll.estimate()<<endl;
    }
    else if(strcmp(argv[2],"pcsa") == 0){
      PCSA pcsa = readStream<PCSA>(gt, file, Buckets);
      cout<<"Estimacion PCSA: "<<pcsa.estimate()<<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    //cout<<"Cardinalidad real: "<<gt.size()<<endl;
    cout << "Time taken by function: "
         << (double)duration.count()/1000.0 << " seconds" << endl;

    return 0;
}

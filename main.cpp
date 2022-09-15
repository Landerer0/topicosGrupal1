#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <cstring>

#include <chrono>
#include <omp.h>

#include "pcsa.hpp"
#include "Hyperloglog.hpp"

using namespace std;
using namespace std::chrono;

const unsigned int Buckets = 16;
const unsigned int k = 31; //tamaño del kmer

const int numThreads = 5; // 80-31 = 49, 49%7=0 division exacta

void lectura(Hyperloglog &hll, PCSA &pcsa, ifstream &file){
  int linea = 0;
  omp_set_num_threads(numThreads);  
  ull progreso = 0;

  for(string line; getline(file, line);){

    // Tipo barra de progreso
    progreso++;
    if(progreso%100000==0) cout << progreso << endl;

    //!OPCION CON PARALELISMO
    // cada iteracion representa a un kmer
    #pragma omp parallel for
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
    omp_set_num_threads(numThreads);  
    ull progreso = 0;

    for(string line; getline(file, line);){

      // Tipo barra de progreso
      progreso++;
      if(progreso%100000==0) cout << progreso << endl;

      //!OPCION CON PARALELISMO
      // cada iteracion representa a un kmer
      #pragma omp parallel for
      for(int i = 0; i <= line.size() - k; i++){
        string aux = line.substr(i,k);  
        estimator.update(aux);
      }


      // #pragma omp parallel for
      // for(int i=0;i<line.size()-k;i++){ // este for es para procesar una linea en particular
      //   string secuencia;
      //   int numCaracteresInvalidos = 0; // se refiere a las N encontradas en el archivo
      //   for(int numCaracteresValidos=0; numCaracteresValidos<k; numCaracteresValidos++){
      //     // nos ubicamos dentro de los caracteres validos
      //     if(i+numCaracteresValidos+numCaracteresInvalidos == line.size()) continue;

      //     // caso de encontrar caracter invalido continuar buscando
      //     if(line[i+numCaracteresValidos+numCaracteresInvalidos]=='N'){
      //       numCaracteresValidos--;
      //       numCaracteresInvalidos++;
      //       continue;
      //     }

      //     // caracter valido
      //     secuencia.push_back(line[i+numCaracteresValidos+numCaracteresInvalidos]);
      //   }

      //   if(secuencia.size()==k){
      //     estimator.update(secuencia);
      //     //gt.insert(secuencia);
      //   }
      // }

      // //! OPCION CON REMOVE
      // line.erase(std::remove(line.begin(), line.end(), 'N'), line.end());
      // // cerr << "line "<< linea << ": " << line << " size: " << line.size() << endl;
      // // linea++;
      // if(line.size() < 31) continue;
      // //#pragma omp parallel for
      // for(int i = 0; i <= line.size() - k; i++){
      //   string aux = line.substr(i,k);  
      //   //cerr << aux << endl;
      //   //gt.insert(aux);
      //   estimator.update(aux);
      // }
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

      // Hyperloglog hll = readStream<Hyperloglog>(gt, file, Buckets);
      // cout<<"Estimacion HLL: "<<hll.estimate()<<endl;
      // ifstream file2(argv[1]); //el archivo se entrega como argumento
      // PCSA pcsa = readStream<PCSA>(gt, file2, Buckets);
      // cout<<"Estimacion PCSA: "<<pcsa.estimate()<<endl;
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

#include "pcsa.hpp"
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

const double phi = 0.77351;

PCSA::PCSA(unsigned int M){
    buckets = M; // almaceno el valor de buckets por si llega a ser necesario
    sketch.assign(M, 0); // inicializo el sketch con M buckets con el valor de 0
    logBuckets = (int)ceil(log2(buckets));
    //cerr << "log buckets: " << logBuckets << endl;
}

PCSA::~PCSA(){
}

void PCSA::update(string kmer){
    // calcular valor hash
    unsigned long long valorHash = hash<string>{}(kmer);

    // sobre el valor hash calcular el bucket correspondiente, 64 = 8*sizeof(valorHash) 
    unsigned char bucketCorrespondiente = (valorHash >> (64 - logBuckets));
    //cerr << (int)bucketCorrespondiente << endl;

    unsigned long long bitsSketch = ( (valorHash << logBuckets) >> logBuckets); // bits a usar del valor hash
    unsigned long long rHash = ~bitsSketch & (bitsSketch + 1); // obtiene el valor para realizar update del sketch

    // actualizar el valor del sketch
    sketch.at(bucketCorrespondiente) = sketch.at(bucketCorrespondiente) | rHash;

    return;
}

void PCSA::showSketch(){
    cout << "Sketch: ";
    auto it = sketch.begin();
    for(it; it != sketch.end(); it++) {
        cout << (unsigned long long) *it << " ";
    }
    cout << endl;
}

unsigned long long PCSA::estimate(){
    // se calcula la suma de los primeros '1's a la derecha de todos los bins
    unsigned long long suma = 0;
    for(int i=0; i<buckets;i++){
        if(sketch.at(i) == 0) continue; // si el valor es 0 el conteo da 64, por lo que se salta
        suma += __builtin_ctzll(sketch.at(i)); // aqui se debe hacer el count de los ceros
    }

    // se calula media simple
    double media = 1.0 * suma / buckets;

    // formula para entregar el valor de la estimacion
    return buckets*pow(2,media)/phi;
}
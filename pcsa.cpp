#include "pcsa.hpp"
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

PCSA::PCSA(unsigned int M){
    buckets = M; // almaceno el valor de buckets por si llega a ser necesario
    sketch.assign(M, 0); // inicializo el sketch con M buckets con el valor de 0
    logBuckets = (int)ceil(log2(buckets));
    cerr << "log buckets: " << logBuckets << endl;
}

PCSA::~PCSA(){
}

void PCSA::update(string kmer){
    // calcular valor hash
    auto valorHash = hash<string>{}(kmer);

    // sobre el valor hash calcular el bucket correspondiente, 64 = 8*sizeof(valorHash) 
    unsigned char bucketCorrespondiente = (valorHash >> (64 - logBuckets)) - 1;
    //cerr << (int)bucketCorrespondiente << endl;

    // actualizar el valor del sketch
    sketch.at(bucketCorrespondiente) = sketch.at(bucketCorrespondiente) | 
                ( (valorHash << logBuckets) >> logBuckets); // hago shifting para eliminar bits de hashing
    //cerr << valorHash << endl;    
    //cerr << ( (valorHash << logBuckets) >> logBuckets) << endl;

    return;
}

void PCSA::showSketch(){
    cout << "Sketch: ";
    auto it = sketch.begin();
    for(it; it != sketch.end(); it++) {
        cout << (unsigned int) *it << " ";
    }
    cout << endl;
}

unsigned long long PCSA::estimate(){
    unsigned long long estimate;
    return estimate;
}
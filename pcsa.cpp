#include "pcsa.hpp"
#include <iostream>
#include <vector>

PCSA::PCSA(unsigned int M){
    buckets = M; // almaceno el valor de buckets por si llega a ser necesario
    sketch.assign(M, 0); // inicializo el sketch con M buckets con el valor de 0
}

PCSA::~PCSA(){
}

void PCSA::update(string kmer){
    // calcular valor hash
    auto valorHash = hash<string>{}(kmer);

    // sobre el valor hash calcular el bucket correspondiente
    

    // AUN NO SE EL VALOR DEL HASH VALUE
    unsigned long long hashValue = hash<string>{}(kmer);
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
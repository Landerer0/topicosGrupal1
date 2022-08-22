#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>

#include "kmer.hpp"
#include "pcsa.hpp"

using namespace std;

const unsigned int Buckets = 4;

void pruebaCaracter(char caracter, Kmer &kmer, PCSA &pcsa){
    kmer.pushBack(caracter);
    cout << kmer.genoma() << endl;
    pcsa.update(kmer.genoma());
    pcsa.showSketch();
    unsigned long long estimacion = pcsa.estimate();
    cerr << "estimacion: " << estimacion << endl;
}

// Importante: hash<string> usa 8 bytes

int main() {
    // vector<unsigned long long> numeros;
    // numeros.push_back(0);
    // numeros.push_back(1);
    // numeros.push_back(2);
    // numeros.push_back(3);
    // numeros.push_back(4);
    // numeros.push_back(5);

    // cerr << numeros.at(0) << " " << __builtin_ctzll(numeros.at(0)) << endl;
    // cerr << numeros.at(1) << " " << __builtin_ctzll(numeros.at(1)) << endl;
    // cerr << numeros.at(2) << " " << __builtin_ctzll(numeros.at(2)) << endl;
    // cerr << numeros.at(3) << " " << __builtin_ctzll(numeros.at(3)) << endl;
    // cerr << numeros.at(4) << " " << __builtin_ctzll(numeros.at(4)) << endl;
    // cerr << numeros.at(5) << " " << __builtin_ctzll(numeros.at(5)) << endl;

    // cerr << pow(2,3) << " " << pow(2, 10);

    // return 0;

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
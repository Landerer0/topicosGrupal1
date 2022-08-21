#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#include "kmer.hpp"
#include "pcsa.hpp"

using namespace std;

const unsigned int Buckets = 4;

// Importante: hash<string> usa 8 bytes

int main() {
    PCSA pcsa(Buckets);
    pcsa.showSketch();
    return 0;

    Kmer kmer("ATTACG");
    cout << kmer.genoma() << endl;
    string s = "Lucas";
    kmer.pushBack('G');
    cout << kmer.genoma() << endl;
    kmer.pushBack('T');
    cout << kmer.genoma() << endl;
    cout << "String: " << s << endl;
    cout << "Hash: " << hash<string>{}(s) << '\n';
    cout << sizeof(hash<string>{}(s)) << endl;
    return 0;
}
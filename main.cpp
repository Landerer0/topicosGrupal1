#include <iostream>
#include <stdlib.h>
#include <string>
#include "kmer.hpp"
#include "sketch.hpp"

using namespace std;

const unsigned int Buckets = 4;

int main() {
    Sketch PCSA(Buckets);
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
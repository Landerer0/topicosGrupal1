#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class PCSA {
    private:
        vector<unsigned char> sketch;
        unsigned int buckets;
    public:
        PCSA(unsigned int M);
        ~PCSA();
        void update(string); // se ingresa un kmer y se actualizan los valores del kmer
        unsigned long long estimate(); // se estima el valor de elementos actuales
        
        
        void showSketch(); // auxiliar para poder imprimir el contenido del sketch
};
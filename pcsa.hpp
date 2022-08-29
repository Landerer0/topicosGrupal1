#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class PCSA {
    private:
        vector<unsigned long long> sketch;
        unsigned int buckets;
        int logBuckets; 
    public:
        PCSA(unsigned int M);
        ~PCSA();
        void update(string); // se ingresa un kmer y se actualizan los valores del kmer
        unsigned long long estimate(); // se estima el valor de elementos actuales
        
        void merge(PCSA &pcsa);
        void intersection(PCSA &pcsa);
        unsigned long long diferencia(PCSA &pcsa);
        unsigned long long diferenciaSimetrica(PCSA &pcsa);
        
        unsigned long long jaccard(PCSA &other);
        
        void showSketch(); // auxiliar para poder imprimir el contenido del sketch
};

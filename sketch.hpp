#include <stdlib.h>
#include <string>

using namespace std;

class Sketch {
    private:
        unsigned char* sketch;
        unsigned int buckets;
        unsigned char* createBucketSpace(); // solo deberia ser llamada para asignar espacio de sketch
    public:
        Sketch(unsigned int M);
        ~Sketch();
        void update(string); // se ingresa un kmer y se actualizan los valores del kmer
        unsigned long long estimate(); // se estima el valor de elementos actuales
};
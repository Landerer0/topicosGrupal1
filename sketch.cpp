#include "sketch.hpp"

Sketch::Sketch(unsigned int M){
    buckets = M; // almaceno el valor de buckets por si llega a ser necesario
    sketch = createBucketSpace(); // asigno el espacio necesario para almacenar M buckets
}

Sketch::~Sketch(){
    free(sketch); // libero la memoria almacenada en el sketch
}

unsigned char* Sketch::createBucketSpace(){
    // la diferencia entre calloc y maloc es que calloc setea la memoria en cero
    unsigned char* bucket = (unsigned char *) calloc(buckets, sizeof(unsigned char));
    return bucket;
}

void Sketch::update(string kmer){
    // AUN NO SE EL VALOR DEL HASH VALUE
    unsigned long long hashValue = hash<string>{}(kmer);
}
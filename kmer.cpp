#include "kmer.hpp"

Kmer::Kmer(string primerKmer){
    genomas = primerKmer;
}

Kmer::~Kmer(){
    
}

void Kmer::pushBack(char baseNitrogenada){
    // reviso que el caracter a ingresar sea valido
    // el caso de que sea '>' no se si solo ocurre al inicio o no, en dicho caso
    // se podria ignorar el primer caracter del texto y eliminar el or del if
    if(baseNitrogenada == 'N' || baseNitrogenada == '>') return;
    genomas.erase(0,1);
    genomas.push_back(baseNitrogenada);
}

string Kmer::genoma(){
    return genomas;
}
#include<string>

using namespace std;

class Kmer{
    private:
        string genomas;
    public:
        Kmer(string);
        ~Kmer();
        void pushBack(char);
        string genoma();
};
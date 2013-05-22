#include "Compressor.cpp"

class Archiver : public Compressor
{
protected:
    void dumpLetters(ostream &out);
    void processLetters();
public:
    Archiver(const char*);
    bool run(const char *filename);
};
#include <iostream>
#include <fstream>
#include <list>
#include "Node.cpp"

using namespace std;

typedef map<char, int> lettersTable;

class Compressor
{
protected:
    ifstream _in;
    lettersTable _letters;
    Node *_lettersTree;
    char *_fname;

    void buildTree();
public:
    Compressor(const char *filename);
    ~Compressor();
    virtual bool run(const char *filename) =0;
};
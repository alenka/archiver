#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include "Node.cpp"

using namespace std;

typedef map<char, int> CharMap;
typedef vector<bool> Code;
typedef map<char, Code> CodeTable;

class Compressor
{
private:
    void buildCharMap();
    void buildCharTree();
    void buildCodeTable(Node *root);
    
    void dumpCharMap(ostream &out);
    void loadCharMap(istream &in);
protected:
    Code code;
    CodeTable codeTable;
    CharMap charMap;
    Node *charTree;
    
    ifstream inputFile;
public:
    Compressor(const char *filename);
    ~Compressor();
    void compress(const char *filename);
    void decompress(const char *filename);
};
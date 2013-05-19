#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include "Node.cpp"

using namespace std;

class Compressor
{
private:
    list<Node*> m_letters;
    char *m_data;
    unsigned long m_dataSize;
    void countLetters();
    Node *buildTree();
public:
    Compressor(const char *data);
    void compress(const char *filename);
};
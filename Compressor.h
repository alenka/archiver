#include <iostream>
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
    Compressor(char *data);
    void encode();
};
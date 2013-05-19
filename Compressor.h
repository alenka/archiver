#include <iostream>
#include <string.h>
#include <list>
#include "Node.cpp"

using namespace std;

class Compressor
{
private:
    list<Node*> m_list;
    char *m_data;
    unsigned long m_dataSize;
    void parseData();
    Node *buildTree();
public:
    void encode(char *data);
};
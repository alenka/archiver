#include "Compressor.h"

Compressor::Compressor(const char *filename)
{
    _fname = new char [strlen(filename)];
    strcpy(_fname, filename);
    _in.open(filename, ios::in | ios::binary);
}

Compressor::~Compressor()
{
    _in.close();
}

void Compressor::buildTree()
{
    list<Node*> tree;

    for (lettersTable::iterator i = _letters.begin(); i != _letters.end(); i++) {
        tree.push_back( new Node(i->second, i->first) );
    }

    while(tree.size() != 1){
        tree.sort(Node::compare);

        Node *left = tree.front();
        tree.pop_front();

        Node *right = tree.front();
        tree.pop_front();

        tree.push_back(new Node(left, right));
    }

    _lettersTree = tree.front();
}
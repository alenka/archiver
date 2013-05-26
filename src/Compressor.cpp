#include "Compressor.h"

Compressor::Compressor(const char *filename)
{
    inputFile.open(filename, ios::in);
}

Compressor::~Compressor()
{
    inputFile.close();
    delete charTree;
}

void Compressor::dumpCharMap(ostream &out)
{
    for(CharMap::iterator i = charMap.begin(); i != charMap.end(); i++)
    {
        out << i->first << i->second;
    }
    out << LAST_SYMBOL;
}

void Compressor::loadCharMap(istream &in)
{
    int count;
    char letter;
    for(char letter = in.get(); letter != LAST_SYMBOL; letter = in.get())
    {
        in >> count;
        charMap[letter] = count;
    }
}

void Compressor::buildCharMap()
{
    while (!inputFile.eof())
    {
        charMap[inputFile.get()]++;
    }
    // back poiner to start
    inputFile.clear();
    inputFile.seekg(0, inputFile.beg);
}

void Compressor::buildCharTree()
{
    list<Node*> tree;

    for(CharMap::iterator i = charMap.begin(); i != charMap.end(); i++)
    {
        tree.push_back(new Node(i->second, i->first));
    }

    while (tree.size()!=1)
    {
        tree.sort(Node::compare);

        Node *left = tree.front();
        tree.pop_front();
        Node *right = tree.front();
        tree.pop_front();

        tree.push_back(new Node(left, right));
    }

    charTree = tree.front();
}

void Compressor::buildCodeTable(Node *root)
{
    if (root->hasChild())
    {
        code.push_back(0);
        buildCodeTable(root->getChild(true));
        code.pop_back();

        code.push_back(1);
        buildCodeTable(root->getChild(false));
        code.pop_back();
    } else {
        codeTable[root->getLetter()] = code;
    }
}

void Compressor::compress(const char *filename)
{
    buildCharMap();
    buildCharTree();
    buildCodeTable(charTree);

    ofstream out(filename, ios::out | ios::binary);

    dumpCharMap(out);
    int count = 0, codeSize, i;
    char buf = 0;
    while (!inputFile.eof())
    {
        Code code = codeTable[inputFile.get()];
        codeSize = (int) code.size();
        for(i = 0; i < codeSize; i++)
        {
            buf |= code[i] << (7 - count);
            if (++count == 8)
            {
                out << buf;
                count = buf = NULL;
            }
        }
    }
    if(count > 0) {
        out << buf;
    }
    out.close();
}

void Compressor::decompress(const char *filename)
{
    ofstream out(filename, ios::out | ios::binary);

    loadCharMap(inputFile);
    buildCharTree();

    Node *parent = charTree;
    int count = 0;
    char byte = inputFile.get();
    while(!inputFile.eof())
    {
        parent = parent->getChild(!(byte & 1 << 7 - count));
        if (!parent->hasChild())
        {
            out << parent->getLetter();
            parent = charTree;
        }
        if (++count == 8) {
            count = 0;
            byte = inputFile.get();
        }
    }
    out.close();
}
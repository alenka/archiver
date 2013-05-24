#include "Compressor.h"

Compressor::Compressor(const char *filename)
{
    inputFile.open(filename, ios::in);
}

Compressor::~Compressor()
{
    inputFile.close();
}

void Compressor::dumpCharMap(ostream &out)
{
    out << charMap.size();
    for(CharMap::iterator i = charMap.begin(); i != charMap.end(); i++)
    {
        out << i->first << i->second;
    }
}

void Compressor::loadCharMap(istream &in)
{
    int size, i, count;
    char letter;
    in >> size;
    for(i = 0; i < size; i++)
    {
        letter = in.get();
        in >> count;
        charMap[letter] = count;
    }
}

void Compressor::buildCharMap()
{
    inputFile.seekg (0, inputFile.end);
    int length = inputFile.tellg();
    inputFile.seekg (0, inputFile.beg);

    while (length--)
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
    Node *left = root->getChild(true),
    *right = root->getChild(false);

    if (left)
    {
        code.push_back(0);
        buildCodeTable(left);
    }

    if (right)
    {
        code.push_back(1);
        buildCodeTable(right);
    }

    char letter = root->getLetter();
    if (letter)
    {
        codeTable[letter] = code;
    }

    code.pop_back();
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
    out << buf;
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
    while(!inputFile.fail())
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
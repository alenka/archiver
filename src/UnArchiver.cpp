#include "UnArchiver.h"

UnArchiver::UnArchiver(const char *filename) : Compressor(filename){}

bool UnArchiver::run(const char *filename)
{
    loadLetters();
    buildTree();

    ofstream out(filename, ios::out | ios::binary);
    if(!out)
    {
        return false;
    }

    Node *parent = _lettersTree;
    int count = 0;
    char byte = _in.get();
    while(!_in.eof())
    {
        bool b = byte & (1 << (7-count) );
        parent = b ? parent->getRight() : parent->getLeft();
        if(parent->isLast())
        {
            out << parent->getLetter();
            parent = _lettersTree;
        }
        if(++count == 8)
        {
            count = 0;
            byte = _in.get();
        }
    }
    out.close();

    return true;
}

void UnArchiver::loadLetters()
{
    int size, count, i;
    char letter;
    _in >> size;
    for(i = 0; i < size; i++)
    {
        _in >> count;
        _in >> letter;
        _letters[letter] = count;
    }
}
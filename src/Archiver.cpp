#include "Archiver.h"

Archiver::Archiver(const char *filename) : Compressor(filename){}

void Archiver::dumpLetters(ostream &out)
{
    out<<_letters.size();
    for(lettersTable::iterator i = _letters.begin(); i != _letters.end(); i++)
    {
        out << i->first << i->second;
    }
}

void Archiver::processLetters()
{
    char letter;
    while(!_in.eof())
    {
        letter = _in.get();
        _letters[letter]++;
    }
    _in.clear();
    _in.seekg(0);
}

bool Archiver::run(const char *filename)
{
    processLetters();
    buildTree();
    codeMap table = _lettersTree->getTable();

    ofstream out(filename, ios::out | ios::binary);
    if(!out)
    {
        return false;
    }

    // dumpLetters(out);

    char letter, buf = NULL;
    int i, count = 0, codeSize;
    code _code;
    while(!_in.eof())
    {
        letter = _in.get();
        _code = table[letter];
        codeSize = _code.size();
        for(i = 0; i < codeSize; i++)
        {
            buf = buf | _code[i] << (7 - count);
            count++;
            if(count == 8)
            {
                out<<buf;
                count = 0;
                buf = 0;
            }
        }
    }
    out.close();
    return true;
}
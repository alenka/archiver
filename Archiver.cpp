#include "Compressor.cpp"

class Archiver : public Compressor
{
protected:
    void dumpLetters(ostream &out);
    void processLetters();
public:
    bool run(const char *filename);
};

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
        _in.get(letter);
        _letters[letter]++;
    }
    _in.close();
    _in.open(_fname);
}

bool Archiver::run(const char *filename)
{
    processLetters();
    buildTree();
    codeMap table = _lettersTree->getTable();

    ofstream out(filename, ios::out);
    if(!out)
    {
        return false;
    }

    dumpLetters(out);
    char letter, buf = NULL;
    int i, count = 0, codeSize;
    code _code;
    while(!_in.eof())
    {
        _in.get(letter);
        _code = table[letter];
        codeSize = _code.size();
        for(i = 0; i < codeSize; i++)
        {
            buf |= _code[i] << (7 - count);
            if(++count == 8)
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
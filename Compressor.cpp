#include "Compressor.h"

Compressor::Compressor(const char *in, const char *out)
{
    _in = ofstream(in, ios::in);
    _out = ofstream(out, ios::out | ios::binary);
}

void Compressor::compress()
{
    processLetters();
    Node *tree = buildTree();
    map<char, code> table;
    tree->buildTable(*&table);

    char temp, buf = 0;
    int i, j, count;
    code _code;
    for(i = 0; i<m_dataSize; i++)
    {
        temp = m_data[i];
        _code = table[temp];
        for(j = 0; j<_code.size(); j++)
        {
            buf |= _code[j] << (7 - count);
            if(++count == 8)
            {
                count = 0;
                out<<buf;
                buf = 0;
            }
        }
    }

    out.close();
}

void Compressor::processLetters()
{
    typedef map<char, int> lettersMap;

    lettersMap letters;
    for(int i = 0; i < m_dataSize; i++){
        letters[m_data[i]]++;
    }

    _out<<letters.size()<<endl;
    for (lettersMap::iterator i = letters.begin(); i != letters.end(); i++) {
        _out<<i->first<<i->second<<endl;
        m_letters.push_back( new Node(i->second, i->first) );
    }
}

Node *Compressor::buildTree()
{
    while(m_letters.size() != 1){
        m_letters.sort(Node::compare);

        Node *left = m_letters.front();
        m_letters.pop_front();

        Node *right = m_letters.front();
        m_letters.pop_front();

        m_letters.push_back(new Node(left, right));
    }
    return m_letters.front();
}
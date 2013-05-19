#include "Compressor.h"

Compressor::Compressor(const char *data)
{
    m_dataSize = strlen(data);
    m_data = new char [m_dataSize];
    strcpy(m_data, data);
    countLetters();
}

void Compressor::compress(const char *filename)
{
    ofstream out(filename, ios::out | ios::binary);
    if(!out)
    {
        throw new exception();
    }

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

void Compressor::countLetters()
{
    map<char, int> lettersCount;
    for(int i = 0; i < m_dataSize; i++){
        lettersCount[m_data[i]]++;
    }

    map<char, int>::iterator i;
    for (i = lettersCount.begin(); i != lettersCount.end(); i++) {
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
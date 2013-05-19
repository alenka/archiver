#include "Compressor.h"

Compressor::Compressor(char *data)
{
    m_data = data;
    m_dataSize = strlen(data);
    countLetters();
}

void Compressor::encode()
{
    Node *tree = buildTree();
    tree->out(cout);
    map< char, vector<bool> > table;
    tree->buildTable(*&table);
    for(int i=0; i<m_dataSize; i++){
        char letter = m_data[i];
        vector<bool> code = table[letter];
        for(int j = 0; j<code.size(); j++){
            cout<<code[j];
        }
    }
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
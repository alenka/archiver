#include "Compressor.h"

Compressor::Compressor(const char *data)
{
    m_dataSize = strlen(data);
    m_data = new char [m_dataSize];
    strcpy(m_data, data);
    countLetters();
}

void Compressor::encode()
{
    Node *tree = buildTree();
    tree->out(cout);
    map< char, vector<bool> > table;
    tree->buildTable(*&table);

    for(int i=0; i<m_dataSize; i++){
        for(int j = 0; j<table[m_data[i]].size(); j++){
            cout<<table[m_data[i]][j];
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
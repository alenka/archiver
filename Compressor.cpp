#include "Compressor.h"

void Compressor::encode(char *data)
{
    m_data = data;
    m_dataSize = strlen(data);
    parseData();
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

void Compressor::parseData()
{
    map<char, int> lettersCount;
    for(int i = 0; i < m_dataSize; i++){
        lettersCount[m_data[i]]++;
    }
    
    map<char, int>::iterator i;
    for (i = lettersCount.begin(); i != lettersCount.end(); i++) {
        m_list.push_back( new Node(i->second, i->first) );
    }
}

Node *Compressor::buildTree()
{
    while(m_list.size() != 1){
        m_list.sort(Node::compare);
        Node *left = m_list.front();
        m_list.pop_front();
        Node *right = m_list.front();
        m_list.pop_front();
        m_list.push_back(new Node(left, right));
    }
    return m_list.front();
}
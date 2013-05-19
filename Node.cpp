#include "Node.h"

Node::Node(int count, char letter)
{
    _count = count;
    _letter = letter;
    _left = _right = NULL;
}
Node::Node(Node *left, Node *right)
{
    _left = left;
    _right = right;
    _letter = NULL;
    _count = left->_count + right->_count;
}
bool Node::compare(Node *left, Node *right)
{
    return left->_count < right->_count;
}

void Node::out(ostream &stream, int k = 5)
{
    if(_left){
        _left->out(stream, k+5);
    }
    for(int i=0; i<k; i++) stream<<" ";
    if(_letter){
        stream <<"("<<_letter<<"["<<_count<<"])\n";
    }else{
        stream <<"["<<_count<<"]\n";
    }
    if(_right){
        _right->out(stream, k+10);
    }
}

void Node::buildTable(map< char, vector<bool> > &table, vector<bool> code = vector<bool>())
{
    if (_left){
        code.push_back(0);
        _left->buildTable(table, code);
    }
    if (_right){
        code.push_back(1);
        _right->buildTable(table, code);
    }
    if (_letter){
        table[_letter] = code;
    }
    code.pop_back();
}
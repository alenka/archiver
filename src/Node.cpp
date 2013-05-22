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

void Node::out(ostream &stream, int k = 50)
{
    for(int i = 0; i < k; i++) stream << " ";

    if(_letter){
        stream <<"("<<_letter<<"["<<_count<<"])"<<endl;
    }else{
        stream <<"["<<_count<<"]"<<endl;
    }

    if(_left){
        _left->out(stream, k-5);
    }

    if(_right){
        _right->out(stream, k+5);
    }
}

codeMap Node::getTable()
{
    codeMap map;
    buildTable(*&map, code());

    return map;
}

void Node::buildTable(codeMap &table, code _code)
{
    if (_left){
        _code.push_back(0);
        _left->buildTable(table, _code);
    }
    if (_right){
        _code.push_back(1);
        _right->buildTable(table, _code);
    }
    if (_letter){
        table[_letter] = _code;
    }
    _code.pop_back();
}

char Node::getLetter()
{
    return _letter;
}

Node *Node::getChild(bool isRight)
{
    return isRight ? _right : _left;
}

bool Node::isLast()
{
    return (_right == NULL && _left == NULL);
}
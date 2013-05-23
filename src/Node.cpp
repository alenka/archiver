#include "Node.h"

Node::Node(Node *_left, Node *_right)
{
    left =  _left;
    right = _right;
    count = left->count + right->count;
}

Node::Node(int _count, char _letter)
{
    left = right = NULL;
    count = _count;
    letter = _letter;
}

bool Node::compare(const Node* l, const Node* r)
{
    return l->count < r->count;
}

bool Node::hasChild()
{
    return (left && right);
}

int Node::getCount()
{
    return count;
}

char Node::getLetter()
{
    return letter;
}

Node *Node::getChild(bool isLeft)
{
    return isLeft ? left : right;
}